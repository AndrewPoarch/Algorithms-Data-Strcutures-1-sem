#include <iostream>
#include <vector>
#include <stack>
#include <set>


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int n;
    std::cin >> n;
    bool flag = true;

    std::vector<int> nums;
    std::set<int> set;

    for (int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;
        nums.push_back(x);
        set.insert(x);
    }
    std::stack<int> preorder;
    int root = INT_MIN;
    for (int num : nums) {
        if (num < root) {
            flag = false;
        }
        while (!preorder.empty() && num > preorder.top()) {
            root = preorder.top();
            preorder.pop();
        }
        preorder.push(num);
    }

    nums.clear();
    // inorder
    for (int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;
        if (set.count(x) == 0) {
            flag = false;
        }
        nums.push_back(x);
    }
    for (int i = 1; i < n; ++i) {
        if (nums[i - 1] > nums[i]) {
            flag = false;
        }
    }



    nums.clear();
    for (int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;
        if (set.count(x) == 0) {
            flag = false;
        }
        nums.push_back(x);
    }
    std::stack<int> postorder;
    root = INT_MAX;
    for (int i = n - 1; i >= 0; --i) {
        if (root < nums[i]) {
            flag = false;
        }
        while (!postorder.empty() && nums[i] < postorder.top()) {
            root = postorder.top();
            postorder.pop();
        }
        postorder.push(nums[i]);
    }

    if (flag) {
        std::cout << "YES";
    } else {
        std::cout << "NO";
    }


    return 0;
}
