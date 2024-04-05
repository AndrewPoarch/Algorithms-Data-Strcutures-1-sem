#include <iostream>

struct Node {
    int apple;
    int lvl;
    Node* left {};
    Node* right {};
    Node* parent {};

    Node(int t_apple, int t_lvl):
        apple(t_apple), lvl(t_lvl) {}

    Node* Insert(Node* root, int value);
};

Node* Node::Insert(Node* root, int value) {
    if (root == nullptr) {
        return new Node(value, 1);
    }

    if (value > root->apple) {
        Node* t_node = Insert(root->right, value);
        root->right = t_node;
        t_node->parent = root;
        t_node->lvl = root->lvl + 1;
    }
    else if (value < root->apple) {
        Node* t_node = Insert(root->left, value);
        root->left = t_node;
        t_node->parent = root;
        t_node->lvl = root->lvl + 1;
    }

    return root;
}

void PrintMax(Node* root, bool* levels) {
    if (!levels[root->lvl]) {
        std::cout << root->apple << ' ';
        levels[root->lvl] = true;
    }
    if (root->right != nullptr)
        PrintMax(root->right, levels);
    if (root->left != nullptr)
        PrintMax(root->left, levels);
}

void PostOrderDelete(Node* node) {
    if (node->left) {
        PostOrderDelete(node->left);
    }
    if (node->right) {
        PostOrderDelete(node->right);
    }
    delete node;
}

int main() {
    int n;
    std::cin >> n;
    Node* root = nullptr;
    bool* levels = new bool[100000] {};

    for (int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;
        root = root->Insert(root, x);
    }

    PrintMax(root, levels);
    PostOrderDelete(root);

    return 0;
}