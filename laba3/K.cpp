#include <iostream>
struct Node
{
  int value;
  struct Node* next;
};

struct list {
  Node* head = nullptr;
  Node* tail = nullptr;

  void push(int value) {
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

  Node* is_in_list(int value) {
    Node* current = head;
    while (current != nullptr) {
      if (current->value == value) {
        return current;
      }
      current = current->next;
    }
    return nullptr;
  }
};


int main() {
  int n;
  std::cin >> n;

  list list;

  for (int i = 1; i <= n; ++i) {
    Node* current = list.is_in_list(i);
    if (current == nullptr) {
      list.push(i);
    }
    
  }


  return 0;
}