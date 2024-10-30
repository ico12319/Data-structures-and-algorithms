#pragma once
#include <iostream>


template<class T>
class doublyLinkedList{
private:
    size_t count = 0;
    
    struct Node{
        T data;
        Node* next;
        Node* prev;
        
        Node(const T& data) : data(data),next(nullptr),prev(nullptr){}
    };
    
    Node* head = nullptr;
    Node* tail = nullptr;
    
    
    void copy(const doublyLinkedList& other);
    void move(doublyLinkedList&& other);
    void destroy();
    
public:
    doublyLinkedList() = default;
    doublyLinkedList(const doublyLinkedList<T>& other);
    doublyLinkedList(doublyLinkedList<T>&& other);
    doublyLinkedList& operator=(const doublyLinkedList<T>& other);
    doublyLinkedList& operator=(doublyLinkedList<T>&& other);
    ~doublyLinkedList();
    
    void push_back(const T& el);
    void push_front(const T& el);
    void pop_back();
    void pop_front();
    
    const T& front() const;
    const T& back() const;
    T& front();
    T& back();
    
    void print() const;
    size_t getSize() const;
    bool isEmpty() const;
    void clear();
    
    
    class DllIterator{
        friend class doublyLinkedList;
        Node* currentElPtr;
        doublyLinkedList& list;
        
    public:
        DllIterator(doublyLinkedList& list,Node* currentElPtr) : list(list),currentElPtr(currentElPtr){}
        T& operator*(){return currentElPtr->data;}
        T& operator->(){return &currentElPtr->data;}
        
        DllIterator& operator++(){
            if(currentElPtr)
                currentElPtr = currentElPtr->next;
            return *this;
        }
        DllIterator operator++(int){
            DllIterator copy(*this);
            ++(*this);
            return copy;
        }
        DllIterator& operator--(){
            if(currentElPtr)
                currentElPtr = currentElPtr->prev;
            else
                currentElPtr = list.tail;
            
            return *this;
        }
        DllIterator operator--(int){
            DllIterator copy(*this);
            --(*this);
            return copy;
        }
        bool operator==(const DllIterator& other) const {return this->currentElPtr == other.currentElPtr;}
        bool operator!=(const DllIterator& other) const {return !(*this == other);}
    };
    
    class ConstDllIterator{
        friend class doublyLinkedList;
        Node* currElPtr;
        const doublyLinkedList& list;
        
    public:
        ConstDllIterator(const doublyLinkedList& list,Node* currElPtr) : list(list),currElPtr(currElPtr){}
        ConstDllIterator(const DllIterator& iter) : list(iter.list),currElPtr(iter.currentElPtr){}
        
        const T& operator*() const{return currElPtr->data;}
        const T& operator->() const{return &currElPtr->data;}
        
        ConstDllIterator& operator++(){
            if(currElPtr)
                currElPtr = currElPtr->next;
            return *this;
        }
        ConstDllIterator operator++(int){
            ConstDllIterator copy(*this);
            ++(*this);
            return copy;
        }
        ConstDllIterator& operator--(){
            if(currElPtr)
                currElPtr = currElPtr->prev;
            else
                currElPtr = list.tail;
            return *this;
        }
        ConstDllIterator operator--(int){
            ConstDllIterator copy(*this);
            --(*this);
            return copy;
        }
        bool operator==(const ConstDllIterator& other) const{return this->currElPtr == other.currElPtr;}
        bool operator!=(const ConstDllIterator& other) const {return !(*this == other);}
    };
    
    DllIterator insert(const T& el,ConstDllIterator& it);
    DllIterator remove(const DllIterator& it);
    
    DllIterator begin(){return DllIterator(*this, head);}
    DllIterator end(){return DllIterator(*this, nullptr);}
    ConstDllIterator cbegin() const{return ConstDllIterator(*this,head);}
    ConstDllIterator cend() const {return ConstDllIterator(*this, nullptr);}
};

template<class T>
doublyLinkedList<T>::doublyLinkedList(const doublyLinkedList<T>& other){
    copy(other);
}

template<class T>
doublyLinkedList<T>::doublyLinkedList(doublyLinkedList<T>&& other){
    move(std::move(other));
}

template<class T>
doublyLinkedList<T>& doublyLinkedList<T>::operator=(const doublyLinkedList& other){
    if(this!=&other){
        destroy();
        copy(other);
    }
    return *this;
}

template<class T>
doublyLinkedList<T>& doublyLinkedList<T>::operator=(doublyLinkedList&& other){
    if(this!=&other){
        destroy();
        move(std::move(other));
    }
    return *this;
}

