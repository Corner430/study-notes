- [1 数组](#1-数组)
  - [167. 两数之和 II - 输入有序数组](#167-两数之和-ii---输入有序数组)
  - [344. 反转字符串](#344-反转字符串)
  - [5. 最长回文子串](#5-最长回文子串)
  - [240. 搜索二维矩阵 II](#240-搜索二维矩阵-ii)
- [2 链表](#2-链表)
  - [83. 删除排序链表中的重复元素](#83-删除排序链表中的重复元素)
  - [92. 反转链表 II](#92-反转链表-ii)
  - [25. K 个一组翻转链表](#25-k-个一组翻转链表)
  - [141. 环形链表](#141-环形链表)
  - [21. 合并两个有序链表](#21-合并两个有序链表)
  - [23. 合并 K 个升序链表](#23-合并-k-个升序链表)
  - [86. 分隔链表](#86-分隔链表)
  - [876. 链表的中间结点](#876-链表的中间结点)
  - [234. 回文链表](#234-回文链表)
  - [138. 随机链表的复制](#138-随机链表的复制)

## 1 数组

### 167. 两数之和 II - 输入有序数组

[167. 两数之和 II - 输入有序数组](https://leetcode-cn.com/problems/two-sum-ii-input-array-is-sorted/description/)

**_python_**

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

**_cpp_**

```cpp
// 左右指针
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int left = 0, right = numbers.size() - 1;
        while (left < right) {
            int sum = numbers[left] + numbers[right];
            if (target == sum) return {left + 1, right + 1};
            else if (target < sum) --right;
            else ++left;
        }
        return {-1, -1};
    }
};

// 哈希
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        unordered_map<int, int> umap;
        for (int i = 0; i < numbers.size(); ++i) {
            auto it = umap.find(target - numbers[i]);
            if (it != umap.end()) return {it->second + 1, i + 1};
            umap[numbers[i]] = i;
        }
        return {-1, -1};
    }
};
```

**_js_**

```js
/**
 * @param {number[]} numbers
 * @param {number} target
 * @return {number[]}
 */
// 左右指针
var twoSum = function (numbers, target) {
  let left = 0,
    right = numbers.length - 1;
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

**_python_**

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

**_cpp_**

```cpp
class Solution {
public:
    void reverseString(vector<char>& s) {
        int left = 0, right = s.size() - 1;
        while (left < right)
            swap(s[left++], s[right--]);
    }
};
```

**_js_**

```js
/**
 * @param {character[]} s
 * @return {void} Do not return anything, modify s in-place instead.
 */
var reverseString = function (s) {
  let i = 0,
    j = s.length - 1;
  while (i < j) {
    [s[i], s[j]] = [s[j], s[i]];
    i++;
    j--;
  }
};
```

### 5. 最长回文子串

[5. 最长回文子串](https://leetcode-cn.com/problems/longest-palindromic-substring/description/)

**_python_**

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

**_cpp_**

```cpp
class Solution {
private:
    int extend(const string& s, int i, int j) {
        int length = 0;
        for (; i >= 0 && j < s.size() && s[i] == s[j]; --i, ++j)
            length += i == j ? 1 : 2;
        return length;
    }

public:
    string longestPalindrome(string s) {
        int mid_index = 0, length = 0;
        for (int i = 0; i < s.size(); ++i) {
            int temp_length = max(extend(s, i, i), extend(s, i, i + 1));
            if (temp_length > length) {
                length = temp_length;
                mid_index = i;
            }
        }
        return s.substr(mid_index - (length - 1) / 2, length);
    }
};
```

**_js_**

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
};

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

### 240. 搜索二维矩阵 II

[240. 搜索二维矩阵 II](https://leetcode-cn.com/problems/search-a-2d-matrix-ii/description/)

```cpp
/* 从右上角开始搜索，如果当前元素大于 target，那么向左移动一列；
 * 如果当前元素小于 target，那么向下移动一行。
 */
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int i = 0, j = matrix[0].size() - 1;
        while (i < matrix.size() && j >= 0)
            if (matrix[i][j] == target) return true;
            else if (matrix[i][j] > target) --j;
            else ++i;
        return false;
    }
};
```

## 2 链表

### 83. 删除排序链表中的重复元素

[83. 删除排序链表中的重复元素](https://leetcode-cn.com/problems/remove-duplicates-from-sorted-list/description/)

**_python_**

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

**_cpp_**

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

**_js_**

```js
var deleteDuplicates = function (head) {
  if (!head || !head.next) return head;

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

### 92. 反转链表 II

[92. 反转链表 II](https://leetcode.cn/problems/reverse-linked-list-ii/description/)

**_python_**

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

**_cpp_**

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
private:
    ListNode* backup = nullptr;
    ListNode* reverse(ListNode* head, int count) {  // head 和 其后的 count 个节点反转
        if (!count) {
            backup = head->next;
            return head;
        }
        ListNode* last = reverse(head->next, count - 1);
        head->next->next = head;
        head->next = backup;
        return last;
    }

public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        if (left == right)
            return head;
        ListNode* dummyHead = new ListNode(0, head);
        ListNode* p = dummyHead;
        for (int count = 1; count < left; ++count)  // left 的前驱
            p = p->next;
        p->next = reverse(p->next, right - left);
        return dummyHead->next;
    }
};
```

### 25. K 个一组翻转链表

[25. K 个一组翻转链表](https://leetcode.cn/problems/reverse-nodes-in-k-group/description/)

**_python_**

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

**_cpp_**

```cpp
class Solution {
private:
    ListNode* reverse(ListNode* left, ListNode* right) { // [)
        ListNode *pre = right, *cur = left;
        while (cur != right) {
            ListNode* temp = cur->next;
            cur->next = pre;
            pre = cur;
            cur = temp;
        }
        return pre;
    }

public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode *left = head, *right = head;
        for (int i = 0; i < k; ++i) {
            if (!right) return head;
            right = right->next;
        }
        ListNode* newHead = reverse(left, right);
        left->next = reverseKGroup(right, k);
        return newHead;
    }
};
```

### 141. 环形链表

[141. 环形链表](https://leetcode.cn/problems/linked-list-cycle/description/)

**_python_**

```python
class Solution:
    def hasCycle(self, head: Optional[ListNode]) -> bool:
        fast = slow = head
        while fast and fast.next:
            fast = fast.next.next
            slow = slow.next
            if fast == slow:
                return True
        return False
```

**_cpp_**

```cpp
class Solution {
public:
    bool hasCycle(ListNode *head) {
        ListNode *fast = head, *slow = head;
        while (fast && fast->next){
            fast = fast->next->next;
            slow = slow->next;
            if (fast == slow) return true;
        }
        return false;
    }
};
```

### 21. 合并两个有序链表

[21. 合并两个有序链表](https://leetcode.cn/problems/merge-two-sorted-lists/description/)

**_python_**

```python
class Solution:
    def mergeTwoLists(self, list1: Optional[ListNode], list2: Optional[ListNode]) -> Optional[ListNode]:
        dummyHead = ListNode(0, list1)
        p, q = dummyHead, list2
        while p.next and q:
            if q.val <= p.next.val:
                cur = q
                q = q.next
                cur.next = p.next
                p.next = cur
            p = p.next

        if q:
            p.next = q
        return dummyHead.next
```

**_cpp_**

```cpp
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode* dummyHead = new ListNode(0, list1);
        ListNode *p = dummyHead, *q = list2;
        while (p->next && q) {
            if (q->val <= p->next->val) {
                ListNode* cur = q;
                q = q->next;
                cur->next = p->next;
                p->next = cur;
            }
            p = p->next;
        }
        if (q)
            p->next = q;
        return dummyHead->next;
    }
};
```

**_js_**

```js

```

### 23. 合并 K 个升序链表

[23. 合并 K 个升序链表](https://leetcode.cn/problems/merge-k-sorted-lists/description/)

**_python_**

```python
class Solution:
    def mergeKLists(self, lists: List[Optional[ListNode]]) -> Optional[ListNode]:
        p = dummyHead = ListNode(0)
        heap = []
        for i in range(len(lists)):
            if lists[i]:
                heapq.heappush(heap, (lists[i].val, i))
                lists[i] = lists[i].next

        while heap:
            val, idx = heapq.heappop(heap)
            p.next = ListNode(val)
            p = p.next
            if lists[idx]:
                heapq.heappush(heap, (lists[idx].val, idx))
                lists[idx] = lists[idx].next

        return dummyHead.next
```

**_cpp_**

```cpp
class Solution {
public:
    struct compare { // min heap
        bool operator()(const ListNode* const& l,
                        const ListNode* const& r) const {
            return l->val > r->val;
        }
    };

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        priority_queue<ListNode*, vector<ListNode*>, compare> pq;
        ListNode* dummyHead = new ListNode();
        ListNode* p = dummyHead;

        for (auto list : lists)
            if (list)
                pq.push(list);

        while (!pq.empty()) {
            ListNode* cur = pq.top();
            pq.pop();
            if (cur->next)
                pq.push(cur->next);
            p->next = cur;
            p = p->next;
        }
        return dummyHead->next;
    }
};
```

**_js_**

```js

```

### 86. 分隔链表

[86. 分隔链表](https://leetcode.cn/problems/partition-list/description/)

**_python_**

```python
class Solution:
    def partition(self, head: Optional[ListNode], x: int) -> Optional[ListNode]:
        p = dummyHead = ListNode(0, head)
        while p.next and p.next.val < x:
            p = p.next

        q = p.next
        while q and q.next:
            if q.next.val < x:
                cur = q.next
                q.next = cur.next
                cur.next = p.next
                p.next = cur
                p = cur
            else:
                q = q.next
        return dummyHead.next
```

**_cpp_**

```cpp
class Solution {
public:
    ListNode* partition(ListNode* head, int x) {
        ListNode* dummyHead = new ListNode(0, head);
        ListNode* p = dummyHead;
        while (p->next && p->next->val < x)
            p = p->next;

        ListNode* q = p->next; // 此时 q 指向右半节点的头，p 指向左半节点的头
        if (!q) return head;
        while (q->next)
            if (q->next->val < x) {
                ListNode* cur = q->next;
                q->next = cur->next;
                cur->next = p->next;
                p->next = cur;
                p = cur;
            } else
                q = q->next;

        return dummyHead->next;
    }
};
```

**_js_**

```js

```

### 876. 链表的中间结点

[876. 链表的中间结点](https://leetcode.cn/problems/middle-of-the-linked-list/description/)

**_python_**

```python
class Solution:
    def middleNode(self, head: Optional[ListNode]) -> Optional[ListNode]:
        fast = slow = head
        while fast and fast.next:
            fast = fast.next.next
            slow = slow.next
        return slow
```

**_cpp_**

```cpp
class Solution {
public:
    ListNode* middleNode(ListNode* head) {
        ListNode *fast = head, *slow = head;
        while (fast && fast->next) {
            fast = fast->next->next;
            slow = slow->next;
        }
        return slow;
    }
};
```

**_js_**

```js

```

### 234. 回文链表

[234. 回文链表](https://leetcode.cn/problems/palindrome-linked-list/description/)

**_python_**

```python
# 借用空间
class Solution:
    def isPalindrome(self, head: Optional[ListNode]) -> bool:
        p = head
        arr = []
        while p:
            arr.append(p.val)
            p = p.next
        left, right = 0, len(arr) - 1
        while left <= right:
            if arr[left] != arr[right]:
                return False
            left += 1
            right -= 1
        return True

# 递归 (dfs)
class Solution:
    def isPalindrome(self, head: Optional[ListNode]) -> bool:
        self.p = head
        def dfs(head: Optional[ListNode]) -> bool:
            if head is None:
                return True

            if not dfs(head.next):
                return False

            if self.p.val != head.val:
                return False

            self.p = self.p.next
            return True

        return dfs(head)

# 双指针 + 反转链表
class Solution:
    def isPalindrome(self, head: Optional[ListNode]) -> bool:
        slow = fast = head
        while fast and fast.next:
            fast = fast.next.next
            slow = slow.next
        if fast:
            slow = slow.next

        # 翻转后半部分链表
        pre, cur = None, slow
        while cur:
            temp = cur.next
            cur.next = pre
            pre = cur
            cur = temp

        while pre:
            if pre.val != head.val:
                return False
            pre = pre.next
            head = head.next
        return True
```

**_cpp_**

```cpp
// 借用空间
class Solution {
  public:
  bool isPalindrome(ListNode *head) {
    vector<int> vec;
    ListNode *p = head;
    while (p) {
      vec.push_back(p->val);
      p = p->next;
    }
    int left = 0, right = vec.size() - 1;
    while (left < right)
      if (vec[left++] != vec[right--]) return false;
    return true;
  }
};

// 递归 （dfs）
class Solution {
private:
    ListNode* p, *headback;
    bool dfs(ListNode* head) {
        if (head == nullptr || (p != headback && p == head))   // 剪枝，到中间就返回
            return true;

        bool res1 = dfs(head->next);
        bool res2 = head->val == p->val;
        p = p->next;
        return res1 && res2;
    }

public:
    bool isPalindrome(ListNode* head) {
        headback = p = head;
        return dfs(head);
    }
};

// 双指针 + 反转链表
class Solution {
public:
  bool isPalindrome(ListNode *head) {
    ListNode *slow = head, *fast = head;
    while (fast && fast->next) {
      slow = slow->next;
      fast = fast->next->next;
    }
    if (fast) slow = slow->next;

    // 翻转后半部分链表
    ListNode *pre = nullptr, *cur = slow, *nex = slow;
    while (cur) {
      nex = cur->next;
      cur->next = pre;
      pre = cur;
      cur = nex;
    }
    while (pre) {
      if (pre->val != head->val) return false;
      pre = pre->next;
      head = head->next;
    }
    return true;
  }
};
```

### 138. 随机链表的复制

[138. 随机链表的复制](https://leetcode-cn.com/problems/copy-list-with-random-pointer/description/)

```cpp
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

/*
 * 一个哈希表 + 两次遍历。
 * 第一次遍历专门克隆节点，借助哈希表把原始节点和克隆节点的映射存储起来；
 * 第二次专门组装节点，照着原数据结构的样子，把克隆节点的指针组装起来。
 */

class Solution {
public:
    Node* copyRandomList(Node* head) {
        unordered_map<Node *, Node *> umap;
        for (Node *p = head; p; p = p->next)    // 原链表和新链表之间的映射
            umap[p] = new Node(p->val);
        for (Node *p = head; p; p = p->next) {
            umap[p]->next = umap[p->next];
            umap[p]->random = umap[p->random];
        }
        return umap[head];
    }
};
```

