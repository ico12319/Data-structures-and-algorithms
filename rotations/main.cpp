#include <iostream>

struct node{
    int val;
    node* left;
    node* right;
    
    node(int val) : val(val),left(nullptr),right(nullptr){}
};

void destroy(node* root){
    if(!root) return;
    destroy(root->left);
    destroy(root->right);
    delete root;
}


node* left_rotation(node* root){
    if(!root || !root->right) return root;
    node* new_root = root->right;
    root->right = new_root->left;
    new_root->left = root;
    root = new_root;
    return root;
}


node* right_rotation(node* root){
    if(!root || !root->left) return root;
    node* new_root = root->left;
    root->left = new_root->right;
    new_root->right = root;
    root = new_root;
    return root;
}

node* left_right_rotation(node* root){
    if(!root || !root->left) return root;
    root->left = left_rotation(root->left);
    return right_rotation(root);
}

node* right_left_rotation(node* root){
    if(!root || !root->right) return root;
    root->right = right_rotation(root->right);
    return left_rotation(root);
}

int main(int argc, const char * argv[]) {
    node* root = new node(1);
    root->right = new node(2);
    root->right->right = new node(3);
    
    root = left_rotation(root);
    std::cout<<root->val<<" "<<root->left->val<<" "<<root->right->val<<std::endl;
    
    root = right_rotation(root);
    std::cout<<root->val<<" "<<root->right->val<<" "<<root->right->right->val<<std::endl;
    
    
    node* root2 = new node(5);
    root2->left = new node(3);
    root2->left->right = new node(4);
    root2 = left_right_rotation(root2);
    std::cout<<root2->val<<" "<<root2->left->val<<" "<<root2->right->val<<std::endl;
    
    node* root3 = new node(3);
    root3->right = new node(5);
    root3->right->left = new node(4);
    root3 = right_left_rotation(root3);
    std::cout<<root3->val<<" "<<root3->left->val<<" "<<root3->right->val<<std::endl;
    
    destroy(root);
    destroy(root2);
    destroy(root3);
    
}
