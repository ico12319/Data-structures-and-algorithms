#include <iostream>

struct node{
    int val;
    node* left;
    node* right;
    
    node(int val) : val(val){}
};


node* left_rotation(node* root){
    if (!root || !root->right) return root;
    node* new_root = root->right;
    root->right = new_root->left;
    new_root->left = root;
    root = new_root;
    return root;
}


node* right_rotation(node* root){
    if (!root || !root->left) return root;
    node* new_root = root->left;
    root->left = new_root->right;
    new_root->right = root;
    root = new_root;
    return root;
}

void in_order(node* root){
    if(!root) return;
    in_order(root->left);
    std::cout<<root->val<<" ";
    in_order(root->right);
}

int main(int argc, const char * argv[]) {
    
    node* root = new node(6);
    root->left = new node(4);
    root->right = new node(8);
    root->right->left = new node(7);
    root->right->right = new node(9);
    
    root = left_rotation(root);
    std::cout<<root->val<<std::endl;
    //in_order(root);
    root = right_rotation(root);
    std::cout<<root->val<<std::endl;
}



