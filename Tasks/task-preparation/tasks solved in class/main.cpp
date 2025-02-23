#include <iostream>
#include <queue>
#include <stack>


// Да се определи височината на дърво с произволен брой наследници, представен с parent_array
std::vector<int> get_next_level(std::vector<int>& curr_level,std::vector<int>& parent_array){
    std::vector<int> next_level;
    for(int i = 0;i<parent_array.size();i++){
        auto it = std::find(curr_level.begin(), curr_level.end(), parent_array[i]);
        if(it != curr_level.end())
            next_level.push_back(i);
    }
    return next_level;
}


int calculate_height(std::vector<int>& parent_array){
    int height = -1;
    std::vector<int> curr_level = {-1};
    while(!curr_level.empty()){
        curr_level = get_next_level(curr_level, parent_array);
        height++;
    }
    return height;
}

// Да се отпечата всички листа на дърво с произволен брой наследнци, представено чрез parent_array
std::vector<int> extract_leaves(std::vector<int>& parent_array){
    std::vector<int> leaves;
    for(int i = 0;i<parent_array.size();i++){
        if(parent_array[i] != -2){
            auto it = std::find(parent_array.begin(),parent_array.end(), i);
            if(it == parent_array.end())
                leaves.push_back(i);
        }
    }
    return leaves;
}

// Да се генерират всички булеви вектори с дължина k
std::vector<std::string> gen_bool_vector(int k){
    std::queue<std::string> q;
    q.push("");
    std::vector<std::string> all_vectors;
    while(!q.empty()){
        auto curr_vector = q.front();
        q.pop();
        if(curr_vector.length() == k)
            all_vectors.push_back(curr_vector);
        else{
            q.push(curr_vector + "0");
            q.push(curr_vector + "1");
        }
    }
    return all_vectors;
}

void print_all_vectors(int k){
    auto vectors = gen_bool_vector(k);
    for(const auto& vector : vectors)
        std::cout<<vector<<std::endl;
}


// Да се провери дали даден стринг е правилно скобуван
bool is_opening_bracket(char s){
    return s == '(' || s == '[' || s == '{';
}

bool is_closing_bracket(char s){
    return s == ')' || s == ']' || s == '}';
}

bool is_corresponding(char opening,char closing){
    if(opening == '(')
        return closing == ')';
    if(opening == '[')
        return closing == ']';
    if(opening == '{')
        return closing == '}';
    return false;
}

bool is_valid_expression(const std::string& expr){
    std::stack<char> s;
    for(const auto& symbol : expr){
        if(is_opening_bracket(symbol))
            s.push(symbol);
        else{
            if(s.empty() || !is_corresponding(s.top(), symbol))
                return false;
            else
                s.pop();
        }
    }
    return s.empty();
}

// Да се изтрият елементите на свързан списък, които отговарят на даден предикат
struct node{
    int val;
    node* next;
    
    node(int val) : val(val),next(nullptr){}
};

template<class predicate>
node* remove(node* head,const predicate& pred){
    node** curr = &head;
    while(*curr){
        if(pred((*curr)->val)){
            node* to_delete = *curr;
            *curr = (*curr)->next;
            delete to_delete;
        }
        else
            curr = &(*curr)->next;
    }
    return head;
}

void print(node* head){
    node* curr = head;
    while(curr){
        std::cout<<curr->val<<" ";
        curr = curr->next;
    }
}

void destroy(node* head){
    node* curr = head;
    while(curr){
        node* to_delete = curr;
        curr = curr->next;
        delete to_delete;
    }
}

// Даден е свързан списък, да се пренареди така, че елементите отговарящи на даден предикат да са в началото а останалите в края

void push_back(node*& head,node*& tail,node* to_add){
    if(!head)
        head = tail = to_add;
    else{
        tail->next = to_add;
        tail = to_add;
    }
}

