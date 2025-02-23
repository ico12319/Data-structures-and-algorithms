#include "graph.h"

oriented_graph::oriented_graph(size_t vertex_count) : vertex_count(vertex_count),adj(vertex_count,std::vector<int>()){}

oriented_graph::oriented_graph(size_t vertex_count,const std::vector<std::vector<int>>& adjecancy_list){
    this->vertex_count = vertex_count;
    this->adj = adjecancy_list;
}

void oriented_graph::add_edge(int from, int to){
    adj[from].push_back(to);
}

size_t oriented_graph::get_vertex_count() const{
    return adj.size();
}

std::vector<int> oriented_graph::get_vertex_children(size_t vertex) const{
    return adj[vertex];
}

std::vector<std::vector<int>> oriented_graph::get_graph_adjecancy_list() const{
    return adj;
}
