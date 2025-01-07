#include "binary_search_tree.hpp"

int main(int argc, const char * argv[]) {
    binary_search_tree<int> bst;
   
    for(int i = 0;i<100;i++)
        bst.insert(i);
    
    //bst.print();
    std::cout<<bst[0]<<std::endl;
    std::cout<<bst[bst.size() - 1]<<std::endl;
    
    auto it = bst.forward_begin();
    it++;
    it++;
    std::cout<<*it<<std::endl;
    
    auto it2 = bst.backward_begin();
    it2--;
    std::cout<<*it2<<std::endl;
    
    std::cout<<bst.size()<<std::endl;
    
}
