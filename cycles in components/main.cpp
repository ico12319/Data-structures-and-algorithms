#include <iostream>
#include <unordered_set>

//Намерете броя на свързаните компоненти в графа, в които има цикъл

class union_find{
private:
    std::vector<int> parent_array;
    std::vector<int> sizes;
    size_t connected_components;
    
public:
    union_find(int n) : connected_components(n){
        parent_array.resize(n);
        for(int i = 0;i<n;i++)
            parent_array[i] = i;
        sizes.resize(n,1);
    }
    
    int find(int node){
        if(node == parent_array[node])
            return node;
        return parent_array[node] = find(parent_array[node]);
    }
    
    bool are_in_one_set(int node1,int node2){
        return find(node1) == find(node2);
    }
    
    bool union_by_size(int node1,int node2){
        auto parent1 = find(node1);
        auto parent2 = find(node2);
        
        if(parent1 == parent2)
            return false;
        if(sizes[parent1] < sizes[parent2]){
            parent_array[parent1] = parent2;
            sizes[parent2] += sizes[parent1];
        }
        else{
            parent_array[parent2] = parent1;
            sizes[parent1] += sizes[parent2];
        }
        connected_components--;
        return true;
    }
    
    size_t components_count() const{
        return connected_components;
    }
};


int compos_with_cycles_count(std::vector<std::vector<int>>& edges,int n){
    std::unordered_set<int> roots_already_in_cycle;
    union_find uf(n);
    int count = 0;
    for(const auto& edge : edges){
        auto from = edge[0];
        auto to = edge[1];
        if(!uf.union_by_size(from, to)){
            auto ultimate_parent = uf.find(from);
            if(!roots_already_in_cycle.contains(ultimate_parent))
                count++;
            roots_already_in_cycle.insert(ultimate_parent);
        }
    }
    return count;
}

int main(int argc, const char * argv[]) {
    int n = 10;
    std::vector<std::vector<int>> edges = {{0,1},{1,2},{0,2},{3,4},{4,5},{6,7},{7,8},{8,9},{9,7}};
    std::cout<<compos_with_cycles_count(edges, n)<<std::endl;
}
