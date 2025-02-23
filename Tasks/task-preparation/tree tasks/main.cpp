#include <iostream>
#include <queue>

struct node{
    int val;
    std::vector<node*> children;
    
    node(int val) : val(val){}
};


struct node_char{
    char val;
    std::vector<node_char*> children;
    
    node_char(char val) : val(val){}
};


void destroy(node* root){
    if(!root)
        return;
    for(auto& child : root->children)
        destroy(child);
    delete root;
}


//Да се напише функция, която приема двоично/произволно дърво и връща дали дадено число се съдържа в него.
bool contains_number(node* root,int target){
    if(!root)
        return false;
    if(root->val == target)
        return true;
    
    for(const auto& child : root->children){
        if(contains_number(child, target))
            return true;
    }
    return false;
}


//Да се напише функция, която приема двоично/произволно дърво и връща сумата на елементите в него.
void find_sum_helper(node* root,int& sum){
    if(!root)
        return;
    sum += root->val;
    for(const auto& child : root->children)
        find_sum_helper(child, sum);
}

int find_sum(node* root){
    int sum = 0;
    find_sum_helper(root, sum);
    return sum;
}

//Да се напише функция, която приема двоично/произволно дърво и връща най-големият елемент в него.
void find_max_helper(node* root,int& max){
    if(!root)
        return;
    max = std::max(max,root->val);
    for(const auto& child : root->children)
        find_max_helper(child, max);
}

int find_max(node* root){
    int max = INT_MIN;
    find_max_helper(root,max);
    return max;
}

//Да се напише функция, която приема двоично/произволно дърво и връща височината му.
int height(node* root){
    if(!root)
        return 0;
    int max_height = -1;
    for(const auto& child : root->children){
        auto curr_height = height(child);
        if(curr_height > max_height)
            max_height = curr_height;
    }
    return max_height + 1;
}

void number_of_elements_helper(node* root,int& count){
    if(!root)
        return;
    count++;
    for(const auto& child : root->children)
        number_of_elements_helper(child, count);
}

int number_of_elements(node* root){
    int count = 0;
    number_of_elements_helper(root,count);
    return count;
}


bool mark_occurances(node* root,std::vector<bool>& numbers){
    if(!root)
        return false;
    if(root->val < 0 || root->val > numbers.size())
        return false;
    if(numbers[root->val])
        return false;
    numbers[root->val] = true;
    for(const auto& child : root->children){
        if(!mark_occurances(child, numbers))
            return false;
    }
    return true;
}

bool are_all_numbers_contained(node* root,int n){
    std::vector<bool> numbers(n,false);
    return mark_occurances(root, numbers);
}


//Да се напише функция, която приема двоично/произволно дърво и връща всички думи, които са получени от корена до някое листо.
void generate_words(node_char* root,std::string& temp,std::vector<std::string>& words){
    if(!root)
        return;
    temp+=root->val;
    if(root->children.empty()){
        words.push_back(temp);
        temp.pop_back();
        return;
    }
    for(const auto& child : root->children)
        generate_words(child, temp, words);
    temp.pop_back();
}


std::vector<std::string> all_words(node_char* root){
    std::string temp;
    std::vector<std::string> words;
    generate_words(root, temp, words);
    return words;
}

//Да се напише функция, която приема двоично/произволно дърво, чиито елементи са символи и цяло число к и отпечатва думата на к-тото ниво на дървото.
std::string word_on_k_level(node_char* root,int k){
    std::string word;
    std::queue<node_char*> q;
    q.push(root);
    int curr_level = 0;
    while(!q.empty()){
        auto curr_level_size = q.size();
        for(int i = 0;i<curr_level_size;i++){
            auto curr = q.front();
            q.pop();
            if(curr_level == k)
                word += curr->val;
            for(const auto& child : curr->children){
                if(child)
                    q.push(child);
            }
        }
        curr_level++;
    }
    return word;
}

// Задача 9: Да се напише функция, която приема произволно дърво и връща сумата на листата.

void sum_leaves_helper(node* root,int& sum){
    if(!root)
        return;
    if(root->children.empty()){
        sum += root->val;
        return;
    }
    for(const auto& child : root->children)
        sum_leaves_helper(child, sum);
}


int sum_leaves(node* root){
    int sum = 0;
    sum_leaves_helper(root, sum);
    return sum;
}


//Задача 4: Дадено е дърво с произволен брой наследници. "Хубав път" в дървото ще наричаме такъв път, в който стойността на всеки връх се дели на стойността на следващия. Да се дефинира функция, която приема такова дърво и връща най-дългия "хубав път" започващ от корена.

void longest_happy_path_helper(node* root,std::vector<int>& curr_path,std::vector<int>& longest_path){
    if(!root)
        return;
    curr_path.push_back(root->val);
    for(const auto& child : root->children){
        if(root->val % child->val == 0)
            longest_happy_path_helper(child, curr_path, longest_path);
    }
    if(curr_path.size() > longest_path.size())
        longest_path = curr_path;
    curr_path.pop_back();
}

std::vector<int> longest_happy_path(node* root){
    std::vector<int> curr_path;
    std::vector<int> longest_path;
    longest_happy_path_helper(root, curr_path, longest_path);
    return longest_path;
}


bool is_right_same_as_left(node* root){
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
        if(curr_level.front() != curr_level.back())
            return false;
    }
    return true;
}

int main(int argc, const char * argv[]) {
    
    node* root = new node(5);
    root->children.push_back(new node(3));
    root->children.push_back(new node(9));
    root->children.push_back(new node(3));
    root->children.at(0)->children.push_back(new node(4));
    root->children.at(0)->children.push_back(new node(3));
    root->children.at(0)->children.push_back(new node(7));
    root->children.at(0)->children.at(2)->children.push_back(new node(9));
    root->children.at(2)->children.push_back(new node(5));
    root->children.at(2)->children.push_back(new node(4));
    root->children.at(2)->children.at(0)->children.push_back(new node(2));
    root->children.at(2)->children.at(1)->children.push_back(new node(9));
    
    std::cout<<is_right_same_as_left(root)<<std::endl;
    
}
