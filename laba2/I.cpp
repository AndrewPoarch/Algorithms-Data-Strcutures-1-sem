#include <iostream>

// nlogn
// logn

int Partition(int* arr, int left_border, int right_border) {
    int i = left_border - 1;
    int j = right_border + 1;
    int pivot = arr[(left_border + right_border) / 2];

    while (true) {
        ++i;
        --j;

        while (arr[i] < pivot) ++i;
        while (arr[j] > pivot) --j;

        if (i >= j) return j;

        std::swap(arr[i], arr[j]);
    }
}

void QuickSort(int* arr, int left_border, int right_border, int k) {
    if (left_border < right_border) {
        int pivot = Partition(arr, left_border, right_border);


        if (k <= pivot) QuickSort(arr, left_border, pivot, k);
        else QuickSort(arr, pivot + 1, right_border, k);

    }
}


int main() {
    int n, k;
    std::cin >> n >> k;

    int* mas = new int[200'000'000];
    int A, B, C;

    std::cin >> A >> B >> C >> mas[0] >> mas[1];

    for (int i = 2; i < n; ++i) mas[i] = A * mas[i-2] + B * mas[i-1] + C;

    QuickSort(mas, 0, n-1, n - k);

    int answer = 0;

    for (int i = k; i >= 1; --i) answer ^= mas[n-i];

    std::cout << answer;

    return 0;
}