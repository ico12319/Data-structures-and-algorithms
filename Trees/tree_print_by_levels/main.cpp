#include <iostream>
#include <queue>

struct node{
    char data;
    std::vector<node*> children;
    
    node(char data) : data(data){}
};

void print_by_levels(node* root){
    std::queue<node*> levels;
    levels.push(root);
    while(!levels.empty()){
        int size = levels.size();
        for(int i = 0;i<size;i++){
            node* curr = levels.front();
            levels.pop();
            
            std::cout<<curr->data<<" ";
            
            if(!curr->children.empty()){
                for(const auto& node : curr->children)
                    levels.push(node);
            }
        }
        std::cout<<std::endl;
    }
}




int main(int argc, const char * argv[]) {
    node* root = new node('a');
    root->children.push_back(new node('b'));
    root->children.push_back(new node('c'));
    root->children.push_back(new node('d'));
    root->children.at(0)->children.push_back(new node('x'));
    root->children.at(0)->children.push_back(new node('y'));
    
    print_by_levels(root);
    
}
