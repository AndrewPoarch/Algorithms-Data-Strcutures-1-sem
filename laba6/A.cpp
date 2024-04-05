#include <iostream>
#include <vector>

class Node {
  public:
    Node(long long value, long long left, long long right):
    value_(value),
    left_(left),
    right_{right} {}

    Node(long long value):
    value_(value) {}

    long long value_{};
    long long left_{};
    long long right_{};
    long long height = 1;
    long long diff = 0;
};


int main() {
    long long n;
    std::cin >> n;

    std::vector<Node> values;

    for (long long i = 0; i < n; ++i) {
        long long k, l, r;
        std::cin >> k >> l >> r;
        values.emplace_back(k, l ,r);
    }

    for (long long i = n - 1; i >= 0; --i) {
        long long temp_sum = values[i].height;
        long long left_height = 0;
        long long right_height = 0;
        if (values[i].left_ != 0) {
            left_height = values[values[i].left_ - 1].height;
        }
        if (values[i].right_ != 0) {
            right_height = values[values[i].right_ - 1].height;
        }
        temp_sum += std::max(left_height, right_height);
        values[i].height = temp_sum;
    }

    for (int i = 0; i < n; ++i) {
        long long diff = 0;
        if (values[i].left_ != 0) {
            diff -= values[values[i].left_ - 1].height;
        }
        if (values[i].right_ != 0) {
            diff += values[values[i].right_ - 1].height;
        }
        values[i].diff = diff;
    }

    for (int i = 0; i < n; ++i) {
        std::cout << values[i].diff << '\n';
    }

    return 0;
}