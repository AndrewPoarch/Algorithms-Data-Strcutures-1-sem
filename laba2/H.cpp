#include <iostream>

// nlogn
// n + n

void Merge(std::pair<int, int>* arr, int left, int mid, int right) {

    int idx1 = 0, idx2 = 0;
    std::pair<int, int>* result = new std::pair<int, int>[right-left];

    while (left + idx1 < mid && mid + idx2 < right) {
        if (arr[left + idx1].first > arr[mid + idx2].first) {
            result[idx1 + idx2] = arr[mid + idx2];
            ++idx2;
        } else {
            result[idx1 + idx2] = arr[left + idx1];
            ++idx1;
        }
    }

    while (idx1 + left < mid) {
        result[idx1 + idx2] = arr[left + idx1];
        ++idx1;
    }
    while (idx2 + mid < right) {
        result[idx1 + idx2] = arr[mid + idx2];
        ++idx2;
    }
    for (int i = 0; i < idx1 + idx2; ++i) arr[left+i] = result[i];

    delete[] result;
}

void MergeSort(std::pair<int, int>* arr, int l, int r) {

    if (l + 1 >= r) return;

    int mid = (l + r) / 2;
    MergeSort(arr, l, mid);
    MergeSort(arr, mid, r);
    Merge(arr, l, mid , r);
}


int main() {
    int n;
    std::cin >> n;
    std::pair<int, int>* input_arr = new std::pair<int, int>[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> input_arr[i].first;
        input_arr[i].second = i;
    }
    std::pair<int, int>* sort_arr = new std::pair<int, int>[n];
    std::copy(input_arr, input_arr + n, sort_arr);


    MergeSort(sort_arr, 0, n);


    for (int i = 0; i < n; ++i) {
        sort_arr[i].first += (sort_arr[i].second - i);
    }

    for (int i = 1; i < n; ++i) {
        if (sort_arr[i].first < sort_arr[i-1].first) {
            std::cout << ":(";
            exit(EXIT_SUCCESS);
        }
    }

    for (int i = 0; i < n; ++i) std::cout << sort_arr[i].first << ' ';

    return 0;
}