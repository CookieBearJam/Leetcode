#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;
#define FWDSTEP 4

// 1.两数之和
vector<int> twoSum(vector<int> &nums, int target) {
    unordered_map<int, int> hash_map;
    vector<int> ret_idx;
    ret_idx.reserve(10);
    // 将数字添加到map中的时候
    int size = nums.size();
    int num_to_find;
    for (int i = 0; i < size; i++) {
        num_to_find = target - nums[i];
        // 如果找到
        if (hash_map.find(num_to_find) != hash_map.end()) {
            // cout<<"ret_0:"<<i<<"ret_1"<<ret_idx[1]<<endl;
            // todo：建议在声明迭代器的时候声明为auto
            auto it = hash_map.find(num_to_find);
            ret_idx[0] = i;
            ret_idx[1] = it->second;
            cout << "ret_0:" << ret_idx[0] << "\tret_1:" << ret_idx[1] << endl;
            return ret_idx;
        }
        hash_map.insert({nums[i], i});
//        } else {
        // 这一段可以改进，因为即使是之前有过的数字，也可以直接添加，对结果没有影响
//            if (hash_map.find(nums[i]) == hash_map.end()) {
//                hash_map.insert({nums[i], i});
//            }
//        }
    }
    return ret_idx;
}


// 2. 两数相加

// Definition for singly-linked list
struct ListNode {
    int val;
    ListNode *next;

    ListNode() : val(0), next(nullptr) {}

    ListNode(int x) : val(x), next(nullptr) {}

    ListNode(int x, ListNode *next) : val(x), next(next) {}
};


void printList(ListNode *list) {
    ListNode *p = list->next;
    while (p != nullptr) {
        cout << "val:" << p->val << endl;
        p = p->next;
    }
}


void addRest(ListNode *listP, ListNode *newListP, bool isCarried) {
    int tmpVal = 0;
    if (listP != nullptr) {
        cout << "第一个参数要长" << endl;
        while (listP != nullptr) {
            // todo:建议初始化一个变量的时候使用auto，防止不适当的cast？
            auto *node1 = new ListNode();
            tmpVal = listP->val + (isCarried ? 1 : 0);
            if (tmpVal >= 10) {
                isCarried = true;
                node1->val = tmpVal % 10;
            } else {
                isCarried = false;
                node1->val = tmpVal % 10;
            }
            // 接上这个节点并且往后移动一格
            node1->next = nullptr;
            newListP->next = node1;
            newListP = newListP->next;
            listP = listP->next;
        }
    }
}

ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
    ListNode *p1 = l1, *p2 = l2;
    int tmpVal = 0, idx = 0;
    bool isCarried = false;
    ListNode *l3, *p3;
    ListNode *headNode = new ListNode();
// 创建一个头节点，不会存储任何的值
    l3 = headNode;
    p3 = l3;

    while (p1 != nullptr && p2 != nullptr) {
        ListNode *node = new ListNode();
        tmpVal = p1->val + p2->val;
        if (tmpVal < 9) {
            // 不超过9的数即使加上进位也不会再进位
            node->val = tmpVal + (isCarried ? 1 : 0);
            isCarried = false;
        } else if (tmpVal == 9) {
            node->val = isCarried ? 0 : 9;
            // isCarried保持原本的值不变
        } else {
            // >9，也就是此次已经发生进位
            node->val = (tmpVal + (isCarried ? 1 : 0)) % 10;
            isCarried = true;
        }
        p1 = p1->next;
        p2 = p2->next;
        // 接上这个节点并且往后移动一格
        node->next = nullptr;
        p3->next = node;
        p3 = p3->next;
        cout << "idx:" << ++idx << endl;
        printList(l3);
    }

// 对于还有的位数
    if (p1 != nullptr) {
        cout << "第一个参数要长" << endl;
        while (p1 != nullptr) {
            ListNode *node1 = new ListNode();
            tmpVal = p1->val + (isCarried ? 1 : 0);
            if (tmpVal >= 10) {
                isCarried = true;
                node1->val = tmpVal % 10;
            } else {
                isCarried = false;
                node1->val = tmpVal % 10;
            }
            // 接上这个节点并且往后移动一格
            node1->next = nullptr;
            p3->next = node1;
            p3 = p3->next;
            p1 = p1->next;
        }
    } else if (p2 != nullptr) {
        cout << "第二个参数要长" << endl;
        while (p2 != nullptr) {
            ListNode *node2 = new ListNode();
            tmpVal = p2->val + (isCarried ? 1 : 0);
            if (tmpVal >= 10) {
                isCarried = true;
                node2->val = tmpVal % 10;
            } else {
                isCarried = false;
                node2->val = tmpVal;
            }
            // 接上这个节点并且往后移动一格
            node2->next = nullptr;
            p3->next = node2;
            p3 = p3->next;
            p2 = p2->next;
        }
    } else {
        // 两个都遍历完了
        cout << "两个都遍历完了嗷" << endl;
    }
    // 如果最高位还有进位
    if (isCarried) {
        ListNode *nodeHighest = new ListNode(1);
        p3->next = nodeHighest;
    }

    return l3;
}


