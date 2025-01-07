#pragma once
#include <iostream>
#include <stack>

template<class value,class comparator = std::less<value>>
class binary_search_tree{
private:
    struct node{
        value val;
        node* left;
        node* right;
        size_t subtree_size = 1;
        
        node(const value& val) : val(val),left(nullptr),right(nullptr),subtree_size(1){}
    };
    
    node* root = nullptr;
    comparator cmp;
    
    node* copy(node* root);
    void move(binary_search_tree&& other);
    void destory(node* root);
    node** find_min(node** root);
    static void print_helper(node* root){
        if(!root) return;
        print_helper(root->left);
        std::cout<<root->val<<" ";
        print_helper(root->right);
    }
    static value& get_element_at_index(node* root,size_t index){
        size_t current_index = root->left ? root->left->subtree_size : 0;
        if(current_index > index)
            get_element_at_index(root->left, index);
        else if(current_index == index)
            return root->val;
        
        return get_element_at_index(root->right, index - current_index - 1);
    }
    
    class forward_iterator{
    private:
        std::stack<node*> nodes;
        
        void push_left(node* root){
            while(root){
                nodes.push(root);
                root = root->left;
            }
        }
        
    public:
        forward_iterator(node* root){
            push_left(root);
        }
        
        forward_iterator& operator++(){
            node* curr_top = nodes.top();
            nodes.pop();
            if(curr_top->right)
                push_left(curr_top->right);
            return *this;
        }
        
        forward_iterator operator++(int  dummy){
            forward_iterator copy(*this);
            ++(*this);
            return copy;
        }
        
        const value& operator*() const{
            return nodes.top()->val;
        }
        
        bool operator==(const forward_iterator& other) const{
            return nodes == other.nodes;
        }
        
        bool operator!=(const forward_iterator& other) const{
            return !(*this == other);
        }
    };
    
    class backward_iterator{
    private:
        std::stack<node*> nodes;
        
        void push_right(node* root){
            while(root){
                nodes.push(root);
                root = root->right;
            }
        }
        
    public:
        backward_iterator(node* root){
            push_right(root);
        }
        
        backward_iterator& operator--(){
            node* curr_top = nodes.top();
            nodes.pop();
            if(curr_top->left)
                push_right(curr_top->left);
            return *this;
        }
        
        backward_iterator operator--(int dummy){
            backward_iterator copy(*this);
            --(*this);
            return copy;
        }
        
        const value& operator*() const{
            return nodes.top()->val;
        }
        
        bool operator==(const backward_iterator& other) const{
            return nodes == other.nodes;
        }
        bool operator!=(const backward_iterator& other) const{
            return !(*this == other);
        }
    };
    
public:
    binary_search_tree() = default;
    binary_search_tree(const binary_search_tree& other);
    binary_search_tree(binary_search_tree&& other);
    binary_search_tree& operator=(const binary_search_tree& other);
    binary_search_tree& operator=(binary_search_tree&& other);
    ~binary_search_tree();
    
    void insert(const value& _value);
    void remove(const value& _value);
    bool contains(const value& _value) const;
    const value& operator[](size_t index) const;
    size_t size() const;
    bool is_empty() const;
    
    forward_iterator forward_begin() const{
        return forward_iterator(root);
    }
    forward_iterator forward_end() const{
        return forward_iterator(nullptr);
    }
    backward_iterator backward_begin() const{
        return backward_iterator(root);
    }
    backward_iterator backward_end() const{
        return backward_iterator(nullptr);
    }
    void print() const;
};

template<class value,class comparator>
class binary_search_tree<value,comparator>::node** binary_search_tree<value,comparator>::find_min(node** root){
    node** curr = root;
    while((*curr)->left)
        curr = &((*curr)->left);
    return curr;
}

