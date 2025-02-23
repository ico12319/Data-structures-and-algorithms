#include <iostream>
#include <queue>

struct node{
    int val;
    std::vector<node*> children;
    
    node(int val) : val(val){}
};

void destroy(node* root){
    if(!root)
        return;
    for(auto& child : root->children)
        destroy(child);
    delete root;
}

// Напишете функция, която проверява дали дърво с произволен брой наследници погледнато от ляво е същото като погледнато от дясно.

bool is_same_from_left_to_right(node* root){
    std::queue<node*> q;
    q.push(root);
    while(!q.empty()){
        auto curr_level_size = q.size();
        std::vector<int> curr_level;
        for(int i = 0;i<curr_level_size;i++){
            node* curr = q.front();
            q.pop();
            curr_level.push_back(curr->val);
            for(const auto& child : curr->children){
                if(child)
                    q.push(child);
            }
        }
        if(curr_level[0] != curr_level[curr_level.size() - 1])
            return false;
    }
    return true;
}

//Дадено е дърво с произволен брой наследници. "Хубав път" в дървото ще наричаме такъв път, в който стойността на всеки връх се дели на стойността на следващия. Да се дефинира функция, която приема такова дърво и връща най-дългия "хубав път" започващ от корена.

void longest_pretty_path_helper(node* root,std::vector<int>& curr_path,std::vector<int>& longest_path){
    if(!root)
        return;
    curr_path.push_back(root->val);
    for(const auto& child : root->children){
        if(root->val % child->val == 0)
            longest_pretty_path_helper(child, curr_path, longest_path);
    }
    if(curr_path.size() > longest_path.size())
        longest_path = curr_path;
    curr_path.pop_back();
    
}

std::vector<int> longest_pretty_path(node* root){
    std::vector<int> curr_path;
    std::vector<int> longest_path;
    longest_pretty_path_helper(root, curr_path, longest_path);
    return longest_path;
}

//Даден е неориентиран граф. Намерете сумата на средно аритметичното на върховете на всички свързани компоненти в графа. Входът е във вида : цяло число n - брой на върховете, цяло число m - брой на ребрата , m реда във вида a b, което означава ребро от а към b.
std::vector<std::vector<int>> convert(std::vector<std::vector<int>>& edges,int n){
    std::vector<std::vector<int>> adj(n,std::vector<int>());
    for(const auto& edge : edges){
        auto from = edge[0];
        auto to = edge[1];
        
        adj[from].push_back(to);
        adj[to].push_back(from);
    }
    return adj;
}

void dfs(std::vector<std::vector<int>>& adj,std::vector<bool>& visited,int& count,int& sum,int src){
    visited[src] = true;
    sum+=src;
    count++;
    for(const auto& child : adj[src]){
        if(!visited[child])
            dfs(adj, visited, count, sum, child);
    }
}

double find_sum_from_average(std::vector<std::vector<int>>& adj){
    std::vector<bool> visited(adj.size(),false);
    double result = 0;
    for(int i = 0;i<adj.size();i++){
        if(!visited[i]){
            int count = 0;
            int sum = 0;
            dfs(adj, visited, count, sum, i);
            auto average = static_cast<double>(sum) / count;
            result += average;
        }
    }
    return result;
}

// Даден е ориентиран граф и стартов връх v. Да се напише функция, която намира сумата на елементите, които са на четно разстояние от v и сумата на елементите, които са на нечетно разстояние от v. Входът е във вида : цяло число n - брой на върховете, цяло число m - брой на ребрата , m реда във вида a b, което репрезентира ребро от а към b.

std::vector<std::vector<int>> convert_to_adj(std::vector<std::vector<int>>& edges,int n){
    std::vector<std::vector<int>> adj(n,std::vector<int>());
    for(const auto& edge : edges){
        auto from = edge[0];
        auto to = edge[1];
        
        adj[from].push_back(to);
    }
    return adj;
}

std::pair<int,int> bfs(std::vector<std::vector<int>>& edges,int n,int src){
    auto adj = convert_to_adj(edges, n);
    std::vector<bool> visited(n,false);
    std::queue<int> q;
    q.push(src);
    visited[src] = true;
    int distance = 0;
    int even_sum = 0;
    int odd_sum = 0;
    while(!q.empty()){
        auto curr_level_size = q.size();
        int curr_level_sum = 0;
        for(int i = 0;i<curr_level_size;i++){
            auto curr_vertex = q.front();
            q.pop();
            curr_level_sum += curr_vertex;
            for(const auto& child : adj[curr_vertex]){
                if(!visited[child]){
                    q.push(child);
                    visited[child] = true;
                }
            }
        }
        if(distance % 2 == 0)
            even_sum += curr_level_sum;
        else
            odd_sum += curr_level_sum;
        distance++;
    }
    return std::make_pair(even_sum, odd_sum);
        
}

int main(int argc, const char * argv[]) {
    node* root = new node(32);
    root->children.push_back(new node(8));
    root->children.push_back(new node(9));
    root->children.push_back(new node(16));
    root->children.at(0)->children.push_back(new node(4));
    root->children.at(0)->children.push_back(new node(7));
    root->children.at(0)->children.push_back(new node(2));
    root->children.at(2)->children.push_back(new node(1));
    root->children.at(2)->children.push_back(new node(4));
    root->children.at(0)->children.at(2)->children.push_back(new node(0));
    root->children.at(2)->children.at(0)->children.push_back(new node(1));
    root->children.at(2)->children.at(1)->children.push_back(new node(3));
    
   
    auto longest_path = longest_pretty_path(root);
    for(const auto& el : longest_path)
        std::cout<<el<<" ";
    std::cout<<std::endl;
    destroy(root);
    
    int n = 9;
    std::vector<std::vector<int>> edges = {{7,8},{4,5},{4,6},{5,6},{2,1},{0,3},{0,1},{2,3}};
    auto adj = convert(edges, n);
    std::cout<<find_sum_from_average(adj)<<std::endl;
    
    
    int nodes_count = 5;
    std::vector<std::vector<int>> edges2 = {{0,4},{0,3},{0,1},{1,3},{1,2},{3,2},{4,3}};
    auto pair = bfs(edges2, nodes_count, 0);
    std::cout<<pair.first<<" "<<pair.second<<std::endl;
    
}
