#include <iostream>
#include <queue>

struct node{
    int val;
    node* left;
    node* right;
    
    node(int val) : val(val){}
};



//Task 01: check if root to leaf paths form a progression
//5, 7, 9, 11, 13, 15 etc.

bool is_progression(std::vector<int>& v){
    if(v.size() <= 2) return true;
    int orig_offset = v[0] - v[1];
    for(int i = 1;i<v.size() - 1;i++){
        if(v[i] - v[i + 1] != orig_offset)
            return false;
    }
    return true;
}


void forms_progression_helper(node* root,bool& flag,std::vector<int>& path){
    if(!root || flag) return;
    path.push_back(root->val);
    if(!root->left && !root->right && is_progression(path)){
        flag = true;
        return;
    }
    forms_progression_helper(root->left, flag, path);
    forms_progression_helper(root->right, flag, path);
    path.pop_back();
}

bool forms_progression(node* root){
    bool flag = false;
    std::vector<int> path;
    forms_progression_helper(root,flag,path);
    return flag;
    
}


//task2 : check whether a tree is a bst(stoycho's way)
// my way -> std::is_sorted(dummy)
bool is_bst_helper(node* root,int left_interval,int right_interval){
    if(!root) return true;
    
    if(root->val < left_interval || root->val > right_interval)
        return false;
    
    return is_bst_helper(root->left, left_interval, root->val) && is_bst_helper(root->right, root->val, right_interval);
}

bool is_bst(node* root){
    return is_bst_helper(root, INT_MIN, INT_MAX);
}

//task3: check if any level in a tree forms a progression
void print(const std::vector<int>& v){
    for(auto it = v.begin();it!=v.end();it++)
        std::cout<<*it<<" ";
    std::cout<<std::endl;
}

void level_progression(node* root){
    if(!root) return;
    std::queue<node*> levels;
    levels.push(root);
    
    while(!levels.empty()){
        size_t level_size = levels.size();
        std::vector<int> progression_candidate;
        for(int i = 0;i<level_size;i++){
            node* curr = levels.front();
            progression_candidate.push_back(curr->val);
            levels.pop();
            if(curr->left)
                levels.push(curr->left);
            if(curr->right)
                levels.push(curr->right);
        }
        if(is_progression(progression_candidate))
            print(progression_candidate);
    }
}
int main(int argc,const char * argv[]) {
    
    node* root = new node(5);
    root->left = new node(7);
    root->right = new node(13);
    root->left->left = new node(9);
    root->left->right = new node(12);
    root->right->left = new node(15);
    root->right->right = new node(18);
    
    level_progression(root);
    
    
}
