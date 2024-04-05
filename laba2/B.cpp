#include <iostream>

// nlogn
// logn


int Partition(int* arr, int left_border, int right_border) {
    int i = left_border - 1;
    int j = right_border + 1;
    int RandIndex = left_border + (rand() % (right_border - left_border  + 1));
    int pivot = arr[RandIndex];

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


int main()
{
    int n;
    std::cin >> n;
    int* weights = new int[n];

    for (int i = 0; i < n; ++i) std::cin >> weights[i];

    QuickSort(weights, 0, n - 1);

    for (int i = 0; i < n; ++i) std::cout << weights[i] << " ";

    delete [] weights;
    return 0;
}