#include <iostream>
#include <vector>

//n logn
// n

void Merge(int* arr, int left, int mid, int right, long long& ans) {

    int idx1 = 0, idx2 = 0;
    int* result = new int[right-left];

    while (left + idx1 < mid && mid + idx2 < right) {
        if (arr[left + idx1] > arr[mid + idx2]) {
            ans += mid - left - idx1;
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
}

void MergeSort(int* arr, int l, int r, long long &ans) {

    if (l + 1 >= r) return;

    int mid = (l + r) / 2;
    MergeSort(arr, l, mid, ans);
    MergeSort(arr, mid, r, ans);
    Merge(arr, l, mid , r, ans);
}

int main() {
    int n;
    long long ans;
    std::cin >> n;

    int* arr = new int[n];
    for (int i =0; i< n; ++i) std::cin >> arr[i];



    MergeSort(arr, 0, n, ans);

//    for (int i = 0; i < n; ++i) std::cout << arr[i] << ' ';
    std::cout <<  ans;

    return 0;
}