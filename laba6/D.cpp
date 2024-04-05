#include <iostream>
#include <utility>
#include <vector>
#include <string>

class Node {
  public:
    Node(std::string value)
    :
    value_(std::move(value))
    {}

    std::string value_{};
    Node* left_{};
    Node* right_{};
    int height_ = 1;
    int diff_ = 0;
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


    Node* Insert(Node* node, const std::string& key) {
        if (node == nullptr) {
            return (new Node(key));
        }
        if (key < node->value_) {
            node->left_ = Insert(node->left_, key);
        }
        else if (key > node->value_) {
            node->right_ = Insert(node->right_, key);
        }

        return Balance(node);
    }
};


void CheckNode(Node* node, const std::string& key, bool& flag) {
    if (node == nullptr) {
        flag = false;
        return;
    } else if (node->value_ == key) {
        flag = true;
        return;
    } else if (key > node->value_) {
        CheckNode(node->right_, key, flag);
    } else if (key < node->value_) {
        CheckNode(node->left_, key, flag);
    }
}

void EditAnswer(const std::string& key, int& count) {
    bool* mask = new bool[100] {};
    for (int i = 0; i < key.size(); ++i) {
        mask[key[i] - '0'] = true;
    }
    for (int i = 0; i < 100; ++i) {
        if (mask[i]) {
            ++count;
        }
    }

    delete[] mask;
}

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
    int n;
    std::cin >> n;
    AVL tree;
    int counter = 0;
    Node* root = nullptr;
    for (int i = 0; i < n; ++i) {
        std::string x;
        std::cin >> x;
        bool flag = false;
        CheckNode(root, x, flag);
        if (!flag) {
            root = tree.Insert(root, x);
        } else {
            EditAnswer(x, counter);
        }
    }


    std::cout << counter;
    PostOrderDelete(root);

    return 0;
}