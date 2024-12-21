#include <iostream>
#include <list>

enum vertex_color{
    white,
    gray,
    black
};

struct graph{
    std::vector<std::list<size_t>>adj;
    size_t nodes_count;
    std::vector<vertex_color> colors;
    
    graph(size_t nodes_count) : nodes_count(nodes_count),adj(nodes_count,std::list<size_t>()),colors(nodes_count,vertex_color::white){}
    
    void add_edge(size_t start,size_t end){
        adj[start].push_back(end);
    }
};

bool has_cycle_colors(graph& graph,std::vector<bool>& visited,size_t src){
    visited[src] = true;
    graph.colors[src] = vertex_color::gray;
    for(const auto& neighbour : graph.adj[src]){
        if(!visited[neighbour]){
            if(has_cycle_colors(graph, visited, neighbour))
                return true;
        }
        else if(visited[neighbour] && graph.colors[neighbour] == vertex_color::gray)
            return true;
    }
    graph.colors[src] = vertex_color::black;
    return false;
}


bool has_cycle(graph& graph,std::vector<bool>& visited,std::vector<bool>& is_in_stack,size_t src){
    if(!visited[src]){
        visited[src] = true;
        is_in_stack[src] = true;
        for(const auto& neighbour : graph.adj[src]){
            if(!visited[neighbour] && has_cycle(graph, visited, is_in_stack, neighbour))
                return true;
            else if(is_in_stack[neighbour])
                return true;
        }
    }
    is_in_stack[src] = false;
    return false;
}

int main(int argc, const char * argv[]) {
    
    graph graph(3);
    graph.add_edge(0, 1);
    graph.add_edge(0, 2);
    graph.add_edge(2, 1);
    graph.add_edge(1, 2);
    std::vector<bool> visited(graph.nodes_count,false);
    
    
    
}
