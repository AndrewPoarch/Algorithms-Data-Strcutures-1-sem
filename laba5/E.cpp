#include <iostream>
#include <string>

struct Node {
    std::string name;
    bool usapple[3] {false, false, false};
    Node* left {};
    Node* right {};
    Node* parent {};

    Node(std::string t_name, int idx):
        name(t_name) {
        usapple[idx] = true;
    }

    Node* Insert(Node* root, std::string value, int index);
};

Node* Exists(Node* root, std::string value) {
    while (root != nullptr) {
        if (root->name == value)
            return root;
        if (root->name > value)
            root = root->left;
        else if (root->name < value)
            root = root->right;
    }

    return nullptr;
}

Node* Node::Insert(Node* root, std::string value, int index) {
    if (root == nullptr) {
        return new Node(value, index);
    }

    if (value > root->name) {
        Node* t_node = Insert(root->right, value, index);
        root->right = t_node;
        t_node->parent = root;
    }
    else if (value < root->name) {
        Node* t_node = Insert(root->left, value, index);
        root->left = t_node;
        t_node->parent = root;
    }

    return root;
}

void PreOrderCount(Node* root, int sums[3]) {
    if (root != nullptr) {
        if (root->usapple[0]) {
            if (root->usapple[1]) {
                if (!root->usapple[2]) {
                    sums[0] += 1;
                    sums[1] += 1;
                }
            } else if (root->usapple[2]) {
                sums[0] += 1;
                sums[2] += 1;
            } else {
                sums[0] += 3;
            }
        } else {
            if (root->usapple[1]) {
                if (root->usapple[2]) {
                    sums[1] += 1;
                    sums[2] += 1;
                } else {
                    sums[1] += 3;
                }
            } else if (root->usapple[2]) {
                sums[2] += 3;
            }
        }
        PreOrderCount(root->left, sums);
        PreOrderCount(root->right, sums);
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

    Node* root = nullptr;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < n; ++j) {
            std::string lab_name;
            std::cin >> lab_name;
            Node* temp = Exists(root, lab_name);
            if (temp == nullptr) {
                root = root->Insert(root, lab_name, i);
            } else {
                temp->usapple[i] = true;
            }
        }
    }

    int sums[3] {0, 0, 0};
    PreOrderCount(root, sums);

    for (int sum: sums) {
        std::cout << sum << ' ';
    }
    PostOrderDelete(root);

    return 0;
}
