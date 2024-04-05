#include <iostream>

int Partition(int* arr, int left_border, int right_border) {
    int i = left_border - 1;
    int j = right_border + 1;
    int RandIndex = left_border + (rand() % (right_border - left_border  + 1));
    long long pivot = arr[RandIndex];

    while (true) {
        ++i;
        --j;

        while (arr[i] < pivot) ++i;
        while (arr[j] > pivot) --j;

        if (i >= j) return j;

        std::swap(arr[i], arr[j]);
    }
}

void QuickSort(int* arr, int left_border, int right_border) {
    if (left_border < right_border) {
        int pivot = Partition(arr, left_border, right_border);

        QuickSort(arr, left_border, pivot);
        QuickSort(arr, pivot + 1, right_border);
    }
}

bool check(const int* mas, int size, int x, int k) {
  int count = 1;
  int element = mas[0];
  for (int i = 0; i < size; ++i) {
    if (mas[i] - element >= x) {
      ++count;
      element = mas[i];
    }
  }

  return count >= k;
}

int main() {
  int n, k;
  std::cin >> n >> k;
  int* mas = new int[n];
  for (int i = 0; i < n; ++i) {
    int num;
    std::cin >> num;

    mas[i] = num;
  }

  QuickSort(mas, 0, n - 1);

  int l = 0;
  int r = static_cast<int>(1e9);
  while (r > l + 1) {
    int m = (l + r) / 2;
    if (check(mas, n, m, k)) {
      l = m;
    } else {
      r = m;
    }
  }
  std::cout << l;


  return 0;
}