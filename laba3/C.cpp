#include <iostream>
#include <vector>

int kLenOfAlphabet = 26;

char** CountSort(char** mas, int n, int index) {
  int* count = new int[kLenOfAlphabet + 1] {};
  for (int i = 0; i < n; ++i) {
    ++count[mas[i][index] - 'a' + 1];
  }
  for (int i = 1; i < kLenOfAlphabet + 1; ++i) {
    count[i] += count[i-1];
  }
  char** final = new char*[n];
  for (int i = 0; i < n; ++i){
    final[count[mas[i][index] - 'a']] = mas[i];
    ++count[mas[i][index] - 'a'];
  }

  return final;
}

int main() {
  int n, k ,t;
  std::cin >> n >> k >> t;
  char** mas = new char*[n];
  for (int i = 0; i < n; ++i) {
    mas[i] = new char[k] {};
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < k; ++j)
      std::cin >> mas[i][j];
  }
  for (int i = 0; i < t; ++i) {
    mas = CountSort(mas, n, k - 1 - i);
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < k; ++j) {
      std::cout << mas[i][j];
    }
    std::cout << '\n';
  }

  return 0;
}