#include <iostream>


struct Node
{
  long long value;
  long long index;
  struct Node* next;
};

struct Stack {
  Node* head = nullptr;

  void push(long long value, long long index) {
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
  void clear() {
    while (head != nullptr) {
      Node* current = head;
      head = head->next;
      delete current;
    }
  }
};


int main() {
  char mas [100000] {};
  std::cin >> mas;

  long long literals[28] {};
  long long final[28] {};
  Stack numbers;
  Stack items;
  long long count_bracket = 0;

  for (int i = 99999; i >= 0; --i) {
    if (count_bracket <= 0) {
      items.clear();
      for (int k = 0; k < 28; ++k) {
        final[k] += literals[k];
        literals[k] = 0;
      }
    }
    if (std::isdigit(mas[i])) {
      long long temp_num = mas[i] - 48;
      if (std::isalpha(mas[--i])) {
        items.push(mas[i] - 65, count_bracket);
        literals[mas[i] - 65] += temp_num;
      } else if (mas[i] == ')') {
        ++count_bracket;
        long long ttt = 1;
        if (numbers.head != nullptr) {
          ttt = numbers.head->value;
        }
        numbers.push(temp_num * ttt, 0);
      }
    } else if (mas[i] == ')') {
      ++count_bracket;
      long long ttt = 1;
      if (numbers.head != nullptr) {
        ttt = numbers.head->value;
      }
      numbers.push(1  * ttt, 0);
    }
    else if (mas[i] == '(') {
      --count_bracket;

      if (numbers.head != nullptr) {
        long long num = numbers.head->value;
        Node *current = items.head;
        while (current != nullptr) {
          if (current->index > 0) {
            literals[current->value] *= num;
            --current->index;
          }
          current = current->next;
        }
        items.clear();
        numbers.pop();
      }
      items.clear();
      for (int k = 0; k < 28; ++k) {
        final[k] += literals[k];
        literals[k] = 0;
      }
    } else if (std::isalpha(mas[i])) {
      items.push(mas[i] - 65, count_bracket);
      literals[mas[i] - 65] += 1;
    }
  }

  for (int k = 0; k < 28; ++k) {
    final[k] += literals[k];
    literals[k] = 0;
  }

  for (int i = 0; i < 28; ++i) {
    if (final[i] != 0) {
      std::cout << static_cast<char>(i + 65);
      if (final[i] != 1) {
        std::cout << final[i];
      }
    }
  }

  return 0;
}