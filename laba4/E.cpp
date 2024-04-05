#include <iostream>


void SiftDown(int* arr, int size, int i) {
  while (2 * i + 1 < size) {
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int j = left;
    if (right < size && arr[right] < arr[left]) {
      j = right;
    }
    if (arr[i] <= arr[j]) {
      break;
    }
    std::swap(arr[i], arr[j]);
    i = j;
  }
}


void heap(int* arr, int size){
  int last_branch = (size / 2) - 1;
  for (int i = last_branch; i >= 0; i--){
    SiftDown(arr, size, i);
  }
}

int main() {
  int n;
  std::cin >> n;
  int* arr = new int[n];
  for (int i = 0; i < n; i++){
    std::cin >> arr[i];
  }
  heap(arr, n);
  for (int i = n - 1; i >= 0; i--){
    std::swap(arr[0], arr[i]);
    SiftDown(arr, i, 0);
  }
  for (int i = n - 1; i >= 0; --i){
    std::cout << arr[i] << " ";
  }
  return 0;
}