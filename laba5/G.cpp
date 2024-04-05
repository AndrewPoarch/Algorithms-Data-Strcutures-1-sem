#include <iostream>


#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using std::cin;


struct Node {
    int value_;
    Node* left {};
    Node* right {};
    Node* parent {};

    Node(int t_value_):
        value_(t_value_) {}

    Node* Insert(Node* root, int value);

};

Node* Exists(Node* root, int value) {
    while (root != nullptr) {
        if (root->value_ == value)
            return root;
        if (root->value_ > value)
            root = root->left;
        else if (root->value_ < value)
            root = root->right;
    }

    return nullptr;
}

Node* Node::Insert(Node* root, int value) {
    if (root == nullptr) {
        return new Node(value);
    }

    if (value > root->value_) {
        Node* t_node = Insert(root->right, value);
        root->right = t_node;
        t_node->parent = root;
    }
    else if (value < root->value_) {
        Node* t_node = Insert(root->left, value);
        root->left = t_node;
        t_node->parent = root;
    }

    return root;
}


Node* Next(Node* root, int value) {
    Node* answer = nullptr;
    while (root != nullptr) {
        if (root->value_ > value) {
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
        if (root->value_ >= value) {

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
            Node* next = Next(t_node, t_node->value_);
            t_node->value_ = next->value_;
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
            Node* next = Next(t_node, t_node->value_);
            t_node->value_ = next->value_;
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


Node* Parse(std::string& input) {
    Node* root = nullptr;
    Node* t_node = root;
    int x = 0;
    int temp = 1;
    for (char c: input) {
        if (c == '-') {
            temp = -1;
        } else if (isdigit(c)) {
            x = x * 10 + c - '0';
        } else if (c == ' ') {
            x *= temp;
        } else if (c == 'l') {
            if (t_node == nullptr) {
                t_node = new Node(x);
                root = nullptr;
                if (root) {
                    root = t_node;
                }
            }
            t_node = t_node->left;
            temp = 1;
            x = 0;
        }  else if (c == 'r') {
            if (t_node == nullptr) {
                t_node = new Node(x);
            }
            t_node = t_node->right;

            temp = 1;
            x = 0;
        }  else if (c == 'u') {
            if (t_node->parent) {
                t_node = t_node->parent;
            } else {
                break;
            }

            temp = 1;
            x = 0;
        }
    }

    return root;
}

int main() {


    std::string input;
    std::getline(std::cin, input);
    std::stringstream stream(input);
    Node* root = Parse(input);

return 0;
}