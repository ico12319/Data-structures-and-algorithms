#include <iostream>


struct node{
    int val;
    node* left;
    node* right;
    
    node(int val) : val(val),left(nullptr),right(nullptr){}
    node(int val,node* left,node* right) : val(val),left(left),right(right){}
};

void traverse(node* root){
    if(!root) return;
    traverse(root->left);
    std::cout<<root->val<<" ";
    traverse(root->right);
}

using iterator = std::vector<int>::const_iterator;
node* build_from_range(iterator begin,iterator end){
    auto distance = std::distance(begin, end);
    if(distance == 0)
        return new node(*begin);
    if(distance < 0)
        return nullptr;
    auto mid = distance / 2;
    return new node(*(begin + mid),build_from_range(begin, begin + mid - 1),build_from_range(begin + mid + 1, end));
}

node* build_binary_search_tree(std::vector<int>& v){
    return build_from_range(v.begin(), v.end() - 1);
}

int main(int argc, const char * argv[]) {
    std::vector<int> v = {1,8,12,24,25};
    auto root = build_binary_search_tree(v);
    std::cout<<root->val<<std::endl;
    traverse(root);
}
