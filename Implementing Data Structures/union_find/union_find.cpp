#include <stdio.h>
#include "union_find.h"

union_find::union_find(int n){
    parent_array.resize(n);
    components_size.resize(n,1);
    for(int i = 0;i<n;i++)
        parent_array[i] = i;
}

int union_find::find(int node){
    if(node == parent_array[node])
        return node;
    return parent_array[node] = find(parent_array[node]); // path compression
}

void union_find::union_by_size(int node1, int node2){
    int ultimate_parent1 = find(node1);
    int ultimate_parent2 = find(node2);
    if(ultimate_parent1 == ultimate_parent2)
        return;
    if(components_size[ultimate_parent1] > components_size[ultimate_parent2]){
        parent_array[ultimate_parent2] = ultimate_parent1;
        components_size[ultimate_parent1] += components_size[ultimate_parent2];
    }
    else{
        parent_array[ultimate_parent1] = ultimate_parent2;
        components_size[ultimate_parent2] += components_size[ultimate_parent1];
    }
}


