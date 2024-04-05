#include <iostream>
#include <vector>

struct Node
{
  int value;
  int index;
  struct Node* next;
};

struct Stack {
  Node* head = nullptr;

  void add(int value, int index) {
    Node* new_node = new Node;
    new_node -> value = value;
    new_node -> index = index;
    new_node -> next = nullptr;
    if (head == nullptr) {
      head = new_node;
    } else {
      new_node->next = head;
      head = new_node;
    }
  }

  void pop() {
    Node* current = head;
    head = head->next;
    delete current;
  }
};

int main() {
  int n;
  std::cin >> n;

  Stack stack;
  int num;

  int* nums = new int[n];
  int* answer = new int[n] {};
  for (int i = 0; i < n; ++i) {
    std::cin >> num;
    nums[i] = num;
  }

  for (int i = n - 1; i >= 0; --i) {
    while (stack.head != nullptr && stack.head->value <= nums[i]) {
      stack.pop();
    }
    if (stack.head != nullptr) {
      answer[i] = stack.head->index - i;
    }
    stack.add(nums[i], i);
    if (stack.head->value > nums[i]) {
      answer[i] = stack.head->index - i;
    }
  }
  for (int i = 0; i < n; ++i) {
    if (answer[i] == 0) {
      answer[i] = -1;
    }
    std::cout << answer[i] << ' ';
  }
}