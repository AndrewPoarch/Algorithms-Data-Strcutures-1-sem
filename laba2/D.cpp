#include <iostream>
#include <vector>

// n
// n

int main() {
    int n;
    std::cin >> n;

    std::vector <int> nums{1, 2};
    if (n == 1) {
        std::cout << 1;
        return 0;
    }
    if (n == 2) {
        std::cout << 1 << " " << 2;
    }

    for (int i = 3; i <= n; ++i) {
        nums.push_back(i);
        std::swap(nums[ ((1 + nums.size())/ 2)-1], nums[i-1]);
    }
    for (int j = 0; j < n; j++) std::cout << nums[j] << " ";
    std::cout << '\n';
    return 0;
}
