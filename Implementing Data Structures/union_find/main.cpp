#include "union_find.h"

int main(int argc, const char * argv[]) {
    union_find uf(5);
    uf.union_by_size(0, 1);
    uf.union_by_size(0, 2);
    
    
    uf.union_by_size(3, 4);
    uf.union_by_size(2, 3);
    if(uf.find(3) == uf.find(0))
        std::cout<<"same group"<<std::endl;
    else
        std::cout<<"not same group"<<std::endl;
}