int lengthOfLongestSubstring(string s) {
    int pre_head_idx = 0, cur_head_idx = 0;
    int pre_len = 0, cur_len = 0;
    int s_len = s.size();
    int tmp_head_idx;
    bool has_repeated = false;
    // 字串的长度不会超过string的长度
//    unordered_set<char> sub_string_set;
    unordered_map<char, int> sub_string_idx_map;


    // cur_head_idx需要不断循环
    for (; cur_head_idx < s_len;) {
        for (int i = cur_head_idx; i < s_len; i++) {
            auto found_it = sub_string_idx_map.find(s[i]);
            if (found_it == sub_string_idx_map.end()) {
                // 没有这个元素
                cur_len++;
                sub_string_idx_map.insert({s[i], i});
            } else {
                // 已经有这个元素了
                if (cur_len > pre_len) {
                    pre_head_idx = cur_head_idx;
                    pre_len = cur_len;
                }
                // 这样写是错误的，是因为set添加元素的顺序不固定，所以我暂时采用一下map，将idx作为value，字母的值作为key
//                cur_head_idx += distance(sub_string_set.begin(), found_it) + 1;
                cur_head_idx = found_it->second + 1;
                sub_string_idx_map.clear();
                cur_len = 0;
                break;
            }
        }
    }

//    if(cur_head_idx >= s_len){
//        return pre_len;
//    }
//
//    for (int i = pre_head_idx; i < pre_len;i++) {
//        cout << item << "\t";
//    }
//    cout << endl;
    return pre_len > cur_len ? pre_len : cur_len;
}


int main() {
    // 1.测试<两数之和>
    vector<int> nums = {2, 7, 11, 15};
    twoSum(nums, 9);
    std::cout << "Hello, World!" << std::endl;

    // 2.测试<两数相加>
    /**
     * 测试用例1：
     * 输入：l1 = [2,4,3], l2 = [5,6,4]
     * 输出: [7,0,8]
     * */
    auto *l1_3 = new ListNode(3);
    auto *l1_2 = new ListNode(4, l1_3);
    auto *l1_1 = new ListNode(2, l1_2);

    auto *l2_3 = new ListNode(4);
    auto *l2_2 = new ListNode(6, l2_3);
    auto *l2_1 = new ListNode(5, l2_2);

    ListNode *ret_list = addTwoNumbers(l1_1, l2_1);
    printList(ret_list);

    /**
     * 测试用例2：
     * 输入：l1 = [0], l2 = [0]
     * 输出: [0]
     * */



    /**
     * 输入：l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
     * 输出：[8,9,9,9,0,0,0,1]
     * */
    auto *l4_7 = new ListNode(9);
    auto *l4_6 = new ListNode(9, l4_7);
    auto *l4_5 = new ListNode(9, l4_6);
    auto *l4_4 = new ListNode(9, l4_5);
    auto *l4_3 = new ListNode(9, l4_4);
    auto *l4_2 = new ListNode(9, l4_3);
    auto *l4_1 = new ListNode(9, l4_2);


    auto *l5_4 = new ListNode(9);
    auto *l5_3 = new ListNode(9, l5_4);
    auto *l5_2 = new ListNode(9, l5_3);
    auto *l5_1 = new ListNode(9, l5_2);

    cout << "测试用例3：" << endl;
    ListNode *ret_list3 = addTwoNumbers(l4_1, l5_1);
    printList(ret_list3);


    // 测试用例1："abcabcbb"：3
    // 测试用例2："bbbbb" ：1
    // 测试用例3："pwwkew" ：3
//    cout << "不重复的最长子串长度，测试用例0:abcabcbb：" << lengthOfLongestSubstring("abcabcbb") << endl;
    cout << "不重复的最长子串长度，测试用例1:abckkwabcwkdcabb：" << lengthOfLongestSubstring("abckkwabcwkdcabb") << endl;
//    cout << "不重复的最长子串长度，测试用例2:bbbbb：" << lengthOfLongestSubstring("bbbbb") << endl;
//    cout << "不重复的最长子串长度，测试用例3:pwwkew：" << lengthOfLongestSubstring("pwwkew") << endl;
    return 0;
}
