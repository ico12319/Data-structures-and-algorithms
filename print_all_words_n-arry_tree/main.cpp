#include <iostream>
#include <queue>


struct node{
    char val;
    std::vector<node*> children;
    
    node(char val) : val(val){}
};


// print all words by levels

std::vector<std::string> level_traversal(node* root){
    std::queue<node*> levels;
    levels.push(root);
    std::vector<std::string> words;
    while(!levels.empty()){
        auto curr_level_size = levels.size();
        std::string curr_level_word;
        for(int i = 0;i<curr_level_size;i++){
            node* curr_top = levels.front();
            levels.pop();
            curr_level_word+=curr_top->val;
            for(const auto& child : curr_top->children){
                if(child)
                    levels.push(child);
            }
        }
        words.push_back(curr_level_word);
    }
    return words;
}

void print_levels(const std::vector<std::string>& words){
    for(const auto& word : words)
        std::cout<<word<<" ";
    std::cout<<std::endl;
}

//print all words form root to leafs
void extract_words_from_root_to_leafs(node* root,std::string& curr_word,std::vector<std::string>& words){
    if(!root) return;
    curr_word+=root->val;
    if(root->children.empty()){
        words.push_back(curr_word);
        curr_word.pop_back();
        return;
    }
    for(const auto& child : root->children){
        extract_words_from_root_to_leafs(child, curr_word, words);
    }
    curr_word.pop_back();
}

std::vector<std::string> extract_words(node* root){
    std::string curr_word;
    std::vector<std::string> words;
    extract_words_from_root_to_leafs(root, curr_word, words);
    return words;
}


int main(int argc, const char * argv[]) {
    node* root = new node('a');
    root->children.push_back(new node('b'));
    root->children.push_back(new node('c'));
    root->children.push_back(new node('d'));
    root->children.at(0)->children.push_back(new node('f'));
    root->children.at(0)->children.push_back(new node('g'));
    root->children.at(1)->children.push_back(new node('k'));
    root->children.at(2)->children.push_back(new node('c'));
    
    auto words = level_traversal(root);
    print_levels(words);
    std::cout<<std::endl;
    
    auto words2 = extract_words(root);
    print_levels(words2);
    
}
