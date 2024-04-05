#include <iostream>

struct Node {
    int key;
    Node* left {};
    Node* right {};
};

void Insert(Node* node, int* keys, int left, int right) {
    int mid = (left + right) / 2;
    node->key = keys[mid];
    if (mid > left){
        node->left = new Node;
        Insert(node->left, keys, left, mid - 1);
    }
    if (mid < right) {
        node->right = new Node;
        Insert(node->right, keys, mid + 1, right);
    }
}

void PreOrder(Node* root) {
    if (root != nullptr) {
        std::cout << root->key << " ";
        PreOrder(root->left);
        PreOrder(root->right);
    }
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
    int* keys = new int[n];

    for (int i = 0; i < n; ++i)
        std::cin >> keys[i];

    Node* root = new Node;
    Insert(root, keys, 0, n - 1);
    PreOrder(root);
    PostOrderDelete(root);

    return 0;
}
