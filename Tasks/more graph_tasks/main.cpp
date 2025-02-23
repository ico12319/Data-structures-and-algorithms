#include <iostream>
#include <map>

//Да се напише функция, която намира сумата на най - големите елементи на отделните свързани компоненти в (неориентиран) граф.

void find_max_element_from_connected_component(std::vector<std::vector<int>>& adj,int src,std::vector<bool>& visited,int& max_element){
    visited[src] = true;
    max_element = std::max(max_element, src);
    for(const auto& neighbour : adj[src]){
        if(!visited[neighbour])
            find_max_element_from_connected_component(adj,neighbour, visited,max_element);
    }
}

int get_sum_from_connected_components(std::vector<std::vector<int>>& adj){
    int final_sum = 0;
    std::vector<bool> visited(adj.size(),false);
    for(int i = 0;i<adj.size();i++){
        if(!visited[i]){
            int curr_max = INT_MIN;
            find_max_element_from_connected_component(adj, i, visited, curr_max);
            final_sum+=curr_max;
        }
    }
    return final_sum;
}


//Имаме n курса, които трябва да вземем, означени с числа от 0 до n - 1. Като вход получаваме вектор от двойки (i, j) и брой на курсовете. Всяка двойка във вектора означава, че курсът с етикет i трябва да се вземе преди курсът с етикет j. Да се провери дали е възможно курсовете да се вземат.

std::vector<std::vector<int>> turn_into_adjecancy_list(std::vector<std::pair<int,int>>& edge_list,int courses_count){
    std::vector<std::vector<int>> adj(courses_count,std::vector<int>());
    for(const auto& edge_link : edge_list){
        auto link1 = edge_link.first;
        auto link2 = edge_link.second;
        adj[link1].push_back(link2);
    }
    return adj;
}

bool has_cycle_helper(std::vector<std::vector<int>>& adj,std::vector<bool>& visited,std::vector<bool>& is_in_stack,int start){
    visited[start] = true;
    is_in_stack[start] = true;
    for(const auto& neighbour : adj[start]){
        if(!visited[neighbour] && has_cycle_helper(adj, visited, is_in_stack, neighbour))
            return true;
        else if(is_in_stack[neighbour])
            return true;
    }
    is_in_stack[start] = false;
    return false;
}

bool has_cycle(std::vector<std::pair<int,int>>& edge_list,int courses_count){
    std::vector<std::vector<int>> adj = turn_into_adjecancy_list(edge_list, courses_count);
    std::vector<bool> visited(courses_count,false);
    std::vector<bool> is_in_stack(courses_count,false);
    for(int i = 0;i<courses_count;i++){
        if(!visited[i] && has_cycle_helper(adj, visited, is_in_stack, i))
            return true;
    }
    return false;
}

//Даден е ориентиран граф от уникални символи g. Да се напише функция, която приема графа и дума с произволна дължина и проверява дали думата може да се получи чрез конкатенирането на последователни различни върхове в графа.

bool can_read(std::multimap<char, char>& graph,size_t at,const std::string& searched_word){
    if(searched_word.size() == 1 && graph.contains(searched_word[0])) return true;
    if(searched_word.size() == 1 && !graph.contains(searched_word[0])) return false;
    if(at == searched_word.size() - 1)
        return true;
    auto successor = graph.find(searched_word[at]);
    if(successor == graph.end())
        return false;
    while(successor != graph.end() && successor->first == searched_word[at]){
        if(successor->second == searched_word[at + 1])
            return can_read(graph, at + 1, searched_word);
        successor++;
    }
    return false;
}


int main(int argc, const char * argv[]) {
    //task 1
    std::vector<std::vector<int>> adj = {{1,3},{0,2},{1,3},{0,2},{4,5},{5,4},{6}};
    std::cout<<get_sum_from_connected_components(adj)<<std::endl;
    
    //task 2
    std::vector<std::pair<int,int>> edge_list = {{0,1},{1,0}};
    int n = 2;
    std::cout<<has_cycle(edge_list, n)<<std::endl;
    
    //task 3
    std::multimap<char, char> graph;
    graph.insert({'A','B'});
    graph.insert({'A','C'});
    graph.insert({'B','D'});
    graph.insert({'B','K'});
    graph.insert({'C','F'});
    
    std::string word = "ABD";
    
    std::cout<<can_read(graph, 0, word)<<std::endl;
    
    
}
