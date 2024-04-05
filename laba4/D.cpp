#include <iostream>
#include <string>
#include <vector>

using std::vector, std::pair;

struct Heap {
  vector<pair<int, int>> nums;

  void SiftUp(int index);

  void SiftDown(int i);

  void DecreaseKey(int key, int new_value);

  void ExtractMax();

  void Insert(int id, int value);

  void Heapify();
};


void Heap::SiftDown( int i) {
  while (2 * i + 1 < nums.size()) {
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int j = left;
    if ((right < nums.size() && nums[right].second > nums[left].second) || (right < nums.size() && nums[right].second == nums[left].second && nums[right].first > nums[left].first)) {
      j = right;
    }

    if ((nums[i].second > nums[j].second) || (nums[i].second == nums[j].second && nums[i].first > nums[j].first)) {
      break;
    }
    std::swap(nums[i], nums[j]);
    i = j;
  }
}

void Heap::SiftUp(int index) {
  if (index == 0)
    return;
  int parent = (index - 1) / 2;

  if (nums[parent].second == nums[index].second && nums[parent].first < nums[index].first) {
    std::swap(nums[parent], nums[index]);
    SiftUp(parent);
  } else if (nums[parent].second < nums[index].second) {
    std::swap(nums[parent], nums[index]);
    SiftUp(parent);
  }
}

void Heap::ExtractMax() {
  std::swap(nums[0], nums[nums.size() - 1]);
  nums.resize(nums.size() - 1);
  SiftDown(0);
}

void Heap::Insert(int id, int value) {
  nums.emplace_back(id, value);
  SiftUp(nums.size() - 1);
}
void Heap::Heapify() {
  for (int i = nums.size() / 2; i >= 0; i--){
    SiftDown(i);
  }
}


int main() {
  int n;
  Heap ratings;
  Heap salaries;

  std::cin >> n;
  for (int i = 0; i < n; ++i) {
    int id, rating, honorarium;
    std::cin >> id >> rating >> honorarium;
    ratings.Insert(id, rating);
    salaries.Insert(id, honorarium);
  }

  int m;
  std::cin >> m;
  int j = 0;
  vector<int> final_codes;
  vector<int> phone_calls;
  for (int i = 0; i < n; ++i) {
    if (ratings.nums[0].first == salaries.nums[0].first) {
      final_codes.push_back(ratings.nums[0].first);
      ratings.ExtractMax();
      salaries.ExtractMax();
    } else {
      if (j < m) {
        std::string answer;
        std::cin >> answer;
        if (answer == "YES") {
          phone_calls.push_back(ratings.nums[0].first);
          final_codes.push_back(ratings.nums[0].first);
        } else if (answer == "NO") {
          phone_calls.push_back(ratings.nums[0].first);

        }
        ++j;
      }
      ratings.ExtractMax();
    }
  }

  for (int i: phone_calls) {
    std::cout << i << " ";
  }
  std::cout << '\n';
  for (int i: final_codes) {
    std::cout << i << " ";
  }


  return 0;
}