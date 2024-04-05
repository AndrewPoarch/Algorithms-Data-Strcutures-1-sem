#include <iostream>

bool operator< (std::pair<long long, int>& a, std::pair<long long, int>& b) {
    if (a.first != b.first) return a.first < b.first;
    return a.second > b.second;
}
bool operator> (std::pair<long long, int>& a, std::pair<long long, int>& b) {
    if (a.first != b.first) return a.first > b.first;
    return a.second < b.second;
}

// nlogn + mn
// logn

int Partition(std::pair<long long, int>* arr, int left_border, int right_border) {
    int i = left_border - 1;
    int j = right_border + 1;
    int RandIndex = left_border + (rand() % (right_border - left_border  + 1));
    std::pair<long long, int> pivot = arr[RandIndex];

    while (true) {
        ++i;
        --j;

        while (arr[i] < pivot) ++i;
        while (arr[j] > pivot) --j;

        if (i >= j) return j;

        std::swap(arr[i], arr[j]);
    }
}

void QuickSort(std::pair<long long, int>* arr, int left_border, int right_border) {
    if (left_border < right_border) {
        int pivot = Partition(arr, left_border, right_border);

        QuickSort(arr, left_border, pivot);
        QuickSort(arr, pivot + 1, right_border);
    }
}


int main() {
    const long long modNum = 1'000'000'007;

    int n, m, k;
    std::cin >> n >> m >> k;

    auto* films = new std::pair<long long, int>[m];

    auto* autority = new long long[n];
    for (int i = 0; i < n; ++i) std::cin >> autority[i];

    // n
    int* scores = new int[n];

    // m * n

    for (int j = 0; j < m; ++j){

        long long temp_sum = 0;

        for (int i = 0; i < n; ++i) {
            std::cin >> scores[i];
            temp_sum = (temp_sum + (scores[i] * autority[i])% modNum)% modNum ;
        }
        films[j].second = j + 1;
        films[j].first = temp_sum;
    }

    QuickSort(films, 0, m -1);

    for (int i = 0; i < k; ++i) {
        std::cout << films[m-i-1].second << ' ';
    }

    delete[] films;
    delete[] autority;
    delete[] scores;

    return 0;
}