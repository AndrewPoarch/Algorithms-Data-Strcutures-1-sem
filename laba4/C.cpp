#include <iostream>
#include <cmath>
#include <cinttypes>
#include <string>
#include <vector>


using std::vector;

struct Queue {
  vector<std::pair<uint64_t, uint64_t>> nums;

  void SiftUp(uint64_t index);

  void SiftDown(uint64_t index);

  uint64_t ExtractMin();

  void Insert(uint64_t element, uint64_t time);

  void Heapify();
};


void Queue::SiftDown(uint64_t i) {
  while (2 * i + 1 < nums.size()) {
    uint64_t left = 2 * i + 1;
    uint64_t right = 2 * i + 2;
    uint64_t j = left;
    if (right < nums.size() && nums[right].second < nums[left].second) {
      j = right;
    }
    if (nums[i].second <= nums[j].second) {
      break;
    }
    std::swap(nums[i], nums[j]);
    i = j;
  }
}

void Queue::SiftUp(uint64_t index) {
  if (index == 0)
    return;
  uint64_t parent = (index - 1) / 2;
  if (nums[parent].second > nums[index].second) {
    std::swap(nums[parent], nums[index]);
    SiftUp(parent);
  }
}

uint64_t Queue::ExtractMin() {
  uint64_t min = nums[0].first;
  std::swap(nums[0], nums[nums.size() - 1]);
  nums.resize(nums.size() - 1);
  SiftDown( 0);
  return min;
}

void Queue::Insert(uint64_t element, uint64_t time) {
  std::pair<uint64_t, uint64_t> newp;
  newp.first = element;
  newp.second = time;
  nums.push_back(newp);
  SiftUp(nums.size() - 1);
}
void Queue::Heapify() {
  for (int i = nums.size() / 2; i >= 0; i--){
    SiftDown(i);
  }
}


struct Heap {
  vector<uint64_t> nums;

  void SiftUp(uint64_t index);

  void SiftDown(uint64_t i);

  uint64_t ExtractMin();

  void Insert(uint64_t element);

  void Heapify();
};


void Heap::SiftDown(uint64_t i) {
  while (2 * i + 1 < nums.size()) {
    uint64_t left = 2 * i + 1;
    uint64_t right = 2 * i + 2;
    uint64_t j = left;
    if (right < nums.size() && nums[right] < nums[left]) {
      j = right;
    }
    if (nums[i] <= nums[j]) {
      break;
    }
    std::swap(nums[i], nums[j]);
    i = j;
  }
}

void Heap::SiftUp(uint64_t index) {
  if (index == 0)
    return;
  uint64_t parent = (index - 1) / 2;
  if (nums[parent] > nums[index]) {
    std::swap(nums[parent], nums[index]);
    SiftUp(parent);
  }
}

uint64_t Heap::ExtractMin() {
  uint64_t min = nums[0];
  std::swap(nums[0], nums[nums.size() - 1]);
  nums.resize(nums.size() - 1);
  SiftDown( 0);
  return min;
}

void Heap::Insert(uint64_t element) {
  nums.push_back(element);
  SiftUp(nums.size() - 1);
}
void Heap::Heapify() {
  for (int i = nums.size() / 2; i >= 0; i--){
    SiftDown(i);
  }
}


int main() {
  int n, m;
  std::cin >> n >> m;

  Heap chefs;

  for (int i = 0; i < n; ++i) {
    uint64_t chef;
    std::cin >> chef;
    chefs.Insert(chef);
  }

  uint64_t sum = 0;
  Queue in_work;

  for (int i = 0; i < m; ++i) {
    uint64_t tick, time_needed;
    std::cin >> tick >> time_needed;

    while (!in_work.nums.empty() && tick >= in_work.nums[0].second) {
      chefs.Insert(in_work.ExtractMin());
    }

    if (!chefs.nums.empty()) {
      uint64_t current_chef = chefs.ExtractMin();
      sum += current_chef * time_needed;
      in_work.Insert(current_chef, time_needed + tick);
    }
  }

  std::cout << sum;

  return 0;
}
