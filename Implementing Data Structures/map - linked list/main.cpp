#include "separate_chaining_map.hpp"

int main(int argc, const char * argv[]) {
    map<int,int> m;
    m.insert(1, 4);
    m.insert(2, 12);
    m.insert(5, 99);
    m.insert(6, 99);
    m.insert(7, 99);
    m.insert(8, 99);
    m.insert(9, 99);
    m.insert(19, 12);
    m.insert(25, 99);
    m.insert(21, 99);
    m.insert(22, 99);
    m.insert(39, 99);
    m.print();
}
