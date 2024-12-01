#include "Bst.hpp"

int main(int argc, const char * argv[]) {
    Bst<int> b;
    
    
    for(int i = 0;i<55;i++)
        b.insert(i);
    
    b.remove(54);
    b.remove(27);
    b.remove(1);
    b.remove(6);
    
    
    for(int i = 0;i<b.getSize();i++)
        std::cout<<b[i]<<" ";
}
