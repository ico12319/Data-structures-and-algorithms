#include <iostream>


struct TreeNode{
    int val;
    TreeNode* left;
    TreeNode* right;
    
    TreeNode(int val) : val(val),left(nullptr),right(nullptr){}
    TreeNode(int val,TreeNode* left,TreeNode* right) : val(val),left(left),right(right){}
};

// Depth-first-search traversals:

void post_order_traversal(TreeNode* root){
    if(!root) return;
    
    post_order_traversal(root->left);
    post_order_traversal(root->right);
    std::cout<<root->val<<" ";
}

bool search(TreeNode* root,int target){
    if(!root) return false;
    
    if(root->val == target)
        return true;
    
    return search(root->left, target) || search(root->right, target);
}

void pre_order_traversal(TreeNode* root){
    if(!root) return;
    
    std::cout<<root->val<<" ";
    pre_order_traversal(root->left);
    pre_order_traversal(root->right);
}

void in_order_traversal(TreeNode* root){
    if(!root)
        return;
    
    in_order_traversal(root->left);
    std::cout<<root->val<<" ";
    in_order_traversal(root->right);
}

void free(TreeNode* root){
    if(!root) return;
    
    free(root->left);
    free(root->right);
    delete root;
}

int main(int argc, const char * argv[]) {
   
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->left->right->left = new TreeNode(9);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(7);
    root->right->right->left = new TreeNode(15);
    
    post_order_traversal(root);
    std::cout<<std::endl;
    std::cout<<search(root, 28)<<std::endl;;
    
    free(root);
    
}