template<class predicate>
node* partition(node* head,const predicate& pred){
    node* true_list_begin = nullptr;
    node* true_list_end = nullptr;
    node* false_list_begin = nullptr;
    node* false_list_end = nullptr;
    
    node* curr = head;
    
    while(curr){
        if(pred(curr->val))
            push_back(true_list_begin, true_list_end, curr);
        else
            push_back(false_list_begin, false_list_end, curr);
        
        curr = curr->next;
    }
    if(true_list_end)
        true_list_end->next = false_list_begin;
    if(false_list_end)
        false_list_end->next = nullptr;
    
    return true_list_begin != nullptr ? true_list_begin : false_list_begin;
}

// Да се сортира свързан списък с merge sort
node* merge(node* list1,node* list2){
    node* new_list_begin = nullptr;
    node* new_list_end = nullptr;
    while(list1 && list2){
        if(list1->val < list2->val){
            push_back(new_list_begin, new_list_end, list1);
            list1 = list1->next;
        }
        else{
            push_back(new_list_begin, new_list_end, list2);
            list2 = list2->next;
        }
    }
    if(list1)
        new_list_end->next = list1;
    if(list2)
        new_list_end->next = list2;
    return new_list_begin;
}

node* find_mid(node* head){
    node* fast = head->next;
    node* slow = head;
    
    while(fast && fast->next){
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

node* merge_sort(node* head){
    if(!head || !head->next)
        return head;
    node* mid = find_mid(head);
    node* left = head;
    node* right = mid->next;
    mid->next = nullptr;
    
    left = merge_sort(left);
    right = merge_sort(right);
    
    return merge(left, right);
    
}


//Да се сортира свързан списък с quick sort
template<class predicate>
std::pair<node*,node*> part(node* head,const predicate& pred){
    node* curr = head;
    node* true_begin = nullptr;
    node* true_end = nullptr;
    node* false_begin = nullptr;
    node* false_end = nullptr;
    
    while(curr){
        if(pred(curr->val))
            push_back(true_begin, true_end, curr);
        else
            push_back(false_begin, false_end,curr);
        curr = curr->next;
    }
    
    if(true_end)
        true_end->next = nullptr;
    if(false_end)
        false_end->next = nullptr;
    return std::make_pair(true_begin, false_begin);
}

std::pair<node*,node*> concat(node* left_begin,node* left_end,node* right_begin,node* right_end){
    if(!left_begin) return std::make_pair(right_begin, right_end);
    if(!right_begin) return std::make_pair(left_begin, left_end);
    
    left_end->next = right_begin;
    return std::make_pair(left_begin, right_end);
}

std::pair<node*,node*> quick_sort(node* head){
    if(!head || !head->next)
        return std::make_pair(head, head);
    auto pivot = head->val;
    auto partition_result = part(head,[&pivot](int x){return x < pivot;});
    node* pivot_ptr = partition_result.second;
    
    auto left_to_concat = quick_sort(partition_result.first);
    auto right_to_concat = quick_sort(partition_result.second->next);
    
    pivot_ptr->next = right_to_concat.first;
    right_to_concat.first = pivot_ptr;
    if(!right_to_concat.second)
        right_to_concat.second = pivot_ptr;
    return concat(left_to_concat.first, left_to_concat.second, right_to_concat.first, right_to_concat.second);
}


// Да се принтират всички думи образувани от корен до листо в дърво с произволен брой наследници
struct n_ary_tree{
    char val;
    std::vector<n_ary_tree*> children;
    
    n_ary_tree(char val) : val(val){}
};

void extract_words_root_to_leaves(n_ary_tree* root,std::string& curr_word,std::vector<std::string>& words){
    if(!root)
        return;
    curr_word += root->val;
    if(root->children.empty()){
        words.push_back(curr_word);
        curr_word.pop_back();
        return;
    }
    for(const auto& child : root->children)
        extract_words_root_to_leaves(child,curr_word, words);
    curr_word.pop_back();
}

std::vector<std::string> extract(n_ary_tree* root){
    std::string curr_word;
    std::vector<std::string> words;
    extract_words_root_to_leaves(root, curr_word, words);
    return words;
}

std::vector<std::string> words_on_each_level(n_ary_tree* root){
    std::queue<n_ary_tree*> q;
    std::vector<std::string> words;
    q.push(root);
    while(!q.empty()){
        auto curr_level_size = q.size();
        std::string curr_word;
        for(int i = 0;i<curr_level_size;i++){
            auto curr = q.front();
            q.pop();
            curr_word += curr->val;
            for(const auto& child : curr->children){
                if(child)
                    q.push(child);
            }
        }
        words.push_back(curr_word);
    }
    return words;
}

// Да се провери дали дърво е binary_search_tree
struct tree{
    int val;
    tree* left;
    tree* right;
    
    tree(int val) : val(val),left(nullptr),right(nullptr){}
    tree(int val,tree* left,tree* right) : val(val),left(left),right(right){}
};

bool is_bst_helper(tree* root,int min,int max){
    if(!root)
        return true;
    if(root->val >= max || root->val <= min)
        return false;
    return is_bst_helper(root->left, min, root->val) && is_bst_helper(root->right, root->val, max);
}


bool is_bst(tree* root){
    int min = INT_MIN;
    int max = INT_MAX;
    return is_bst_helper(root, min, max);
}

// Да се построи balanced binary_search_tree от сортиран масив
using iterator = std::vector<int>::iterator;
tree* build_from_range(iterator begin,iterator end){
    auto distance = std::distance(begin, end);
    if(begin == end)
        return new tree(*begin);
    auto mid = distance / 2;
    return new tree(mid,build_from_range(begin, begin + mid - 1),build_from_range(begin + mid + 1, end));
}

tree* build_from_sorted(std::vector<int>& sorted){
    return build_from_range(sorted.begin(), sorted.end() - 1);
}

//Напишете функция, която получава като аргумент едносвързан списък с елементи цели числа. Функцията трябва да го сортира по следното правило - в началото на списъка трябва да останат четните елементи, подредени в нарастващ ред, след това нечетните елементи, подредени в намаляващ ред.Бонус: премахнете повтарящите се елементи.

node* reverse(node* head){
    node* next = nullptr;
    node* prev = nullptr;
    
    while(head){
        next = head->next;
        head->next = prev;
        prev = head;
        head = next;
    }
    return prev;
}

node* shuffle(node* head){
    auto partition_result = part(head, [](int x){return x % 2 == 0;});
    auto evens = partition_result.first;
    evens = merge_sort(evens);
    auto odds = partition_result.second;
    odds = merge_sort(odds);
    odds = reverse(odds);
    
    auto curr = evens;
    while(curr && curr->next)
        curr = curr->next;
    
    curr->next = odds;
    return evens;
        
}


int main() {
    
    
    n_ary_tree* root = new n_ary_tree('A');
    root->children.push_back(new n_ary_tree('B'));
    root->children.push_back(new n_ary_tree('K'));
    root->children.push_back(new n_ary_tree('H'));
    root->children.at(0)->children.push_back(new n_ary_tree('C'));
    root->children.at(0)->children.push_back(new n_ary_tree('D'));
    root->children.at(0)->children.push_back(new n_ary_tree('F'));
    root->children.at(2)->children.push_back(new n_ary_tree('J'));
    
    auto words = extract(root);
    for(const auto& word : words)
        std::cout<<word<<" ";
    std::cout<<std::endl;
    
    auto words_level_order = words_on_each_level(root);
    for(const auto& word : words_level_order)
        std::cout<<word<<" ";
    std::cout<<std::endl;
    
    
    tree* root1 = new tree(18);
    root1->left = new tree(14);
    root1->left->left = new tree(11);
    root1->left->right = new tree(16);
    root1->right = new tree(24);
    root1->right->left = new tree(20);
    root1->right->right = new tree(28);
    
    std::cout<<is_bst(root1)<<std::endl;
    
    
    node* head = new node(2);
    head->next = new node(0);
    head->next->next = new node(5);
    head->next->next->next = new node(9);
    head->next->next->next->next = new node(4);
    head->next->next->next->next->next = new node(99);
    
    auto shuff = shuffle(head);
    print(shuff);
}
