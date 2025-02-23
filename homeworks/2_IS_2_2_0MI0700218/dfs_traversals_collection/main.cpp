#include "dfs_traversals.h"

int main(){
    oriented_graph graph(4);
    graph.add_edge(0, 1);
    graph.add_edge(0, 2);
    graph.add_edge(1, 2);
    graph.add_edge(2, 1);
    graph.add_edge(1, 3);
    graph.add_edge(3, 0);
    
    dfs_traversals traversal(graph, 0);
    
    
    std::cout<<traversal<<std::endl;


}
