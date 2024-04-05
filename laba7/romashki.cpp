#include <iostream>
#include <vector>


int main() {
    int x, y;
    std::cin >> x >> y;

    int* mas = new int[x*y];

    for (int i = 0; i < x * y; ++i) {
        int h;
        std::cin >> h;
        mas[i] = h;

    }


    for (int i = 0; i < x * y; ++i) {
        std::cout  << mas[i];
    }

}