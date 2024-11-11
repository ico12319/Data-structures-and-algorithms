#pragma once
#include <iostream>

template<class T,class Comparator = std::less<T>>
class binary_search_tree{
private:
    
    struct Node{
        T data;
        Node* left;
        Node* right;
        
        Node(const T& data) : data(data),left(nullptr),right(nullptr){}
        Node(const T& data,Node* left,Node* right) : data(data),left(left),right(right){}
    };
    
    Node* root = nullptr;
    size_t size = 0;
    Comparator comp;
    
    Node* copy(Node* curr);
    void move(binary_search_tree&& other);
    void destroy(Node* curr);
    Node** find_min(Node** root) const;
    
public:
    binary_search_tree() = default;
    binary_search_tree(const binary_search_tree& other);
    binary_search_tree(binary_search_tree&& other) noexcept;
    binary_search_tree& operator=(const binary_search_tree& other);
    binary_search_tree& operator=(binary_search_tree&& other) noexcept;
    ~binary_search_tree();
    
    bool insert(const T& el);
    bool remove(const T& el);
    bool contains(const T& el) const;
    
    size_t getSize() const;
    bool isEmpty() const;
};

template<class T,class Comparator>
bool binary_search_tree<T,Comparator>::contains(const T& el) const{
    Node* curr = root;
    while(curr){
        if(comp(el,curr->data))
            curr = curr->left;
        else if(comp(curr->data,el))
            curr = curr->right;
        else
            return true;
    }
    return false;
}

template<class T,class Comparator>
bool binary_search_tree<T,Comparator>::insert(const T& el){
    Node** curr = &root;
    while(*curr){
        if(comp(el,(*curr)->data))
            curr = &(*curr)->left;
        else if(comp((*curr)->data,el))
            curr = &(*curr)->right;
        else
            return false;
    }
    *curr = new Node(el);
    size++;
    return true;
}

template<class T,class Comparator>
void binary_search_tree<T,Comparator>::destroy(Node* curr){
    if(!curr)
        return;
    destroy(curr->left);
    destroy(curr->right);
    delete curr;
}

template<class T,class Comparator>
binary_search_tree<T,Comparator>::~binary_search_tree(){
    destroy(root);
}

template<class T,class Comparator>
typename binary_search_tree<T,Comparator>::Node* binary_search_tree<T,Comparator>::copy(Node* curr){
    if(!curr)
        return;
    Node* newRoot = new Node(curr->data);
    newRoot->left = copy(curr->left);
    newRoot->right = copy(curr->right);
    return newRoot;
}

template<class T,class Comparator>
binary_search_tree<T,Comparator>::binary_search_tree(const binary_search_tree<T,Comparator>& other){
    this->root = copy(other.root);
    this->size = other.size;
    this->comp = other.comp;
}


template<class T,class Comparator>
binary_search_tree<T,Comparator>& binary_search_tree<T,Comparator>::operator=(const binary_search_tree<T,Comparator>& other){
    
    if(this!=&other){
        destroy(root);
        root = copy(other.root);
        size = other.size;
        comp = other.comp;
    }
    return *this;
}

template<class T,class Comparator>
void binary_search_tree<T,Comparator>::move(binary_search_tree&& other){
    this->root = other.root;
    this->size = other.size;
    this->comp = other.comp;
    
    other.root = nullptr;
    other.size = 0;
}

template<class T,class Comparator>
binary_search_tree<T,Comparator>::binary_search_tree(binary_search_tree<T,Comparator>&& other) noexcept{
    move(std::move(other));
}

template<class T,class Comparator>
binary_search_tree<T,Comparator>& binary_search_tree<T,Comparator>::operator=(binary_search_tree<T,Comparator>&& other) noexcept{
    if(this!=&other){
        destroy(root);
        move(std::move(other));
    }
    return *this;
}

template<class T,class Comparator>
typename binary_search_tree<T,Comparator>::Node** binary_search_tree<T,Comparator>::find_min(typename binary_search_tree<T,Comparator>::Node** root) const{
    Node** curr = root;
    while((*curr)->left)
        curr = &(*curr)->left;
    
    return curr;
}

template<class T,class Comparator>
bool binary_search_tree<T,Comparator>::remove(const T& el){
    Node** curr = &root;
    while(*curr){
        if(comp(el,curr->data))
            curr = &(*curr)->left;
        else if(comp(curr->data,el))
            curr = &(*curr)->right;
        else
            break;
    }
    if(!(*curr))
        return false;
    
    Node* toDelete = *curr;
    if(!(*curr)->left && !(*curr)->right) // leaf node
        *curr = nullptr;
    else if(!(*curr)->left && (*curr)->right) // only one right child
        *curr = *curr->left;
    else if((*curr)->left && !(*curr)->right) // only one left child
        *curr = *curr->right;
    else{
        Node** min_in_right_subtree = find_min(&(*curr)->right);
        
        *curr = *min_in_right_subtree;
        *min_in_right_subtree = (*min_in_right_subtree)->right;
        
        (*curr)->left = toDelete->left;
        (*curr)->right = toDelete->right;
        
        delete toDelete;
        size--;
        return true;
    }
    
}

template<class T,class Comparator>
bool binary_search_tree<T,Comparator>::isEmpty() const{
    return size == 0;
}

template<class T,class Comparator>
size_t binary_search_tree<T,Comparator>::getSize() const{
    return size;
}


