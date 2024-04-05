#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Node {
    Node* left;
    Node* right;
    int key;
    int height;
    bool used;

    Node() : key(0), height(1), left(nullptr), right(nullptr), used(false) {}
    explicit Node(int k) : key(k), height(1), left(nullptr), right(nullptr), used(false) {}
};

int get_height(Node* my_node) {
    if (my_node == nullptr) {
        return 0;
    }
    if (my_node->used) {
        return my_node->height;
    }
    if (my_node->left != nullptr) {
        my_node->left->height = get_height(my_node->left);
        my_node->left->used = true;
        if (my_node->right != nullptr) {
            my_node->right->height = get_height(my_node->right);
            my_node->right->used = true;
            return (max(my_node->left->height, my_node->right->height) + 1);
        } else {
            return my_node->left->height + 1;
        }
    } else {
        if (my_node->right != nullptr) {
            my_node->right->height = get_height(my_node->right);
            my_node->right->used = true;
            return my_node->right->height + 1;
        } else {
            return 1;
        };
    }
}

void update_height(Node* root) {
    if (root != nullptr) {
        int left_h = get_height(root->left);
        int right_h = get_height(root->right);
        if (left_h > right_h) {
            root->height = left_h + 1;
        } else {
            root->height = right_h + 1;
        }
    }
}

void update_heights(Node* root) {
    if (root != nullptr) {
        update_heights(root->left);
        root->height = get_height(root);
        update_heights(root->right);
    }
}

Node* small_left_rotate(Node* root) {
    Node* tmp = root->right;
    root->right = tmp->left;
    tmp->left = root;
    update_height(root);
    update_height(tmp);

    return tmp;
}

Node* small_right_rotate(Node* root) {
    Node* tmp = root->left;
    root->left = tmp->right;
    tmp->right = root;
    update_height(root);
    update_height(tmp);

    return tmp;
}

Node* big_left_rotate(Node* root) {
    root->right = small_right_rotate(root->right);

    return small_left_rotate(root);
}

int balance(Node* my_node) {
    if (my_node == nullptr) {
        return 0;
    }

    return (get_height(my_node->left) - get_height(my_node->right));
}

Node* do_balance(Node* my_node) {
    update_height(my_node);
    int balance_factor = balance(my_node);
    if (balance_factor > 1) {
        if (balance(my_node->right) < 0) {
            my_node->right = small_left_rotate(my_node->right);
        }
        return small_right_rotate(my_node);
    } else if (balance_factor < -1) {
        if (balance(my_node->left) > 0) {
            my_node->left = small_right_rotate(my_node->left);
        }
        return small_left_rotate(my_node);
    }

    return my_node;
}

Node* insert(Node* root, int key) {
    if (root == nullptr) {
        return new Node(key);
    }
    if (root->key > key) {
        root->left = insert(root->left, key);
    } else if (root->key < key) {
        root->right = insert(root->right, key);
    }
//    update_height(root);

    return do_balance(root);
}

void print_balanced_tree(Node* root) {
    queue<Node*> tree;
    tree.push(root);
    int counter = 1;
    while (!tree.empty()) {
        Node* tmp = tree.front();
        tree.pop();
        int ind_l = 0;
        int ind_r = 0;
        if (tmp->left != nullptr) {
            tree.push(tmp->left);
            ++counter;
            ind_l = counter;
        }
        if (tmp->right != nullptr) {
            tree.push(tmp->right);
            ++counter;
            ind_r = counter;
        }
        cout << tmp->key << ' ' << ind_l << ' ' << ind_r << '\n';
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    if (n == 0) {
        int k;
        cin >> k;
        cout << 1 << '\n';
        cout << k << ' ' << 0 << ' ' << 0;
        return 0;
    }
    vector<Node*> tree(n + 1);
    for (int i = 1; i < n + 1; ++i) {
        int key, l_ind, r_ind;
        cin >> key >> l_ind >> r_ind;
        if (tree[i] == nullptr) {
            tree[i] = new Node(key);
        } else {
            tree[i]->key = key;
        }
        if (l_ind != 0) {
            tree[l_ind] = new Node();
            tree[i]->left = tree[l_ind];
        }
        if (r_ind != 0) {
            tree[r_ind] = new Node();
            tree[i]->right = tree[r_ind];
        }
    }
    Node* root = tree[1];
    update_heights(root);
    int ins;
    cin >> ins;
    root = insert(root, ins);
    cout << n + 1 << '\n';
    print_balanced_tree(root);
}