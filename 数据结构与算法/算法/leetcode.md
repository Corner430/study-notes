## 1 数组

### [704. 二分查找](https://leetcode.cn/problems/binary-search/description/)

给定一个 `n` 个元素有序的（升序）整型数组 `nums` 和一个目标值 `target`  ，写一个函数搜索 `nums` 中的 `target`，如果目标值存在返回下标，否则返回 `-1`。

**示例 1:**

输入: `nums = [-1,0,3,5,9,12]`, `target = 9`
输出: `4`
解释: `9` 出现在 `nums` 中并且下标为 `4`

**示例 2:**

输入: `nums = [-1,0,3,5,9,12]`, `target = 2`
输出: `-1`
解释: `2` 不存在 `nums` 中因此返回 `-1`

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

给定一个排序数组和一个目标值，在数组中找到目标值，并返回其索引。如果目标值不存在于数组中，返回它将会被按顺序插入的位置。

请必须使用时间复杂度为 `O(log n)` 的算法。

**示例 1:**

输入：`nums = [1,3,5,6]`, `target = 5`
输出：`2`

**示例 2:**

输入：`nums = [1,3,5,6]`, `target = 2`
输出：`1`

**示例 3:**

输入：`nums = [1,3,5,6]`, `target = 7`
输出：`4`

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

给定一个按照升序排列的整数数组 `nums`，和一个目标值 `target`。找出给定目标值在数组中的开始位置和结束位置。

如果数组中不存在目标值 `target`，返回 `[-1, -1]`。

**进阶：**

你可以设计并实现时间复杂度为 `O(log n)` 的算法解决此问题吗？

**示例 1:**

输入：`nums = [5,7,7,8,8,10]`, `target = 8`
输出：`[3,4]`

**示例 2:**

输入：`nums = [5,7,7,8,8,10]`, `target = 6`
输出：`[-1,-1]`

***python***

```python

```

***cpp***

```cpp

```

