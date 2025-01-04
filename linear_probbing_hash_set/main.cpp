#include "hash_set.h"

int main(int argc, const char * argv[]) {
    hash_set<int> set;
    set.insert(1);
    set.insert(2);
    set.insert(16);
    set.insert(24);
    set.insert(2);
    
   
    auto it = set.find(28);
    std::cout<<*it<<std::endl;
    
    
    
    for (auto it = set.cbegin(); it!=set.cend(); it++) {
        std::cout<<*it<<" ";
    }
}
