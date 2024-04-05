
#include <iostream>
#include <string>

struct Node {
    std::string value_;
    bool usapple[3] {false, false, false};
    Node* left_ {};
    Node* right_ {};
    int height_ = 1;
    int diff_ = 0;


    Node(std::string t_name, int idx):
        value_(t_name) {
        usapple[idx] = true;
    }

};

Node* Exists(Node* root, std::string value) {
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


    Node* Insert(Node* node, std::string key, int idx) {
        if (node == nullptr) {
            return (new Node(key, idx));
        }

        if (key < node->value_) {
            node->left_ = Insert(node->left_, key, idx);
        }
        else if (key > node->value_) {
            node->right_ = Insert(node->right_, key, idx);
        }

        return Balance(node);
    }
};

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
        PreOrderCount(root->left_, sums);
        PreOrderCount(root->right_, sums);
    }
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
    Node* root = nullptr;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < n; ++j) {
            std::string lab_name;
            std::cin >> lab_name;
            Node* temp = Exists(root, lab_name);
            if (temp == nullptr) {
                root = tree.Insert(root, lab_name, i);
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
