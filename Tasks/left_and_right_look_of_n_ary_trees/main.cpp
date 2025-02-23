#include <iostream>
#include <queue>




struct node{
    int val;
    std::vector<node*> children;
    
    node(int val) : val(val){}
};


std::vector<int> left_look(node* root){
    std::queue<node*> curr_level;
    std::vector<int> left_look;
    left_look.push_back(root->val);
    curr_level.push(root);
    while(!curr_level.empty()){
        auto curr_level_size = curr_level.size();
        for(int i = 0;i<curr_level_size;i++){
            node* curr_top = curr_level.front();
            curr_level.pop();
            for(const auto& child : curr_top->children){
                if(child)
                    curr_level.push(child);
            }
        }
        if(!curr_level.empty())
            left_look.push_back(curr_level.front()->val);
    }
    return left_look;
}

std::vector<int> right_look(node* root){
    std::queue<node*> curr_level;
    std::vector<int> right_view;
    curr_level.push(root);
    while(!curr_level.empty()){
        auto curr_level_size = curr_level.size();
        std::vector<int> level;
        for(int i = 0;i<curr_level_size;i++){
            node* curr_top = curr_level.front();
            curr_level.pop();
            level.push_back(curr_top->val);
            for(const auto& child : curr_top->children){
                if(child)
                    curr_level.push(child);
            }
        }
        right_view.push_back(level.back());
    }
    return right_view;
}

int main(int argc, const char * argv[]) {
    node* root = new node(6);
    root->children.push_back(new node(8));
    root->children.push_back(new node(5));
    root->children.push_back(new node(4));
    root->children.at(0)->children.push_back(new node(0));
    root->children.at(0)->children.push_back(new node(1));
    root->children.at(1)->children.push_back(new node(2));
    root->children.at(1)->children.push_back(new node(3));
    root->children.at(1)->children.push_back(new node(10));
    root->children.at(2)->children.push_back(new node(11));
    root->children.at(2)->children.at(0)->children.push_back(new node(16));
    
    auto left_view = right_look(root);
    for(const auto& el : left_view)
        std::cout<<el<<" ";
    
}
