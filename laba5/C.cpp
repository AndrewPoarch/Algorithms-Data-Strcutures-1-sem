#include <iostream>
#include <vector>


struct Node {
    int apple;
    int child_amount = 0;
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
    ++root->child_amount;

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
            Node* t_parent = next->parent;
            while (t_parent != nullptr) {
                --t_parent->child_amount;
                t_parent = t_parent->parent;
            }
        }
    }

    if (t_node->parent != nullptr) {
        Node* parent = t_node->parent;
        if (t_node->left == nullptr && t_node->right == nullptr) {
            if (parent->left == t_node) {
                --parent->child_amount;
                parent->left = nullptr;
            }
            else if (parent->right == t_node) {
                --parent->child_amount;
                parent->right = nullptr;
            }
            while (parent->parent != nullptr) {
                --parent->parent->child_amount;
                parent = parent->parent;
            }
        }
        else if (t_node->left == nullptr || t_node->right == nullptr) {
            if (t_node->left == nullptr) {
                if (parent->left == t_node) {
                    parent->left = t_node->right;
                    --parent->child_amount;

                } else {
                    parent->right = t_node->right;
                    --parent->child_amount;
                }
                t_node->right->parent = parent;

            } else {
                if (parent->left == t_node) {
                    parent->left = t_node->left;
                    --parent->child_amount;
                } else {
                    parent->right = t_node->left;
                    --parent->child_amount;
                }
                t_node->left->parent = parent;
            }

            while (parent->parent != nullptr) {
                --parent->parent->child_amount;
                parent = parent->parent;
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

            Node* t_parent = next->parent;
            while (t_parent != nullptr) {
                --t_parent->child_amount;
                t_parent = t_parent->parent;
            }

        }
    }

    return root;
}

void KMax(Node* root,  int k) {
    int r_amount = 0;
    if (root->right != nullptr) {
        r_amount = root->right->child_amount + 1;
    }
    if (r_amount + 1 == k) {
        std::cout << root->apple << '\n';
    } else if (r_amount + 1 > k) {
        KMax(root->right, k);
    } else if (r_amount + 1 < k) {
        KMax(root->left, k - r_amount - 1);
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

    for (int i = 0; i < n; ++i) {
        int action = INT_MIN;
        int x;
        std::cin >> action >> x;

        if (action == 1) {
            if (Exists(root, x) == nullptr) {
                root = root->Insert(root, x);
            }
        } else if (action == -1) {
            root = Delete(root, x);
        } else if (action == 0) {
            if (root != nullptr && root->child_amount + 1 >= x ) {
                KMax(root, x);
            }

        }
    }
    PostOrderDelete(root);

    return 0;
}