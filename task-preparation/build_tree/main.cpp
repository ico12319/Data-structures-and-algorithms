#include <iostream>

//Да се напише функция, която като вход приема масив и връща дърво, в което лявото поддърво на корена съдържа чеслата по - малки от 0, а дясното поддърво тези по - големи от 0. Стойността на корена може да е произволно число от масива.
struct node{
    int val;
    node* left;
    node* right;
    
    node(int val) : val(val),left(nullptr),right(nullptr){}
    node(int val,node* left,node* right) : val(val),left(left),right(right){}
};

using iterator = std::vector<int>::iterator;
node* build_tree_from_range(iterator begin,iterator end){
    auto distance = std::distance(begin, end);
    if(distance == 0)
        return new node(*begin);
    if(distance < 0)
        return nullptr;
    auto mid = distance / 2;
    return new node(*(begin + mid),build_tree_from_range(begin, begin + mid - 1),build_tree_from_range(begin + mid + 1, end));
}

node* build_tree(std::vector<int>& arr){
    std::partition(arr.begin(), arr.end(), [](int x){return x < 0;});
    return build_tree_from_range(arr.begin(), arr.end() - 1);
}

void in_order(node* root){
    if(!root)
        return;
    in_order(root->left);
    std::cout<<root->val<<" ";;
    in_order(root->right);
}

void destroy(node* root){
    if(!root)
        return;
    destroy(root->left);
    destroy(root->right);
    delete root;
}

int main(int argc, const char * argv[]) {
    std::vector<int> v = {-9,8,5,1,-1,4,-12};
    auto root = build_tree(v);
    in_order(root);
    destroy(root);
}
