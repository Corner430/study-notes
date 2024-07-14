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

```

### [15. 三数之和](https://github.com/Corner430/study-notes/blob/main/数据结构与算法/算法/代码随想录.md#15-三数之和)

### [42. 接雨水](https://github.com/Corner430/study-notes/blob/main/数据结构与算法/算法/代码随想录.md#42-接雨水)
