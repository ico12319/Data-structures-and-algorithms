#include "binary_search_tree.hpp"

int main(int argc, const char * argv[]) {
    binary_search_tree<int> bst;
    bst.insert(1);
    bst.insert(18);
    bst.insert(0);
    bst.insert(22);
    
        
    
    auto it = bst.forward_begin();
    it++;
    it++;
    it++;
    
    auto it2 = bst.backward_begin();
    it2--;
    it2--;
    it2--;
    std::cout<<*it2<<std::endl;

}
