#include <iostream>
#include <vector>
#include <string>
using std::vector, std::cin, std::cout, std::pair;


int main() {
  vector<pair<int, int>> local_max;
  int n;
  cin >> n;
  int* mas = new int[n];
  for (int i = 0; i < n; ++i) {
    cin >> mas[i];
  }


  if (mas[0] > 0 && mas[0] > mas[1])
    local_max.emplace_back(0, mas[0]);
  for (int i = 1; i < n - 1; ++i) {
    if (mas[i] > mas[i - 1] && mas[i] > mas[i + 1])
      local_max.emplace_back(i, mas[i]);
  }
  if (mas[n-1] > 0 && mas[n - 1] > mas[n - 2])
    local_max.emplace_back(n - 1, mas[n -1]);


  int max_right = 0;
  long long ans = 0;
  pair<int, int> left;
  pair<int, int> right;
  for (int i = 0; i < local_max.size(); ++i) {
    if (left.first == 0 && left.second == 0) {
      left = local_max[i];
      continue;
    }
    if (right.first == 0 && right.second == 0) {
      max_right = local_max[i].second;
      right = local_max[i];
      continue;
    }

    if (left.second <= right.second) {
      for (int j = left.first; j < right.first; ++j) {
        ans += left.second - mas[j];

      }
      left = right;

      right = local_max[i];
      max_right = right.second;
    }

    if (left.second > right.second){
      if (max_right < local_max[i].second) {
        right = local_max[i];
        max_right = right.second;
      }
      if (max_right > local_max[i].second) {
        for (int j = left.first + 1; j < right.first; ++j) {
          ans = ans + std::min(left.second, right.second) - mas[j];
        }
        left = right;
        right = local_max[i];
      }
    }
  }



  for (int j = left.first + 1; j < right.first; ++j) {
    ans = ans + std::min(left.second, right.second) - mas[j];
  }

  cout << ans;

  return 0;
}