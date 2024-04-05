#include <iostream>
#include <vector>
#include <string>
using std::vector, std::cin;


struct Heap {
  vector<int> nums;

  void SiftUp(int index);

  void SiftDown(int i);

  void DecreaseKey(int key, int new_value);

  void ExtractMin();

  void Insert(int element);

  void Heapify();
};


void Heap::SiftDown( int i) {
  while (2 * i + 1 < nums.size()) {
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int j = left;
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

void Heap::SiftUp(int index) {
  if (index == 0)
    return;
  int parent = (index - 1) / 2;
  if (nums[parent] > nums[index]) {
    std::swap(nums[parent], nums[index]);
    SiftUp(parent);
  }
}
void Heap::DecreaseKey(int key, int new_value) {
  for (int i = 0; i < nums.size(); ++i) {
    if (nums[i] == key) {
      nums[i] = new_value;
      SiftDown(i);
      SiftUp(i);
      break;
    }
  }
}
void Heap::ExtractMin() {
  if (nums.size() == 0) {
    std::cout << '*' << '\n';
    return;
  }
  std::cout << nums[0] << '\n';
  std::swap(nums[0], nums[nums.size() - 1]);
  nums.resize(nums.size() - 1);
  SiftDown( 0);
}

void Heap::Insert(int element) {
  nums.push_back(element);
  SiftUp(nums.size() - 1);
}
void Heap::Heapify() {
  for (int i = nums.size() / 2; i >= 0; i--){
    SiftDown(i);
  }
}

Heap* Merge(Heap* first, Heap* second) {
  Heap* new_queue = new Heap;
  new_queue->nums.reserve(16);
  for (int i = 0; i < first->nums.size(); ++i) {
    new_queue->nums.push_back(first->nums[i]);
  }
  for (int i = 0; i < second->nums.size(); ++i) {
    new_queue->nums.push_back(second->nums[i]);
  }
  new_queue->Heapify();
  return new_queue;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  std::string message;
  vector<Heap*> Queues;
  while (cin >> message) {
    if (message == "create") {
      Heap* new_queue = new Heap;
      new_queue->nums.reserve(16);
      Queues.push_back(new_queue);
    } else if (message == "insert") {
      int k, x;
      cin >> k >> x;
      Queues[k]->Insert(x);
    } else if (message == "extract-min") {
      int k;
      cin >> k;
      Queues[k]->ExtractMin();
    } else if (message == "decrease-key") {
      int k, x, y;
      cin >> k >> x >> y;
      Queues[k]->DecreaseKey(x, y);
    } else if (message == "merge") {
      int a, b;
      cin >> a >> b;
      Queues.push_back(Merge(Queues[a], Queues[b]));
    }
  }
}