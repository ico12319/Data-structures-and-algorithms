#include "map.hpp"

int main(int argc, const char * argv[]) {
    map<int,int> m;
    m.insert(1, 12);
    m.insert(1, 5);
    m.insert(2, 6);
    m.insert(7, 9);
    m.insert(17, 44);
    
    std::cout<<m.contains(17)<<std::endl;
    m.erase(17);
    m.print();
}
