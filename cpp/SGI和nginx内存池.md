- [source insight](https://www.sourceinsight.com/) 是一个优秀的源代码阅读工具

# 1 C++ STL 空间配置器

[容器空间配置器](ttps://github.com/Corner430/study-notes/blob/main/cpp/cpp%E4%B8%AD%E7%BA%A7%E7%AC%94%E8%AE%B0.md#42-%E5%AE%B9%E5%99%A8%E7%A9%BA%E9%97%B4%E9%85%8D%E7%BD%AE%E5%99%A8-allocator)

```cpp
template<typename _Tp, typename _Alloc = std::allocator<_Tp> >
```

- `allocate` 负责给容器开辟内存空间，通过 `malloc` 实现
- `deallocate` 负责释放容器的内存空间，通过 `free` 实现
- `construct` 负责在已经开辟的内存空间上构造对象，通过 定位 `new` 实现
- `destroy` 负责在已经构造的对象上析构对象，通过 显式调用析构函数 实现

> **空间配置器作用**
>
> - 分离了对象的内存分配和对象的构造
> - 分离了对象的析构和内存的释放

# 2 SGI STL 空间配置器

## 2.1 定义

> - SGI STL 包含了一级空间配置器和二级空间配置器
>
> ![20240605001406](https://cdn.jsdelivr.net/gh/Corner430/Picture/images/20240605001406.png)
>
> 二级空间配置器 `allocator` 采用了基于 `freelist` 自由链表原理的**内存池**机制实现内存管理

```cpp
template <class _Tp, class _Alloc = __STL_DEFAULT_ALLOCATOR(_Tp) >
class vector : protected _Vector_base<_Tp, _Alloc>

// 如上所见，容器的默认空间配置器是宏定义 __STL_DEFAULT_ALLOCATOR(_Tp)

# ifndef __STL_DEFAULT_ALLOCATOR
#   ifdef __STL_USE_STD_ALLOCATORS
#       define __STL_DEFAULT_ALLOCATOR(T) allocator< T >    // 一级空间配置器
#   else
#       define __STL_DEFAULT_ALLOCATOR(T) alloc // 二级空间配置器
#   endif
# endif
```

## 2.2 一级空间配置器

```cpp
// 定义了一个模板类__malloc_alloc_template，__inst是模板参数
template <int __inst>
class __malloc_alloc_template {

private:

    // 定义了两个私有的静态函数，用于在内存分配失败时尝试重新分配内存
    static void* _S_oom_malloc(size_t);
    static void* _S_oom_realloc(void*, size_t);

#ifndef __STL_STATIC_TEMPLATE_MEMBER_BUG
    // 定义了一个私有的静态函数指针，用于设置内存分配失败时的处理函数
    static void (* __malloc_alloc_oom_handler)();
#endif

public:

    // 定义了一个静态函数allocate，用于分配内存
    static void* allocate(size_t __n)
    {
        void* __result = malloc(__n);
        if (0 == __result) __result = _S_oom_malloc(__n);
        return __result;
    }

    // 定义了一个静态函数deallocate，用于释放内存
    static void deallocate(void* __p, size_t /* __n */)
    {
        free(__p);
    }

    // 定义了一个静态函数reallocate，用于重新分配内存
    static void* reallocate(void* __p, size_t /* old_sz */, size_t __new_sz)
    {
        void* __result = realloc(__p, __new_sz);
        if (0 == __result) __result = _S_oom_realloc(__p, __new_sz);
        return __result;
    }

    // 定义了一个静态函数__set_malloc_handler，用于设置内存分配失败时的处理函数
    static void (* __set_malloc_handler(void (*__f)()))()
    {
        void (* __old)() = __malloc_alloc_oom_handler;
        __malloc_alloc_oom_handler = __f;
        return(__old);
    }

};
```

## 2.3 二级空间配置器

> - 防止小块内存频繁的申请和释放，导致内存碎片化
> - SGI STL 二级空间配置器内存池的实现优点：
>   1. 对于每一个字节数的 chunk 块，都是给出一部分进行使用，另一部分作为备用。备用的 chunk 块可以给当前字节数或者其他字节数的内存分配请求使用。
>   2. 对于备用内存池中的 chunk 块划分完之后，如果还有剩余的很小的内存块，再次分配的时候，会把这些小的内存块再次分配出去，而不会浪费掉。
>   3. 当指定字节数内存分配失败之后，有一个异常处理的过程，会去 `bytes - 128` 字节所有的 chunk 块进行查看，如果哪个字节数有空闲的 chunk 块，就会把这个 chunk 块分配出去。
>   4. 如果都失败，会调用 `oom_malloc` 函数，这个函数是一个回调函数，用户可以自己定义，用于处理内存分配失败的情况。


### 2.3.1 重要类型和变量定义

```cpp
// 内存池粒度信息
enum {_ALIGN = 8}; // 内存对齐的字节数，通常为8
enum {_MAX_BYTES = 128}; // 可以处理的最大字节数，超过这个值的内存请求将由系统内存分配器处理
enum {_NFREELISTS = 16}; // 自由链表的数量，由 _MAX_BYTES/_ALIGN 计算得出


// 每一个内存chunk块的头信息
union _Obj {
union _Obj* _M_free_list_link; // 指向下一个空闲块的指针
char _M_client_data[1];    // 客户端看到的数据，实际上可能会更大
};


// 组织所有自由链表的数组，数组的每一个元素的类型是_Obj*，全部初始化为0
static _Obj* __STL_VOLATILE _S_free_list[_NFREELISTS];


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

### 2.3.2 重要的辅助接口函数

```cpp
/* 一种常见的内存对齐技巧，效率很高. 将 __bytes 上调至最邻近的 8 的倍数*/
static size_t _S_round_up(size_t __bytes) {
    return (((__bytes) + (int) _S_ALIGN-1) & ~((int) _S_ALIGN - 1));
}


/*返回 __bytes 大小的chunk块位于 free-list 中的编号*/
static size_t _S_freelist_index(size_t __bytes) {
    return (((__bytes) + (int) _S_ALIGN-1)/(int)_S_ALIGN - 1);
}
```

### 2.3.3 内存池管理函数

```cpp
// 分配内存的入口函数
static void* allocate(size_t __n)

// 负责把分配好的chunk块进行连接，添加到自由链表当中
static void* _S_refill(size_t __n);

// 分配相应内存字节大小的chunk块，并且给下面三个成员变量初始化
static char* _S_chunk_alloc(size_t __size, int& __nobjs);

// 把chunk块归还到内存池
static void deallocate(void* __p, size_t __n);

// 内存池扩容缩容函数
template <bool threads, int inst>
void*
__default_alloc_template<threads, inst>::reallocate(void* __p,
                                                    size_t __old_sz,
                                                    size_t __new_sz)
```

### 2.3.4 `class __default_alloc_template` (内存池) 的实现

![20240602205509](https://cdn.jsdelivr.net/gh/Corner430/Picture/images/20240602205509.png)

```cpp
template <bool threads, int inst>
class __default_alloc_template {

private:
  // Really we should use static const int x = N
  // instead of enum { x = N }, but few compilers accept the former.
#if ! (defined(__SUNPRO_CC) || defined(__GNUC__))
    enum {_ALIGN = 8};          // 内存对齐的字节数
    enum {_MAX_BYTES = 128};    // 可以处理的最大字节数
                                //超过这个值的内存请求将使用一级配置器同样的方式处理
    enum {_NFREELISTS = 16};    // _MAX_BYTES/_ALIGN, free-lists的个数
# endif
  // 上调至 _ALIGN 的倍数
  static size_t
  _S_round_up(size_t __bytes)
    { return (((__bytes) + (size_t) _ALIGN-1) & ~((size_t) _ALIGN - 1)); }

__PRIVATE:
  // free-lists 的节点构造
  union _Obj {
        union _Obj* _M_free_list_link;  // 指向下一个空闲块
        char _M_client_data[1];    /* The client sees this.        */
  };
private:
# if defined(__SUNPRO_CC) || defined(__GNUC__) || defined(__HP_aCC)
  // _NFREELISTS 个自由链表, 会被初始化为0
    static _Obj* __STL_VOLATILE _S_free_list[];
        // Specifying a size results in duplicate def for 4.1
# else
    static _Obj* __STL_VOLATILE _S_free_list[_NFREELISTS];
# endif
  // 根据区块大小，决定使用第 n 号区块
  static  size_t _S_freelist_index(size_t __bytes) {
        return (((__bytes) + (size_t)_ALIGN-1)/(size_t)_ALIGN - 1);
  }

  // Returns an object of size __n, and optionally adds to size __n free list.
  // 负责把分配好的chunk块进行连接，添加到自由链表当中
  static void* _S_refill(size_t __n);
  // Allocates a chunk for nobjs of size size.  nobjs may be reduced
  // if it is inconvenient to allocate the requested number.
  // 分配相应内存字节大小的chunk块，并且给下面三个成员变量初始化
  static char* _S_chunk_alloc(size_t __size, int& __nobjs);

  // Chunk allocation state.
  static char* _S_start_free;   // 内存池起始位置
  static char* _S_end_free;     // 内存池结束位置
  static size_t _S_heap_size;   // 当前堆的大小

# ifdef __STL_THREADS
    static _STL_mutex_lock _S_node_allocator_lock;
# endif

    // It would be nice to use _STL_auto_lock here.  But we
    // don't need the NULL check.  And we do need a test whether
    // threads have actually been started.
    class _Lock;
    friend class _Lock;
    class _Lock {
        public:
            _Lock() { __NODE_ALLOCATOR_LOCK; }
            ~_Lock() { __NODE_ALLOCATOR_UNLOCK; }
    };

public:

  // __n 是请求的内存大小, 必须大于0
  static void* allocate(size_t __n)
  {
    void* __ret = 0;

    // 如果请求的内存大于_MAX_BYTES（这是一个预设的阈值），则采用和一级空间配置器相同的方式分配内存
    if (__n > (size_t) _MAX_BYTES) {
      __ret = malloc_alloc::allocate(__n);
    }
    else {
      // 否则，从内存池中分配。首先找到对应大小的自由链表
      // __my_free_list 是一个_Obj*指针(二级指针)，指向自由链表的头部
      _Obj* __STL_VOLATILE* __my_free_list
          = _S_free_list + _S_freelist_index(__n);
      // Acquire the lock here with a constructor call.
      // This ensures that it is released in exit or during stack
      // unwinding.
      // 在多线程环境下，需要加锁以保证线程安全
#     ifndef _NOTHREADS
      /*REFERENCED*/
      _Lock __lock_instance;
#     endif
      // 从自由链表中取出一个对象
      _Obj* __RESTRICT __result = *__my_free_list;
      if (__result == 0)   // 如果自由链表为空，那么需要填充自由链表
        __ret = _S_refill(_S_round_up(__n));
      else {    // 否则，直接从自由链表中取出一个对象，并更新自由链表
        *__my_free_list = __result -> _M_free_list_link;
        __ret = __result;
      }
    }

    // 返回分配的内存
    return __ret;
  };

  /* __p may not be 0 */
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
          = _S_free_list + _S_freelist_index(__n); // 计算内存块应该加入哪个自由链表
      _Obj* __q = (_Obj*)__p;   // 将void*指针转换为_Obj*指针

      // acquire lock
#       ifndef _NOTHREADS
      /*REFERENCED*/
      _Lock __lock_instance;    // 创建一个锁，用于保护自由链表的操作
#       endif /* _NOTHREADS */
      // 头插法，将内存块加入到自由链表中
      __q -> _M_free_list_link = *__my_free_list;
      *__my_free_list = __q;
      // lock is released here
    }
  }

  // 内存池扩容缩容函数
  static void* reallocate(void* __p, size_t __old_sz, size_t __new_sz);

} ;
```

### 2.3.5 `_S_refill(size_t __n);` 函数的实现

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

### 2.3.6 `_S_chunk_alloc(size_t __size, int& __nobjs);` 函数的实现

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

### 2.3.7 `malloc_alloc::allocate(size_t __n);` 函数的实现

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

### 2.3.8 `reallocate` 函数的实现

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

## 2.4 手写 SGI STL 内存池

```cpp
```


# 3 nginx 内存池

[nginx github](https://github.com/nginx/nginx)

## 3.1 `/src/core/ngx_palloc.h` 文件剖析

```cpp
/* ---------------------重要类型定义----------------------- */

/*
 * NGX_MAX_ALLOC_FROM_POOL 应该是 (ngx_pagesize - 1)，在x86上是4095。
 * 在Windows NT上，它可以减少内核中锁定的页面数量。
 */
// 定义从内存池中最大可分配的内存大小
#define NGX_MAX_ALLOC_FROM_POOL  (ngx_pagesize - 1)

// 定义默认的内存池大小为16KB
#define NGX_DEFAULT_POOL_SIZE    (16 * 1024)

// 定义内存池的对齐大小为16字节
#define NGX_POOL_ALIGNMENT       16

// 将 d 向上对齐到 a 的倍数
#define ngx_align(d, a)     (((d) + (a - 1)) & ~(a - 1))

// 定义最小的内存池大小
#define NGX_MIN_POOL_SIZE                                                     \
    ngx_align((sizeof(ngx_pool_t) + 2 * sizeof(ngx_pool_large_t)),            \
              NGX_POOL_ALIGNMENT)


/*
 * ngx_pool_cleanup_pt 是一个函数指针类型，该函数接收一个void*类型的参数，没有返回值。
 * 通常用于定义清理操作，当内存池销毁时，会调用这个函数进行清理。
 */
// 清理回掉函数的类型定义
typedef void (*ngx_pool_cleanup_pt)(void *data);

// 定义了一个结构体类型ngx_pool_cleanup_s，同时定义了一个别名ngx_pool_cleanup_t
typedef struct ngx_pool_cleanup_s  ngx_pool_cleanup_t;

struct ngx_pool_cleanup_s {
    ngx_pool_cleanup_pt   handler;  // 清理操作的处理函数，是一个函数指针
    void                 *data;     // 清理操作的数据，是一个void*类型的指针，传给handler函数
    ngx_pool_cleanup_t   *next;     // 指向下一个清理操作的指针
};


// 定义了一个结构体类型ngx_pool_large_s，同时定义了一个别名ngx_pool_large_t
typedef struct ngx_pool_large_s  ngx_pool_large_t;

// 大块内存类型定义
struct ngx_pool_large_s {
    ngx_pool_large_t     *next;  // 指向下一个大块内存
    void                 *alloc; // 记录分配的大块内存的起始地址
};


// ngx_pool 的数据头部
typedef struct {
    u_char               *last;  // 指向内存池中当前可用内存的开始位置
    u_char               *end;   // 指向内存池中内存的结束位置
    ngx_pool_t           *next;  // 指向下一个内存池的指针
    ngx_uint_t            failed; // 记录当前内存池内存分配失败的次数
} ngx_pool_data_t;


// 定义了一个结构体类型ngx_pool_s，同时定义了一个别名ngx_pool_t
typedef struct ngx_pool_s            ngx_pool_t;

// 定义了一个结构体类型ngx_pool_s
struct ngx_pool_s {
    ngx_pool_data_t       d;       // 内存池的数据头
    size_t                max;     // 内存池中可分配的最大内存大小
    ngx_pool_t           *current; // 指向当前内存池
    ngx_chain_t          *chain;   // 指向内存池中的内存链
    ngx_pool_large_t     *large;   // 指向内存池中的大块内存
    ngx_pool_cleanup_t   *cleanup; // 指向内存池的清理操作
    ngx_log_t            *log;     // 指向日志对象，用于记录内存池的操作日志
};


typedef struct {
    ngx_fd_t              fd;
    u_char               *name;
    ngx_log_t            *log;
} ngx_pool_cleanup_file_t;


/* ----------------nginx 内存池重要函数接口-------------------- */

// 创建内存池
ngx_pool_t *ngx_create_pool(size_t size, ngx_log_t *log);

// 销毁内存池
void ngx_destroy_pool(ngx_pool_t *pool);

// 重置内存池
void ngx_reset_pool(ngx_pool_t *pool);

// 内存分配函数，支持内存对齐
void *ngx_palloc(ngx_pool_t *pool, size_t size);

// 内存分配函数，不支持内存对齐
void *ngx_pnalloc(ngx_pool_t *pool, size_t size);

// 内存分配函数，支持内存初始化0
void *ngx_pcalloc(ngx_pool_t *pool, size_t size);

void *ngx_pmemalign(ngx_pool_t *pool, size_t size, size_t alignment);

// 内存释放（大块内存）
ngx_int_t ngx_pfree(ngx_pool_t *pool, void *p);

/*
 * ngx_pool_cleanup_add 是一个函数，用于在内存池中添加一个清理操作。
 * 参数：
 *   p: 指向内存池的指针
 *   size: 清理操作的数据大小
 * 返回值：
 *   返回一个指向新添加的清理操作的指针
 */
ngx_pool_cleanup_t *ngx_pool_cleanup_add(ngx_pool_t *p, size_t size);

#endif /* _NGX_PALLOC_H_INCLUDED_ */
```

## 3.2 `/src/core/ngx_palloc.c` 文件剖析

```cpp
// 分配小块内存
static ngx_inline void *ngx_palloc_small(ngx_pool_t *pool, size_t size,
    ngx_uint_t align);

// 创建新的内存池，并返回一个需要分配的内存块的起始地址
static void *ngx_palloc_block(ngx_pool_t *pool, size_t size);

// 分配大块内存
static void *ngx_palloc_large(ngx_pool_t *pool, size_t size);


/*
    * 创建内存池
    * 参数：
    *   size: 需要创建内存池的大小
    *   log: 日志对象
    * 返回值：
    *   返回一个指向新创建的内存池的指针
    */
ngx_pool_t *
ngx_create_pool(size_t size, ngx_log_t *log)
{
    ngx_pool_t  *p; // 用于保存新创建的内存池的指针

    // 调用 ngx_memalign 函数分配一块对齐的内存，大小为 size
    p = ngx_memalign(NGX_POOL_ALIGNMENT, size, log);
    if (p == NULL) {
        return NULL;
    }

    // 初始化内存池的数据头
    p->d.last = (u_char *) p + sizeof(ngx_pool_t);  // 设置内存池中当前可用内存的开始位置
    p->d.end = (u_char *) p + size; // 设置内存池中内存的结束位置
    p->d.next = NULL;   // 设置指向下一个内存池的指针为NULL
    p->d.failed = 0;    // 设置内存池内存分配失败的次数为0

    // 真正可被分配出去的内存大小
    size = size - sizeof(ngx_pool_t);   // 计算内存池中可用内存的大小
    // 设置内存池中可分配的最大内存大小
    p->max = (size < NGX_MAX_ALLOC_FROM_POOL) ? size : NGX_MAX_ALLOC_FROM_POOL;

    // 初始化当前内存池其它成员变量
    p->current = p;     // 设置指向当前内存池的指针
    p->chain = NULL;    // 设置指向内存池中的内存链的指针为NULL
    p->large = NULL;    // 设置指向内存池中的大块内存的指针为NULL
    p->cleanup = NULL;  // 设置指向内存池的清理操作的指针为NULL
    p->log = log;       // 设置指向日志对象的指针

    return p;           // 返回新创建的内存池的指针
}


/*
 * 销毁内存池
 * 参数：
 *   pool: 指向内存池的指针
 */
void
ngx_destroy_pool(ngx_pool_t *pool)
{
    ngx_pool_t          *p, *n; // 用于遍历内存池的指针
    ngx_pool_large_t    *l;     // 用于遍历大块内存的指针
    ngx_pool_cleanup_t  *c;     // 用于遍历清理操作的指针

    // 遍历内存池的清理操作
    for (c = pool->cleanup; c; c = c->next) {
        if (c->handler) {
            ngx_log_debug1(NGX_LOG_DEBUG_ALLOC, pool->log, 0,
                           "run cleanup: %p", c);
            c->handler(c->data);
        }
    }

#if (NGX_DEBUG)
    // 如果开启了调试模式，打印一些调试信息

    // 打印内存池中的大块内存
    for (l = pool->large; l; l = l->next) {
        ngx_log_debug1(NGX_LOG_DEBUG_ALLOC, pool->log, 0, "free: %p", l->alloc);
    }

    // 打印内存池中的内存链
    for (p = pool, n = pool->d.next; /* void */; p = n, n = n->d.next) {
        ngx_log_debug2(NGX_LOG_DEBUG_ALLOC, pool->log, 0,
                       "free: %p, unused: %uz", p, p->d.end - p->d.last);

        if (n == NULL) {
            break;
        }
    }

#endif

    // 释放内存池中的大块内存
    for (l = pool->large; l; l = l->next) {
        if (l->alloc) {
            ngx_free(l->alloc);
        }
    }

    // 释放内存池中的内存链
    for (p = pool, n = pool->d.next; /* void */; p = n, n = n->d.next) {
        ngx_free(p);

        if (n == NULL) {
            break;
        }
    }
}


/*
 * 重置内存池
 * 参数：
 *   pool: 指向内存池的指针
 */
void
ngx_reset_pool(ngx_pool_t *pool)
{
    ngx_pool_t        *p;   // 用于遍历内存池的指针
    ngx_pool_large_t  *l;   // 用于遍历大块内存的指针

    // 遍历内存池中的大块内存，释放大块内存
    for (l = pool->large; l; l = l->next) {
        if (l->alloc) {
            ngx_free(l->alloc);
        }
    }

    // 重置内存池中的内存链
    for (p = pool; p; p = p->d.next) {
        p->d.last = (u_char *) p + sizeof(ngx_pool_t);
        p->d.failed = 0;
    }

    pool->current = pool;   // 将当前内存池设置为传入的内存池
    pool->chain = NULL;
    pool->large = NULL;
}


/*
 * 内存分配函数(内存对齐)
 * 参数：
 *   pool: 指向内存池的指针
 *   size: 需要分配的内存大小
 * 返回值：
 *   返回一个指向分配的内存的指针
 */
void *
ngx_palloc(ngx_pool_t *pool, size_t size)
{
#if !(NGX_DEBUG_PALLOC)
    // 如果请求的内存大小小于等于内存池中可分配的最大内存大小
    if (size <= pool->max) {
        // 从内存池中分配一块小内存，第三个参数 1 表示内存对齐
        return ngx_palloc_small(pool, size, 1);
    }
#endif

    // 否则，从内存池中分配一块大内存
    return ngx_palloc_large(pool, size);
}


/*
 * 内存分配函数(不需要内存对齐)
 * 参数：
 *   pool: 指向内存池的指针
 *   size: 需要分配的内存大小
 * 返回值：
 *   返回一个指向分配的内存的指钩
 */
void *
ngx_pnalloc(ngx_pool_t *pool, size_t size)
{
#if !(NGX_DEBUG_PALLOC)
    // 如果请求的内存大小小于等于内存池中可分配的最大内存大小
    if (size <= pool->max) {
        // 从内存池中分配一块小内存，第三个参数 0 表示不需要内存对齐
        return ngx_palloc_small(pool, size, 0);
    }
#endif

    // 否则，从内存池中分配一块大内存
    return ngx_palloc_large(pool, size);
}


/*
 * 小块内存分配函数，支持内存对齐
 * 参数：
 *   pool: 指向内存池的指针
 *   size: 需要分配的内存大小
 *   align: 1 表示需要内存对齐，0 表示不需要对齐
 * 返回值：
 *   返回一个指向分配的内存的指针
 */
static ngx_inline void *
ngx_palloc_small(ngx_pool_t *pool, size_t size, ngx_uint_t align)
{
    u_char      *m; // 用于保存分配的内存的起始地址
    ngx_pool_t  *p; // 用于遍历内存池

    p = pool->current;  // 从当前内存池开始遍历

    do {
        m = p->d.last;  // 获取内存池中当前可用内存的开始位置

        if (align) {
            // 将 m 向上对齐到 NGX_ALIGNMENT 的倍数
            m = ngx_align_ptr(m, NGX_ALIGNMENT);
        }

        // 如果当前内存池的剩余内存足够分配 size 大小的内存
        if ((size_t) (p->d.end - m) >= size) {
            // 更新内存池中当前可用内存的开始位置
            p->d.last = m + size;

            return m;   // 返回分配的内存的起始地址
        }

        // 如果当前内存池的剩余内存不足以分配 size 大小的内存
        // 继续向下一个内存池查找
        p = p->d.next;

    } while (p);    // 直到遍历完所有内存池都没有找到合适的内存块

    // 如果所有内存池都没有找到合适的内存块，那么调用 ngx_palloc_block 函数分配一块新的内存池，并返回分配的内存的起始地址（不是新的内存池的起始地址！！！也不是新的内存池可用内存的起始地址！！！）
    return ngx_palloc_block(pool, size);
}


/*
 * 分配一块新的内存池
 * 参数：
 *   pool: 指向内存池的指针
 *   size: 需要分配的内存大小
 * 返回值：
 *   返回一个指向分配的内存的指针
 */
static void *
ngx_palloc_block(ngx_pool_t *pool, size_t size)
{
    u_char      *m;         // 用于保存分配的内存的起始地址
    size_t       psize;     // 新的内存池的大小
    ngx_pool_t  *p, *new;   // p 用于遍历内存池，new 指向新的内存池

    // 计算新的内存池的大小，与传入内存池的大小相同
    psize = (size_t) (pool->d.end - (u_char *) pool);

    // 调用 ngx_memalign 函数分配一块对齐的内存，大小为 psize
    m = ngx_memalign(NGX_POOL_ALIGNMENT, psize, pool->log);
    if (m == NULL) {
        return NULL;
    }

    // 初始化新的内存池
    new = (ngx_pool_t *) m;

    new->d.end = m + psize;
    new->d.next = NULL;
    new->d.failed = 0;

    // 让 m 指向新内存池可用内存的起始位置, 存储结果，最后返回出去
    m += sizeof(ngx_pool_data_t);
    m = ngx_align_ptr(m, NGX_ALIGNMENT);
    new->d.last = m + size; // 更新内存池中当前可用内存的开始位置

    // 遍历内存池，找到最后一个内存池
    for (p = pool->current; p->d.next; p = p->d.next) {
        if (p->d.failed++ > 4) {
            // 如果当前内存池的内存分配失败次数超过4次，那么将当前内存池的指针指向下一个内存池
            pool->current = p->d.next;
        }
    }

    // 将最后一个内存池的指针指向新的内存池，尾插
    p->d.next = new;

    // 返回分配的内存的起始地址
    return m;
}


/*
 * 分配大块内存
 * 参数：
 *   pool: 指向内存池的指针
 *   size: 需要分配的内存大小
 * 返回值：
 *   返回一个指向分配的内存的指针
 */
static void *
ngx_palloc_large(ngx_pool_t *pool, size_t size)
{
    void              *p;       // 保存分配的内存的起始地址
    ngx_uint_t         n;       // 用于计数
    ngx_pool_large_t  *large;   // 遍历大块内存

    p = ngx_alloc(size, pool->log);
    if (p == NULL) {
        return NULL;
    }

    n = 0;

    // 遍历内存池中的大块内存
    for (large = pool->large; large; large = large->next) {
        if (large->alloc == NULL) {
            // 如果找到一个未分配的大块内存，那么将分配的内存的起始地址赋值给 alloc
            large->alloc = p;
            return p;
        }

        if (n++ > 3) { // 最多查 4 次
            break;
        }
    }

    // 在内存池分配的小块内存中分配一块 ngx_pool_large_t 结构体大小的内存
    // 用于记录分配的大块内存的信息
    large = ngx_palloc_small(pool, sizeof(ngx_pool_large_t), 1);
    if (large == NULL) {
        // 内存池中小块内存区域不足，释放分配的大块内存
        ngx_free(p);
        return NULL;
    }

    // 将分配的内存的起始地址赋值给 alloc
    large->alloc = p;
    // 将新分配的大块内存插入到内存池的大块内存链表的头部
    large->next = pool->large;
    pool->large = large;

    return p;   // 返回分配的大块内存的起始地址
}


/*
 * ngx_pfree 是一个函数，用于在内存池中释放一块大内存。
 * 参数：
 *   pool: 指向内存池的指针
 *   p: 指向需要释放的大内存的指针
 * 返回值：
 *   如果成功释放内存，返回NGX_OK；如果没有找到需要释放的内存，返回NGX_DECLINED
 */
ngx_int_t
ngx_pfree(ngx_pool_t *pool, void *p)
{
    ngx_pool_large_t  *l;

    // 遍历内存池中的所有大内存
    for (l = pool->large; l; l = l->next) {
        // 如果找到了需要释放的内存
        if (p == l->alloc) {
            // 记录一条调试日志
            ngx_log_debug1(NGX_LOG_DEBUG_ALLOC, pool->log, 0,
                           "free: %p", l->alloc);
            // 释放内存
            ngx_free(l->alloc);
            // 将指针设置为NULL
            l->alloc = NULL;

            // 返回成功
            return NGX_OK;
        }
    }

    // 如果没有找到需要释放的内存，返回失败
    return NGX_DECLINED;
}


/*
 * 内存分配函数，调用 ngx_palloc 分配对齐的内存，并支持内存初始化0
 * 参数：
 *   pool: 指向内存池的指针
 *   size: 需要分配的内存大小
 * 返回值：
 *   返回一个指向分配的内存的指针
 */
void *
ngx_pcalloc(ngx_pool_t *pool, size_t size)
{
    void *p;

    p = ngx_palloc(pool, size);
    if (p) {
        ngx_memzero(p, size); // 将分配的内存初始化为0
    }

    return p;   // 返回分配的内存的指针，如果分配失败，返回NULL
}


/*
 * ngx_pool_cleanup_add 是一个函数，用于在内存池中添加一个清理操作。
 * 参数：
 *   p: 指向内存池的指针
 *   size: 清理操作的数据大小
 * 返回值：
 *   返回一个指向新添加的清理操作的指针，如果内存分配失败，返回NULL
 */
ngx_pool_cleanup_t *
ngx_pool_cleanup_add(ngx_pool_t *p, size_t size)
{
    ngx_pool_cleanup_t  *c;

    // 从内存池中分配一块内存，用于存储清理操作
    c = ngx_palloc(p, sizeof(ngx_pool_cleanup_t));
    // 如果内存分配失败，返回NULL
    if (c == NULL) {
        return NULL;
    }

    // 如果指定了清理操作的数据大小
    if (size) {
        // 从内存池中分配一块内存，用于存储清理操作的数据
        c->data = ngx_palloc(p, size);
        // 如果内存分配失败，返回NULL
        if (c->data == NULL) {
            return NULL;
        }

    // 如果没有指定清理操作的数据大小，将数据指针设置为NULL
    } else {
        c->data = NULL;
    }

    // 初始化清理操作的处理函数和下一个清理操作的指针
    c->handler = NULL;
    c->next = p->cleanup;

    // 将新添加的清理操作添加到内存池的清理操作链表的头部
    p->cleanup = c;

    // 记录一条调试日志，表示添加了一个清理操作
    ngx_log_debug1(NGX_LOG_DEBUG_ALLOC, p->log, 0, "add cleanup: %p", c);

    // 返回新添加的清理操作
    return c;
}
```

### 3.2.1 `ngx_memalign(NGX_POOL_ALIGNMENT, size, log);` 函数的实现

```cpp
#if (NGX_HAVE_POSIX_MEMALIGN || NGX_HAVE_MEMALIGN)

void *ngx_memalign(size_t alignment, size_t size, ngx_log_t *log);

#else

// 如果系统不支持posix_memalign或memalign函数，那么ngx_memalign就是一个宏，它直接调用ngx_alloc函数分配内存
#define ngx_memalign(alignment, size, log)  ngx_alloc(size, log)

#endif


/* -----------------ngx_alloc 函数的实现------------------- */
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


/* -----------------ngx_memalign 函数的实现------------------- */

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

### 3.2.2 nginx 内存释放问题

> - nginx 大块内存通过 `ngx_pfree` 函数释放
> - 小块内存看似没有提供任何的内存释放函数，这是因为直接通过 `last` 指针偏移来分配内存，无法进行小块内存的回收。**但是，`ngx_reset_pool` 函数可以重置内存池，等待下一次请求。**
>
> **nginx 的本质是一个 http 的短链接服务器**
>   - 客户端（浏览器）发起一个 `request` 请求，到达 `nginx` 服务器，处理完成后 `nginx` 给客户端返回一个 `response` 响应，`http(nginx)` 服务器主动断开 `tcp` 连接。
>   - 对于 `http 1.1` 的 `keep-avlie: 60s`
>       - http(nginx) 服务器返回响应以后，需要等待 60s，60s 之内客户端又发来请求，时间重置。
>       - 否则 60s 之后，nginx 就主动断开连接，此时 nginx 可以调用 `ngx_reset_pool` 函数，重置内存池，等待下一次请求。


## 3.3 编译测试 nginx 内存池功能


## 3.4 手写 nginx 内存池

```cpp
```