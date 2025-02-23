#include <iostream>
#include <queue>

//"Лявоориентиран път" в двоично дърво се нарича всеки път от корена на дървото до листо, в който движението винаги се извършва наляво към левия наследник и се допуска най-много едно придвижване надясно.

struct node{
    int val;
    node* left;
    node* right;
    
    node(int val) : val(val),left(nullptr),right(nullptr){}
};


void destroy(node* root){
    if(!root)
        return;
    destroy(root->left);
    destroy(root->right);
    delete root;
}

void left_oriented_paths(node* root,std::vector<int>& curr_path,std::vector<std::vector<int>>& all_paths,bool go_right){
    if(!root)
        return;
    curr_path.push_back(root->val);
    if(!root->left && !root->right){
        all_paths.push_back(curr_path);
        curr_path.pop_back();
        return;
    }
    left_oriented_paths(root->left, curr_path,all_paths, go_right);
    if(go_right)
        return;
    go_right = true;
    left_oriented_paths(root->right, curr_path, all_paths, go_right);
    curr_path.pop_back();
}

std::vector<std::vector<int>> all_left_oriented_paths(node* root){
    std::vector<int> path;
    std::vector<std::vector<int>> all_paths;
    left_oriented_paths(root,path , all_paths, false);
    return all_paths;
}

//От стандартния вход постъпват две естествени числа N ≤ 50 и K ≤ 2500, последвани от K на брой двойки от естествени числа (vi, ui), i = 0,...,K-1. Въведените стойности дефинират неориентиран граф граф G: <V={0,...,N-1}, E={(vi, ui) | i = 0,...,K-1} U {(ui, vi) | i = 0,...,K-1}}. Да се реализира подходящо представяне на графа и за така въведения граф да се намери и изведе на стандартния изход:Броя на различните му свързани компоненти.За всяка свързана компонента да се изведе списък с върховете, които принадлежат към нея.Информацията за свързаните компоненти да се изведе подредена относно броя на елементите им.


struct comparator{
    bool operator()(const std::vector<int>& v1,const std::vector<int>& v2) const{
        return v1.size() < v2.size();
    }
};

void dfs(std::vector<std::vector<int>>& adj,std::vector<bool>& visited,std::vector<int>& nodes_in_component,int src){
    visited[src] = true;
    nodes_in_component.push_back(src);
    for(const auto& child : adj[src]){
        if(!visited[child])
            dfs(adj, visited,nodes_in_component, child);
    }
}

std::priority_queue<std::vector<int>,std::vector<std::vector<int>>,comparator> components_info(std::vector<std::vector<int>>& adj,int& components_count){
    std::vector<std::vector<int>> components;
    std::vector<bool> visited(adj.size(),false);
    for(int i = 0;i<adj.size();i++){
        if(!visited[i]){
            std::vector<int> elements_in_component;
            components_count++;
            dfs(adj, visited, elements_in_component, i);
            components.push_back(elements_in_component);
        }
    }
    std::priority_queue<std::vector<int>,std::vector<std::vector<int>>,comparator> pq(components.begin(),components.end());
    return pq;
}


//Да се дефинира шаблон Counter, който реализира “преброител” на елементи от тип T. Преброителят се инициализира с нулева бройка за всички елементи от тип T и позволява да се “добавя” и “премахва” по един брой от даден елемент x на T. Шаблонът да дефинира следните операции:
//[0.25т.] operator +=: увеличава броя на елемента x;

//[0.25т.] съответен оператор +;

//[0.25т.] operator -=: намалява броя на елемента x;

//[0.25т.] съответен оператор -;

//[0.25т.] count: Връща колко елемента имат брой, различен от 0;

//[0.25т.] оператор за индексиране [x], дава броя на x;

//[0.25т.] operator + за събиране на два брояча (бройките на резултатния брояч са сумите на бройките на изходните броячи).

template<class value>
class counter{
private:
    std::unordered_map<value, size_t> count;
    
public:
    counter() = default;
    counter& operator+=(int x){
        count[x]++;
        return *this;
    }
    counter operator+(int x){
        counter copy(*this);
        (*this)+=x;
        return copy;
    }
    counter& operator-=(int x){
        count[x]--;
        if(count[x] == 0)
            count.erase(x);
        return *this;
    }
    counter operator-(int x){
        counter copy(*this);
        (*this)-=x;
        return copy;
    }
    size_t get_count() const{
        return count.size();
    }
    
    size_t operator[](size_t element) const{
        auto it = count.find(element);
        if(it != count.end())
            return it->second;
        return 0;
    }
};

struct list_node{
    int val;
    list_node* next;
    
    list_node(int val) : val(val),next(nullptr){}
};

void destroy(list_node* head){
    list_node* curr = head;
    while(curr){
        auto to_delete = curr;
        curr = curr->next;
        delete to_delete;
    }
}

int main(int argc, const char * argv[]) {;
}
