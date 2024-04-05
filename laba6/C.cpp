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
};

Node* Build(Node* root, std::vector<Node*>& nodes, int index) {
    root = nodes[index];

    if (root->idx_left_ != 0) {
        root->left_ = Build(root->left_, nodes, root->idx_left_ - 1);
    }
    if (root->idx_right_ != 0) {
        root->right_ = Build(root->right_, nodes, root->idx_right_ - 1);
    }

    return root;
}

int index_counter = 1;

void PreOrder(Node* root) {
    root->idx_left_ = 0;
    root->idx_right_ = 0;
    if (root->left_ != nullptr) {
        root->idx_left_ = ++index_counter;
        PreOrder(root->left_);
    }
    if (root->right_ != nullptr) {
        root->idx_right_ = ++index_counter;
        PreOrder(root->right_);
    }
}

void PrintAnswer(Node* root) {
    if (root == nullptr) {
        return;
    }
    std::cout << root->value_ << " " << root->idx_left_ << " " << root->idx_right_ << "\n";
    PrintAnswer(root->left_);
    PrintAnswer(root->right_);
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

    if (n == 0) {
        std::cout << 1 << '\n';
        int x;
        std::cin >> x;
        std::cout << x << ' ' << 0 << ' ' << 0 << '\n';
        return 0;
    }

    std::vector<Node*> values;

    for (int i = 0; i < n; ++i) {
        int k, l, r;
        std::cin >> k >> l >> r;
        Node* node = new Node();
        node->value_ = k;
        node->idx_left_ = l;
        node->idx_right_ = r;
        node->height_ = 1;
        values.push_back(node);
    }

    for (int i = n - 1; i >= 0; --i) {
        if (values[i]->idx_right_ == 0) {
            if (values[i]->idx_left_ != 0) {
                values[i]->height_ += values[values[i]->idx_left_ - 1]->height_;
            }
        } else if (values[i]->idx_left_ == 0) {
            if (values[i]->idx_right_ != 0) {
                values[i]->height_ += values[values[i]->idx_right_ - 1]->height_;
            }
        } else if (values[i]->idx_right_ != 0 && values[i]->idx_left_ != 0) {
            if (values[i]->idx_right_ != 0) {
                if (values[values[i]->idx_left_ - 1]->height_ < values[values[i]->idx_right_ - 1]->height_) {
                    values[i]->height_ += values[values[i]->idx_right_ - 1]->height_;
                } else {
                    values[i]->height_ += values[values[i]->idx_left_ - 1]->height_;
                }
            }
        }
    }

    Node* root = Build(nullptr, values, 0);

    int x;
    std::cin >> x;

    AVL tree;
    root = tree.Insert(root, x);
    PreOrder(root);
    std::cout << n + 1 << '\n';
    PrintAnswer(root);
    PostOrderDelete(root);

    return 0;
}