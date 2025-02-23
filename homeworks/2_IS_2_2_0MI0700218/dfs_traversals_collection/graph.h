#pragma once
#include <iostream>

class oriented_graph{
private:
    std::vector<std::vector<int>> adj;
    size_t vertex_count;
    
public:
    oriented_graph() = default;
    oriented_graph(size_t vertex_count);
    oriented_graph(size_t vertex_count,const std::vector<std::vector<int>>& adjecancy_list);
    void add_edge(int from,int to);
    size_t get_vertex_count() const;
    std::vector<int> get_vertex_children(size_t vertex) const;
    std::vector<std::vector<int>> get_graph_adjecancy_list() const;
};
