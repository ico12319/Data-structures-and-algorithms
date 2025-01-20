#include <iostream>
#include <unordered_set>
#include <stack>

struct node{
    int val;
    node* left;
    node* right;
    
    node(int val) : val(val),left(nullptr),right(nullptr){}
    node(int val,node* left,node* right) : val(val),left(left),right(right){}
};

void in_order(node* root){
    if(!root)
        return;
    in_order(root->left);
    std::cout<<root->val<<" ";
    in_order(root->right);
}

void destroy(node* root){
    if(!root)
        return;
    destroy(root->left);
    destroy(root->right);
    delete root;
}

bool is_bst_helper(node* root,int minimum,int maximum){
    if(!root)
        return true;
    if(root->val >= maximum || root->val <= minimum)
        return false;
    return is_bst_helper(root->left, minimum, root->val) && is_bst_helper(root->right, root->val, maximum);
}

bool is_bst(node* root){
    int minimum = INT_MIN;
    int maximum = INT_MAX;
    return is_bst_helper(root, minimum, maximum);
}

using const_iterator = std::vector<int>::const_iterator;
node* build_from_range(const_iterator begin,const_iterator end){
    if(begin > end)
        return nullptr;
    if(begin == end)
        return new node(*begin);
    
    auto distance = std::distance(begin, end);
    int mid = distance / 2;
    return new node(*(begin + mid),build_from_range(begin, begin + mid - 1),build_from_range(begin + mid + 1, end));
}

node* build_balanced_tree(const std::vector<int>& sorted){
    return build_from_range(sorted.begin(), sorted.end() - 1);
}

node** find_min(node** root){
    node** curr = root;
    while((*curr)->left)
        curr = &(*curr)->left;
    return curr;
}

node* remove(node* root,int val){
    node** curr = &root;
    while(*curr){
        if((*curr)->val < val)
            curr = &(*curr)->right;
        else if((*curr)->val > val)
            curr = &(*curr)->left;
        else
            break;
    }
    if(!(*curr))
        return root;
    node* to_delete = *curr;
    
    if(!((*curr)->left) && !((*curr)->right))
        *curr = nullptr;
    else if(!(*curr)->left)
        *curr = (*curr)->right;
    else if(!(*curr)->right)
        *curr = (*curr)->left;
    else{
        node** right_min = find_min(&(*curr)->right);
        *curr = *right_min;
        *right_min = (*right_min)->right;
        (*curr)->left = to_delete->left;
        (*curr)->right = to_delete->right;
    }
    delete to_delete;
    return root;
}

//solution with additional memory
void convert_to_search_ready(node* root,std::unordered_set<int>& seen){
    if(!root)
        return;
    seen.insert(root->val);
    convert_to_search_ready(root->left, seen);
    convert_to_search_ready(root->right, seen);
}

void find_difference(node* root,const std::unordered_set<int>& seen,std::vector<int>& order){
    if(!root)
        return;
    find_difference(root->left, seen, order);
    if(!seen.contains(root->val))
        order.push_back(root->val);
    find_difference(root->right, seen, order);
}

std::vector<int> differences(node* root1,node* root2){
    std::unordered_set<int> seen;
    std::vector<int> diffs;
    convert_to_search_ready(root2, seen);
    find_difference(root1, seen, diffs);
    return diffs;
}

//solution with iterator
struct bst_iterator{
private:
    std::stack<node*> nodes;
    
    void push_left(node* root){
        node* curr = root;
        while(curr){
            nodes.push(curr);
            curr = curr->left;
        }
    }
public:
    bst_iterator(node* root){
        push_left(root);
    }
    bst_iterator& operator++(){
        node* curr = nodes.top();
        nodes.pop();
        if(curr->right)
            push_left(curr->right);
        return *this;
    }
    bst_iterator operator++(int){
        bst_iterator copy(*this);
        ++(*this);
        return copy;
    }
    int operator*() const{
        return nodes.top()->val;
    }
    bool is_end_reached() const{
        return nodes.empty();
    }
};

std::vector<int> find_diff(node* root1,node* root2){
    bst_iterator from(root1);
    bst_iterator what(root2);
    std::vector<int> diff;
    while(!from.is_end_reached() && !what.is_end_reached()){
        if(*from < *what){
            diff.push_back(*from);
            ++from;
        }
        else if(*from > *what)
            ++what;
        else{
            ++what;
            ++from;
        }
    }
    
    while(!from.is_end_reached()){
        diff.push_back(*from);
        ++from;
    }
    return diff;
}


int main(int argc, const char * argv[]) {
   
    node* root = new node(18);
    root->left = new node(15);
    root->right = new node(24);
    root->left->left = new node(11);
    root->left->left->left = new node(8);
    root->left->right = new node(17);
    root->left->right->left = new node(16);
    
    node* root2 = new node(18);
    root2->left = new node(17);
    root2->right = new node(24);
    root2->left->left = new node(11);

    
    auto diffs = find_diff(root,root2);
    for(const auto& el : diffs)
        std::cout<<el<<" ";
    
}
