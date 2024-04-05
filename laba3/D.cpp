#include <iostream>
#include <vector>

struct Node
{
  int value;
  struct Node* next;
  struct Node* prev;
};

struct List {
  Node* head = nullptr;
  Node* tail = nullptr;
  int size = 0;

  void add_node(int value) {
    Node* new_node = new Node;
    new_node -> value = value;
    new_node -> next = nullptr;
    new_node -> prev = nullptr;
    if (head == nullptr) {
      head = new_node;
      tail = new_node;
    } else {
      tail->next = new_node;
      new_node->prev = tail;
      tail = new_node;
    }
    ++size;
  }

  void delete_first_node() {
    Node* current = head;
    head = head->next;
    head->prev = nullptr;
    --size;
    delete current;
  }

  void delete_last_node() {
    Node* current = tail;
    tail = tail->prev;
    tail->next = nullptr;
    --size;
    delete current;
  }

};


int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);



  List list;
  int n, m;
  std::cin >> n >> m;

  if (n < m) {
    m = n;
  }

  for (int i = 0; i < n ; ++i) {
    int number;
    std::cin >> number;
    if (list.size < 5) {
      list.add_node(number);
    } else {
      int first = list.head->value;
      list.delete_first_node();
      int second = list.tail->value;
      list.delete_last_node();

      // сортирую полученные элементы
      int array[3] {first, second, number};
      int j = 0;
      for (int k = 1; k < 3; ++k) {
        int el = array[k];
        j = k - 1;
        while (j >= 0 && array[j] > el) {
          array[j+1] = array[j];
          --j;
        }
        array[j+1] = el;
      }

      list.add_node(array[1]);
      list.add_node(array[2]);

    }
  }

  for (int i = 0; i < m; ++i) {
    std::cout << list.head->value << ' ';
    list.head = list.head->next;
  }

  return 0;
}
//9 9
//4 12 28 34 6 7 100 3 99