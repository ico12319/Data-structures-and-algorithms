#pragma once
#include <iostream>
#include <stack>

template <class T, typename Compare = std::less<T>>
class Bst
{
private:
    struct Node
    {
        T data;
        Node* left;
        Node* right;
        size_t sub_tree_size = 1;
        Node(const T& data, Node* left = nullptr, Node* right = nullptr) : data(data), left(left), right(right) {}
    };

    Node* root = nullptr;
    size_t size = 0;
    Compare comp;

    Node** findMinNode(Node** root);
    void free(Node* current);
    Node* copy(Node* current);

public:
    Bst() = default;
    explicit Bst(const Compare& comparator) : comp(comparator) {}
    Bst(const Bst<T, Compare>& other);
    Bst<T, Compare>& operator=(const Bst<T, Compare>& other);
    ~Bst();

    bool insert(const T& data);
    bool contains(const T& data) const;
    bool remove(const T& data);

    size_t getSize() const;
    bool isEmpty() const;
    const T& operator[](size_t index) const;

    class ForwardIterator
    {
    private:
        std::stack<Node*> nodeStack;

        void pushLeft(Node* node)
        {
            while (node)
            {
                nodeStack.push(node);
                node = node->left;
            }
        }

    public:
        ForwardIterator(Node* root = nullptr)
        {
            pushLeft(root);
        }

        T& operator*() const
        {
            return nodeStack.top()->data;
        }

        ForwardIterator& operator++()
        {
            Node* node = nodeStack.top();
            nodeStack.pop();
            if (node->right) {
                pushLeft(node->right);
            }
            return *this;
        }
        ForwardIterator operator++(int)
        {
            ForwardIterator old = *this;
            ++(*this);
            return old;
        }

        bool operator!=(const ForwardIterator& other) const
        {
            return nodeStack != other.nodeStack;
        }

        bool operator==(const ForwardIterator& other) const
        {
            return nodeStack == other.nodeStack;
        }
    };
    
    class BacwardIterator{
    private:
        std::stack<Node*> nodes;
        
        void push_right(Node* curr){
            while(curr){
                nodes.push(curr);
                curr = curr->right;
            }
        }
    public:
        BacwardIterator(Node* root){
            push_right(root);
        }
        BacwardIterator& operator--(){
            Node* top = nodes.top();
            nodes.pop();
            if(top->left)
                push_right(top->left);
            return *this;
        }
        BacwardIterator operator--(int){
            BacwardIterator copy(*this);
            --(*this);
            return copy;
        }
        
        T& operator*() const{
            return nodes.top()->data;
        }
        
        bool operator==(const BacwardIterator& other) const{
            return nodes == other.nodes;
        }
        bool operator!=(const BacwardIterator& other) const{
            return !(*this == other);
        }
    };

    ForwardIterator begin() const
    {
        return ForwardIterator(root);
    }

    ForwardIterator end() const
    {
        return ForwardIterator(nullptr);
    }
    
    BacwardIterator b_begin() const{
        return BacwardIterator(root);
    }
    BacwardIterator b_end() const{
        return BacwardIterator(nullptr);
    }
};

template <class T, typename Compare>
bool Bst<T, Compare>::insert(const T& data)
{
    Node** current = &root;
    std::stack<Node*> nodes;

    while (*current)
    {
        nodes.push(*current);
        if (comp(data, (*current)->data))
            current = &(*current)->left;
        else if (comp((*current)->data, data))
            current = &(*current)->right;
        else
            return false;
    }
    *current = new Node(data);
    size++;
    
    while(!nodes.empty()){
        Node* curr = nodes.top();
        nodes.pop();
        curr->sub_tree_size++;
    }
    return true;
}

template <class T, typename Compare>
bool Bst<T, Compare>::contains(const T& data) const
{
    Node* current = root;

    while (current)
    {
        if (comp(data, current->data))
            current = current->left;
        else if (comp(current->data, data))
            current = current->right;
        else
            return true;
    }
    return false;
}

template <class T, typename Compare>
typename Bst<T, Compare>::Node** Bst<T, Compare>::findMinNode(Node** root)
{
    Node** current = root;

    while ((*current)->left)
        current = &(*current)->left;
    
    return current;
}

template <class T, typename Compare>
bool Bst<T, Compare>::remove(const T& data)
{
    Node** current = &root;
    std::stack<Node*> nodes;

    while (*current)
    {
        nodes.push(*current);
        if (comp(data, (*current)->data))
            current = &(*current)->left;
        else if (comp((*current)->data, data))
            current = &(*current)->right;
        else
            break;
    }

    if (!(*current))
        return false;

    Node* toDelete = *current;

    if (!(*current)->left && !(*current)->right)
        *current = nullptr;
    else if (!(*current)->right)
        *current = (*current)->left;
    else if (!(*current)->left)
        *current = (*current)->right;
    else
    {
        Node** rightMin = findMinNode(&(*current)->right);
        size_t orig_subtree_size = (*current)->sub_tree_size;
        Node* temp = (*current)->right;
        while(temp && temp != *rightMin){
            nodes.push(temp);
            temp = temp->left;
        }
        *current = *rightMin;
        *rightMin = (*rightMin)->right;
        
        (*current)->sub_tree_size = orig_subtree_size - 1;

        (*current)->left = toDelete->left;
        (*current)->right = toDelete->right;
    }
    delete toDelete;
    size--;
    while(!nodes.empty()){
        Node* curr = nodes.top();
        nodes.pop();
        curr->sub_tree_size--;
    }
    return true;
}

template <class T, typename Compare>
size_t Bst<T, Compare>::getSize() const
{
    return size;
}

template <class T, typename Compare>
bool Bst<T, Compare>::isEmpty() const
{
    return getSize() == 0;
}

template <class T, typename Compare>
typename Bst<T, Compare>::Node* Bst<T, Compare>::copy(Node* current)
{
    if (!current)
        return nullptr;
    Node* res = new Node(current->data);
    res->sub_tree_size = current->sub_tree_size;
    res->left = copy(current->left);
    res->right = copy(current->right);
    return res;
}

template <class T, typename Compare>
void Bst<T, Compare>::free(Node* current)
{
    if (!current)
        return;
    free(current->left);
    free(current->right);
    delete current;
}

template <class T, typename Compare>
Bst<T, Compare>::Bst(const Bst<T, Compare>& other) : comp(other.comp)
{
    root = copy(other.root);
    size = other.size;
}

template <class T, typename Compare>
Bst<T, Compare>& Bst<T, Compare>::operator=(const Bst<T, Compare>& other)
{
    if (this != &other)
    {
        free(root);
        root = copy(other.root);
        size = other.size;
        comp = other.comp;
        
    }
    return *this;
}

template <class T, typename Compare>
Bst<T, Compare>::~Bst()
{
    free(root);
}


template<class T,class Compare>
const T& Bst<T,Compare>::operator[](size_t index) const{
    Node* curr = root;
    while(curr){
        size_t left_subtree_size = curr->left ? curr->left->sub_tree_size : 0;
        if(index < left_subtree_size)
            curr = curr->left;
        else if(index == left_subtree_size)
            return curr->data;
        else{
            index -= (left_subtree_size + 1);
            curr = curr->right;
        }
    }
    throw std::invalid_argument("Invalid index!");
}


void treeSort(std::vector<int>& v)
{
    Bst<int> bst;
    for (int i = 0; i < v.size(); i++)
        bst.insert(v.at(i));

    unsigned index = 0;
    for (auto it = bst.begin(); it != bst.end(); it++)
        v.at(index++) = *it;
}


