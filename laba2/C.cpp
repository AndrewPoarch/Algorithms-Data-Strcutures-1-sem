#include <iostream>


int main() {

  // O(n)
  // n + k

    // Реализация Count Sort O(k)
    int n;
    std::cin >> n;

    int* sticks = new int[n];

    int max = 0;
    int temp = 0;

    for (int i = 0; i < n; ++i) {
        std::cin >> temp;
        if (temp > max) max = temp;
        sticks[i] = temp;
    }

    int* indexes = new int[max + 1];

    for (int i = 0; i < n; ++i) indexes[sticks[i]]++;
    for (int i = 1; i <= max; ++i) indexes[i] += indexes[i-1];

    int* finalArr = new int[n];

    for (int i = 0; i < n; ++i){
        finalArr[indexes[sticks[i]] - 1] = sticks[i];
        indexes[sticks[i]]--;
    }

    // Поиск максимальной суммы

    long long int a = 0, b = 0;
    long long int temp_sum = 0;
    long long int final_sum = 0;


    for (int i = n -1 ; i > 0; --i) {
        if (finalArr[i] == finalArr[i-1]) {
            if (a == 0) a = finalArr[i];
            else if (b == 0) b = finalArr[i];
            --i;
        } else if (finalArr[i] - 1 == finalArr[i-1]) {
            if (a == 0) a = finalArr[i] - 1;
            else if (b == 0) b = finalArr[i] - 1;
            --i;
        }
        if (a != 0 && b != 0) {
            temp_sum = a*b;
            final_sum += static_cast <long long int> (temp_sum);
            a = 0;
            b = 0;
        }
    }

    std::cout << final_sum;

    delete[] sticks;
    delete[] indexes;
    delete[] finalArr;

    return 0;
}