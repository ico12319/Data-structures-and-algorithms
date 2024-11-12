#include <iostream>
#include <queue>

// Binary tree tasks:

struct TreeNode{
    int val;
    TreeNode* left;
    TreeNode* right;
    
    TreeNode(int val) : val(val),left(nullptr),right(nullptr){}
    TreeNode(int val,TreeNode* left,TreeNode* right) : val(val),left(left),right(right){}
};


struct Node_char{
    char val;
    Node_char* left;
    Node_char* right;
    
    Node_char(char val) : val(val),left(nullptr),right(nullptr){}
    Node_char(char val,Node_char* left,Node_char* right) : val(val),left(left),right(right){}
};

void destroy(TreeNode* root){
    if(!root) return;
    
    destroy(root->left);
    destroy(root->right);
    delete root;
}

//Задача 1: Да се напише функция, която приема двоично/произволно дърво и връща дали дадено число се съдържа в него.
bool is_contained(TreeNode* root,int target){
    if(!root) return false;
    
    if(root->val == target) return true;
    
    return is_contained(root->left, target) || is_contained(root->right, target);
}

//Задача 2: Да се напише функция, която приема двоично/произволно дърво и връща сумата на елементите в него.
int find_sum(TreeNode* root){
    if(!root) return 0;
    
    return root->val + find_sum(root->left) + find_sum(root->right);
}

//Задача 3: Да се напише функция, която приема двоично/произволно дърво и връща най-големият елемент в него.
int max = 0;
int find_max(TreeNode* root){
    if(!root) return max;
    
    max = std::max(max, root->val);
    return std::max(find_max(root->left),find_max(root->right));
}

//Задача 4: Да се напише функция, която приема двоично/произволно дърво и връща височината му.
size_t height(TreeNode* root){
    if(!root) return 0;
    return 1 + std::max(height(root->left), height(root->right));
}

//Задача 5: Да се напише функция, която приема двоично/произволно дърво и връща броя на елементите му.
size_t elements_count(TreeNode* root){
    if(!root) return 0;
    
    return 1 + elements_count(root->left) + elements_count(root->right);
}

//Задача 6: Да се напише функция, която приема двоично/произволно дърво и връща колко пъти даден елемент се среща в него

int count_target_occur_helper(TreeNode* root,int target,int& count){
    if(!root) return 0;
    
    if(target == root->val)
        count++;
    return count_target_occur_helper(root->left, target, count) + count_target_occur_helper(root->right, target, count);
}

int count_target_occur(TreeNode* root,int target){
    int count = 0;
    count_target_occur_helper(root, target, count);
    return count;
}

//Задача 7: Да се напише функция, която приема двоично/произволно дърво с n върха и проверява дали числата от 1 до n се срещат точно веднъж в дървото.
bool mark_occur(TreeNode* root,std::vector<bool>& is_presented){
    if(!root) return true;
    if(root->val < 1 || root->val > is_presented.size())
        return false;
    if(is_presented[root->val - 1]) return false;
    is_presented[root->val - 1] = true;
    return mark_occur(root->left, is_presented) && mark_occur(root->right, is_presented);
}

bool are_occuring_once(TreeNode* root){
    size_t n = elements_count(root);
    std::vector<bool> presence(n,0);
    mark_occur(root, presence);
    for(int i = 0;i<n;i++){
        if(!presence[i])
            return false;
    }
    return true;
}


//Задача 8: Да се напише функция, която приема двоично/произволно дърво, чиито елементи са символи и цяло число к и отпечатва думата на к-тото ниво на дървото
std::vector<std::vector<char>> bfs(Node_char* root){
    if(!root) return {};
    std::queue<Node_char*> levels;
    std::vector<std::vector<char>> res;
    levels.push(root);
    while(!levels.empty()){
        std::vector<char> elements;
        int currSize = levels.size();
        for(int i = 0;i<currSize;i++){
            Node_char* curr = levels.front();
            levels.pop();
            
            elements.push_back(curr->val);
            if(curr->left)
                levels.push(curr->left);
            if(curr->right)
                levels.push(curr->right);
        }
        res.push_back(elements);
    }
    return res;
}

void print_word_on_certain_level(Node_char* root,int level){
    std::vector<std::vector<char>> levels = bfs(root);
    for(int i = 0;i<levels[level - 1].size();i++)
        std::cout<<levels[level - 1][i];
    std::cout<<std::endl;
    
}

//Задача 7: Да се напише функция, която приема двоично/произволно дърво и връща всички думи, които са получени от корена до някое листо.

void fillWords(Node_char* root,std::vector<std::string>& words,std::string currWord){
    if(!root) return;
    if(!root->left && !root->right)
        words.push_back(currWord + (char)root->val);
    
    fillWords(root->left, words, currWord + (char)root->val);
    fillWords(root->right, words, currWord + (char)root->val);
}

std::vector<std::string> getWords(Node_char* root){
    std::vector<std::string> words;
    fillWords(root, words, "");
    return words;
}

void print(const std::vector<std::string>& v){
    for(const auto& el : v)
        std::cout<<el<<" ";
    std::cout<<std::endl;
}

int main() {
   
    Node_char* root = new Node_char('I');
    root->left = new Node_char('V');
    root->right = new Node_char('A');
    root->left->left = new Node_char('C');
    root->left->right = new Node_char('H');
    
    root->right->left = new Node_char('I');
    root->right->right = new Node_char('C');
    
    print_word_on_certain_level(root, 3);
    
    std::vector<std::string> res = getWords(root);
    for(const auto& el : res)
        std::cout<<el<<std::endl;
    
}
