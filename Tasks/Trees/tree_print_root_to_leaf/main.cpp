#include <iostream>


struct binary_node{
    char val;
    binary_node* left;
    binary_node* right;
    
    binary_node(char val) : val(val),left(nullptr),right(nullptr){}
};


struct nary_node{
    char root;
    std::vector<nary_node*> children;
};

void print_dfs_helper(binary_node* root,std::string& word){
    if(!root) return;
    word+=root->val;
    if(!root->left && !root->right)
        std::cout<<word<<std::endl;
    print_dfs_helper(root->left, word);
    print_dfs_helper(root->right, word);
    word.pop_back();
}


void print_dfs_binary(binary_node* root){
    std::string word;
    print_dfs_helper(root,word);
}


void print_dfs_helper_nary_tree(nary_node* root,std::string& str){
    str+=root->root;
    if(root->children.empty())
        std::cout<<str<<std::endl;
    else{
        for(const auto& node : root->children)
            print_dfs_helper_nary_tree(node, str);
    }
    str.pop_back();
}


void print_dfs_nary(nary_node* root){
    std::string str;
    print_dfs_helper_nary_tree(root, str);
}

int main(int argc, const char * argv[]) {
    
    nary_node* root = new nary_node{'a'};
    root->children.push_back(new nary_node{'b'});
    root->children.push_back(new nary_node{'c'});
    root->children.push_back(new nary_node{'d'});
    root->children.at(0)->children.push_back(new nary_node{'x'});
    root->children.at(0)->children.push_back(new nary_node{'y'});
    
    
}
