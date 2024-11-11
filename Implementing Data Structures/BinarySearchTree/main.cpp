#include "binary_search_tree.hpp"

int main(int argc, const char * argv[]) {
    
    binary_search_tree<int> tree;
    tree.insert(4);
    tree.insert(2);
    tree.insert(6);
    tree.insert(1);
    tree.insert(-15);
    tree.insert(3);
    tree.insert(5);
    tree.insert(7);
    
    
    binary_search_tree<int>::Node** curr = &tree.root;
    binary_search_tree<int>::Node** min = tree.find_min(curr);
    std::cout<<(*min)->data<<std::endl;
    
    
}
