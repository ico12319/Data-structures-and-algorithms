#include <stdio.h>
#include "dfs_traversals.h"

void dfs_traversals::generate_all_traversals(oriented_graph& graph, int src,std::vector<std::vector<int>>& adjacency,size_t index){
        if (index == adjacency.size()) {
            oriented_graph permuted_graph(graph.get_vertex_count(), adjacency);
            dfs_traversal traversal(permuted_graph, src);
            traversals.insert(traversal);
            return;
        } 
        do {
            generate_all_traversals(graph, src, adjacency, index + 1);
        }
        while (std::next_permutation(adjacency[index].begin(), adjacency[index].end()));
}

dfs_traversals::dfs_traversals(oriented_graph& graph,int src){
    auto adj_list = graph.get_graph_adjecancy_list();
    generate_all_traversals(graph, src,adj_list,0);
}

std::ostream& operator<<(std::ostream& os,const dfs_traversals& obj){
    int path_count = 1;
    for(const auto& traversal : obj.traversals){
        std::cout<<"Path "<<path_count<<":"<<" ";
        os<<traversal<<std::endl;
        
        os<<"Tree edges:"<<std::endl;
        if(traversal.get_tree_edges().empty()) os<<"None:"<<std::endl;
        for(const auto& edges : traversal.get_tree_edges())
            os<<edges.first<<" "<<edges.second<<std::endl;
        
        os<<"Back edges:"<<std::endl;
        if(traversal.get_back_edges().empty()) os<<"None:"<<std::endl;
        for(const auto& edges : traversal.get_back_edges())
            os<<edges.first<<" "<<edges.second<<std::endl;
       
        os<<"Forward edges:"<<std::endl;
        if(traversal.get_forward_edges().empty()) os<<"None:"<<std::endl;
        for(const auto& edges : traversal.get_forward_edges())
            os<<edges.first<<" "<<edges.second<<std::endl;
        
        os<<"Cross edges:"<<std::endl;
        if(traversal.get_cross_edges().empty()) os<<"None:"<<std::endl;
        for(const auto& edges : traversal.get_cross_edges())
            os<<edges.first<<" "<<edges.second<<std::endl;
        path_count++;
    }
    return os;
}


const class dfs_traversals::const_dfs_traversal_iterator dfs_traversals::cbegin() const{
    return const_dfs_traversal_iterator(traversals.cbegin());
}

const class dfs_traversals::const_dfs_traversal_iterator dfs_traversals::cend() const{
    return const_dfs_traversal_iterator(traversals.cend());
}
