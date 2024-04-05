#include <iostream>
#include <cmath>
#include <vector>
#include <string>

int main() {
    int n;
    std::cin >> n;

    int quantity = std::pow(2, n);

    std::vector<std::string> gray_codes;

    for (int i = 0; i < quantity; ++i) {
        gray_codes.push_back("0");
        for (int j = 0; j < n - 1; ++j) {
            gray_codes[i] += "0";
        }
    }

    gray_codes[1][n - 1] = '1';
    int p = 2;
    for (int i = 2; i < n + 1; ++i) {
        int t = p - 1;
        p = p * 2;
        for (int k = (p / 2); k < p; ++k) {
            gray_codes[k] = gray_codes[t];
            --t;
        }
        for (int j = p / 2; j < p; ++j) {
            gray_codes[j][n - i] = '1';
        }
    }



    for (std::string code: gray_codes) {
        for (int i = 0; i < n; ++i) {
            std::cout << code[i];
        }
        std::cout << '\n';
    }
}