- [source insight](https://www.sourceinsight.com/) 是一个优秀的源代码阅读工具


# 1 C++ STL 空间配置器

[容器空间配置器](ttps://github.com/Corner430/study-notes/blob/main/cpp/cpp%E4%B8%AD%E7%BA%A7%E7%AC%94%E8%AE%B0.md#42-%E5%AE%B9%E5%99%A8%E7%A9%BA%E9%97%B4%E9%85%8D%E7%BD%AE%E5%99%A8-allocator)


```cpp
template <typename T, typename Alloc=alloc<T>>
class vector{
};
```

- `allocate` 负责给容器开辟内存空间，通过 `malloc` 实现
- `deallocate` 负责释放容器的内存空间，通过 `free` 实现
- `construct` 负责在已经开辟的内存空间上构造对象，通过 定位 `new` 实现
- `destroy` 负责在已经构造的对象上析构对象，通过 显式调用析构函数 实现

> 空间配置器作用
>   - 分离了对象的内存分配和对象的构造
>   - 分离了对象的析构和内存的释放

# 2 SGI STL 空间配置器

## 2.1 SGI STL 空间配置器的相关定义

> - SGI STL 包含了一级空间配置器和二级空间配置器，其中一级空间配置器 `allocator` 采用 `malloc` 和 `free` 来 管理内存，和C++标准库中提供的 `allocator` 是一样的，但其二级空间配置器 `allocator` 采用了基于 `freelist` 自由链表原理的**内存池**机制实现内存管理。
> 
>   - 一级 `allocate` 和 `deallocate` 采用 `malloc` 和 `free` 实现
>   - 二级 `allocate` 和 `deallocate` 采用 `memory pool` 实现
>
> - 容器底层存储的对象的构造和析构，是通过全局的函数模版 `construct` 和 `destroy` 来实现的，这两个函数模版的实现是通过 `placement new` 和 显式调用析构函数 来实现的。

```cpp
template <class _Tp, class _Alloc = __STL_DEFAULT_ALLOCATOR(_Tp) >
class vector : protected _Vector_base<_Tp, _Alloc>
```

可以看到，容器的默认空间配置器是 `__STL_DEFAULT_ALLOCATOR( _Tp)`，它是一个宏定义，如下:

```cpp
# ifndef __STL_DEFAULT_ALLOCATOR
#   ifdef __STL_USE_STD_ALLOCATORS
#       define __STL_DEFAULT_ALLOCATOR(T) allocator< T >
#   else
#       define __STL_DEFAULT_ALLOCATOR(T) alloc
#   endif
# endif
```

总结：
- 如果 `__STL_USE_STD_ALLOCATORS` 被定义，默认分配器是 `allocator<T>`，一级空间配置器
- 如果 `__STL_USE_STD_ALLOCATORS` 没有被定义，默认分配器是 `alloc`，二级空间配置器

```cpp
template <int __inst>
class __malloc_alloc_template // 一级空间配置器内存管理类 -- 通过malloc和free管理内存
```

```cpp
template <bool threads, int inst>
class __default_alloc_template  // 二级空间配置器内存管理类 -- 通过自定义内存池实现内存管理
```

![20240602205509](https://cdn.jsdelivr.net/gh/Corner430/Picture/images/20240602205509.png)

## 2.2 重要类型和变量定义

```cpp
// 内存池粒度信息
enum {_ALIGN = 8}; // 内存对齐的字节数，通常为8
enum {_MAX_BYTES = 128}; // 可以处理的最大字节数，超过这个值的内存请求将由系统内存分配器处理
enum {_NFREELISTS = 16}; // 自由链表的数量，由 _MAX_BYTES/_ALIGN 计算得出
```

```cpp
// 每一个内存chunk块的头信息
union _Obj {
union _Obj* _M_free_list_link; // 指向下一个空闲块的指针
char _M_client_data[1];    // 客户端看到的数据，实际上可能会更大
};
```

```cpp
// 组织所有自由链表的数组，数组的每一个元素的类型是_Obj*，全部初始化为0
static _Obj* __STL_VOLATILE _S_free_list[_NFREELISTS];
```

```cpp
// Chunk allocation state. 记录内存chunk块的分配情况
static char* _S_start_free; // 指向堆中当前可用内存的开始位置
static char* _S_end_free; // 指向堆中当前可用内存的结束位置
static size_t _S_heap_size; // 当前堆的大小

// _S_start_free 是一个静态成员，表示内存池起始位置的指针。初始值为0，即空指针。
template <bool __threads, int __inst>
char* __default_alloc_template<__threads, __inst>::_S_start_free = 0;

// _S_end_free 是一个静态成员，表示内存池结束位置的指针。初始值为0，即空指针。
template <bool __threads, int __inst>
char* __default_alloc_template<__threads, __inst>::_S_end_free = 0;

// _S_heap_size 是一个静态成员，表示已经配置的堆大小。初始值为0。
template <bool __threads, int __inst>
size_t __default_alloc_template<__threads, __inst>::_S_heap_size = 0;
```

## 2.3 重要的辅助接口函数

```cpp
/*将 __bytes 上调至最邻近的 8 的倍数*/
// 一种常见的内存对齐技巧，效率很高
static size_t _S_round_up(size_t __bytes) {
    return (((__bytes) + (int) _S_ALIGN-1) & ~((int) _S_ALIGN - 1));
}
```

```cpp
/*返回 __bytes 大小的chunk块位于 free-list 中的编号*/
static size_t _S_freelist_index(size_t __bytes) {
    return (((__bytes) + (int) _S_ALIGN-1)/(int)_S_ALIGN - 1);
}
```

## 2.4 内存池管理函数

```cpp
// 分配内存的入口函数
static void* allocate(size_t __n)

// 负责把分配好的chunk块进行连接，添加到自由链表当中
static void* _S_refill(size_t __n);

// 分配相应内存字节大小的chunk块，并且给下面三个成员变量初始化
static char* _S_chunk_alloc(size_t __size, int& __nobjs);

// 把chunk块归还到内存池
static void deallocate(void* __p, size_t __n);

// 内存池扩容函数
template <bool threads, int inst>
void*
__default_alloc_template<threads, inst>::reallocate(void* __p,
                                                    size_t __old_sz,
                                                    size_t __new_sz)
```

### 2.4.1 `allocate` 函数的实现

> - 防止小块内存频繁的申请和释放，导致内存碎片化
> - SGI STL 二级空间配置器内存池的实现优点：
>   1. 对于每一个字节数的 chunk 块，都是给出一部分进行使用，另一部分作为备用。备用的 chunk 块可以给当前字节数或者其他字节数的内存分配请求使用。
>   2. 对于备用内存池中的 chunk 块划分完之后，如果还有剩余的很小的内存块，再次分配的时候，会把这些小的内存块再次分配出去，而不会浪费掉。
>   3. 当指定字节数内存分配失败之后，有一个异常处理的过程，会去 `bytes - 128` 字节所有的 chunk 块进行查看，如果哪个字节数有空闲的 chunk 块，就会把这个 chunk 块分配出去。
>   4. 如果都失败，会调用 `oom_malloc` 函数，这个函数是一个回调函数，用户可以自己定义，用于处理内存分配失败的情况。

```cpp
// __n 是请求的内存大小，必须大于0
static void* allocate(size_t __n)
{
  void* __ret = 0;

  // 如果请求的内存大于_MAX_BYTES（这是一个预设的阈值），则直接调用malloc分配内存
  if (__n > (size_t) _MAX_BYTES) {
    __ret = malloc_alloc::allocate(__n);
  }
  else {
    // 否则，从内存池中分配。首先找到对应大小的自由链表
    _Obj* __STL_VOLATILE* __my_free_list
        = _S_free_list + _S_freelist_index(__n);
    // Acquire the lock here with a constructor call.
    // This ensures that it is released in exit or during stack
    // unwinding.
    // 在多线程环境下，需要加锁以保证线程安全
#   ifndef _NOTHREADS
    /*REFERENCED*/
    _Lock __lock_instance;
#   endif
    // 从自由链表中取出一个对象
    _Obj* __RESTRICT __result = *__my_free_list;
    // 如果自由链表为空，那么需要填充自由链表
    if (__result == 0)
      __ret = _S_refill(_S_round_up(__n));
    else {
      // 否则，直接从自由链表中取出一个对象，并更新自由链表
      *__my_free_list = __result -> _M_free_list_link;
      __ret = __result;
    }
  }

  // 返回分配的内存
  return __ret;
};
```

上述代码中 `_S_refill(_S_round_up(__n));` 函数的实现

```cpp
// __n 是请求的内存大小，必须大于0
template <bool __threads, int __inst>
void*
__default_alloc_template<__threads, __inst>::_S_refill(size_t __n)
{
  // 首先尝试获取20个大小为__n的内存块
  int __nobjs = 20;
  char* __chunk = _S_chunk_alloc(__n, __nobjs);
  _Obj* __STL_VOLATILE* __my_free_list;
  _Obj* __result;
  _Obj* __current_obj;
  _Obj* __next_obj;
  int __i;

  // 如果只获取到一个内存块，那么直接返回这个内存块
  if (1 == __nobjs) return(__chunk);
  // 否则，将获取到的内存块加入到自由链表中
  __my_free_list = _S_free_list + _S_freelist_index(__n);

  // 在内存块中建立自由链表
  __result = (_Obj*)__chunk;  // 第一个对象
  *__my_free_list = __next_obj = (_Obj*)(__chunk + __n);  // 第二个对象
  // 从第三个对象开始，每个对象的_M_free_list_link指向下一个对象
  for (__i = 1; ; __i++) {
    __current_obj = __next_obj;
    __next_obj = (_Obj*)((char*)__next_obj + __n);
    // 如果已经处理到最后一个对象，那么将其_M_free_list_link设置为0，表示自由链表的结束
    if (__nobjs - 1 == __i) {
      __current_obj -> _M_free_list_link = 0;
      break;
    } else {
      __current_obj -> _M_free_list_link = __next_obj;
    }
  }
  // 返回第一个对象，这个对象将被分配出去
  return(__result);
}
```

上述代码中 `_S_chunk_alloc(__n, __nobjs);` 函数的实现

```cpp
// __size 是请求的内存块大小，必须大于0
// __nobjs 是请求的内存块数量
template <bool __threads, int __inst>
char*
__default_alloc_template<__threads, __inst>::_S_chunk_alloc(size_t __size, 
                                                            int& __nobjs)
{
    char* __result;  // 用于保存分配的内存块的起始地址
    size_t __total_bytes = __size * __nobjs;  // 计算总共需要的内存大小
    size_t __bytes_left = _S_end_free - _S_start_free;  // 计算内存池中剩余的内存大小

    // 如果内存池中的内存足够，那么直接从内存池中分配
    if (__bytes_left >= __total_bytes) {
        __result = _S_start_free;  // 分配的内存块的起始地址就是内存池的起始地址
        _S_start_free += __total_bytes;  // 更新内存池的起始地址
        return(__result);  // 返回分配的内存块的起始地址
    } else if (__bytes_left >= __size) {
        // 如果内存池中的内存不足以满足所有请求，但至少可以满足一个请求，那么分配尽可能多的内存块
        __nobjs = (int)(__bytes_left/__size);  // 计算可以分配的内存块数量
        __total_bytes = __size * __nobjs;  // 计算实际分配的内存大小
        __result = _S_start_free;  // 分配的内存块的起始地址就是内存池的起始地址
        _S_start_free += __total_bytes;  // 更新内存池的起始地址
        return(__result);  // 返回分配的内存块的起始地址
    } else {
        // 如果内存池中的内存连一个内存块的大小都不够，那么需要向系统申请新的内存
        size_t __bytes_to_get = 
      2 * __total_bytes + _S_round_up(_S_heap_size >> 4);  // 计算需要申请的内存大小
        // 尝试利用内存池中剩余的内存
        if (__bytes_left > 0) {
            _Obj* __STL_VOLATILE* __my_free_list =
                        _S_free_list + _S_freelist_index(__bytes_left);  // 计算剩余内存应该放入哪个自由链表

            ((_Obj*)_S_start_free) -> _M_free_list_link = *__my_free_list;  // 将剩余内存加入到自由链表中
            *__my_free_list = (_Obj*)_S_start_free;  // 更新自由链表的头部
        }
        // 向系统申请新的内存
        _S_start_free = (char*)malloc(__bytes_to_get);  // 申请新的内存
        if (0 == _S_start_free) {
            // 如果申请失败，那么尝试从更大的自由链表中取内存
            size_t __i;
            _Obj* __STL_VOLATILE* __my_free_list;
        _Obj* __p;
            for (__i = __size;
                 __i <= (size_t) _MAX_BYTES;
                 __i += (size_t) _ALIGN) {
                __my_free_list = _S_free_list + _S_freelist_index(__i);  // 计算应该从哪个自由链表中取内存
                __p = *__my_free_list;
                if (0 != __p) {
                    *__my_free_list = __p -> _M_free_list_link;  // 从自由链表中取出内存
                    _S_start_free = (char*)__p;  // 更新内存池的起始地址
                    _S_end_free = _S_start_free + __i;  // 更新内存池的结束地址
                    return(_S_chunk_alloc(__size, __nobjs));  // 重新尝试分配内存
                }
            }
        _S_end_free = 0;	// In case of exception.
            _S_start_free = (char*)malloc_alloc::allocate(__bytes_to_get);  // 如果所有的自由链表都没有足够的内存，那么抛出异常
        }
        _S_heap_size += __bytes_to_get;  // 更新堆的大小
        _S_end_free = _S_start_free + __bytes_to_get;  // 更新内存池的结束地址
        return(_S_chunk_alloc(__size, __nobjs));  // 重新尝试分配内存
    }
}
```

上述代码中 `malloc_alloc::allocate(__n);` 函数的实现
```cpp
// __n 是请求的内存大小
static void* allocate(size_t __n)
{
  void* __result = malloc(__n);  // 尝试调用malloc函数分配内存
  if (0 == __result) __result = _S_oom_malloc(__n);  // 如果分配失败，那么调用_S_oom_malloc函数尝试分配内存
  return __result;  // 返回分配的内存的地址
}


// __n 是请求的内存大小
template <int __inst>
void*
__malloc_alloc_template<__inst>::_S_oom_malloc(size_t __n)
{
  void (* __my_malloc_handler)();  // 定义一个函数指针，用于处理内存不足的情况
  void* __result;  // 用于保存分配的内存的地址

  for (;;) {  // 无限循环，直到分配成功或者无法处理内存不足的情况
    __my_malloc_handler = __malloc_alloc_oom_handler;  // 获取处理内存不足的函数
    if (0 == __my_malloc_handler) { __THROW_BAD_ALLOC; }  // 如果没有设置处理函数，那么抛出异常
    (*__my_malloc_handler)();  // 调用处理函数，尝试处理内存不足的情况
    __result = malloc(__n);  // 再次尝试分配内存
    if (__result) return(__result);  // 如果分配成功，那么返回内存的地址
  }
}

#ifndef __STL_STATIC_TEMPLATE_MEMBER_BUG
  // 静态成员函数指针，用于处理内存分配失败的情况
  // 如果内存分配失败，那么会调用这个函数尝试处理内存不足的问题
  static void (* __malloc_alloc_oom_handler)(); // 留给用户的回调函数接口
#endif
```

### 2.4.2 `deallocate` 函数的实现

```cpp
// __p 是要释放的内存块的起始地址，不能为0
// __n 是要释放的内存块的大小
static void deallocate(void* __p, size_t __n)
{
  // 如果要释放的内存块大小超过了_MAX_BYTES，那么直接调用malloc_alloc的deallocate函数释放内存
  if (__n > (size_t) _MAX_BYTES)
    malloc_alloc::deallocate(__p, __n);
  else {
    // 否则，将内存块加入到相应的自由链表中
    _Obj* __STL_VOLATILE*  __my_free_list
        = _S_free_list + _S_freelist_index(__n);  // 计算内存块应该加入哪个自由链表
    _Obj* __q = (_Obj*)__p;  // 将void*指针转换为_Obj*指针

    // acquire lock
#   ifndef _NOTHREADS
    /*REFERENCED*/
    _Lock __lock_instance;  // 创建一个锁，用于保护自由链表的操作
#   endif /* _NOTHREADS */
    __q -> _M_free_list_link = *__my_free_list;  // 将内存块加入到自由链表中
    *__my_free_list = __q;  // 更新自由链表的头部
    // lock is released here
  }
}
```


### 2.4.3 `reallocate` 函数的实现

```cpp
// __p 是旧的内存的地址
// __old_sz 是旧的内存的大小
// __new_sz 是新的内存的大小
template <bool threads, int inst>
void*
__default_alloc_template<threads, inst>::reallocate(void* __p,
                          size_t __old_sz,
                          size_t __new_sz)
{
  void* __result;  // 用于保存新的内存的地址
  size_t __copy_sz;  // 用于保存需要复制的数据的大小

  // 如果旧的内存大小和新的内存大小都超过了_MAX_BYTES，那么直接调用realloc函数重新分配内存
  if (__old_sz > (size_t) _MAX_BYTES && __new_sz > (size_t) _MAX_BYTES) {
    return(realloc(__p, __new_sz));
  }
  // 如果旧的内存大小和新的内存大小经过调整后相等，那么直接返回旧的内存的地址
  if (_S_round_up(__old_sz) == _S_round_up(__new_sz)) return(__p);
  __result = allocate(__new_sz);  // 分配新的内存
  __copy_sz = __new_sz > __old_sz? __old_sz : __new_sz;  // 计算需要复制的数据的大小
  memcpy(__result, __p, __copy_sz);  // 将旧的内存中的数据复制到新的内存中
  deallocate(__p, __old_sz);  // 释放旧的内存
  return(__result);  // 返回新的内存的地址
}
```

# 3 nginx 内存池

[nginx github](https://github.com/nginx/nginx)

定位到 `/src/core/ngx_palloc.c` 和 `/src/core/ngx_palloc.h` 文件

```cpp
/*
 * NGX_MAX_ALLOC_FROM_POOL 应该是 (ngx_pagesize - 1)，在x86上是4095。
 * 在Windows NT上，它可以减少内核中锁定的页面数量。
 */
#define NGX_MAX_ALLOC_FROM_POOL  (ngx_pagesize - 1)  // 定义从内存池中最大可分配的内存大小

#define NGX_DEFAULT_POOL_SIZE    (16 * 1024)  // 定义默认的内存池大小为16KB

#define NGX_POOL_ALIGNMENT       16  // 定义内存池的对齐大小为16字节

// 定义最小的内存池大小
// 首先计算ngx_pool_t和ngx_pool_large_t的大小，然后将其对齐到NGX_POOL_ALIGNMENT
#define NGX_MIN_POOL_SIZE                                                     \
    ngx_align((sizeof(ngx_pool_t) + 2 * sizeof(ngx_pool_large_t)),            \
              NGX_POOL_ALIGNMENT)

// d 是需要对齐的数值
// a 是对齐的大小
#define ngx_align(d, a)     (((d) + (a - 1)) & ~(a - 1))  // 将d向上对齐到a的倍数
```

## 3.1 重要类型定义

```cpp
struct ngx_pool_s {
    ngx_pool_data_t       d;  // 内存池的数据部分
    size_t                max;  // 内存池中可分配的最大内存大小
    ngx_pool_t           *current;  // 指向当前内存池的指针
    ngx_chain_t          *chain;  // 指向内存池中的链表的指针
    ngx_pool_large_t     *large;  // 指向内存池中的大块内存的指针
    ngx_pool_cleanup_t   *cleanup;  // 指向内存池的清理函数的指针
    ngx_log_t            *log;  // 指向日志对象的指针
};

typedef struct ngx_pool_s            ngx_pool_t;  // 定义结构体别名为ngx_pool_t

typedef struct {
  u_char               *last;  // 指向当前可用内存的开始位置
  u_char               *end;  // 指向当前内存块的结束位置
  ngx_pool_t           *next;  // 指向下一个内存池的指针
  ngx_uint_t            failed;  // 记录当前内存池分配内存失败的次数
} ngx_pool_data_t;
```


```cpp
typedef struct ngx_pool_large_s ngx_pool_large_t;
// 大块内存类型定义
struct ngx_pool_large_s {
  ngx_pool_large_t *next; // 下一个大块内存
  void *alloc; // 记录分配的大块内存的起始地址
};
```

```cpp
typedef void (*ngx_pool_cleanup_pt)(void *data); // 清理回调函数的类型定义
typedef struct ngx_pool_cleanup_s ngx_pool_cleanup_t;
// 清理操作的类型定义，包括一个清理回调函数，传给回调函数的数据和下一个清理操作的地址
struct ngx_pool_cleanup_s {
  ngx_pool_cleanup_pt handler; // 清理回调函数
  void *data; // 传递给回调函数的指针
  ngx_pool_cleanup_t *next; // 指向下一个清理操作
};
```

## 3.2 nginx内存池重要函数接口

```cpp
ngx_pool_t *ngx_create_pool(size_t size, ngx_log_t *log); // 创建内存池
void ngx_destroy_pool(ngx_pool_t *pool); // 销毁内存池
void ngx_reset_pool(ngx_pool_t *pool); // 重置内存池
void *ngx_palloc(ngx_pool_t *pool, size_t size); // 内存分配函数，支持内存对齐
void *ngx_pnalloc(ngx_pool_t *pool, size_t size); // 内存分配函数，不支持内存对齐
void *ngx_pcalloc(ngx_pool_t *pool, size_t size); // 内存分配函数，支持内存初始化0
ngx_int_t ngx_pfree(ngx_pool_t *pool, void *p // 内存释放（大块内存）
```

```cpp
ngx_pool_cleanup_t *ngx_pool_cleanup_add(ngx_pool_t *p, size_t size); // 添加清理 handler
```

### 3.2.1 `ngx_create_pool` 函数的实现

```cpp
/*
 * size 是需要创建的内存池的大小
 * log 是日志对象，用于记录日志信息
 */
ngx_pool_t *
ngx_create_pool(size_t size, ngx_log_t *log)
{
  ngx_pool_t  *p;  // 用于保存新创建的内存池的指针

  // 调用ngx_memalign函数分配一块对齐的内存，大小为size
  p = ngx_memalign(NGX_POOL_ALIGNMENT, size, log);
  if (p == NULL) {  // 如果内存分配失败，返回NULL
    return NULL;
  }

  // 初始化新创建的内存池
  p->d.last = (u_char *) p + sizeof(ngx_pool_t);  // 设置当前可用内存的开始位置
  p->d.end = (u_char *) p + size;  // 设置当前内存块的结束位置
  p->d.next = NULL;  // 设置下一个内存池的指针为NULL
  p->d.failed = 0;  // 设置分配内存失败的次数为0

  // 计算内存池中可分配的最大内存大小
  size = size - sizeof(ngx_pool_t);
  p->max = (size < NGX_MAX_ALLOC_FROM_POOL) ? size : NGX_MAX_ALLOC_FROM_POOL;

  // 初始化其他成员
  p->current = p;  // 设置当前内存池的指针为p
  p->chain = NULL;  // 设置链表的指针为NULL
  p->large = NULL;  // 设置大块内存的指针为NULL
  p->cleanup = NULL;  // 设置清理函数的指针为NULL
  p->log = log;  // 设置日志对象为log

  return p;  // 返回新创建的内存池的指针
}
```

#### 3.2.1.1 `ngx_memalign(NGX_POOL_ALIGNMENT, size, log);` 函数的实现

```cpp
#if (NGX_HAVE_POSIX_MEMALIGN || NGX_HAVE_MEMALIGN)

// alignment 是对齐的大小
// size 是需要分配的内存的大小
// log 是日志对象，用于记录日志信息
void *ngx_memalign(size_t alignment, size_t size, ngx_log_t *log);

#else

// 如果系统不支持posix_memalign或memalign函数，那么ngx_memalign就是一个宏，它直接调用ngx_alloc函数分配内存
#define ngx_memalign(alignment, size, log)  ngx_alloc(size, log)

#endif
```

```cpp
#if (NGX_HAVE_POSIX_MEMALIGN)

/*
 * alignment 是对齐的大小
 * size 是需要分配的内存的大小
 * log 是日志对象，用于记录日志信息
 */
void *
ngx_memalign(size_t alignment, size_t size, ngx_log_t *log)
{
    void  *p;  // 用于保存分配的内存的指针
    int    err;  // 用于保存posix_memalign函数的返回值

    // 调用posix_memalign函数分配一块对齐的内存
    err = posix_memalign(&p, alignment, size);

    if (err) {  // 如果内存分配失败，记录错误日志
        ngx_log_error(NGX_LOG_EMERG, log, err,
                      "posix_memalign(%uz, %uz) failed", alignment, size);
        p = NULL;
    }

    // 记录调试日志，输出分配的内存的地址、大小和对齐的大小
    ngx_log_debug3(NGX_LOG_DEBUG_ALLOC, log, 0,
                   "posix_memalign: %p:%uz @%uz", p, size, alignment);

    return p;  // 返回分配的内存的指针
}

#elif (NGX_HAVE_MEMALIGN)

/*
 * alignment 是对齐的大小
 * size 是需要分配的内存的大小
 * log 是日志对象，用于记录日志信息
 */
void *
ngx_memalign(size_t alignment, size_t size, ngx_log_t *log)
{
    void  *p;  // 用于保存分配的内存的指针

    // 调用memalign函数分配一块对齐的内存
    p = memalign(alignment, size);
    if (p == NULL) {  // 如果内存分配失败，记录错误日志
        ngx_log_error(NGX_LOG_EMERG, log, ngx_errno,
                      "memalign(%uz, %uz) failed", alignment, size);
    }

    // 记录调试日志，输出分配的内存的地址、大小和对齐的大小
    ngx_log_debug3(NGX_LOG_DEBUG_ALLOC, log, 0,
                   "memalign: %p:%uz @%uz", p, size, alignment);

    return p;  // 返回分配的内存的指针
}

#endif
```

```cpp
/*
 * size 是需要分配的内存的大小
 * log 是日志对象，用于记录日志信息
 */
void *
ngx_alloc(size_t size, ngx_log_t *log)
{
    void  *p;  // 用于保存分配的内存的指针

    // 调用malloc函数分配一块内存，大小为size
    p = malloc(size);
    if (p == NULL) {  // 如果内存分配失败，记录错误日志
        ngx_log_error(NGX_LOG_EMERG, log, ngx_errno,
                      "malloc(%uz) failed", size);
    }

    // 记录调试日志，输出分配的内存的地址和大小
    ngx_log_debug2(NGX_LOG_DEBUG_ALLOC, log, 0, "malloc: %p:%uz", p, size);

    return p;  // 返回分配的内存的指针
}
```

### 3.2.2 `ngx_destroy_pool` 函数的实现

```cpp
/*
 * pool 是需要销毁的内存池对象
 */
void
ngx_destroy_pool(ngx_pool_t *pool)
{
    ngx_pool_t          *p, *n;  // 用于遍历内存池链表的指针
    ngx_pool_large_t    *l;  // 用于遍历大内存链表的指针
    ngx_pool_cleanup_t  *c;  // 用于遍历清理操作链表的指针

    // 遍历清理操作链表，执行所有的清理操作
    for (c = pool->cleanup; c; c = c->next) {
        if (c->handler) {
            ngx_log_debug1(NGX_LOG_DEBUG_ALLOC, pool->log, 0,
                           "run cleanup: %p", c);
            c->handler(c->data);
        }
    }

#if (NGX_DEBUG)
    // 如果开启了调试模式，打印一些调试信息

    // 打印大内存链表中的所有内存
    for (l = pool->large; l; l = l->next) {
        ngx_log_debug1(NGX_LOG_DEBUG_ALLOC, pool->log, 0, "free: %p", l->alloc);
    }

    // 打印内存池链表中的所有内存池节点
    for (p = pool, n = pool->d.next; /* void */; p = n, n = n->d.next) {
        ngx_log_debug2(NGX_LOG_DEBUG_ALLOC, pool->log, 0,
                       "free: %p, unused: %uz", p, p->d.end - p->d.last);

        if (n == NULL) {
            break;
        }
    }

#endif

    // 遍历大内存链表，释放所有的大内存
    for (l = pool->large; l; l = l->next) {
        if (l->alloc) {
            ngx_free(l->alloc);
        }
    }

    // 遍历内存池链表，释放所有的内存池节点
    for (p = pool, n = pool->d.next; /* void */; p = n, n = n->d.next) {
        ngx_free(p);

        if (n == NULL) {
            break;
        }
    }
}
```


### 3.2.3 `ngx_reset_pool` 函数的实现

```cpp
/*
 * pool 是需要重置的内存池对象
 */
void
ngx_reset_pool(ngx_pool_t *pool)
{
    ngx_pool_t        *p;  // 用于遍历内存池链表的指针
    ngx_pool_large_t  *l;  // 用于遍历大内存链表的指针

    // 遍历大内存链表，释放所有的大内存
    for (l = pool->large; l; l = l->next) {
        if (l->alloc) {
            ngx_free(l->alloc);
        }
    }

    // 遍历内存池链表，将所有的内存池节点重置为初始状态
    for (p = pool; p; p = p->d.next) {
        p->d.last = (u_char *) p + sizeof(ngx_pool_t);
        p->d.failed = 0;
    }

    // 将当前内存池设置为传入的内存池
    pool->current = pool;
    // 将内存池的chain设置为NULL
    pool->chain = NULL;
    // 将内存池的large设置为NULL
    pool->large = NULL;
}
```


### 3.2.4 `ngx_palloc`, `ngx_pnalloc` 和 `ngx_pcalloc` 函数的实现

```cpp
/*
 * pool 是内存池对象
 * size 是需要分配的内存的大小
 */
void *
ngx_palloc(ngx_pool_t *pool, size_t size)
{
#if !(NGX_DEBUG_PALLOC)
  // 如果需要分配的内存大小小于等于内存池中可分配的最大内存大小
  if (size <= pool->max) {
    // 从内存池中分配一块小内存，第三个参数1表示需要对齐
    return ngx_palloc_small(pool, size, 1);
  }
#endif

  // 如果需要分配的内存大小大于内存池中可分配的最大内存大小，从内存池中分配一块大内存
  return ngx_palloc_large(pool, size);
}
```

**上述代码中 `ngx_palloc_small(pool, size, 1);` 函数的实现**

```cpp
/*
 * pool 是内存池对象
 * size 是需要分配的内存的大小
 * align 表示是否需要对齐，如果align为1，表示需要对齐，如果align为0，表示不需要对齐
 */
static ngx_inline void *
ngx_palloc_small(ngx_pool_t *pool, size_t size, ngx_uint_t align)
{
    u_char      *m;  // 用于保存分配的内存的指针
    ngx_pool_t  *p;  // 用于遍历内存池的指针

    p = pool->current;  // 从当前内存池开始遍历

    do {
        m = p->d.last;  // 获取当前内存池的最后一个可用内存的地址

        if (align) {
            // 如果需要对齐，调用ngx_align_ptr函数对m进行对齐
            m = ngx_align_ptr(m, NGX_ALIGNMENT);
        }

        if ((size_t) (p->d.end - m) >= size) {
            // 如果当前内存池的剩余内存大小大于等于需要分配的内存大小
            p->d.last = m + size;  // 更新当前内存池的最后一个可用内存的地址

            return m;  // 返回分配的内存的指针
        }

        p = p->d.next;  // 如果当前内存池的剩余内存大小小于需要分配的内存大小，遍历下一个内存池

    } while (p);  // 如果所有的内存池的剩余内存大小都小于需要分配的内存大小，结束遍历

    // 如果所有的内存池的剩余内存大小都小于需要分配的内存大小，调用ngx_palloc_block函数分配一个新的内存池，并从新的内存池中分配内存
    return ngx_palloc_block(pool, size);
}
```

**上述代码中 `ngx_palloc_block(pool, size);` 函数的实现**

```cpp
/*
 * pool 是当前内存池对象
 * size 是需要分配的内存的大小
 */
static void *
ngx_palloc_block(ngx_pool_t *pool, size_t size)
{
    u_char      *m;  // 用于保存分配的内存的指针
    size_t       psize;  // 新的内存池的大小
    ngx_pool_t  *p, *new;  // p用于遍历内存池，new用于保存新的内存池的指针

    // 计算新的内存池的大小
    psize = (size_t) (pool->d.end - (u_char *) pool);

    // 分配一块对齐的内存作为新的内存池
    m = ngx_memalign(NGX_POOL_ALIGNMENT, psize, pool->log);
    if (m == NULL) {
        // 如果内存分配失败，返回NULL
        return NULL;
    }

    // 初始化新的内存池
    new = (ngx_pool_t *) m;
    new->d.end = m + psize;
    new->d.next = NULL;
    new->d.failed = 0;

    // 计算新的内存池中可用内存的起始地址
    m += sizeof(ngx_pool_data_t);
    m = ngx_align_ptr(m, NGX_ALIGNMENT);
    new->d.last = m + size;

    // 遍历当前内存池，找到最后一个内存池
    for (p = pool->current; p->d.next; p = p->d.next) {
        if (p->d.failed++ > 4) {
            // 如果当前内存池的失败次数大于4，更新当前内存池为下一个内存池
            pool->current = p->d.next;
        }
    }

    // 将新的内存池添加到内存池链表的末尾
    p->d.next = new;

    // 返回新的内存池中可用内存的起始地址
    return m;
}
```

**`ngx_palloc_large` 函数的实现**

```cpp
// 定义了一个名为ngx_pool_large_t的结构体类型
typedef struct ngx_pool_large_s  ngx_pool_large_t;

// 定义了ngx_pool_large_s结构体
struct ngx_pool_large_s {
    ngx_pool_large_t     *next;  // 指向下一个大内存节点的指针
    void                 *alloc;  // 指向分配的大内存的指针
};

/*
 * pool 是内存池对象
 * size 是需要分配的内存的大小
 */
static void *
ngx_palloc_large(ngx_pool_t *pool, size_t size)
{
    void              *p;  // 用于保存分配的内存的指针
    ngx_uint_t         n;  // 用于计数
    ngx_pool_large_t  *large;  // 用于遍历大内存链表的指针

    // 分配一块大内存
    p = ngx_alloc(size, pool->log);
    if (p == NULL) {
        // 如果内存分配失败，返回NULL
        return NULL;
    }

    n = 0;

    // 遍历大内存链表
    for (large = pool->large; large; large = large->next) {
        if (large->alloc == NULL) {
            // 如果找到一个未使用的大内存节点，将分配的内存赋值给这个节点，并返回分配的内存的指针
            large->alloc = p;
            return p;
        }

        if (n++ > 3) {
            // 如果遍历了3个以上的大内存节点都没有找到未使用的节点，结束遍历
            break;
        }
    }

    // 如果大内存链表中没有未使用的节点，分配一个新的大内存节点
    large = ngx_palloc_small(pool, sizeof(ngx_pool_large_t), 1);
    if (large == NULL) {
        // 如果节点分配失败，释放之前分配的大内存，并返回NULL
        ngx_free(p);
        return NULL;
    }

    // 初始化新的大内存节点，并将其添加到大内存链表的头部
    large->alloc = p;
    large->next = pool->large;
    pool->large = large;

    // 返回分配的大内存的指针
    return p;
}
```


```cpp
/*
 * pool 是内存池对象
 * size 是需要分配的内存的大小
 */
void *
ngx_pnalloc(ngx_pool_t *pool, size_t size)
{
#if !(NGX_DEBUG_PALLOC)
  // 如果需要分配的内存大小小于等于内存池中可分配的最大内存大小
  if (size <= pool->max) {
    // 从内存池中分配一块小内存，第三个参数0表示不需要对齐
    return ngx_palloc_small(pool, size, 0);
  }
#endif

  // 如果需要分配的内存大小大于内存池中可分配的最大内存大小，从内存池中分配一块大内存
  return ngx_palloc_large(pool, size);
}


/*
 * pool 是内存池对象
 * size 是需要分配的内存的大小
 */
void *
ngx_pcalloc(ngx_pool_t *pool, size_t size)
{
    void *p;  // 用于保存分配的内存的指针

    // 从内存池中分配一块内存
    p = ngx_palloc(pool, size);
    if (p) {
        // 如果内存分配成功，将这块内存初始化为0
        ngx_memzero(p, size);
    }

    return p;  // 返回分配的内存的指针，如果内存分配失败，返回NULL
}
```


### 3.2.5 `ngx_pfree` 函数的实现

> nginx 大块内存分配 =》 内存释放 ngx_pfree 函数
>
> nginx 小块内存分配 =》 没有提供任何的内存释放函数。实际上，从小块内存的分配方式来看（直接通过 last 指针偏移来分配内存），它也没办法进行小块内存的回收。
>
> nginx 本质 ： http 服务器
>   - 是一个短链接的服务器，客户端（浏览器）发起一个 request 请求，到达 nginx 服务器以后，处理完成，nginx 给客户端返回一个 response 响应，http 服务器主动断开 tcp 连接。
>   - http 1.1 keep-avlie: 60s, http 服务器（nginx）返回响应以后，需要等待 60s，60s 之内客户端又发来请求，时间重置。否则 60s 之后，nginx 就主动断开连接，此时 nginx 可以调用 ngx_reset_pool 函数，重置内存池，等待下一次请求。

```cpp
/*
 * pool 是内存池对象
 * p 是需要释放的内存的指针
 */
ngx_int_t
ngx_pfree(ngx_pool_t *pool, void *p)
{
    ngx_pool_large_t  *l;  // 用于遍历大内存链表的指针

    // 遍历大内存链表
    for (l = pool->large; l; l = l->next) {
        if (p == l->alloc) {
            // 如果找到需要释放的内存，打印一条调试信息
            ngx_log_debug1(NGX_LOG_DEBUG_ALLOC, pool->log, 0,
                           "free: %p", l->alloc);
            // 释放内存
            ngx_free(l->alloc);
            // 将大内存节点的alloc设置为NULL
            l->alloc = NULL;

            // 返回NGX_OK表示释放成功
            return NGX_OK;
        }
    }

    // 如果没有找到需要释放的内存，返回NGX_DECLINED表示释放失败
    return NGX_DECLINED;
}
```

### 3.2.6 `ngx_pool_cleanup_add` 函数的实现

```cpp
// 清理操作的类型定义
typedef struct ngx_pool_cleanup_s  ngx_pool_cleanup_t;

// 清理操作的结构体
struct ngx_pool_cleanup_s {
    ngx_pool_cleanup_pt   handler;  // 清理操作的处理函数
    void                 *data; // 传递给处理函数的数据
    ngx_pool_cleanup_t   *next; // 指向下一个清理操作
};

/*
 * p 是内存池对象
 * size 是清理操作数据的大小
 */
ngx_pool_cleanup_t *
ngx_pool_cleanup_add(ngx_pool_t *p, size_t size)
{
    ngx_pool_cleanup_t  *c;  // 用于保存新的清理操作的指针

    // 分配一个新的清理操作
    c = ngx_palloc(p, sizeof(ngx_pool_cleanup_t));
    if (c == NULL) {
        // 如果分配失败，返回NULL
        return NULL;
    }

    if (size) {
        // 如果清理操作数据的大小不为0，分配一块内存用于保存清理操作数据
        c->data = ngx_palloc(p, size);
        if (c->data == NULL) {
            // 如果分配失败，返回NULL
            return NULL;
        }

    } else {
        // 如果清理操作数据的大小为0，将data设置为NULL
        c->data = NULL;
    }

    // 初始化新的清理操作
    c->handler = NULL;  // 清理操作的处理函数
    c->next = p->cleanup;  // 下一个清理操作

    // 将新的清理操作添加到内存池的清理操作链表的头部
    p->cleanup = c;

    // 打印一条调试信息
    ngx_log_debug1(NGX_LOG_DEBUG_ALLOC, p->log, 0, "add cleanup: %p", c);

    // 返回新的清理操作的指针
    return c;
}
```

## 3.3 编译测试 nginx 内存池功能