template<class T>
doublyLinkedList<T>::~doublyLinkedList(){
    destroy();
}

template<class T>
void doublyLinkedList<T>::destroy(){
    Node* curr = head;
    while(curr){
        Node* toDelete = curr;
        curr = curr->next;
        delete toDelete;
    }
    head = tail = nullptr;
    count = 0;
}

template<class T>
void doublyLinkedList<T>::copy(const doublyLinkedList<T>& other){
    Node* curr = other.head;
    while(curr){
        push_back(curr->data);
        curr = curr->next;
    }
    count = other.count;
}

template<class T>
void doublyLinkedList<T>::move(doublyLinkedList<T>&& other){
    head = other.head;
    tail = other.tail;
    count = other.count;
    
    other.head = other.tail = nullptr;
    other.count = 0;
}

template<class T>
const T& doublyLinkedList<T>::front() const{
    if(isEmpty())
        throw std::runtime_error("The list is empty!");
    return head->data;
}


template<class T>
T& doublyLinkedList<T>::front(){
    if(isEmpty())
        throw std::runtime_error("The list is empty!");
    return head->data;
}

template<class T>
const T& doublyLinkedList<T>::back() const{
    if(isEmpty())
        throw std::runtime_error("The list is empty");
    return tail->data;
}

template<class T>
T& doublyLinkedList<T>::back(){
    if(isEmpty())
        throw std::runtime_error("The list is empty");
    return tail->data;
}


template<class T>
void doublyLinkedList<T>::print() const{
    Node* curr = head;
    while(curr){
        std::cout<<curr->data<<" ";
        curr = curr->next;
    }
}

template<class T>
size_t doublyLinkedList<T>::getSize() const{
    return count;
}

template<class T>
bool doublyLinkedList<T>::isEmpty() const{
    return head == nullptr;
}


template<class T>
void doublyLinkedList<T>::push_back(const T& el){
    Node* newTail = new Node(el);
    if(tail == nullptr)
        head = tail = newTail;
    else{
        tail->next = newTail;
        newTail->prev = tail;
        tail = newTail;
    }
    count++;
}

template<class T>
void doublyLinkedList<T>::push_front(const T& el){
    Node* newHead = new Node(el);
    if(head == nullptr)
        head = tail = newHead;
    else{
        head->prev = newHead;
        newHead->next = head;
        head = newHead;
    }
    count++;
}


template<class T>
void doublyLinkedList<T>::pop_back(){
    if (isEmpty())
            throw std::runtime_error("The list is empty!");
    
    if(head == tail){
        delete head;
        head = tail = nullptr;
    }
    else{
        tail->prev->next = nullptr;
        
        Node* toDelete = tail;
        tail = tail->prev;
        delete toDelete;
    }
    count--;
}


template<class T>
void doublyLinkedList<T>::pop_front(){
    if(isEmpty())
        throw std::runtime_error("The list is empty!");
    if(head == tail){
        delete head;
        head = tail = nullptr;
    }
    else{
        head->next->prev = nullptr;
        Node* toDelete = head;
        head = head->next;
        delete toDelete;
    }
    count--;
}

template<class T>
void doublyLinkedList<T>::clear(){
    destroy();
}

// 1 2 3 -> 1 3 2 3
template<class T>
doublyLinkedList<T>::DllIterator doublyLinkedList<T>::insert(const T& el, ConstDllIterator& it){
    if(it == cbegin()){
        push_front(el);
        return begin();
    }
    else if(it == cend()){
        push_back(el);
        return end();
    }
    else{
        Node* curr = it.currElPtr;
        Node* toInsert = new Node(el);
        
        toInsert->next = curr;
        toInsert->prev = curr->prev;
        curr->prev->next = toInsert;
        curr->prev = toInsert;
        count++;
        
        return DllIterator(*this, toInsert);
    }
    
}

// 1 -> 2 -> 3 -> 4 = 1 -> 2 -> 4
template<class T>
doublyLinkedList<T>::DllIterator doublyLinkedList<T>::remove(const DllIterator& it){
    if(it == begin()){
        pop_front();
        return begin();
    }
    else if(it == end()){
        pop_back();
        return end();
    }
    else{
        Node* curr = it.currentElPtr;
        if (!curr)
            throw std::runtime_error("Cannot remove end iterator");
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
        Node* nextNode = curr->next;
        
        delete curr;
        count--;
        return DllIterator(*this, nextNode);
        
    }
}
