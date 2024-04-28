- [1 数组](#1-数组)
  - [704. 二分查找](#704-二分查找)
  - [35. 搜索插入位置](#35-搜索插入位置)
  - [34. 在排序数组中查找元素的第一个和最后一个位置](#34-在排序数组中查找元素的第一个和最后一个位置)
  - [69. x 的平方根](#69-x-的平方根)
  - [367. 有效的完全平方数](#367-有效的完全平方数)
  - [27. 移除元素](#27-移除元素)
  - [26. 删除排序数组中的重复项](#26-删除排序数组中的重复项)
  - [283. 移动零](#283-移动零)
  - [844. 比较含退格的字符串](#844-比较含退格的字符串)
  - [977. 有序数组的平方](#977-有序数组的平方)
  - [209. 长度最小的子数组](#209-长度最小的子数组)
  - [904. 水果成篮](#904-水果成篮)
  - [76. 最小覆盖子串](#76-最小覆盖子串)
  - [59. 螺旋矩阵 II](#59-螺旋矩阵-ii)
  - [54. 螺旋矩阵](#54-螺旋矩阵)
  - [剑指Offer 29. 顺时针打印矩阵](#剑指offer-29-顺时针打印矩阵)
  - [167. 两数之和 II - 输入有序数组](#167-两数之和-ii---输入有序数组)
  - [344. 反转字符串](#344-反转字符串)
  - [5. 最长回文子串](#5-最长回文子串)
  - [83. 删除排序链表中的重复元素](#83-删除排序链表中的重复元素)
  - [剑指 Offer 57. 和为s的两个数字](#剑指-offer-57-和为s的两个数字)
  - [剑指 Offer II 006. 排序数组中两个数字之和](#剑指-offer-ii-006-排序数组中两个数字之和)


## 1 数组

### [704. 二分查找](https://leetcode.cn/problems/binary-search/description/)

***python***

```python
class Solution:
    def search(self, nums: List[int], target: int) -> int:
        left, right = 0, len(nums) - 1  # []
        while left <= right:
            mid = left + (right - left) // 2
            if nums[mid] == target:
                return mid
            elif nums[mid] < target:
                left = mid + 1
            else:
                right = mid - 1
        return -1
```

***cpp***

```cpp
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1; // []
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] == target)
                return mid;
            else if (nums[mid] < target)
                left = mid + 1;
            else
                right = mid - 1;
        }
        return -1;
    }
};
```

### [35. 搜索插入位置](https://leetcode.cn/problems/search-insert-position/description/)

***python***

```python
class Solution:
    def searchInsert(self, nums: List[int], target: int) -> int:
        left, right = 0, len(nums) - 1
        while left <= right:
            mid = left + (right - left) // 2
            if nums[mid] == target:
                return mid
            elif nums[mid] > target:
                right = mid - 1
            else :
                left = mid + 1
        return left
```

***cpp***

```cpp
class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1; // []
        while(left <= right){
            int mid = left + (right - left) / 2;
            if (nums[mid] == target)
                return mid;
            else if (nums[mid] > target)
                right = mid - 1;
            else 
                left = mid + 1;
        }
        return left;
    }
};
```

### [34. 在排序数组中查找元素的第一个和最后一个位置](https://leetcode-cn.com/problems/find-first-and-last-position-of-element-in-sorted-array/description/)

***python***

```python

```

***cpp***

```cpp

```

### [69. x 的平方根](https://leetcode-cn.com/problems/sqrtx/description/)

***python***

```python

```

***cpp***

```cpp

```

### [367. 有效的完全平方数](https://leetcode-cn.com/problems/valid-perfect-square/description/)

***python***

```python

```

***cpp***

```cpp

```

### [27. 移除元素](https://leetcode-cn.com/problems/remove-element/description/)

***python***

```python

```

***cpp***

```cpp

```

### [26. 删除排序数组中的重复项](https://leetcode.cn/problems/remove-duplicates-from-sorted-array/description/)

***python***

```python

```

***cpp***

```cpp

```

### [283. 移动零](https://leetcode-cn.com/problems/move-zeroes/description/)

***python***

```python

```

***cpp***

```cpp

```

### [844. 比较含退格的字符串](https://leetcode-cn.com/problems/backspace-string-compare/description/)

***python***

```python

```

***cpp***

```cpp

```

### [977. 有序数组的平方](https://leetcode-cn.com/problems/squares-of-a-sorted-array/description/)

***python***

```python

```

***cpp***

```cpp

```

### [209. 长度最小的子数组](https://leetcode-cn.com/problems/minimum-size-subarray-sum/description/)

***python***

```python

```

***cpp***

```cpp

```

### [904. 水果成篮](https://leetcode-cn.com/problems/fruit-into-baskets/description/)

***python***

```python

```

***cpp***

```cpp

```

### [76. 最小覆盖子串](https://leetcode-cn.com/problems/minimum-window-substring/description/)

***python***

```python

```

***cpp***

```cpp

```

### [59. 螺旋矩阵 II](https://leetcode-cn.com/problems/spiral-matrix-ii/description/)

***python***

```python

```

***cpp***

```cpp

```

### [54. 螺旋矩阵](https://leetcode-cn.com/problems/spiral-matrix/description/)

***python***

```python

```

***cpp***

```cpp

```

### [剑指Offer 29. 顺时针打印矩阵](https://leetcode-cn.com/problems/shun-shi-zhen-da-yin-ju-zhen-lcof/description/)

***python***

```python

```

***cpp***

```cpp

```

### [167. 两数之和 II - 输入有序数组](https://leetcode-cn.com/problems/two-sum-ii-input-array-is-sorted/description/)

***python***

```python

```

***cpp***

```cpp

```

### [344. 反转字符串](https://leetcode-cn.com/problems/reverse-string/description/)

***python***

```python

```

***cpp***

```cpp

```

### [5. 最长回文子串](https://leetcode-cn.com/problems/longest-palindromic-substring/description/)

***python***

```python

```

***cpp***

```cpp

```

### [83. 删除排序链表中的重复元素](https://leetcode-cn.com/problems/remove-duplicates-from-sorted-list/description/)

***python***

```python

```

***cpp***

```cpp

```

### [剑指 Offer 57. 和为s的两个数字](https://leetcode-cn.com/problems/he-wei-sde-liang-ge-shu-zi-lcof/description/)

[]()

### [剑指 Offer II 006. 排序数组中两个数字之和](https://leetcode-cn.com/problems/two-sum-ii-input-array-is-sorted/description/)

[]()