#include <iostream>


int main()
{
    int n;
    std::cin >> n;

    int sticks[1000001];

    int max = 0;
    int temp;

    for (int i = 0; i < n; ++i) {
        std::cin >> temp;
        if (temp > max) max = temp;
        sticks[i] = temp;
    }

    std::cout << max;

    return 0;
}