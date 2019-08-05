#include <bits/stdc++.h>

#define INF 1e9;

using namespace std;

struct node{
    int key, prior;
    int size;
    node *left, *right;
    node(int n_key = 0){
        left = nullptr;
        right = nullptr;
        key = n_key;
        size = 1;
        prior = (rand() << 15 | rand());
    }
};


int size(node* root){
    if (root == nullptr) return 0;
    else return root->size;
}

void upd(node* root){
    if (root == nullptr) return;
    root->size = size(root->left) + size(root->right) + 1;
}

node* merge(node* root1, node* root2){
    if (root1 == nullptr) return root2;
    if (root2 == nullptr) return root1;

    if (root1->prior < root2->prior){
        root1->right = merge(root1->right, root2);
        upd(root1);
        return root1;
    }
    else{
        root2->left = merge(root1, root2->left);
        upd(root2);
        return root2;
    }
}

pair <node*, node*> split(node* root, int k){
    if (root == nullptr) return {nullptr, nullptr};

    if (root->key < k){
        auto p = split(root->right, k);
        root->right = p.first;
        upd(root);
        return {root, p.second};
    }
    else{
        auto p = split(root->left, k);
        root->left = p.second;
        upd(root);
        return {p.first, root};
    }
}

node* insert(node* root, node* v){
    if (root == nullptr) return v;
    if (v == nullptr) return root;

    if (v->prior < root->prior){
        auto p = split(root, v->key);
        v->left = p.first;
        v->right = p.second;
        upd(v);
        return v;
    }
    else{
        if (v->key < root->key) root->left = insert(root->left, v);
        else root->right = insert(root->right, v);
        upd(root);
        return root;
    }
}

bool find(node* root, int key){
    if (root == nullptr) return false;
    if (root->key == key) return true;
    if (key < root->key) return find(root->left, key);
    else return find(root->right, key);
}

node* erase(node* root, int key){
    if (root == nullptr) return root;
    if (root->key == key) return merge(root->left, root->right);
    if (key < root->key) root->left = erase(root->left, key);
    else root->right = erase(root->right, key);
    upd(root);
    return root;
}

pair <node*, node*> split_size(node* root, int k){
    if (root == nullptr) return {nullptr, nullptr};

    if (size(root->left) >= k){
        auto p = split_size(root->left, k);
        root->left = p.second;
        upd(root);
        return {p.first, root};
    }
    else{
        auto p = split_size(root->right, k - size(root->left) - 1);
        root->right = p.first;
        upd(root);
        return {root, p.second};
    }
}

int find_kth(node* root, int id){
    if (root == nullptr) return -INF;

    if (size(root->left) == id) return root->key;

    if (size(root->left) > id) return find_kth(root->left, id);
    else return find_kth(root->right, id - size(root->left) - 1);
}

int find_num(node* root, int key){
    if (root == nullptr) return -INF;
    if (key < root->key) return find_num(root->left, key);
    else return find_num(root->right, key) + size(root->left) + 1;
}

void write(node* root){
    if (root == nullptr) return;
    write(root->left);
    cout << root->key << " ";
    write(root->right);
}


node* root = nullptr;

int main(){
    return 0;
    int n;
    cin >> n;
    while (n){
        --n;
        string s;
        cin >> s;
        if (s == "add"){
            int key;
            cin >> key;
            node* v = new node(key);
            root = insert(root, v);
        }
        if (s == "erase"){
            int key;
            cin >> k;
            root = erase(root, key);
        }
        if (s == "write"){
            write(root);
            cout << endl;
        }
        if (s == "kth"){
            int id;
            cin >> id;
            cout << find_kth(root, id) << endl;
        }
        if (s == "number"){
            int key;
            cin >> key;
            cout << find_num(root, key) << endl;
        }
    }
}
