#include <iostream>
#include <cmath>
#include <cinttypes>
#include <string>
#include <vector>


struct int2023_t {
  static const int kBlockSize = 1'000'000'000;
  std::vector<int> components {};
};


int2023_t from_string(const std::string& buff) {
  int2023_t result;
  for (long long i = buff.length(); i > 0; i -= 9) {
    if (i < 9)
      result.components.push_back(atoi(buff.substr(0, i).c_str()));
    else
      result.components.push_back(atoi(buff.substr(i - 9, 9).c_str()));
  }

  return result;
}

int2023_t operator+(int2023_t left, const int2023_t& right) {
  int carry = 0;
  for (size_t i = 0; i < std::max(left.components.size(), right.components.size()) || carry != 0; ++i) {
    if (i == left.components.size()) {
      left.components.push_back(0);
    }
    left.components[i] += carry + (i < right.components.size() ? right.components[i] : 0);
    carry = left.components[i] >= int2023_t::kBlockSize;
    if (carry != 0) {
      left.components[i] -= int2023_t::kBlockSize;
    }
  }

  return left;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  int n;
  std::cin >> n;
  int2023_t sum;

  for (int i = 0; i < n; ++i) {
    std::string buffer;
    std::cin >> buffer;
    int2023_t current = from_string(buffer);
    sum = sum + current;
  }
  printf ("%d", sum.components.empty() ? 0 : sum.components.back());
  for (int i=static_cast<int>(sum.components.size()-2); i>=0; --i)
    printf ("%09d", sum.components[i]);

  return 0;
}