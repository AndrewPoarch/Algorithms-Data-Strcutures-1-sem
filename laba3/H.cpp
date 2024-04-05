#include <iostream>

struct Node
{
  long long value;
  int index;
  struct Node* next;
};

struct Stack {
  Node* head = nullptr;
  int size = 0;

  void push(long long value, int index) {
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
    ++size;
  }

  void pop() {
    Node* current = head;
    head = head->next;
    delete current;
    --size;
  }
};

int main()
{
  int n;
  std::cin >> n;
  Stack stack;

  long long max_area = 0;
  long long top_element;
  long long temp_area;

  stack.push(-1, 0);

  for (int i = 1; i <= n + 1; ++i) {
    long long num;
    int index = i;
    if (i > n) {
      num = 0;
    } else {
      std::cin >> num;
    }

    while (num <= stack.head->value) {
      index = stack.head->index;
      top_element = stack.head->value;
      stack.pop();
      temp_area = top_element * (i - index);

      if (temp_area > max_area) {
        max_area = temp_area;
      }
    }
    stack.push(num, index);
  }

  for (int i = 1; i < stack.size; ++i) {
    top_element = stack.head->value;
    stack.pop();
    temp_area = top_element * i;

    if (temp_area > max_area) {
      max_area = temp_area;
    }
  }
  std::cout << max_area;

  return 0;
}