#include <iostream>

std::vector<std::vector<int>> convert(std::vector<std::vector<int>>& edges,int n){
    std::vector<std::vector<int>> adj(n,std::vector<int>());
    for(const auto& edge : edges){
        auto from = edge[0];
        auto to = edge[1];
        
        adj[from].push_back(to);
        adj[to].push_back(from);
    }
    return adj;
}

bool contains_cycle_helper(int current,std::vector<std::vector<int>>& adj,std::vector<bool>& visited,int parent){
    visited[current] = true;
    for(const auto& child : adj[current]){
        if(!visited[child]){
            if(contains_cycle_helper(child, adj, visited, current))
                return true;
        }
        else if(child != parent)
            return true;
    }
    return false;
}

bool contains_cycle(std::vector<std::vector<int>>& adj){
    std::vector<bool> visited(adj.size(),false);
    for(int i = 0;i<adj.size();i++){
        if(!visited[i] && contains_cycle_helper(i, adj, visited, -1))
            return true;
    }
    return false;
}

int main(int argc, const char * argv[]) {
    std::vector<std::vector<int>> edges = {{0,1},{1,2},{2,3},{3,4},{4,5},{5,0}};
    auto adj = convert(edges, 6);
    std::cout<<contains_cycle(adj)<<std::endl;
}
