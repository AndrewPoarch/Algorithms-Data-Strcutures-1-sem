#include <iostream>
#include <vector>

class Node {
  public:
    Node() = default;

    Node(int value, int left, int right)
        :
        value_(value),
        idx_left_(left),
        idx_right_(right)
    {}

    Node(int value)
        :
        value_(value){}

    int value_{};
    int idx_left_{};
    int idx_right_{};
    Node* left_{};
    Node* right_{};
    int height_ = 1;
};

class AVL {
  public:
    Node* RightTurn(Node* root) {
        Node* node = root->left_;
        root->left_ = node->right_;
        node->right_ = root;

        FixHeight(root);
        FixHeight(node);

        return node;
    }
    Node* LeftTurn(Node* root) {
        Node* node = root->right_;
        root->right_ = node->left_;
        node->left_ = root;

        FixHeight(root);
        FixHeight(node);

        return node;
    }

    void FixHeight(Node* node) {
        int left = node->left_ ? node->left_->height_ : 0;
        int right = node->right_ ? node->right_->height_ : 0;
        node->height_ = std::max(left, right) + 1;
    }


    int GetDiff(Node* node) {
        if(node->left_ && node->right_){
            return node->left_->height_ - node->right_->height_;
        }
        else if(node->left_ && node->right_ == nullptr){
            return node->left_->height_;
        }
        else if(node->left_== nullptr && node->right_ ){
            return -node->right_->height_;
        }

        return 0;
    }

    Node* Balance(Node* node) {
        FixHeight(node);
        if (GetDiff(node) == -2) {
            if (GetDiff(node->right_) > 0) {
                node->right_ = RightTurn(node->right_);
            }
            return LeftTurn(node);
        }
        if (GetDiff(node) == 2) {
            if (GetDiff(node->left_) < 0) {
                node->left_ = LeftTurn(node->left_);
            }
            return RightTurn(node);
        }

        return node;
    }


    Node* Insert(Node* node, int key) {
        if (node == nullptr) {
            return (new Node(key, 0, 0));
        }
        if (key < node->value_) {
            node->left_ = Insert(node->left_, key);
        }
        else if (key > node->value_) {
            node->right_ = Insert(node->right_, key);
        }

        return Balance(node);
    }

    Node* Exists(Node* root, int value) {
        while (root != nullptr) {
            if (root->value_ == value)
                return root;
            if (root->value_ > value)
                root = root->left_;
            else if (root->value_ < value)
                root = root->right_;
        }

        return nullptr;
    }

    Node* FindMax(Node* p) {
        return p->right_ ? FindMax(p->right_) : p;
    }

    Node* Delete(Node* root, int key) {
        if (root == nullptr) {
            return root;
        }
        if (key < root->value_) {
            root->left_ = Delete(root->left_, key);
        } else if (key > root->value_) {
            root->right_= Delete(root->right_, key);
        } else if (root->left_ != nullptr && root->right_ != nullptr) {
            root->value_ = FindMax(root->left_)->value_;
            root->left_ = Delete(root->left_, root->value_);
        } else if (root->left_ != nullptr) {
            Node* node_to_delete = root;
            root = root->left_;
            delete node_to_delete;
        } else if (root->right_ != nullptr) {
            Node* node_to_delete = root;
            root = root->right_;
            delete node_to_delete;
        } else {
            delete root;
            root = nullptr;

            return root;
        }

        return Balance(root);
    }
};

void PostOrderDelete(Node* node) {
    if (node->left_) {
        PostOrderDelete(node->left_);
    }
    if (node->right_) {
        PostOrderDelete(node->right_);
    }
    delete node;
}


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int n;
    std::cin >> n;
    std::string message;
    AVL tree;
    int x;
    Node* root = nullptr;

    for (int i = 0; i < n; ++i) {
        std::cin >> message;
        if (message == "A") {
            std::cin >> x;
            root = tree.Insert(root, x);
            std::cout << -tree.GetDiff(root) << '\n';

        } else if (message == "D") {
            std::cin >> x;
            root = tree.Delete(root, x);
            if (root) {
                std::cout << -tree.GetDiff(root) << '\n';
            } else {
                std::cout << 0 << '\n';
            }
        } else {
            std::cin >> x;
            if (tree.Exists(root, x))
                std::cout << "Y\n";
            else
                std::cout << "N\n";
        }
    }

    PostOrderDelete(root);

    return 0;
}