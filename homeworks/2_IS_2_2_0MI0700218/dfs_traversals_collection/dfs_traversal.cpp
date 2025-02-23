#include <stdio.h>
#include "dfs_traversal.h"

dfs_traversal::dfs_traversal(oriented_graph& graph,int staring_node) : time(0){
    this->graph = graph;
    std::vector<bool> visited(graph.get_vertex_count(),false);
    std::vector<bool> is_in_stack(graph.get_vertex_count(),false);
    std::vector<int> discovery_time(graph.get_vertex_count(),0);
    for(int i = 0;i<graph.get_vertex_count();i++){
        if(!visited[i])
            generate_dfs_path_helper(visited, staring_node, is_in_stack, discovery_time);
    }
}

void dfs_traversal::generate_dfs_path_helper(std::vector<bool>& visited, int src, std::vector<bool>& is_in_stack,std::vector<int>& discovery_time){
    visited[src] = true;
    is_in_stack[src] = true;
    traversal.push_back(src);
    discovery_time[src] = ++time;
    for(const auto& child : graph.get_vertex_children(src)){
        if(!visited[child]){
            tree_edges.emplace_back(src,child);
            generate_dfs_path_helper(visited, child, is_in_stack,discovery_time);
        }
        else if(is_in_stack[child])
            back_edges.emplace_back(src,child);
        else
        {
            if(discovery_time[child] > discovery_time[src])
                forward_edges.emplace_back(src,child);
            else
                cross_edges.emplace_back(src,child);
        }
    }
    is_in_stack[src] = false;
 }

std::vector<std::pair<int,int>> dfs_traversal::get_back_edges() const{
    return back_edges;
}

std::vector<std::pair<int,int>> dfs_traversal::get_forward_edges() const{
    return forward_edges;
}

std::vector<std::pair<int,int>> dfs_traversal::get_cross_edges() const{
    return cross_edges;
}

std::vector<std::pair<int,int>> dfs_traversal::get_tree_edges() const{
    return tree_edges;
}

std::vector<int> dfs_traversal::dfs_path() const{
    return traversal;
}

std::ostream& operator<<(std::ostream& os,const dfs_traversal& traversal){
    for(int i = 0;i<traversal.traversal.size();i++)
        os<<traversal.traversal[i]<<" ";
    return os;
}

