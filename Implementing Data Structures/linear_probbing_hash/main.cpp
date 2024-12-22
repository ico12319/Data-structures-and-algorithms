#include "linear_probbing_hash.hpp"

int main(int argc, const char * argv[]) {
    linear_probbing_hash<int, int> table;
    table.insert(1, 2);
    table.insert(12, 5);
    table.insert(2, 8);
    table.insert(12,8);
    table.insert(6, 0);
    table.erase(6);
    table.erase(1);
    table.insert(1, 8);

    table.erase(2);
    table.print();

}
