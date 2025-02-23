#pragma once
#include "graph.h"
#include <fstream>

class dfs_traversal{
private:
    oriented_graph graph;
    std::vector<int> traversal;
    std::vector<std::pair<int,int>> tree_edges;
    std::vector<std::pair<int,int>> back_edges;
    std::vector<std::pair<int,int>> forward_edges;
    std::vector<std::pair<int,int>> cross_edges;
    int time = 0;

    void generate_dfs_path_helper(std::vector<bool>& visited,int src,std::vector<bool>& is_in_stack,std::vector<int>& discovery_time);

public:
    dfs_traversal(oriented_graph& graph,int starting_node);
    std::vector<std::pair<int,int>> get_back_edges() const;
    std::vector<std::pair<int,int>> get_forward_edges() const;
    std::vector<std::pair<int,int>> get_cross_edges() const;
    std::vector<std::pair<int,int>> get_tree_edges() const;
    std::vector<int> dfs_path() const;
    friend std::ostream& operator<<(std::ostream& os,const dfs_traversal& traversal);
};



