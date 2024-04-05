#include <iostream>

struct Node
{
  int value;
  struct Node* next;
};

struct list {
  Node* head = nullptr;
  Node* tail = nullptr;

  void add_node(int value) {
    Node* new_node = new Node;
    new_node -> value = value;
    new_node -> next = nullptr;
    if (head == nullptr) {
      head = new_node;
      tail = new_node;
    } else {
      tail->next = new_node;
      tail = new_node;
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
  list list;
  int n;
  std::cin >> n;
  for (int i = 0; i < n; ++i) {
    char action;
    int number;

    std::cin >> action;
    if (action == '+') {
      std::cin >> number;
      list.add_node(number);
    }
    if (action == '-') {
      list.delete_and_print_last_node();
    }
  }

  return 0;
}