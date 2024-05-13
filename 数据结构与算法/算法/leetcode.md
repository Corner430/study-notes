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
- [2 链表](#2-链表)
  - [83. 删除排序链表中的重复元素](#83-删除排序链表中的重复元素)
  - [203.移除链表元素](#203移除链表元素)
  - [707. 设计链表](#707-设计链表)
  - [206.反转链表](#206反转链表)
  - [92. 反转链表 II](#92-反转链表-ii)
  - [25. K 个一组翻转链表](#25-k-个一组翻转链表)
  - [24. 两两交换链表中的节点](#24-两两交换链表中的节点)
  - [19.删除链表的倒数第N个节点](#19删除链表的倒数第n个节点)
  - [面试题 02.07. 链表相交](#面试题-0207-链表相交)
  - [141. 环形链表](#141-环形链表)
  - [142.环形链表II](#142环形链表ii)
  - [21. 合并两个有序链表](#21-合并两个有序链表)
  - [23. 合并 K 个升序链表](#23-合并-k-个升序链表)
  - [86. 分隔链表](#86-分隔链表)
  - [876. 链表的中间结点](#876-链表的中间结点)
  - [234. 回文链表](#234-回文链表)
  - [1553. 吃掉 N 个橘子的最少天数](#1553-吃掉-n-个橘子的最少天数)


## 1 数组

### 704. 二分查找

[704. 二分查找](https://leetcode.cn/problems/binary-search/description/)

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

### 35. 搜索插入位置

[35. 搜索插入位置](https://leetcode.cn/problems/search-insert-position/description/)

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

### 34. 在排序数组中查找元素的第一个和最后一个位置

[34. 在排序数组中查找元素的第一个和最后一个位置](https://leetcode-cn.com/problems/find-first-and-last-position-of-element-in-sorted-array/description/)

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


### 69. x 的平方根

[69. x 的平方根](https://leetcode-cn.com/problems/sqrtx/description/)

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

### 367. 有效的完全平方数

[367. 有效的完全平方数](https://leetcode-cn.com/problems/valid-perfect-square/description/)

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

### 27. 移除元素

[27. 移除元素](https://leetcode-cn.com/problems/remove-element/description/)

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

### 26. 删除排序数组中的重复项

[26. 删除排序数组中的重复项](https://leetcode.cn/problems/remove-duplicates-from-sorted-array/description/)

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

### 283. 移动零

[283. 移动零](https://leetcode-cn.com/problems/move-zeroes/description/)

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

### 844. 比较含退格的字符串

[844. 比较含退格的字符串](https://leetcode-cn.com/problems/backspace-string-compare/description/)

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

### 977. 有序数组的平方

[977. 有序数组的平方](https://leetcode-cn.com/problems/squares-of-a-sorted-array/description/)

***python***

```python
class Solution:
    def sortedSquares(self, nums: List[int]) -> List[int]:
        res = [0] * len(nums)
        nums = [num * num for num in nums]
        i, j, k = 0, len(nums) - 1, len(nums) - 1
        while k >= 0:
            if nums[i] >= nums[j]:
                res[k] = nums[i]
                i += 1
            else:
                res[k] = nums[j]
                j -= 1
            k -= 1
        return res
```

***cpp***

```cpp
class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        for (int& num : nums)
            num = num * num;

        vector<int> res(nums.size());
        for (int i = 0, j = nums.size() - 1, k = j; k >= 0; --k)
            nums[i] >= nums[j] ? res[k] = nums[i++] : res[k] = nums[j--];

        return res;
    }
};
```

***js***

```js
/**
 * @param {number[]} nums
 * @return {number[]}
 */
var sortedSquares = function (nums) {
    // 将 nums 数组中的每个元素取平方，并生成一个新的数组
    nums = nums.map(num => num * num)
    let res = new Array(nums.length);
    let i = 0, j = nums.length - 1, k = nums.length - 1;
    while (k >= 0) {
        if (nums[i] >= nums[j]) {
            res[k] = nums[i];
            i++;
        } else {
            res[k] = nums[j];
            j--;
        }
        k--;
    }
    return res;
};
```

### 209. 长度最小的子数组

[209. 长度最小的子数组](https://leetcode-cn.com/problems/minimum-size-subarray-sum/description/)

***python***

```python
class Solution:
    def minSubArrayLen(self, target: int, nums: List[int]) -> int:
        left, right = 0, 0  # [)
        sum = 0
        res = len(nums) + 1
        while right < len(nums):
            while right < len(nums) and sum < target:
                sum += nums[right]
                right += 1
            while sum >= target:
                res = min(res, right - left)
                sum -= nums[left]
                left += 1
        return 0 if res == len(nums) + 1 else res
```

***cpp***

```cpp
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int res = INT32_MAX;
        int sum = 0;
        for (size_t i = 0, j = 0; i < nums.size(); ++i) {
            sum += nums[i];
            while (sum >= target) {
                int subLength = i - j + 1;
                res = res < subLength ? res : subLength;
                sum -= nums[j++];
            }
        }
        return res == INT32_MAX ? 0 : res;
    }
};
```

***js***

```js
/**
 * @param {number} target
 * @param {number[]} nums
 * @return {number}
 */
var minSubArrayLen = function (target, nums) {
    let left = 0, right = 0;    // [)
    let sum = 0;
    let res = nums.length + 1;
    while (right < nums.length) {
        sum += nums[right];
        right++;
        while (sum >= target) {
            res = Math.min(res, right - left);  // 注意是Math.min()
            sum -= nums[left++];
        }
    }
    return res === nums.length + 1 ? 0 : res;
};
```

### 904. 水果成篮

[904. 水果成篮](https://leetcode-cn.com/problems/fruit-into-baskets/description/)

***python***

```python
class Solution:
    def totalFruit(self, fruits: List[int]) -> int:
        fruit_map = {}
        left, right = 0, 0
        temp_res, res = 0, 0
        for fruit in fruits:
            if fruit in fruit_map:
                fruit_map[fruit] += 1
            else:
                fruit_map[fruit] = 1
            
            if len(fruit_map) <= 2:
                temp_res += 1
                res = max(res, temp_res)
            else:
                while len(fruit_map) > 2:
                    fruit_map[fruits[left]] -= 1
                    if fruit_map[fruits[left]] == 0:
                        del fruit_map[fruits[left]]
                    left += 1
                temp_res = right - left + 1
            right += 1
        return res
```

***cpp***

```cpp
class Solution {
public:
    int totalFruit(vector<int>& fruits) {
        unordered_map<int, int> umap;
        int res = 0, temp_res = 0;
        int left = 0, right = 0;
        while (right < fruits.size()) {
            ++umap[fruits[right]]; // 加入元素
            right++;

            if (umap.size() <= 2) { // 收获结果
                temp_res += 1;
                res = max(res, temp_res);
            } else {    // 收缩窗口
                while (umap.size() > 2) {
                    --umap[fruits[left]];
                    if (umap[fruits[left]] == 0)
                        umap.erase(fruits[left]);
                    ++left;
                }
                temp_res = right - left;
            }
        }
        return res;
    }
};
```

***js***

```js
/**
 * @param {number[]} fruits
 * @return {number}
 */
var totalFruit = function (fruits) {
    const fruitMap = new Map();
    let res = 0, tempRes = 0;
    let slow = 0, fast = 0;
    for (const fruit of fruits) {
        fruitMap.set(fruit, (fruitMap.get(fruit) || 0) + 1);

        if (fruitMap.size <= 2) {
            tempRes += 1;
            res = Math.max(res, tempRes);
        } else {
            while (fruitMap.size > 2) {
                fruitMap.set(fruits[slow], fruitMap.get(fruits[slow]) - 1);
                if (fruitMap.get(fruits[slow]) === 0) {
                    fruitMap.delete(fruits[slow]);
                }
                slow += 1;
            }
            tempRes = fast - slow + 1;
        }
        fast += 1;
    }
    return res;
};
```

### 76. 最小覆盖子串

[76. 最小覆盖子串](https://leetcode-cn.com/problems/minimum-window-substring/description/)

***python***

```python
class Solution:
    def minWindow(self, s: str, t: str) -> str:
        need = {}
        for c in t:
            if c in need:
                need[c] += 1
            else:
                need[c] = 1
        left, right, start_index = 0, 0, 0
        length = 100001
        invalid = len(need)

        while right < len(s):
            # 扩大窗口
            if s[right] in need:
                need[s[right]] -= 1
                if need[s[right]] == 0:
                    invalid -= 1
            right += 1

            while invalid == 0:
                # 缩小窗口
                if s[left] in need:
                    need[s[left]] += 1
                    if need[s[left]] > 0:
                        invalid += 1
                        if right - left < length: # 收获结果
                            start_index = left
                            length = right - left
                left += 1
        return "" if length == 100001 else s[start_index:start_index + length]
        
```

***cpp***

```cpp
class Solution {
public:
    string minWindow(string s, string t) {
        unordered_map<char, int> umap;
        for (char c : t)
            umap[c]++;
        int left = 0, right = 0; // [)
        int invalid = umap.size();
        int start_index = 0, length = 100001;
        while (right < s.size()) {
            // 扩大窗口
            auto it = umap.find(s[right++]);
            if (it != umap.end()) {
                --it->second;
                if (it->second == 0)
                    invalid--;
            }

            // 收缩窗口
            while (invalid == 0) {
                auto it = umap.find(s[left]);
                if (it != umap.end()) {
                    ++it->second;
                    if (it->second > 0) {
                        invalid++;
                        if (right - left < length) { // 收获结果
                            start_index = left;
                            length = right - left;
                        }
                    }
                }
                ++left;
            }
        }
        return length == 100001 ? "" : s.substr(start_index, length);
    }
};
```

***js***

```js
/**
 * @param {string} s
 * @param {string} t
 * @return {string}
 */
var minWindow = function (s, t) {
    let umap = new Map();
    for (let c of t) {
        umap.set(c, (umap.get(c) || 0) + 1);
    }
    let left = 0, right = 0;
    let invalid = umap.size;
    let start_index = 0, length = 100001;

    while (right < s.length) {
        // 扩大窗口
        let char = s[right++];
        if (umap.has(char)) {
            umap.set(char, umap.get(char) - 1);
            if (umap.get(char) === 0) {
                invalid--;
            }
        }

        // 收缩窗口
        while (invalid === 0) {
            let charLeft = s[left];
            if (umap.has(charLeft)) {
                umap.set(charLeft, umap.get(charLeft) + 1);
                if (umap.get(charLeft) > 0) {
                    invalid++;
                    if (right - left < length) { // 收获结果
                        start_index = left;
                        length = right - left;
                    }
                }
            }
            left++;
        }
    }
    return length === 100001 ? "" : s.substr(start_index, length);
};
```

### 59. 螺旋矩阵 II

[59. 螺旋矩阵 II](https://leetcode-cn.com/problems/spiral-matrix-ii/description/)

***python***

```python
class Solution:
    def generateMatrix(self, n: int) -> List[List[int]]:
        res = [[0] * n for _ in range(n)] # 二维数组
        left_bound, right_bound = 0, n - 1
        up_bound, down_bound = 0, n - 1
        count = 1

        while count <= n * n:
            # 上边
            for j in range(left_bound, right_bound + 1):
                res[up_bound][j] = count
                count += 1
            up_bound += 1

            # 右边
            for i in range(up_bound, down_bound + 1):
                res[i][right_bound] = count
                count += 1
            right_bound -= 1

            # 下边
            for j in range(right_bound, left_bound - 1, - 1):
                res[down_bound][j] = count
                count += 1
            down_bound -= 1

            # 左边
            for i in range(down_bound, up_bound - 1, -1):
                res[i][left_bound] = count
                count += 1
            left_bound += 1

        return res
```

***cpp***

```cpp
class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> res(n, vector<int>(n));
        int leftBound = 0, rightBound = n - 1;
        int upBound = 0, downBound = n - 1;
        int count = 1;
        while (count <= n * n) {
            // 上边
            for (int j = leftBound; j <= rightBound; ++j)
                res[upBound][j] = count++;
            upBound++;

            // 右边
            for (int i = upBound; i <= downBound; ++i)
                res[i][rightBound] = count++;
            rightBound--;

            // 下边
            for (int j = rightBound; j >= leftBound; --j)
                res[downBound][j] = count++;
            downBound--;

            // 左边
            for (int i = downBound; i >= upBound; --i)
                res[i][leftBound] = count++;
            leftBound++;
        }
        return res;
    }
};
```

***js***

```js
/**
 * @param {number} n
 * @return {number[][]}
 */
var generateMatrix = function (n) {
    let res = new Array(n).fill().map(() => new Array(n).fill(0));
    let leftBound = 0, rightBound = n - 1;
    let upBound = 0, downBound = n - 1;
    let count = 1;

    while (count <= n * n) {
        // 上边
        for (let j = leftBound; j <= rightBound; j++)
            res[upBound][j] = count++;
        upBound++;

        // 右边
        for (let i = upBound; i <= downBound; i++)
            res[i][rightBound] = count++;
        rightBound--;

        // 下边
        for (let j = rightBound; j >= leftBound; j--)
            res[downBound][j] = count++;
        downBound--;

        // 左边
        for (let i = downBound; i >= upBound; i--)
            res[i][leftBound] = count++;
        leftBound++;
    }
    return res;
};
```

### 54. 螺旋矩阵

[54. 螺旋矩阵](https://leetcode-cn.com/problems/spiral-matrix/description/)

***python***

```python
class Solution:
    def spiralOrder(self, matrix: List[List[int]]) -> List[int]:
        res = []
        m, n = len(matrix), len(matrix[0])
        up_bound, down_bound = 0, m - 1
        left_bound, right_bound = 0, n - 1

        while up_bound <= down_bound and left_bound <= right_bound:
            # 上边
            for j in range(left_bound, right_bound + 1):
                res.append(matrix[up_bound][j])
            up_bound += 1
            if up_bound > down_bound:
                break
            
            # 右边
            for i in range(up_bound, down_bound + 1):
                res.append(matrix[i][right_bound])
            right_bound -= 1
            if left_bound > right_bound:
                break
            
            # 下边
            for j in range(right_bound, left_bound - 1, -1):
                res.append(matrix[down_bound][j])
            down_bound -= 1

            # 左边
            for i in range(down_bound, up_bound - 1, -1):
                res.append(matrix[i][left_bound])
            left_bound += 1
        return res
            
```

***cpp***

```cpp
class Solution {
  public:
  vector<int> spiralOrder(vector<vector<int>>& matrix) {
    vector<int> res;
    int m = matrix.size(), n = matrix[0].size();  // 行 列
    int up_bound = 0, down_bound = m - 1;
    int left_bound = 0, right_bound = n - 1;
    while (up_bound <= down_bound && left_bound <= right_bound)
    {
      // 上
      for (int j = left_bound; j <= right_bound; j++)
        res.push_back(matrix[up_bound][j]);
      up_bound++;
      if (up_bound > down_bound) break;

      // 右
      for (int i = up_bound; i <= down_bound; i++)
        res.push_back(matrix[i][right_bound]);
      right_bound--;
      if (left_bound > right_bound) break;

      // 下
      for (int j = right_bound; j >= left_bound; j--)
        res.push_back(matrix[down_bound][j]);
      down_bound--;

      // 左
      for (int i = down_bound; i >= up_bound; i--)
        res.push_back(matrix[i][left_bound]);
      left_bound++;
    }
    return res;
  }
};
```

***js***

```js
/**
 * @param {number[][]} matrix
 * @return {number[]}
 */
var spiralOrder = function (matrix) {
    let res = [];
    let m = matrix.length, n = matrix[0].length;
    let upBound = 0, downBound = m - 1;
    let leftBound = 0, rightBound = n - 1;

    while (upBound <= downBound && leftBound <= rightBound) {
        // 上
        for (let j = leftBound; j <= rightBound; j++) {
            res.push(matrix[upBound][j]);
        }
        upBound++;
        if (upBound > downBound) break;

        // 右
        for (let i = upBound; i <= downBound; i++) {
            res.push(matrix[i][rightBound]);
        }
        rightBound--;
        if (leftBound > rightBound) break;

        // 下
        for (let j = rightBound; j >= leftBound; j--) {
            res.push(matrix[downBound][j]);
        }
        downBound--;

        // 左
        for (let i = downBound; i >= upBound; i--) {
            res.push(matrix[i][leftBound]);
        }
        leftBound++;
    }
    return res;
};
```

### 剑指Offer 29. 顺时针打印矩阵

[剑指Offer 29. 顺时针打印矩阵](https://leetcode-cn.com/problems/shun-shi-zhen-da-yin-ju-zhen-lcof/description/)

同 [54. 螺旋矩阵](#54-螺旋矩阵)

### 167. 两数之和 II - 输入有序数组

[167. 两数之和 II - 输入有序数组](https://leetcode-cn.com/problems/two-sum-ii-input-array-is-sorted/description/)

***python***

```python
# 左右指针
class Solution:
    def twoSum(self, numbers: List[int], target: int) -> List[int]:
        left, right = 0, len(numbers) - 1
        while left < right:
            sum = numbers[left] + numbers[right]
            if sum == target:
                return [left + 1, right + 1]
            elif sum < target:
                left += 1
            else:
                right -= 1
        return [-1, -1]

# 哈希
class Solution:
    def twoSum(self, numbers: List[int], target: int) -> List[int]:
        umap = {}
        for i, num in enumerate(numbers):
            if target - num in umap:
                return [umap[target - num] + 1, i + 1]
            umap[num] = i
```

***cpp***

```cpp
// 左右指针
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int left = 0, right = numbers.size() - 1;
        while(left < right){
            int sum = numbers[left] + numbers[right];
            if(target == sum) return vector<int> {left+1,right+1};
            else if(target < sum) right--;
            else left++;
        }
        return vector<int> {-1,-1};
    }
};

// 哈希
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        unordered_map<int, int> umap;
        for (int i = 0 ; i < numbers.size(); i++){
            auto it = umap.find(target - numbers[i]);
            if(it != umap.end()) return vector<int> {it->second + 1, i + 1};
            umap[numbers[i]] = i;
        }
        return vector<int> {-1, -1};
    }
};
```

***js***

```js
/**
 * @param {number[]} numbers
 * @param {number} target
 * @return {number[]}
 */
// 左右指针
var twoSum = function (numbers, target) {
    let left = 0, right = numbers.length - 1;
    while (left < right) {
        let sum = numbers[left] + numbers[right];
        if (target === sum) {
            return [left + 1, right + 1];
        } else if (target < sum) {
            right--;
        } else {
            left++;
        }
    }
    return [-1, -1];
};

// 哈希
var twoSum = function (numbers, target) {
    let umap = new Map();
    for (let i = 0; i < numbers.length; i++) {
        if (umap.has(target - numbers[i])) {
            return [umap.get(target - numbers[i]) + 1, i + 1];
        }
        umap.set(numbers[i], i);
    }
};
```

### 344. 反转字符串

[344. 反转字符串](https://leetcode-cn.com/problems/reverse-string/description/)

***python***

```python
class Solution:
    def reverseString(self, s: List[str]) -> None:
        """
        Do not return anything, modify s in-place instead.
        """
        left, right = 0, len(s) - 1
        while left < right:
            s[left], s[right] = s[right], s[left]
            left += 1
            right -= 1
```

***cpp***

```cpp
class Solution {
public:
    void reverseString(vector<char>& s) {
        int i = 0, j = s.size() - 1;
        while (i < j)
            swap(s[i++], s[j--]);
    }
};
```

***js***

```js
/**
 * @param {character[]} s
 * @return {void} Do not return anything, modify s in-place instead.
 */
var reverseString = function (s) {
    let i = 0, j = s.length - 1;
    while (i < j) {
        [s[i], s[j]] = [s[j], s[i]];
        i++;
        j--;
    }
};
```

### 5. 最长回文子串

[5. 最长回文子串](https://leetcode-cn.com/problems/longest-palindromic-substring/description/)

***python***

```python
class Solution:
    def extend(self, s: str, i: int, j: int) -> int:
        res = 0
        while i >= 0 and j < len(s) and s[i] == s[j]:
            if i != j:
                res += 2
            else:
                res += 1
            i -= 1
            j += 1
        return res

    def longestPalindrome(self, s: str) -> str:
        length = 1
        start_index = 0
        for i in range(len(s)):
            length1 = self.extend(s, i, i)
            length2 = self.extend(s, i, i + 1)
            length = max(length, length1, length2)
            if length == length1:
                start_index = i - (length1 - 1) // 2
            elif length == length2:
                start_index = i - length2 // 2 + 1
        return s[start_index : start_index + length]
```

***cpp***

```cpp
class Solution {
private:
  int extend(string &s, int i, int j) {
    int res = 0;
    while (i >= 0 && j < s.size() && s[i] == s[j]) {
      if (i != j)
        res += 2;
      else
        res++;
      i--;
      j++;
    }
    return res;
  }

public:
  string longestPalindrome(string s) {
    int length = 1;
    int startIndex = 0;
    for (int i = 0; i < s.size(); i++) {
      int length1 = extend(s, i, i);
      int length2 = extend(s, i, i + 1);
      length = max({length, length1, length2});
      if (length == length1)
        startIndex = i - (length1 - 1) / 2;
      else if (length == length2)
        startIndex = i - length2 / 2 + 1;
    }
    return s.substr(startIndex, length);
  }
};
```

***js***

```js
/**
 * @param {string} s
 * @return {string}
 */

var extend = function (s, i, j) {
    let res = 0;
    while (i >= 0 && j < s.length && s[i] === s[j]) {
        if (i !== j) {
            res += 2;
        } else {
            res += 1;
        }
        i--;
        j++;
    }
    return res;
}

var longestPalindrome = function (s) {
    let length = 1;
    let startIndex = 0;
    for (let i = 0; i < s.length; i++) {
        let length1 = extend(s, i, i);
        let length2 = extend(s, i, i + 1);
        let lengthTemp = Math.max(length, length1, length2);
        if (lengthTemp === length1) {
            startIndex = i - Math.floor((length1 - 1) / 2);
        } else if (lengthTemp === length2) {
            startIndex = i - Math.floor(length2 / 2) + 1;
        }
        length = lengthTemp;
    }
    return s.substring(startIndex, startIndex + length);
};
```

----------------------------

## 2 链表

### 83. 删除排序链表中的重复元素

[83. 删除排序链表中的重复元素](https://leetcode-cn.com/problems/remove-duplicates-from-sorted-list/description/)

***python***

```python
class Solution:
    def deleteDuplicates(self, head: Optional[ListNode]) -> Optional[ListNode]:
        if not head:
            return head
        p = head
        while p.next:
            if p.next.val == p.val:
                p.next = p.next.next
            else:
                p = p.next
        return head
```

***cpp***

```cpp
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if (!head)
            return head;
        ListNode* p = head;
        while (p->next) {
            if (p->next->val == p->val) {
                ListNode* del = p->next;
                p->next = del->next;
                delete del;
            }else
                p = p->next;
        }
        return head;
    }
};
```

***js***

```js
var deleteDuplicates = function (head) {
     if (!head || !head.next) 
        return head;

    let p = head;
    while (p.next) {
        if (p.next.val === p.val) {
            p.next = p.next.next;
        } else {
            p = p.next;
        }
    }
    return head;
};
```


### 203.移除链表元素

[203.移除链表元素](https://leetcode.cn/problems/remove-linked-list-elements/description/)

***python***
```python
class Solution:
    def removeElements(self, head: Optional[ListNode], val: int) -> Optional[ListNode]:
        dummyHead = ListNode(0, head);
        p = dummyHead;
        while p.next:
            if p.next.val == val:
                p.next = p.next.next
            else:
                p = p.next
        return dummyHead.next
```

***cpp***
```cpp
class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        ListNode* dummyHead = new ListNode(0, head);
        ListNode* p = dummyHead;
        while (p->next) {
            if (p->next->val == val) {
                ListNode* temp = p->next;
                p->next = temp->next;
                delete temp;
            } else
                p = p->next;
        }
        return dummyHead->next;
    }
};
```

***js***
```js
var removeElements = function (head, val) {
    const dummyHead = new ListNode(0, head);
    let p = dummyHead;
    while (p.next) {
        if (p.next.val === val) {
            const temp = p.next;
            p.next = temp.next;
            temp.next = null; // Optional: Helps in garbage collection
        } else {
            p = p.next;
        }
    }
    return dummyHead.next;
};
```

### 707. 设计链表

[707. 设计链表](https://leetcode.cn/problems/design-linked-list/description/)

***python***
```python
class ListNode:
    def __init__(self, val = 0,next = None):
        self.val = val
        self.next = next

class MyLinkedList:

    def __init__(self):
        self.head = None
        self.size = 0

    def get(self, index: int) -> int:
        if index < 0 or index >= self.size:
            return -1
        p = self.head
        for _ in range(index):
            p = p.next
        return p.val

    def addAtHead(self, val: int) -> None:
        self.head = ListNode(val, self.head)
        self.size += 1

    def addAtTail(self, val: int) -> None:
        p = self.head
        while p.next:
            p = p.next
        p.next = ListNode(val)
        self.size += 1

    def addAtIndex(self, index: int, val: int) -> None:
        if index < 0 or index > self.size:
            return
        p = self.head
        for _ in range(index - 1):
            p = p.next
        p.next = ListNode(val, p.next)
        self.size += 1

    def deleteAtIndex(self, index: int) -> None:
        if index < 0 or index >= self.size:
            return
        p = self.head
        for _ in range(index - 1):
            p = p.next
        p.next = p.next.next
        self.size -= 1



# Your MyLinkedList object will be instantiated and called as such:
# obj = MyLinkedList()
# param_1 = obj.get(index)
# obj.addAtHead(val)
# obj.addAtTail(val)
# obj.addAtIndex(index,val)
# obj.deleteAtIndex(index)
```

***cpp***
```cpp
class MyLinkedList {
private:
    // 定义链表
    struct ListNode {
        int val;
        ListNode* next;
        ListNode() : val(0), next(nullptr) {}
        ListNode(int x) : val(x), next(nullptr) {}
        ListNode(int x, ListNode* next) : val(x), next(next) {}
    };

    ListNode* _dummyHead;
    int _size;

public:
    MyLinkedList() {
        _dummyHead = new ListNode();
        _size = 0;
    }

    int get(int index) {
        if (index < 0 || index >= _size)
            return -1;
        ListNode* p = _dummyHead->next;
        while (index--)
            p = p->next;
        return p->val;
    }

    void addAtHead(int val) {
        ListNode* p = new ListNode(val, _dummyHead->next);
        _dummyHead->next = p;
        ++_size;
    }

    void addAtTail(int val) {
        ListNode* p = _dummyHead;
        while (p->next)
            p = p->next;
        p->next = new ListNode(val);
        ++_size;
    }

    void addAtIndex(int index, int val) {
        ListNode* p = _dummyHead;
        if (index < 0 || index > _size)
            return;
        while (index--)
            p = p->next;
        ListNode* temp = new ListNode(val, p->next);
        p->next = temp;
        ++_size;
    }

    void deleteAtIndex(int index) {
        if (index < 0 || index >= _size)
            return;
        ListNode* p = _dummyHead;
        while (index--)
            p = p->next;
        ListNode* temp = p->next;
        p->next = p->next->next;
        delete temp;
        --_size;
    }
};

/**
 * Your MyLinkedList object will be instantiated and called as such:
 * MyLinkedList* obj = new MyLinkedList();
 * int param_1 = obj->get(index);
 * obj->addAtHead(val);
 * obj->addAtTail(val);
 * obj->addAtIndex(index,val);
 * obj->deleteAtIndex(index);
 */
```

***js***
```js
var ListNode = function (val = 0, next = null) {
    this.val = val;
    this.next = next;
};

var MyLinkedList = function () {
    this._dummyHead = new ListNode();
    this._size = 0;
};

/** 
 * @param {number} index
 * @return {number}
 */
MyLinkedList.prototype.get = function (index) {
    if (index < 0 || index >= this._size)
        return -1;
    let p = this._dummyHead.next;
    while (index--)
        p = p.next;
    return p.val;
};

/** 
 * @param {number} val
 * @return {void}
 */
MyLinkedList.prototype.addAtHead = function (val) {
    const p = new ListNode(val, this._dummyHead.next);
    this._dummyHead.next = p;
    this._size++;
};

/** 
 * @param {number} val
 * @return {void}
 */
MyLinkedList.prototype.addAtTail = function (val) {
    let p = this._dummyHead;
    while (p.next)
        p = p.next;
    p.next = new ListNode(val);
    this._size++;
};

/** 
 * @param {number} index 
 * @param {number} val
 * @return {void}
 */
MyLinkedList.prototype.addAtIndex = function (index, val) {
    if (index < 0 || index > this._size)
        return;
    let p = this._dummyHead;
    while (index--)
        p = p.next;
    const temp = new ListNode(val, p.next);
    p.next = temp;
    this._size++;
};

/** 
 * @param {number} index
 * @return {void}
 */
MyLinkedList.prototype.deleteAtIndex = function (index) {
    if (index < 0 || index >= this._size)
        return;
    let p = this._dummyHead;
    while (index--)
        p = p.next;
    p.next = p.next.next;
    this._size--;
};

/**
 * Your MyLinkedList object will be instantiated and called as such:
 * var obj = new MyLinkedList()
 * var param_1 = obj.get(index)
 * obj.addAtHead(val)
 * obj.addAtTail(val)
 * obj.addAtIndex(index,val)
 * obj.deleteAtIndex(index)
 */
```

### 206.反转链表

[206.反转链表](https://leetcode.cn/problems/reverse-linked-list/description/)

***python***
```python
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next

# 逐个节点反转
class Solution:
    def reverseList(self, head: Optional[ListNode]) -> Optional[ListNode]:
        pre, cur = None, head
        while cur:
            temp = cur.next
            cur.next = pre
            pre = cur
            cur = temp
        return pre

# 递归
class Solution:
    def reverseList(self, head: Optional[ListNode]) -> Optional[ListNode]:
        if head == None or head.next == None:
            return head
        
        last = self.reverseList(head.next)
        head.next.next = head
        head.next = None
        return last
```

***cpp***
```cpp
// 逐个翻转每个节点的指向
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode *pre = nullptr;
        ListNode *cur = head;
        while (cur)
        {
            ListNode *temp = cur->next;
            cur->next = pre;
            pre = cur;
            cur = temp;
        }
        return pre;
    }
};

// 递归
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if(head==nullptr || head->next == nullptr) return head;
        ListNode *last = reverseList(head->next);
        head->next->next = head;
        head->next = nullptr;
        return last;
    }
};
```

***js***
```js
/**
 * Definition for singly-linked list.
 * function ListNode(val, next) {
 *     this.val = (val===undefined ? 0 : val)
 *     this.next = (next===undefined ? null : next)
 * }
 */
/**
 * @param {ListNode} head
 * @return {ListNode}
 */
// 逐个节点反转
var reverseList = function (head) {
    let pre = null;
    let cur = head;
    while (cur) {
        const temp = cur.next;
        cur.next = pre;
        pre = cur;
        cur = temp;
    }
    return pre;
};

// 递归
var reverseList = function (head) {
    if (head === null || head.next === null)
        return head;

    const last = reverseList(head.next);
    head.next.next = head;
    head.next = null;
    return last;
};
```

### 92. 反转链表 II

[92. 反转链表 II](https://leetcode.cn/problems/reverse-linked-list-ii/description/)

***python***
```python
# 迭代法
class Solution:
    def reverseBetween(
        self, head: Optional[ListNode], left: int, right: int
    ) -> Optional[ListNode]:
        if left == right:
            return head
        dummyHead = ListNode(0, head)
        p = dummyHead
        for _ in range(left - 1):
            p = p.next
        # 此时 p 指向 left 的前驱
        pre, cur = p.next, p.next.next
        for _ in range(right - left):
            temp = cur.next
            cur.next = pre
            pre = cur
            cur = temp
        p.next.next = cur
        p.next = pre
        return dummyHead.next

# 递归
class Solution:
    backup = None  # right 的后继

    def reverse(self, q, count, right):
        if count == right:
            self.backup = q.next
            return q
        count += 1
        last = self.reverse(q.next, count, right)
        q.next.next = q  # 调转指向
        q.next = self.backup  # 指向 right 的后继
        return last

    def reverseBetween(
        self, head: Optional[ListNode], left: int, right: int
    ) -> Optional[ListNode]:
        if left == right:
            return head
        dummyHead = ListNode(0, head)
        p = dummyHead
        for _ in range(1, left):
            p = p.next
        # 此时 p 指向 left 的前驱
        p.next = self.reverse(p.next, left, right)
        return dummyHead.next
```

***cpp***
```cpp
// 迭代法
class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        if (left == right)
            return head;

        ListNode* dummyHead = new ListNode(0, head);
        ListNode* p = dummyHead;
        int count = left - 1;
        while (count--) // p 指向 left 的前驱
            p = p->next;
        ListNode* pre = p->next;
        ListNode* cur = pre->next;
        count = right - left;
        while (count--) {
            ListNode* count = cur->next;
            cur->next = pre;
            pre = cur;
            cur = count;
        }
        p->next->next = cur;
        p->next = pre;
        return dummyHead->next;
    }
};

// 递归
class Solution {
public:
    ListNode* backup = nullptr;     // right 的后继
    ListNode* reverse(ListNode* q, int& count, const int& right) {
        if (count == right) {
            backup = q->next;
            return q;
        }
        ++count;
        ListNode* last = reverse(q->next, count, right);
        q->next->next = q;      // 调转指向
        q->next = backup;       // 指向 right 的后继
        return last;
    }

    ListNode* reverseBetween(ListNode* head, int left, int right) {
        if (left == right)
            return head;
        ListNode* dummyHead = new ListNode(0, head);
        ListNode* p = dummyHead;
        for (int count = 1; count < left; count++)
            p = p->next;
        // 此时 p 指向 left 的前驱
        p->next = reverse(p->next, left, right);
        return dummyHead->next;
    }
};
```

***js***
```js

```

### 25. K 个一组翻转链表

[25. K 个一组翻转链表](https://leetcode.cn/problems/reverse-nodes-in-k-group/description/)

***python***
```python
class Solution:
    def reverse(self, head: ListNode, tail: ListNode):  # [)
        pre, cur = None, head
        while cur != tail:
            temp = cur.next
            cur.next = pre
            pre = cur
            cur = temp
        return pre

    def reverseKGroup(self, head: Optional[ListNode], k: int) -> Optional[ListNode]:
        p = q = head
        for _ in range(k):
            if q == None:
                return head
            q = q.next
        # 此时 q 指向下一组的头节点
        last = self.reverse(p, q)
        p.next = self.reverseKGroup(q, k)
        return last
```

***cpp***
```cpp
class Solution {
private:
  ListNode* reverse(ListNode* a, ListNode* b) { // [)
    ListNode* pre = nullptr;
    ListNode *cur = a, *next = a;
    while (cur != b) {
      next = cur->next;
      cur->next = pre;
      pre = cur;
      cur = next;
    }
    return pre;
  }

public:
  ListNode* reverseKGroup(ListNode* head, int k) {
    if (head == nullptr) return head;
    ListNode *a, *b;
    a = b = head;
    for (int i = 0; i < k; i++) {
      if (b == nullptr) return head;
      b = b->next;
    }

    // 此时 b 指向下一组的头节点
    ListNode* newHead = reverse(a, b);
    a->next = reverseKGroup(b, k);
    return newHead;
  }
};
```

***js***
```js
```

### 24. 两两交换链表中的节点

[24. 两两交换链表中的节点](https://leetcode.cn/problems/swap-nodes-in-pairs/description/)

***python***
```python
```

***cpp***
```cpp
```

***js***
```js
```

### 19.删除链表的倒数第N个节点

[19.删除链表的倒数第N个节点](https://leetcode.cn/problems/remove-nth-node-from-end-of-list/description/)

***python***
```python
```

***cpp***
```cpp
```

***js***
```js
```

### 面试题 02.07. 链表相交

[面试题 02.07. 链表相交](https://leetcode.cn/problems/intersection-of-two-linked-lists-lcci/description/)

***python***
```python
```

***cpp***
```cpp
```

***js***
```js
```

### 141. 环形链表

[141. 环形链表](https://leetcode.cn/problems/linked-list-cycle/description/)

***python***
```python
```

***cpp***
```cpp
```

***js***
```js
```

### 142.环形链表II

[142.环形链表II](https://leetcode.cn/problems/linked-list-cycle-ii/description/)

***python***
```python
```

***cpp***
```cpp
```

***js***
```js
```

### 21. 合并两个有序链表

[21. 合并两个有序链表](https://leetcode.cn/problems/merge-two-sorted-lists/description/)

***python***
```python
```

***cpp***
```cpp
```

***js***
```js
```

### 23. 合并 K 个升序链表

[23. 合并 K 个升序链表](https://leetcode.cn/problems/merge-k-sorted-lists/description/)

***python***
```python
```

***cpp***
```cpp
```

***js***
```js
```

### 86. 分隔链表

[86. 分隔链表](https://leetcode.cn/problems/partition-list/description/)

***python***
```python
```

***cpp***
```cpp
```

***js***
```js
```

### 876. 链表的中间结点

[876. 链表的中间结点](https://leetcode.cn/problems/middle-of-the-linked-list/description/)

***python***
```python
```

***cpp***
```cpp
```

***js***
```js
```

### 234. 回文链表
[234. 回文链表](https://leetcode.cn/problems/palindrome-linked-list/description/)

***python***
```python
```

***cpp***
```cpp
```

***js***
```js
```



### 1553. 吃掉 N 个橘子的最少天数

[1553. 吃掉 N 个橘子的最少天数](https://leetcode.cn/problems/minimum-number-of-days-to-eat-n-oranges/description/)

***python***

```python
class Solution:
    memo = {0: 0, 1: 1, 2: 2}

    def minDays(self, n: int) -> int:
        if n in self.memo:
            return self.memo[n]

        self.memo[n] = min(self.minDays(n // 2) + n % 2, self.minDays(n // 3) + n % 3) + 1
        return self.memo[n]
```

***cpp***

```cpp
// 动态规划超时
class Solution {
public:
    int minDays(int n) {
        if (n == 1 || n == 2)  return n;
        if (n == 3) return 2;
        vector<int> dp(n + 1);
        dp[1] = 1, dp[2] = 2, dp[3] = 2;
        for (int i = 4; i <= n; i++) {
            int res1 = i, res2 = i;
            if (i % 2 == 0)
                res1 = dp[i / 2] + 1;
            if (i % 3 == 0)
                res2 = dp[i / 3] + 1;
            dp[i] = min({res1, res2, dp[i - 1] + 1});
        }
        return dp[n];
    }
};

// memo
class Solution {
public:
    unordered_map<int, int> umap{{1, 1}, {2, 2}};

    int minDays(int n) {
        if (umap.count(n))
            return umap[n];
        int d2 = n % 2, d3 = n % 3;
        return umap[n] = min(d2 + minDays(n / 2), d3 + minDays(n / 3)) + 1;
    }
};
```