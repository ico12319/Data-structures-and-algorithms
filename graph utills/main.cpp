#include <iostream>
#include <queue>

//topological sort
//in order to implement this the graph must be DAG!
void topological_sort(std::vector<std::vector<int>>& adj,std::vector<bool>& visited,std::vector<int>& top_sorted,int src){
    visited[src] = true;
    for(const auto& child : adj[src]){
        if(!visited[child])
            topological_sort(adj, visited, top_sorted, child);
    }
    top_sorted.push_back(src);
}

//dijkstra

struct dijkstra_utills{
    int curr_vertex;
    int weight;
    
    bool operator<(const dijkstra_utills& other) const{
        return weight > other.weight;
    }
};

std::vector<int> dijkstra(std::vector<std::vector<std::pair<int,int>>>& adj,int start){
    std::vector<bool> visited(adj.size(),false);
    std::vector<int> distances(adj.size(),INT_MAX);
    std::priority_queue<dijkstra_utills> pq;
    pq.push({start,0});
    distances[start] = 0;
    while(!pq.empty()){
        auto curr_vertex = pq.top().curr_vertex;
        auto curr_weight = pq.top().weight;
        pq.pop();
        
        if(visited[curr_vertex])
            continue;
        visited[curr_vertex] = true;
        
        for(const auto& child : adj[curr_vertex]){
            // relax phase
            if(child.second + curr_weight < distances[child.first]){
                distances[child.first] = child.second + curr_weight;
                pq.push({child.first,child.second + curr_weight});
            }
        }
    }
    return distances;
}


//count connected components in graph
//we can use both dfs and bfs for this goal

void dfs(std::vector<std::vector<int>>& adj,std::vector<bool>& visited,int start){
    visited[start] = true;
    for(const auto& child : adj[start]){
        if(!visited[child])
            dfs(adj, visited, child);
    }
}

int count_connected_components(std::vector<std::vector<int>>& adj){
    int components = 0;
    std::vector<bool> visited(adj.size(),false);
    for(int i = 0;i<adj.size();i++){
        if(!visited[i]){
            dfs(adj, visited, i);
            components++;
        }
    }
    return components;
}

int main(int argc, const char * argv[]) {
    std::vector<std::vector<int>> adj = {{1,2,3},{},{},{}};
    std::vector<bool> visited(adj.size(),false);
    std::vector<int> top_sorted;
    topological_sort(adj, visited, top_sorted, 0);
    for(const auto& el : top_sorted)
        std::cout<<el<<" ";
    std::cout<<std::endl;
    
    
    std::vector<std::vector<int>> adj2 = {{1,2,3},{},{},{},{5},{}};
    std::cout<<count_connected_components(adj2)<<std::endl;
        
    
}
