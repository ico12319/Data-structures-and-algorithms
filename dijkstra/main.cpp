#include <iostream>
#include <queue>

std::vector<int> dijkstra(std::vector<std::vector<std::pair<int,int>>>& adj,int src){
    std::vector<int> distances(adj.size(),INT_MAX);
    std::priority_queue<std::pair<int,int>,std::vector<std::pair<int,int>>,std::greater<>> pq;
    pq.emplace(0,src);
    while(!pq.empty()){
        int curr_distance = pq.top().first;
        int curr_node = pq.top().second;
        pq.pop();
        for(const auto& node : adj[curr_node]){
            int distance_to_node = curr_distance + node.second;
            if(distance_to_node < distances[node.first]){
                distances[node.first] = distance_to_node;
                pq.emplace(distance_to_node,node.first);
            }
        }
    }
    return distances;

}

int main(int argc, const char * argv[]) {
    std::vector<std::vector<std::pair<int,int>>> adj = {{{1,4},{2,2}},{{0,4},{2,1}},{{0,2},{1,1}}};
    auto distances = dijkstra(adj, 0);
    std::cout<<distances[1]<<std::endl;
}
