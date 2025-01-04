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
        
        node(const value& val) : val(val),left(nullptr),right(nullptr){}
        node(const value& val,node* left,node* right) : val(val),left(left),right(right){}
    };
    
    node* root = nullptr;
    comparator cmp;
    size_t size = 0;
    
    node* copy(node* root);
    void print_helper(node* root) const;
    node** find_min_node(node** root);
    void move(const binary_search_tree& other);
    void destroy(node* root);
    
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
        value& operator*() const{
            return nodes.top()->val;
        }
        forward_iterator& operator++(){
            node* curr_top = nodes.top();
            nodes.pop();
            if(curr_top->right)
                push_left(curr_top->right);
            return *this;
        }
        forward_iterator operator++(int){
            forward_iterator copy(*this);
            ++(*this);
            return copy;
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
        backward_iterator operator--(int){
            backward_iterator copy(*this);
            --(*this);
            return copy;
        }
        value& operator*() const{
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
    binary_search_tree(const comparator& cmp);
    binary_search_tree(const binary_search_tree& other);
    binary_search_tree(binary_search_tree&& other);
    binary_search_tree& operator=(const binary_search_tree& other);
    binary_search_tree& operator=(binary_search_tree&& other);
    ~binary_search_tree();
    forward_iterator forward_begin() const{
        return forward_iterator(root);
    }
    forward_iterator forward_end() const{
        return forward_iterator(nullptr);
    }
    backward_iterator backward_begin() const{
        return backward_iterator(root);
    }
    backward_iterator bacward_end() const{
        return backward_iterator(nullptr);
    }
    void insert(const value& element);
    bool contains(const value& element) const;
    void remove(const value& element);
    void print() const;
    size_t get_size() const;
    bool is_empty() const;
};

template<class value,class comparator>
class binary_search_tree<value,comparator>::node** binary_search_tree<value,comparator>::find_min_node(node** root){
    node** curr = root;
    while((*curr)->left)
        curr = &(*curr)->left;
    return curr;
}

template<class value,class comparator>
class binary_search_tree<value,comparator>::node* binary_search_tree<value,comparator>::copy(node* root){
    if(!root) return root;
    node* copy = new node(root->val);
    copy->left = copy(root->left);
    copy->right = copy(root->right);
    return copy;
}

template<class value,class comparator>
void binary_search_tree<value,comparator>::move(const binary_search_tree& other){
    this->root = other.root;
    this->cmp = other.cmp;
    this->size = other.size;
    
    other.root = nullptr;
    other.size = 0;
}

template<class value,class comparator>
void binary_search_tree<value,comparator>::destroy(node* root){
    if(!root) return;
    destroy(root->left);
    destroy(root->right);
    delete root;
}

template<class value,class comparator>
binary_search_tree<value,comparator>::binary_search_tree(const binary_search_tree& other){
    root = copy(root);
    size = other.size;
    cmp = other.cmp;
}

template<class value,class comparator>
binary_search_tree<value,comparator>::binary_search_tree(binary_search_tree&& other){
    move(std::move(other));
}

template<class value,class comparator>
binary_search_tree<value,comparator>::binary_search_tree(const comparator& cmp){
    this->cmp = cmp;
}

template<class value,class comparator>
binary_search_tree<value,comparator>& binary_search_tree<value,comparator>::operator=(const binary_search_tree<value,comparator>& other){
    if(*this!=other){
        destroy(root);
        root = copy(other.root);
        size = other.size;
        cmp = other.cmp;
    }
    return *this;
}

template<class value,class comparator>
binary_search_tree<value,comparator>& binary_search_tree<value,comparator>::operator=( binary_search_tree<value,comparator>&& other){
    if(*this!=other){
        destroy(root);
        move(std::move(other));
    }
    return *this;
}

template<class value,class comparator>
binary_search_tree<value,comparator>::~binary_search_tree(){
    destroy(root);
}

template<class value,class comparator>
void binary_search_tree<value,comparator>::insert(const value& element){
    node** current = &root;
    while(*current){
        if(cmp((*current)->val,element))
           current = &(*current)->right;
        else if(cmp(element,(*current)->val))
            current = &(*current)->left;
        else
            return;;
    }
    *current = new node(element);
    size++;
}

template<class value,class comparator>
bool binary_search_tree<value,comparator>::contains(const value& element) const{
    node* curr = root;
    while(curr){
        if(cmp(curr->val,element))
            curr = curr->right;
        else  if(cmp(element,curr->val))
            curr = curr->right;
        else
            return true;
    }
    return false;
}

template<class value,class comparator>
void binary_search_tree<value,comparator>::remove(const value& element){
    node** curr = &root;
    while(*curr){
        if(cmp((*curr)->val,element))
            curr = &(*curr)->right;
        else if(cmp(element,(*curr)->val))
            curr = &(*curr)->left;
        else
            break;
    }
    if(!(*curr))
        return;
    node* to_delete = *curr;
    if(!(*curr)->left && !(*curr)->right)
        *curr = nullptr;
    else if(!(*curr)->right)
        *curr = (*curr)->left;
    else if(!(*curr)->left)
        *curr = (*curr)->right;
    else{
        node** right_min = find_min_node(&(*curr)->right);
        *curr = *right_min;
        *right_min = (*right_min)->right;
        
        (*curr)->left = to_delete->left;
        (*curr)->right = to_delete->right;
    }
    delete to_delete;
    size--;
}


template<class value,class comparator>
void binary_search_tree<value,comparator>::print() const{
    print_helper(root);
}

template<class value,class comparator>
void binary_search_tree<value,comparator>::print_helper(node* root) const{
    if(!root) return;
    print_helper(root->left);
    std::cout<<root->val<<" ";
    print_helper(root->right);
}

template<class value,class comparator>
bool binary_search_tree<value,comparator>::is_empty() const{
    return size == 0;
}

template<class value,class comparator>
size_t binary_search_tree<value,comparator>::get_size() const{
    return size;
}

