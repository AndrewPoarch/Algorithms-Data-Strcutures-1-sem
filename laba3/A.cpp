#include <iostream>

struct Node
{
  int value;
  struct Node* next;
};

struct Stack {
  Node* head = nullptr;

  void add_node(int value) {
    Node* new_node = new Node;
    new_node -> value = value;
    new_node -> next = nullptr;
    if (head == nullptr) {
      head = new_node;
    } else {
      new_node->next = head;
      head = new_node;
    }
  }
  void delete_and_print_last_node() {
    Node* current = head;
    std::cout << current->value << '\n';
    head = head->next;
    delete current;
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  Stack stack;
  int n;
  std::cin >> n;
  for (int i = 0; i < n; ++i) {
    char action;
    int number;

    std::cin >> action;
    if (action == '+') {
      std::cin >> number;
      stack.add_node(number);
    }
    if (action == '-') {
      stack.delete_and_print_last_node();
    }
  }

  return 0;
}