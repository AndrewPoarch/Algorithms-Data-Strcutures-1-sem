#include <iostream>
#include <vector>
#include <string>

using std::cin;


struct Node {
    int apple;
    Node* left {};
    Node* right {};
    Node* parent {};

    Node(int t_apple):
    apple(t_apple) {}

    Node* Insert(Node* root, int value);

};

Node* Exists(Node* root, int value) {
    while (root != nullptr) {
        if (root->apple == value)
            return root;
        if (root->apple > value)
            root = root->left;
        else if (root->apple < value)
            root = root->right;
    }

    return nullptr;
}

Node* Node::Insert(Node* root, int value) {
    if (root == nullptr) {
        return new Node(value);
    }

    if (value > root->apple) {
        Node* t_node = Insert(root->right, value);
        root->right = t_node;
        t_node->parent = root;
    }
    else if (value < root->apple) {
        Node* t_node = Insert(root->left, value);
        root->left = t_node;
        t_node->parent = root;
    }

    return root;
}


Node* Next(Node* root, int value) {
    Node* answer = nullptr;
    while (root != nullptr) {
        if (root->apple > value) {
            answer = root;
            root = root->left;
        } else {
            root = root->right;
        }
    }
    return answer;
}
Node* Prev(Node* root, int value) {
    Node* answer = nullptr;
    while (root != nullptr) {
        if (root->apple >= value) {

            root = root->left;
        } else {
            answer = root;
            root = root->right;
        }
    }
    return answer;
}

Node* Delete(Node* root, int value) {
    Node* t_node = Exists(root, value);
    if (t_node == nullptr)
        return root;
    if (t_node->parent == nullptr) {
        if (t_node->left == nullptr && t_node->right == nullptr) {
            return nullptr;
        }
        else if (t_node->left == nullptr || t_node->right == nullptr) {
            if (t_node->left == nullptr) {
                t_node->right->parent = nullptr;
                return t_node->right;
            } else {
                t_node->left->parent = nullptr;
                return t_node->left;
            }
        } else {
            Node* next = Next(t_node, t_node->apple);
            t_node->apple = next->apple;
            if (next->parent->left == next) {
                next->parent->left = next->right;
                if (next->right != nullptr) {
                    next->right->parent = next->parent;
                }
            } else {
                next->parent->right = next->right;
                if (next->right != nullptr) {
                    next->right->parent = next->parent;
                }
            }
        }
    }

    if (t_node->parent != nullptr) {
        Node* parent = t_node->parent;
        if (t_node->left == nullptr && t_node->right == nullptr) {
            if (parent->left == t_node)
                parent->left = nullptr;
            if (parent->right == t_node)
                parent->right = nullptr;
        }
        else if (t_node->left == nullptr || t_node->right == nullptr) {
            if (t_node->left == nullptr) {
                if (parent->left == t_node)
                    parent->left = t_node->right;
                else
                    parent->right = t_node->right;
                t_node->right->parent = parent;
            } else {
                if (parent->left == t_node)
                    parent->left = t_node->left;
                else
                    parent->right = t_node->left;
                t_node->left->parent = parent;
            }
        } else {
            Node* next = Next(t_node, t_node->apple);
            t_node->apple = next->apple;
            if (next->parent->left == next) {
                next->parent->left = next->right;
                if (next->right != nullptr) {
                    next->right->parent = next->parent;
                }
            } else {
                next->parent->right = next->right;
                if (next->right != nullptr) {
                    next->right->parent = next->parent;
                }
            }
        }
    }

    return root;
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
    std::string messapple;
    Node* root = nullptr;
    int x;
    while (cin >> messapple) {
        if (messapple == "insert") {
            cin >> x;
            if (Exists(root, x) == nullptr) {
                root = root->Insert(root, x);
            }

        } else if (messapple == "delete") {
            cin >> x;
            Node* t_node = Delete(root, x);
            root = t_node;

        } else if (messapple == "exists") {
            cin >> x;
            if (Exists(root, x) != nullptr)
                std::cout << "true\n";
            else
                std::cout << "false\n";
        } else if (messapple == "next") {
            cin >> x;
            Node* t_node = Next(root, x);
            if (t_node == nullptr)
                std::cout << "none\n";
            else
                std::cout << t_node->apple << '\n';

        } else if (messapple == "prev") {
            cin >> x;
            Node* t_node = Prev(root, x);
            if (t_node == nullptr)
                std::cout << "none\n";
            else
                std::cout << t_node->apple << '\n';
        }
    }
    PostOrderDelete(root);

    return 0;
}