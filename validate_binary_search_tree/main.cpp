#include <iostream>

struct node{
    int val;
    node* left;
    node* right;
    
    node(int val) : val(val),left(nullptr),right(nullptr){}
};


bool is_bst_helper(node* root,long long minimum,long long maximum){
    if(!root) return true;
    if(root->val < minimum || root->val > maximum)
        return false;
    return is_bst_helper(root->left, minimum, root->val) && is_bst_helper(root->right, root->val, maximum);
}

bool is_valid_bst(node* root){
    if(!root) return true;
    long long minimum = LONG_LONG_MAX;
    long long maximum = LONG_LONG_MAX;
    return is_bst_helper(root, minimum, maximum);
}

int main(int argc, const char * argv[]) {
    
    node* root = new node(8);
    root->left = new node(2);
    root->right = new node(20);
    root->right->left = new node(18);
    root->right->left->left = new node(16);
    root->right->left->right = new node(19);
    root->right->right = new node(24);
    root->right->right->left = new node(22);
    root->right->right->left->right = new node(23);
    root->right->right->right = new node(28);
    
    std::cout<<is_valid_bst(root)<<std::endl;
}
