#include <iostream>
#include <list>
#include <queue>

int find_shortest_path(std::vector<std::list<int>>& adj,int start,int end,std::vector<bool>& seen){
    std::queue<int> q;
    q.push(start);
    seen[start] = true;
    int distance = 0;
    while(!q.empty()){
        size_t curr_level_size = q.size();
        for(int i = 0;i<curr_level_size;i++){
            auto curr_node = q.front();
            q.pop();
            for(const auto& neighbour : adj[curr_node]){
                if(!seen[neighbour]){
                    if(neighbour == end)
                        return distance + 1;
                    q.push(neighbour);
                    seen[neighbour] = true;
                }
            }
        }
        distance++;
    }
    return -1;
}

void dfs_helper(std::vector<std::list<int>>& adj,std::vector<bool>& seen,int start){
    std::cout<<start<<" ";
    seen[start] = true;
    for(int i = 0;i<adj.size();i++){
        if(!seen[i])
            dfs_helper(adj, seen, i);
    }
}

void dfs(std::vector<std::list<int>>& adj){
    std::vector<bool> seen(adj.size(),false);
    dfs_helper(adj, seen, 0);
}

void bfs(std::vector<std::list<int>>& adj,int src){
    std::vector<bool> seen(adj.size(),false);
    std::queue<int> nodes;
    nodes.push(src);
    seen[src] = true;
    while(!nodes.empty()){
        auto curr = nodes.front();
        nodes.pop();
        
        std::cout<<curr<<" ";
        for(const auto& neighbour : adj[curr]){
            if(!seen[neighbour]){
                nodes.push(neighbour);
                seen[neighbour] = true;
            }
        }
    }
}


int main(int argc, const char * argv[]) {
    
    std::vector<std::list<int>> adjecancy_list = {{1,4},{0,3,2},{1,3},{1,2,4},{0,3}};
    std::vector<bool> seen(adjecancy_list.size(),false);
    dfs(adjecancy_list);
    std::cout<<std::endl;
    bfs(adjecancy_list, 0);
}
