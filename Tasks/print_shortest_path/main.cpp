#include <iostream>
#include <queue>


struct dijkstra_utills{
    size_t curr_vertex;
    size_t weight;
    
    bool operator<(const dijkstra_utills& other) const{
        return weight > other.weight;
    }
};


void init_parent_array(std::vector<size_t>& parent_array){
    for(int i = 0;i<parent_array.size();i++)
        parent_array[i] = i;
}



std::vector<size_t> find_shortest_path(std::vector<std::vector<std::pair<size_t,size_t>>>& adj,size_t start,size_t end){
    std::vector<size_t> distances(adj.size(),INT_MAX);
    std::vector<bool> visited(adj.size(),false);
    std::vector<size_t> parent_array(adj.size(),0);
    init_parent_array(parent_array);
    std::priority_queue<dijkstra_utills> pq;
    distances[start] = 0;
    pq.push({start,0});
    while(!pq.empty()){
        auto vertex = pq.top().curr_vertex;
        auto weight = pq.top().weight;
        pq.pop();
        for(const auto& child : adj[vertex]){
            if(!visited[child.first] && child.second + weight < distances[child.first]){
                parent_array[child.first] = vertex;
                distances[child.first] = child.second + weight;
                pq.push({child.first,distances[child.first]});
            }
        }
        visited[vertex] = true;
    }
    
    std::vector<size_t> shortest_path;
    size_t curr_node = end;
    if(distances[end] == INT_MAX)
        return {};
    shortest_path.push_back(curr_node);
    while(parent_array[curr_node] != curr_node){
        curr_node = parent_array[curr_node];
        shortest_path.push_back(curr_node);
    }
    std::reverse(shortest_path.begin(),shortest_path.end());
    return shortest_path;
}

int main(int argc, const char * argv[]) {
    std::vector<std::vector<std::pair<size_t,size_t>>> adj = {{{1,2},{3,1}},{{0,2},{2,4},{4,5}},{{3,3},{1,4},{4,1}},{{0,1},{2,3}},{{1,5},{2,1}}};
    auto shortest_path = find_shortest_path(adj, 0, 4);
    for(const auto& el : shortest_path)
        std::cout<<el<<" ";
    std::cout<<std::endl;
    
}
