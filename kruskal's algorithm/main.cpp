#include <iostream>

class union_find{
private:
    std::vector<int> parent_array;
    std::vector<int> size;
    
public:
    union_find(int n){
        parent_array.resize(n);
        size.resize(n,1);
        
        for(int i = 0;i<n;i++)
            parent_array[i] = i;
    }
    
    bool union_by_size(int node1,int node2){
        int ultimate_parent1 = find(node1);
        int ultimate_parent2 = find(node2);
        
        if(ultimate_parent1 == ultimate_parent2)
            return false;
        if(size[ultimate_parent1] < size[ultimate_parent2]){
            parent_array[ultimate_parent1] = ultimate_parent2;
            size[ultimate_parent2] += size[ultimate_parent1];
        }
        else{
            parent_array[ultimate_parent2] = ultimate_parent1;
            size[ultimate_parent1] += size[ultimate_parent2];
        }
        return true;
    }
    
    int find(int node){
        if(node == parent_array[node])
            return node;
        return parent_array[node] = find(parent_array[node]);
    }
};

struct edge{
    int from;
    int to;
    int weight;
    
    bool operator<(const edge& other) const{
        return weight < other.weight;
    }
};


int minimal_spanning_tree_weight(const std::vector<std::vector<std::pair<int,int>>>& adj){
    int total_weight = 0;
    std::vector<edge> edges;
    for(int i = 0;i<adj.size();i++){
        int from = i;
        for(const auto& child : adj[i]){
            int to = child.first;
            int weight = child.second;
            edges.push_back({from,to,weight});
        }
    }
    std::sort(edges.begin(),edges.end());
    union_find uf(adj.size());
    for(int i = 0;i<edges.size();i++){
        if(uf.union_by_size(edges[i].from, edges[i].to))
            total_weight += edges[i].weight;
    }
    return total_weight;
    
}


int main(int argc, const char * argv[]) {
    std::vector<std::vector<std::pair<int,int>>> adj = {{{1,10},{3,5},{2,6}},{{0,10},{3,15}},{{0,6},{3,4}},{{0,5},{2,4}}};
    std::cout<<minimal_spanning_tree_weight(adj)<<std::endl;
}
