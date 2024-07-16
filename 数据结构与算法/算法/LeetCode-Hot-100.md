- [哈希](#哈希)
  - [1. 两数之和](#1-两数之和)
  - [49. 字母异位词分组](#49-字母异位词分组)
  - [128. 最长连续序列](#128-最长连续序列)
- [双指针](#双指针)
  - [283. 移动零](#283-移动零)
  - [11. 盛最多水的容器](#11-盛最多水的容器)
  - [15. 三数之和](#15-三数之和)
  - [42. 接雨水](#42-接雨水)
- [滑动窗口](#滑动窗口)
  - [3. 无重复字符的最长子串](#3-无重复字符的最长子串)
  - [438. 找到字符串中所有字母异位词](#438-找到字符串中所有字母异位词)
- [子串](#子串)
  - [560. 和为 K 的子数组](#560-和为-k-的子数组)
  - [239. 滑动窗口最大值](#239-滑动窗口最大值)
  - [76. 最小覆盖子串](#76-最小覆盖子串)

## 哈希

### [1. 两数之和](https://github.com/Corner430/study-notes/blob/main/数据结构与算法/算法/代码随想录.md#1-两数之和)

### [49. 字母异位词分组](https://github.com/Corner430/study-notes/blob/main/数据结构与算法/算法/代码随想录.md#49-字母异位词分组)

### 128. 最长连续序列

[128. 最长连续序列](https://leetcode.cn/problems/longest-consecutive-sequence/description/?envType=study-plan-v2&envId=top-100-liked)

**_cpp_**

```cpp
// 排序 + 去重
class Solution {
public:
  int longestConsecutive(vector<int> &nums) {
    if (nums.size() == 0) return 0;
    sort(nums.begin(), nums.end());
    int res = 1, count = 1;
    for (int i = 1; i < nums.size(); ++i)
      if (nums[i] == nums[i - 1] + 1)
        res = max(res, ++count);
      else if (nums[i] != nums[i - 1])
        count = 1;
    return res;
  }
};

// 无序哈希，哈希自带去重
class Solution {
public:
  int longestConsecutive(vector<int> &nums) {
    if (nums.size() == 0) return 0;
    unordered_set<int> uset(nums.begin(), nums.end());
    int ans = 1;

    while (!uset.empty()) {
      auto it = uset.begin();
      int cur = *it, up = 1, down = 1;
      uset.erase(cur);
      while (uset.find(cur + up) != uset.end())
        uset.erase(cur + up++);
      while (uset.find(cur - down) != uset.end())
        uset.erase(cur - down++);
      ans = max(ans, up + down - 1);
    }
    return ans;
  }
};

// 有序哈希
class Solution {
public:
  int longestConsecutive(vector<int> &nums) {
    if (nums.size() == 0) return 0;
    set<int> set(nums.begin(), nums.end());
    int ans = 1, count = 1;

    for (auto it = set.begin(); it != set.end(); ++it)
      if (set.find(*it + 1) != set.end()) ans = max(ans, ++count);
      else count = 1;
    return ans;
  }
};
```

## 双指针

### [283. 移动零](https://github.com/Corner430/study-notes/blob/main/数据结构与算法/算法/代码随想录.md#283-移动零)

### 11. 盛最多水的容器

[11. 盛最多水的容器](https://leetcode.cn/problems/container-with-most-water/description/?envType=study-plan-v2&envId=top-100-liked)

**_cpp_**

```cpp
// 左右指针，谁低谁走
class Solution {
public:
  int maxArea(vector<int> &height) {
    int res = 0;
    int left = 0, right = height.size() - 1;
    while (left < right) {
      res = max(res, (right - left) * min(height[right], height[left]));
      height[left] < height[right] ? ++left : --right;
    }
    return res;
  }
};
```

### [15. 三数之和](https://github.com/Corner430/study-notes/blob/main/数据结构与算法/算法/代码随想录.md#15-三数之和)

### [42. 接雨水](https://github.com/Corner430/study-notes/blob/main/数据结构与算法/算法/代码随想录.md#42-接雨水)

## 滑动窗口

### [3. 无重复字符的最长子串](https://leetcode.cn/problems/longest-substring-without-repeating-characters/description/?envType=study-plan-v2&envId=top-100-liked)

**_cpp_**

```cpp
class Solution {
public:
  int lengthOfLongestSubstring(string s) {
    int res = 0;
    int hash[256] = {0};
    for (int left = 0, right = 0; right < s.size(); ++right) {  // [)
      ++hash[s[right]]; // 扩大窗口
      while (hash[s[right]] > 1) --hash[s[left++]]; // 缩小窗口
      res = max(res, right - left + 1); // 合法的时候更新结果
    }
    return res;
  }
};
```

### [438. 找到字符串中所有字母异位词](https://github.com/Corner430/study-notes/blob/main/数据结构与算法/算法/代码随想录.md#438-找到字符串中所有字母异位词)

## 子串

### 560. 和为 K 的子数组

[560. 和为 K 的子数组](https://leetcode.cn/problems/subarray-sum-equals-k/description/?envType=study-plan-v2&envId=top-100-liked)

**_cpp_**

```cpp

```

### [239. 滑动窗口最大值](https://github.com/Corner430/study-notes/blob/main/数据结构与算法/算法/代码随想录.md#239-滑动窗口最大值)

### [76. 最小覆盖子串](https://github.com/Corner430/study-notes/blob/main/数据结构与算法/算法/代码随想录.md#76-最小覆盖子串)
