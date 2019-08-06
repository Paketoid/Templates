#include <bits/stdc++.h>

using namespace std;

struct node{
    node *left, *right;
    int value, prior;
    int size, sum;
    int prom;
    bool reverse;
    node(int n_value = 0){
        left = nullptr;
        right = nullptr;
        value = n_value;
        size = 1;
        prom = 0;
        reverse = false;
        sum = n_value;
        prior = ((rand() << 15) | rand());
    }
};


void push(node* root){
    if (root == nullptr) return;
    root->value += root->prom;
    root->sum += root->size * root->prom;
    if (root->reverse) swap(root->left, root->right);
    if (root->left != nullptr){
        root->left->prom += root->prom;
        root->left->reverse ^= root->reverse;
    }
    if (root->right != nullptr){
        root->right->prom += root->prom;
        root->right->reverse ^= root->reverse;
    }
    root->prom = 0;
    root->reverse = false;
}

int size(node* root){
    if (root == nullptr) return 0;
    return root->size;
}

int sum(node* root){
    if (root == nullptr) return 0;
    return root->sum;
}

void upd(node* root){
    if (root == nullptr) return;
    push(root->left);
    push(root->right);
    root->size = size(root->left) + size(root->right) + 1;
    root->sum = sum(root->left) + sum(root->right) + root->value;
}

node* merge(node* root1, node* root2){
    push(root1);
    push(root2);
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
    push(root);
    if (root == nullptr) return {nullptr, nullptr};

    if (size(root->left) >= k){
        auto p = split(root->left, k);
        root->left = p.second;
        upd(root);
        return {p.first, root};
    }
    else{
        auto p = split(root->right, k - size(root->left) - 1);
        root->right = p.first;
        upd(root);
        return {root, p.second};
    }
}


void write(node* root){
    if (root == nullptr) return;
    push(root);
    write(root->left);
    cout << root->value << " ";
    write(root->right);
}


node *root = nullptr;


int get_sum(int l, int r){
    auto p1 = split(root, r + 1);
    auto p2 = split(p1.first, l);
    int ans = sum(p2.second);
    root = merge(p2.first, p2.second);
    root = merge(root, p1.second);
    return ans;
}

void s_upd(int l, int r, int val){
    auto p1 = split(root, r + 1);
    auto p2 = split(p1.first, l);
    if (p2.second != nullptr) p2.second->prom += val;
    root = merge(p2.first, p2.second);
    root = merge(root, p1.second);
}

void reverse(int l, int r){
    auto p1 = split(root, r + 1);
    auto p2 = split(p1.first, l);
    if (p2.second != nullptr){
        p2.second->reverse = true;
    }
    root = merge(p2.first, p2.second);
    root = merge(root, p1.second);
}

void push_back(int val){
    node *v = new node(val);
    root = merge(root, v);
}


int main(){
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++){
        int a;
        cin >> a;
        push_back(a);
    }
    for (int i = 0; i < m; i++){
        string s;
        cin >> s;
        if (s == "write"){
            write(root);
            cout << endl;
        }
        if (s == "upd"){
            int l, r, val;
            cin >> l >> r >> val;
            s_upd(l, r, val);
        }
        if (s == "get"){
            int l, r;
            cin >> l >> r;
            cout << get_sum(l, r) << endl;
        }
        if (s == "add"){
            int val;
            cin >> val;
            push_back(val);
        }
        if (s == "rev"){
            int l, r;
            cin >> l >> r;
            reverse(l, r);
        }
    }
    return 0;
}

