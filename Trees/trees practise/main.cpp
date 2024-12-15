#include <iostream>
#include <queue>

struct node{
    char val;
    std::vector<node*> children;
    
    node(char val) : val(val){}
};

void generate_all_words_from_root_to_leaves(node* root,std::vector<std::string>& words,std::string& curr_word){
    curr_word+=root->val;
    if(root->children.size() == 0)
        words.push_back(curr_word);
    else{
        for(const auto& node : root->children)
            generate_all_words_from_root_to_leaves(node, words, curr_word);
    }
    curr_word.pop_back();
}

auto generate_words(node* root){
    std::vector<std::string> words;
    std::string curr_word;
    generate_all_words_from_root_to_leaves(root, words, curr_word);
    return words;
}

auto generate_all_words_by_levels(node* root){
    std::queue<node*> nodes;
    nodes.push(root);
    std::vector<std::string> words;
    while (!nodes.empty()) {
        size_t curr_size = nodes.size();
        std::string curr_word;
        for(int i = 0;i<curr_size;i++){
            node* curr_node = nodes.front();
            nodes.pop();
            curr_word+=curr_node->val;
            
            if(!curr_node->children.empty())
                for(int i = 0;i<curr_node->children.size();i++)
                    nodes.push(curr_node->children[i]);
        }
        words.push_back(curr_word);
    }
    return words;
}


auto get_children(std::vector<int>& curr_level,std::vector<int>& parrent_array){
    std::vector<int> children;
    for(int i = 0;i<parrent_array.size();i++){
        auto it = std::find(curr_level.begin(),curr_level.end(),parrent_array[i]);
        if(it != curr_level.end())
            children.push_back(i);
    }
    return children;
}

auto get_height(std::vector<int>& parrent_array){
    size_t height = -1;
    std::vector<int> curr_level = {-1};
    while(!curr_level.empty()){
        height++;
        curr_level = get_children(curr_level, parrent_array);
    }
    return height;
}

int main(int argc, const char * argv[]) {
   
    std::vector<int> parrent_array = {-1,0,0,1,1,2};
    std::cout<<get_height(parrent_array)<<std::endl;
}