template<class value,class comparator>
void binary_search_tree<value,comparator>::insert(const value& _value){
    node** curr = &root;
    std::stack<node*> to_increase;
    while(*curr){
        to_increase.push(*curr);
        if(cmp((*curr)->val,_value))
            curr = &((*curr)->right);
        else if(cmp(_value,(*curr)->val))
            curr = &((*curr)->left);
        else return;
    }
    *curr = new node(_value);
    while(!to_increase.empty()){
        node* curr_top = to_increase.top();
        curr_top->subtree_size++;
        to_increase.pop();
    }
}

template<class value,class comparator>
bool binary_search_tree<value,comparator>::contains(const value& _value) const{
    node* curr = root;
    while(curr){
        if(cmp(curr->val,_value))
            curr = curr->right;
        else if(cmp(_value,curr->val))
            curr = curr->left;
        else
            return true;
    }
    return false;
}

template<class value,class comparator>
void binary_search_tree<value,comparator>::remove(const value& _value){
    node** curr = &root;
    std::stack<node*> to_decrease;
    while(*curr){
        if(cmp((*curr)->val,_value))
            curr = &((*curr)->right);
        else if(cmp(_value,(*curr)->val))
            curr = &((*curr)->left);
        else
            break;
        to_decrease.push(*curr);
    }
    if(!(*curr))
        return;
    node* to_delete = *curr;
    if(!((*curr)->left) && !((*curr)->right))
        *curr = nullptr;
    else if(!((*curr)->left))
        *curr = (*curr)->right;
    else if(!((*curr)->right))
        *curr = (*curr)->left;
    else{
        node** right_min = find_min(&((*curr)->right));
        *curr = *right_min;
        *right_min = (*right_min)->right;
        (*curr)->left = to_delete->left;
        (*curr)->right = to_delete->right;
    }
    delete to_delete;
    while(!to_decrease.empty()){
        node* curr_top = to_decrease.top();
        to_decrease.pop();
        curr_top->subtree_size--;
    }
}


template<class value,class comparator>
const value& binary_search_tree<value,comparator>::operator[](size_t index) const{
    return get_element_at_index(this->root, index);
}

template<class value,class comparator>
bool binary_search_tree<value,comparator>::is_empty() const{
    return root == nullptr;
}

template<class value,class comparator>
size_t binary_search_tree<value,comparator>::size() const{
    return root != nullptr ? root->subtree_size : 0;
}

template<class value,class comparator>
class binary_search_tree<value,comparator>::node* binary_search_tree<value,comparator>::copy(node* root){
    if(!root)
        return nullptr;
    node* res = new node(root->val);
    res->left = copy(root->left);
    res->right = copy(root->right);
    return res;
}

template<class value,class comparator>
void binary_search_tree<value,comparator>::destory(node* root){
    if(!root)
        return;
    destory(root->left);
    destory(root->right);
    delete root;
}

template<class value,class comparator>
binary_search_tree<value,comparator>::~binary_search_tree(){
    destory(this->root);
}

template<class value,class comparator>
binary_search_tree<value,comparator>::binary_search_tree(const binary_search_tree& other){
    copy(other.root);
    this->cmp = other.cmp;
}

template<class value,class comparator>
binary_search_tree<value,comparator>& binary_search_tree<value,comparator>::operator=(const binary_search_tree& other){
    if(this!=&other){
        destroy(root);
        copy(other.root);
        this->cmp = other.cmp;
    }
    return *this;
}


template<class value,class comparator>
binary_search_tree<value,comparator>& binary_search_tree<value,comparator>::operator=( binary_search_tree&& other){
    if(this!=&other){
        destroy(root);
        move(std::move(other));
        this->cmp = other.cmp;
    }
    return *this;
}


template<class value,class comparator>
void binary_search_tree<value,comparator>::move(binary_search_tree&& other){
    this->root = other.root;
    this->cmp = other.cmp;
    other.root = nullptr;
}


template<class value,class comparator>
binary_search_tree<value,comparator>::binary_search_tree(binary_search_tree&& other){
    move(std::move(other));
}


template<class value,class comparator>
void binary_search_tree<value,comparator>::print() const{
    print_helper(this->root);
}
