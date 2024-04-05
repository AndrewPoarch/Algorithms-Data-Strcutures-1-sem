#include <iostream>

int main() {
  int n;
  std::cin >> n;

  long* mas = new long[n];

  for (int i = 0; i < n; ++i) {
    std::cin >> mas[i];
  }

  for (int  i = 0; i < n; ++i) {
    if ((i * 2 + 1) < n) {
      if (mas[i] > mas[i * 2 + 1]) {
        std::cout << "NO";
        return 0;
      }
    }
    if ((i * 2 + 2) < n) {
      if (mas[i] > mas[i * 2 + 2]) {
        std::cout << "NO";
        return 0;
      }
    }
  }

  std::cout << "YES";
  return 0;
}