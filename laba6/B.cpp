#include <iostream>
#include <vector>

static int index_counter = 1;


class Node {
  public:
    Node(int value, int left, int right, int diff):
        value_(value),
        left_(left),
        right_{right},
        diff_(diff){}

    Node(int value, int left, int right):
        value_(value),
        left_(left),
        right_{right}
        {}

    Node(int value):
        value_(value) {}

    int value_{};
    int left_{};
    int right_{};
    Node* lptr{};
    Node* rptr{};
    int height = 1;
    int diff_ = 0;
};

Node* Insert(Node* root, const std::vector<Node*>& nodes, int index) {
    root = nodes[index];

    if (root->left_ != 0) {
        root->lptr = Insert(root->lptr, nodes, root->left_ - 1);
    }
    if (root->right_ != 0) {
        root->rptr = Insert(root->rptr, nodes, root->right_ - 1);
    }

    return root;
}

Node* LeftTurn(Node* root) {
    Node* p = root->rptr;
    root->rptr = p->lptr;
    p->lptr = root;

    return p;
}
Node* BigLeftTurn(Node* root) {
    Node* b = root->rptr;
    Node* c = b->lptr;
    root->rptr = c->lptr;
    b->lptr = c->rptr;
    c->lptr = root;
    c->rptr = b;

    return c;
}




void PreOrder(Node* root) {
    root->left_ = 0;
    root->right_ = 0;
    if (root->lptr != nullptr) {
        root->left_ = ++index_counter;
        PreOrder(root->lptr);
    }
    if (root->rptr != nullptr) {
        root->right_ = ++index_counter;
        PreOrder(root->rptr);
    }
}

void PrintAnswer(Node* root, std::vector<Node*>& val) {
    if (root == nullptr) {
        return;
    }
    val.push_back(new Node(root->value_, root->left_, root->right_));
    PrintAnswer(root->lptr, val);
    PrintAnswer(root->rptr, val);

}

int main() {
    int n;
    std::cin >> n;

    std::vector<Node*> values;

    for (int i = 0; i < n; ++i) {
        int k, l, r;
        std::cin >> k >> l >> r;
        values.push_back(new Node(k, l ,r));
    }

    for (int i = n - 1; i >= 0; --i) {
        int temp_sum = values[i]->height;
        int left_height = 0;
        int right_height = 0;
        if (values[i]->left_ != 0) {
            left_height = values[values[i]->left_ - 1]->height;
        }
        if (values[i]->right_ != 0) {
            right_height = values[values[i]->right_ - 1]->height;
        }
        temp_sum += std::max(left_height, right_height);
        values[i]->height = temp_sum;
    }


    Node* root = Insert(nullptr, values, 0);

    int left = 0;
    int right = 0;

    if (root->rptr->lptr) {
        left = root->rptr->lptr->height;
    }
    if (root->rptr->rptr) {
        right = root->rptr->rptr->height;
    }


    if (right - left == -1) {
        root = BigLeftTurn(root);
    } else {
        root = LeftTurn(root);
    }


    values.clear();
    std::cout << n << '\n';
    PreOrder(root);
//    std::cout << root->value_ << " " << root->left_ << " " << root->right_ << '\n';
    PrintAnswer(root, values);

    for (int i = 0; i < n; ++i) {
        std::cout << values[i]->value_ << " " << values[i]->left_ << " " << values[i]->right_ << "\n";
    }

    return 0;
}
