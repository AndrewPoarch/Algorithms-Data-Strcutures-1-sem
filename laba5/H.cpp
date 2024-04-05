#include <iostream>
#include <vector>

struct Node {
    int value_;
    Node* left {};
    Node* right {};
    Node* parent {};

    Node(int t_value_):
        value_(t_value_) {}

};

class BST {
  public:
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

    Node* Insert(Node* root, int value) {
        if (root == nullptr) {
            return new Node(value);
        }

        if (value > root->value_) {
            Node* t_node = Insert(root->right, value);
            root->right = t_node;
            t_node->parent = root;
        } else if (value < root->value_) {
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
            } else if (t_node->left == nullptr || t_node->right == nullptr) {
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
            } else if (t_node->left == nullptr || t_node->right == nullptr) {
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

    void PreOrder(std::vector<int>& ans, Node* root) {
        if (root != nullptr) {
            PreOrder(ans, root->left);
            ans.push_back(root->value_);
            PreOrder(ans, root->right);
        }
    }

    void Merge(BST& first, BST& second) {
        while (second.root_ != nullptr) {
            first.root_ = first.Insert(first.root_, second.root_->value_);
            second.root_ = second.Delete(second.root_, second.root_->value_);
        }
    }

    Node* root_ = nullptr;

};

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
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;

    BST first;
    BST second;

    std::string message;
    std::vector<int> ans;


    for (int i = 0; i < n; ++i) {
        std::cin >> message;
        if (message == "buy") {
            int k, x;
            std::cin >> k >> x;
            if (k == 1) {
                first.root_ = first.Insert(first.root_, x);
            } else {
                second.root_ = second.Insert(second.root_, x);
            }
        } else if (message == "sell") {
            int k, x;
            std::cin >> k >> x;
            if (k == 1) {
                first.root_ = first.Delete(first.root_, x);
            } else {
                second.root_ = second.Delete(second.root_, x);
            }
        } else {
            first.Merge(first, second);
            second.root_ = nullptr;
            first.PreOrder(ans, first.root_);
            for (int j = 0; j < ans.size(); ++j) {
                std::cout << ans[j];
                if (j < ans.size() - 1) {
                    std::cout << ' ';
                }
            }
            if (!ans.empty()) {
                std::cout << '\n';
            }
            ans.clear();
        }
    }
    PostOrderDelete(first.root_);
    PostOrderDelete(second.root_);

    return 0;
}