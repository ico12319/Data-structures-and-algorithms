#pragma once
#include <iostream>

class union_find{
private:
    std::vector<int> parent_array;
    std::vector<int> components_size;
    
public:
    union_find(int n);
    void union_by_size(int node1,int node2);
    int find(int node);
};
