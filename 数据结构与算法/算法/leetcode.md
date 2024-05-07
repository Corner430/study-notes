- [1 数组](#1-数组)
  - [1.1 二分查找](#11-二分查找)
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

### 1.1 二分查找

#### [704. 二分查找](https://leetcode.cn/problems/binary-search/description/)

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

***js***
```js
var search = function (nums, target) {
    let l = 0, r = nums.length - 1; // []
    while (l <= r) {
        let mid = (r + l) >> 1;
        if (nums[mid] === target) return mid;
        else if (nums[mid] < target)
            l = mid + 1;
        else r = mid - 1;
    }
    return -1;
};
```

#### [35. 搜索插入位置](https://leetcode.cn/problems/search-insert-position/description/)

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

***js***
```js
var searchInsert = function (nums, target) {
    let left = 0, right = nums.length - 1;
    while (left <= right) {
        let mid = (left + right) >> 1;
        if (nums[mid] === target)
            return mid;
        else if (nums[mid] < target)
            left = mid + 1;
        else right = mid - 1;
    }
    return left;
};
```

#### [34. 在排序数组中查找元素的第一个和最后一个位置](https://leetcode-cn.com/problems/find-first-and-last-position-of-element-in-sorted-array/description/)

***python***
```python
class Solution:
    def searchRange(self, nums: List[int], target: int) -> List[int]:
        left, right = 0, len(nums) - 1  # []

        def getLeftBound(nums, target):
            nonlocal left, right
            while left <= right:
                mid = left + (right - left) // 2
                if nums[mid] >= target:
                    right = mid - 1
                else:
                    left = mid + 1
            if left < len(nums) and nums[left] == target:
                return left
            return -1

        def getRightBound(nums, target):
            nonlocal left, right
            right = len(nums) - 1
            while left <= right:
                mid = left + (right - left) // 2
                if nums[mid] <= target:
                    left = mid + 1
                else:
                    right = mid - 1
            return right

        leftBound = getLeftBound(nums, target)
        if leftBound == -1:
            return [-1, -1]
        return [leftBound, getRightBound(nums, target)]
```

***cpp***
```cpp
class Solution {
public:
    int left = 0, right;
    int findLeftBound(const vector<int>& nums, const int& target) {
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] >= target)
                right = mid - 1;
            else
                left = mid + 1;
        }
        if (left < nums.size() && nums[left] == target)
            return left;
        return -1;
    }

    int findRightBound(const vector<int>& nums, const int& target) {
        right = nums.size() - 1; // []
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] <= target)
                left = mid + 1;
            else
                right = mid - 1;
        }
        return right;
    }

    vector<int> searchRange(vector<int>& nums, int target) {
        right = nums.size() - 1; // []
        int leftBound = findLeftBound(nums, target);
        if (leftBound == -1)
            return {-1, -1};
        return {leftBound, findRightBound(nums, target)};
    }
};
```

***js***
```js
var searchLeftBound = function (nums, target) {
    while (left <= right) {
        let mid = (left + right) >> 1;
        if (nums[mid] >= target)
            right = mid - 1;
        else
            left = mid + 1;
    }
    if (left < nums.length && nums[left] === target)
        return left;
    return -1;
};

var searchRightBound = function (nums, target) {
    right = nums.length - 1;
    while (left <= right) {
        let mid = (left + right) >> 1;
        if (nums[mid] <= target)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return right;
};

var searchRange = function (nums, target) {
    left = 0;
    right = nums.length - 1;
    let leftBound = searchLeftBound(nums, target);
    if (leftBound === -1) return [-1, -1];
    return [leftBound, searchRightBound(nums, target)];
};
```


#### [69. x 的平方根](https://leetcode-cn.com/problems/sqrtx/description/)

***python***
```python
class Solution:
    def mySqrt(self, x: int) -> int:
        if x == 0:
            return x
        left, right = 1, x
        while left <= right:
            mid = left + (right - left) // 2
            if x // mid == mid:
                return mid
            elif x // mid > mid:
                left = mid + 1
            else :
                right = mid - 1
        return right
```

***cpp***
```cpp
class Solution {
public:
    int mySqrt(int x) {
        if (x == 0)
            return 0;
        int left = 1, right = x;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (x / mid == mid) // 防止数值溢出
                return mid;
            else if (x / mid > mid)
                left = mid + 1;
            else
                right = mid - 1;
        }
        return right;
    }
};
```

***js***
```js
var mySqrt = function (x) {
    if (x === 0) return x;
    let left = 1, right = x;
    while (left <= right) {
        let mid = left + ((right - left) >> 1);
        if (mid === Math.floor(x / mid))
            return mid;
        else if (mid < Math.floor(x / mid))
            left = mid + 1;
        else
            right = mid - 1;
    }
    return right;
};
```

#### [367. 有效的完全平方数](https://leetcode-cn.com/problems/valid-perfect-square/description/)

***python***
```python
class Solution:
    def isPerfectSquare(self, num: int) -> bool:
        left, right = 1, num
        while left <= right:
            mid = left + (right - left) // 2
            if mid * mid == num:
                return True
            elif mid * mid < num:
                left = mid + 1
            else:
                right = mid - 1
        return False
```

***cpp***
```cpp
class Solution {
public:
    bool isPerfectSquare(int num) {
        int left = 1, right = num;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if ((long)mid * mid == num)
                return true;
            else if ((long)mid * mid < num)
                left = mid + 1;
            else
                right = mid - 1;
        }
        return false;
    }
};
```

***js***
```js
var isPerfectSquare = function (num) {
    let left = 1, right = num;
    while (left <= right) {
        let mid = left + ((right - left) >> 1);
        if (mid * mid == num)
            return true;
        else if (mid * mid < num)
            left = mid + 1;
        else right = mid - 1;
    }
    return false;
};
```

#### [27. 移除元素](https://leetcode-cn.com/problems/remove-element/description/)

***python***
```python
class Solution(object):
    def removeElement(self, nums, val):
        left, right  = 0, len(nums) - 1
        while left <= right:
            while left <= right and nums[left] != val:
                left += 1
            while left <= right and nums[right] == val:
                right -= 1
            if left <= right:
                nums[left] = nums[right]
                left += 1
                right -= 1
        return left
```

***cpp***
```cpp
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int left = 0, right = nums.size() - 1; // []
        while (left <= right) {
            while (left <= right && nums[left] != val)
                left++;
            while (left <= right && nums[right] == val)
                right--;
            if (left <= right)
                nums[left++] = nums[right--];
        }
        return left;
    }
};
```

***js***
```js
var removeElement = function(nums, val) {
    let slow = 0, fast = 0;
    for(; fast < nums.length; fast++)
        if (nums[fast] != val)
            nums[slow++] = nums[fast];
    return slow;
};
```

#### [26. 删除排序数组中的重复项](https://leetcode.cn/problems/remove-duplicates-from-sorted-array/description/)

***python***

```python
class Solution:
    def removeDuplicates(self, nums: List[int]) -> int:
        slow, fast = 0, 0
        while fast < len(nums):
            if fast < len(nums) - 1 and nums[fast] == nums[fast + 1]:
                fast += 1
                continue
            else:
                nums[slow] = nums[fast]
                slow += 1
                fast += 1
        return slow
```

***cpp***

```cpp
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int slow = 0, fast = 0;
        while (fast < nums.size()) {
            if (fast < nums.size() - 1 && nums[fast] == nums[fast + 1]){
                fast++;
                continue;
            }
            else
                nums[slow++] = nums[fast];
            fast++;
        }
        return slow;
    }
};
```

***js***
```js
var removeDuplicates = function(nums) {
    let slow = 1, fast = 0;
    while (fast < nums.length){
        if (fast > 0 && nums[fast] != nums[fast - 1])
            nums[slow++] = nums[fast];
        fast++;
    }
    return slow;
};
```

#### [283. 移动零](https://leetcode-cn.com/problems/move-zeroes/description/)

***python***

```python
class Solution:
    def moveZeroes(self, nums: List[int]) -> None:
        slow, fast = 0, 0
        while fast < len(nums):
            if nums[fast]:
                nums[slow] = nums[fast]
                slow += 1
            fast += 1
        while slow < len(nums):
            nums[slow] = 0
            slow += 1
```

***cpp***

```cpp
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int slow = 0, fast = 0;
        for(; fast < nums.size(); fast++)
            if(nums[fast])
                nums[slow++] = nums[fast];

        while(slow < nums.size())
            nums[slow++] = 0;
    }
};
```

***js***
```js
var moveZeroes = function (nums) {
    let slow = 0, fast = 0;
    for (; fast < nums.length; fast++)
        if (nums[fast] != 0)
            nums[slow++] = nums[fast];

    while (slow < nums.length)
        nums[slow++] = 0;
};
```

#### [844. 比较含退格的字符串](https://leetcode-cn.com/problems/backspace-string-compare/description/)

***python***

```python
class Solution:
    def backspaceCompare(self, s: str, t: str) -> bool:
        def modify(S):
            stack = []
            for char in S:
                if char != '#':
                    stack.append(char)
                elif stack:
                    stack.pop()
            return ''.join(stack)

        return modify(s) == modify(t)


# ----------------------------
class Solution:
    def backspaceCompare(self, s: str, t: str) -> bool:
        return self.modifyString(s) == self.modifyString(t)
    
    def modifyString(self, s: str) -> str:
        slow, fast = 0, 0
        s_list = list(s)
        while fast < len(s_list):
            if s_list[fast] != '#':
                s_list[slow] = s_list[fast]
                slow += 1
            elif slow > 0:
                slow -= 1

            fast += 1
        return ''.join(s_list[:slow])
```

***cpp***

```cpp
class Solution
{
public:
    bool backspaceCompare(string s, string t)
    {
        modifyString(s);
        modifyString(t);
        return s == t;
    }

private:
    void modifyString(string &s)
    {
        int slow = 0, fast = 0;
        for (; fast < s.length(); ++fast)
            if (s[fast] == '#' && slow > 0)
                --slow;
            else if (s[fast] != '#')
                s[slow++] = s[fast];
        s.resize(slow);
    }
};
```

***js***
```js
var backspaceCompare = function (s, t) {
    modify = function (s) {
        let slow = 0, sArr = s.split('');
        for (let fast = 0; fast < sArr.length; fast++) {
            if (sArr[fast] != '#')
                sArr[slow++] = sArr[fast];
            else if (slow > 0)
                slow--;
        }
        sArr.length = slow;
        return sArr.join('');
    }
    s = modify(s);
    t = modify(t);
    return s == t;
};
```

#### [977. 有序数组的平方](https://leetcode-cn.com/problems/squares-of-a-sorted-array/description/)

***python***

```python

```

***cpp***

```cpp

```

***js***

```js

```

#### [209. 长度最小的子数组](https://leetcode-cn.com/problems/minimum-size-subarray-sum/description/)

***python***

```python

```

***cpp***

```cpp

```

#### [904. 水果成篮](https://leetcode-cn.com/problems/fruit-into-baskets/description/)

***python***

```python

```

***cpp***

```cpp

```

#### [76. 最小覆盖子串](https://leetcode-cn.com/problems/minimum-window-substring/description/)

***python***

```python

```

***cpp***

```cpp

```

#### [59. 螺旋矩阵 II](https://leetcode-cn.com/problems/spiral-matrix-ii/description/)

***python***

```python

```

***cpp***

```cpp

```

#### [54. 螺旋矩阵](https://leetcode-cn.com/problems/spiral-matrix/description/)

***python***

```python

```

***cpp***

```cpp

```

#### [剑指Offer 29. 顺时针打印矩阵](https://leetcode-cn.com/problems/shun-shi-zhen-da-yin-ju-zhen-lcof/description/)

***python***

```python

```

***cpp***

```cpp

```

#### [167. 两数之和 II - 输入有序数组](https://leetcode-cn.com/problems/two-sum-ii-input-array-is-sorted/description/)

***python***

```python

```

***cpp***

```cpp

```

#### [344. 反转字符串](https://leetcode-cn.com/problems/reverse-string/description/)

***python***

```python

```

***cpp***

```cpp

```

#### [5. 最长回文子串](https://leetcode-cn.com/problems/longest-palindromic-substring/description/)

***python***

```python

```

***cpp***

```cpp

```

#### [83. 删除排序链表中的重复元素](https://leetcode-cn.com/problems/remove-duplicates-from-sorted-list/description/)

***python***

```python

```

***cpp***

```cpp

```

#### [剑指 Offer 57. 和为s的两个数字](https://leetcode-cn.com/problems/he-wei-sde-liang-ge-shu-zi-lcof/description/)

[]()

#### [剑指 Offer II 006. 排序数组中两个数字之和](https://leetcode-cn.com/problems/two-sum-ii-input-array-is-sorted/description/)

[]()