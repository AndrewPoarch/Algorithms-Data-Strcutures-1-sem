#include <iostream>
// nlogn
// logn
int Partition(std::pair<long long, long long>* arr, int left_border, int right_border) {
    int i = left_border - 1;
    int j = right_border + 1;
    int RandIndex = left_border + (rand() % (right_border - left_border  + 1));
    long long pivot = arr[RandIndex].first;

    while (true) {
        ++i;
        --j;

        while (arr[i].first < pivot) ++i;
        while (arr[j].first > pivot) --j;

        if (i >= j) return j;

        std::swap(arr[i], arr[j]);
    }
}

void QuickSort(std::pair<long long, long long>* arr, int left_border, int right_border) {
    if (left_border < right_border) {
        int pivot = Partition(arr, left_border, right_border);

        QuickSort(arr, left_border, pivot);
        QuickSort(arr, pivot + 1, right_border);
    }
}


int main() {
    int n;
    std::cin >> n;

    long long sum = 0;

    long long day_counter = 0;


    auto* labworks = new std::pair<long long, long long>[n];

    for (int i = 0; i < n; ++i) std::cin >> labworks[i].first >> labworks[i].second;

    QuickSort(labworks, 0, n - 1);

//    for (int i =0; i < n; ++i) std::cout << labworks[i].first << ' ' << labworks[i].second << '\n';

    for (int i =0; i < n; ++i) {
        sum += labworks[i].second - (labworks[i].first + day_counter);
        day_counter += labworks[i].first;
    }

    std::cout << sum;


    return 0;
}