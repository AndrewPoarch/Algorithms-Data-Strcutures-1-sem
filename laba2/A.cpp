#include <iostream>
using namespace std;

// n^2
// 1
int main() {
  int n;
  cin >> n;

  int slippers[10001];
  for (int i = 0; i < n; ++i) cin >> slippers[i];

  int slipper;
  int j = 0;

  for (int i = 1; i < n; ++i) {
    slipper = slippers[i];
    j = i - 1;
    while (j >= 0 && slippers[j] > slipper) {
      slippers[j+1] = slippers[j];
      --j;
    }
    slippers[j+1] = slipper;
  }
  for (int i = 0; i < n; ++i) cout << slippers[i] << " ";

  return 0;
}