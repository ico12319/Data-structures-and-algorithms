#pragma once
#include "Node.hpp"

template<class T>
class DoublyLinkedList{
private:
    Node<T>* head = nullptr;
    Node<T>* tail = nullptr;
    size_t size = 0;
   
    
    void copy(const DoublyLinkedList& other);
    void move(DoublyLinkedList&& other);
    void destroy();
    Node<T>* getMid(Node<T>* head);
    template<class Pred>
    Node<T>* merge(Node<T>* left, Node<T>* right, const Pred& pred);
    template<class Pred>
    Node<T>* mergeSort(Node<T>* head, const Pred& pred);
    
public:
    DoublyLinkedList() = default;
    DoublyLinkedList(const DoublyLinkedList& other);
    DoublyLinkedList(DoublyLinkedList&& other);
    DoublyLinkedList& operator=(const DoublyLinkedList& other);
    DoublyLinkedList& operator=(DoublyLinkedList&& other);
    ~DoublyLinkedList();
    
    class iterator{
    private:
        friend class DoublyLinkedList;
        DoublyLinkedList* list;
        Node<T>* curElPtr;
        
    public:
        iterator() = default;
        iterator(DoublyLinkedList* list,Node<T>* currElPtr) : list(list),curElPtr(currElPtr){}
        iterator& operator++(){
            if(curElPtr)
                curElPtr = curElPtr->next;
            return *this;

        }
        iterator operator++(int){
            iterator copy(*this);
            ++(*this);
            return copy;
        }
        iterator& operator--(){
            if(curElPtr)
                curElPtr = curElPtr->prev;
            else
                
                curElPtr = list->tail;
            return *this;
        }
        iterator operator--(int){
            iterator copy(*this);
            --(*this);
            return copy;
        }
        
        T& operator*(){
            return curElPtr->data;
        }
        
        T* operator->(){
            return &curElPtr->data;
        }
        
        bool operator==(const iterator& other) const{
            return (curElPtr == other.curElPtr);
        }
        bool operator!=(const iterator& other) const{
            return !(*this == other);
        }
    };
    
    class const_iterator{
    private:
        friend class DoublyLinkedList;
       const DoublyLinkedList* list;
        Node<T>* currElPtr;
        
    public:
        const_iterator() = default;
        const_iterator(const DoublyLinkedList* list,Node<T>* currElPtr) : list(list),currElPtr(currElPtr){}
        const_iterator(const iterator& other) : list(other.list),currElPtr(other.curElPtr){}
        
        const_iterator& operator++(){
            if(currElPtr)
                currElPtr = currElPtr->next;
            return *this;
        }
        const_iterator operator++(int){
            const_iterator copy(*this);
            ++(*this);
            return copy;
        }
        const_iterator& operator--(){
            if(currElPtr)
                currElPtr = currElPtr->prev;
            else
                currElPtr = list->tail;
            return *this;
        }
        const_iterator operator--(int){
            const_iterator copy(*this);
            --(*this);
            return copy;
        }
        const T& operator*() const{
            return currElPtr->data;
        }
        const T* operator->() const{
            return &currElPtr->data;
        }
        
        bool operator==(const const_iterator& other) const{
            return (currElPtr == other.currElPtr);
        }
        bool operator!=(const const_iterator& other) const{
            return !(*this == other);
        }
        
    };
    
    void push_back(const T& el);
    void push_front(const T& el);
    void pop_back();
    void pop_front();
    iterator insert_after(const const_iterator& it,const T& el);
    iterator remove(const const_iterator& it);
    
    
    iterator begin();
    iterator end();
    const_iterator c_begin() const;
    const_iterator c_end() const;
    
    T& front();
    T& back();
    const T& front() const;
    const T& back() const;
    
    const size_t getSize() const;
    bool isEmpty() const;
    Node<T>* getHead() const;
    Node<T>* getTail() const;
    void print() const;
    
    template<class Pred>
    void mergeSort(const Pred& pred);
};


template <class T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>& other){
    copy(other);
}

template<class T>
DoublyLinkedList<T>::DoublyLinkedList(DoublyLinkedList<T>&& other){
    move(std::move(other));
}

template<class T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList<T>& other){
    if(this!=&other){
        destroy();
        copy(other);
    }
    return *this;
}

template<class T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(DoublyLinkedList<T>&& other){
    if(this!=&other){
        destroy();
        move(std::move(other));
    }
    return *this;
}

template<class T>
DoublyLinkedList<T>::~DoublyLinkedList(){
    destroy();
}

template<class T>
void DoublyLinkedList<T>::push_back(const T& el){
    Node<T>* newTail = new Node(el);
    if(isEmpty())
        head = tail = newTail;
    else{
        newTail->prev = tail;
        tail->next = newTail;
        tail = newTail;
    }
    size++;
}

// 1 2 3 - > 4 1 2 3
template<class T>
void DoublyLinkedList<T>::push_front(const T& el){
    Node<T>* newHead = new Node(el);
    if(isEmpty())
        head = tail = newHead;
    else{
        newHead->next = head;
        head->prev = newHead;
        head = newHead;
    }
    size++;
        
}

template<class T>
void DoublyLinkedList<T>::pop_back(){
    if(isEmpty())
        return;
    
    if(head == tail){
        delete head;
        head = tail = nullptr;
    }
    else{
        Node<T>* toDelete = tail;
        tail->prev->next = nullptr;
        tail = tail->prev;
        
        delete toDelete;
    }
    size--;
}

// 1 2 3 -> 1 3 2 3
template<class T>
typename DoublyLinkedList<T>::iterator DoublyLinkedList<T>::insert_after(const const_iterator& it,const T& el){
    Node<T>* newNode = new Node(el);
    Node<T>* currNode = it.currElPtr;
    if (currNode == nullptr) {
           
        if (tail == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    else {
        newNode->next = currNode->next;
        newNode->prev = currNode;

        if (currNode->next != nullptr) {
            currNode->next->prev = newNode;
        } else {
            tail = newNode;
        }

            currNode->next = newNode;
        }

           size++;
           return iterator(this, newNode);
    
}

template<class T>
typename DoublyLinkedList<T>::iterator DoublyLinkedList<T>::begin(){
    return iterator(this, head);
}

template<class T>
typename DoublyLinkedList<T>::iterator DoublyLinkedList<T>::end(){
    return iterator(this, nullptr);
}

template<class T>
typename DoublyLinkedList<T>::const_iterator DoublyLinkedList<T>::c_begin() const{
    return const_iterator(this, head);
}

template<class T>
typename DoublyLinkedList<T>::const_iterator DoublyLinkedList<T>::c_end() const{
    return const_iterator(this, nullptr);
}

template<class T>
const T& DoublyLinkedList<T>::front() const{
    return head->data;
}

template<class T>
const T& DoublyLinkedList<T>::back() const{
    return tail->data;
}

template<class T>
T& DoublyLinkedList<T>::front(){
    return head->data;
}

template<class T>
T& DoublyLinkedList<T>::back(){
    return tail->data;
}

template<class T>
const size_t DoublyLinkedList<T>::getSize() const{
    return size;
}

template<class T>
bool DoublyLinkedList<T>::isEmpty() const{
    return head == nullptr;
}

// 1 2 3 ->  2 3
template<class T>
void DoublyLinkedList<T>::pop_front(){
    if(isEmpty())
        return;
    
    if(head == tail){
        delete head;
        head = tail = nullptr;
    }
    else{
        Node<T>* toDelete = head;
        head->next->prev = nullptr;
        head = head->next;
        delete toDelete;
    }
    size--;
}
// 1 2 3 4 -> 1 2 4
template<class T>
typename DoublyLinkedList<T>::iterator DoublyLinkedList<T>::remove(const const_iterator& it){
    Node<T>* currEl = it.currElPtr;
    
    if(it == c_begin()){
        pop_front();
        return begin();
    }
    if(it == --c_end()){
        pop_back();
        return end();
    }
    else{
        Node<T>* toDelete = currEl;
        currEl->next->prev = currEl->prev;
        currEl->prev->next = currEl->next;
        Node<T>* nextNode = toDelete->next;
        delete toDelete;
        size--;
        return iterator(this, nextNode);

    }
}

template<class T>
void DoublyLinkedList<T>::copy(const DoublyLinkedList<T>& other){
    Node<T>* otherCurr = other.head;
    while(otherCurr){
        push_back(otherCurr->data);
        otherCurr = otherCurr->next;
    }
}

template<class T>
void DoublyLinkedList<T>::move(DoublyLinkedList<T>&& other){
    head = other.head;
    tail = other.tail;
    size = other.size;
       
    other.head = other.tail = nullptr;
    other.size = 0;
}

template<class T>
void DoublyLinkedList<T>::destroy(){
    Node<T>* curr = head;
        while(curr){
            Node<T>* toDelete = curr;
            curr = curr->next;
            delete toDelete;
        }
        head = tail = nullptr;
        size = 0;
}

template<class T>
Node<T>* DoublyLinkedList<T>::getHead() const{
    return head;
}
template<class T>
Node<T>* DoublyLinkedList<T>::getTail() const{
    return tail;
}

template<class T>
void DoublyLinkedList<T>::print() const{
    Node<T>* curr = head;
    while(curr){
        std::cout<<curr->data<<" ";
        curr = curr->next;
    }
}


template<class T>
Node<T>* DoublyLinkedList<T>::getMid(Node<T>* head) {
    if (!head)
        return nullptr;

    Node<T>* slow = head;
    Node<T>* fast = head;

    while (fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}

template<class T>
template<class Pred>
Node<T>* DoublyLinkedList<T>::merge(Node<T>* left, Node<T>* right, const Pred& pred) {
    if (!left)
        return right;
    if (!right)
        return left;

    Node<T>* result = nullptr;

    if (pred(left->data, right->data)) {
        result = left;
        result->next = merge(left->next, right, pred);
        if (result->next)
            result->next->prev = result;
    } else {
        result = right;
        result->next = merge(left, right->next, pred);
        if (result->next)
            result->next->prev = result;
    }

    return result;
}


template<class T>
template<class Pred>
Node<T>* DoublyLinkedList<T>::mergeSort(Node<T>* head, const Pred& pred) {
    if (!head || !head->next)
        return head;

    Node<T>* mid = getMid(head);
    Node<T>* nextToMid = mid->next;

   
    mid->next = nullptr;
    if (nextToMid)
        nextToMid->prev = nullptr;

    Node<T>* left = mergeSort(head, pred);
    Node<T>* right = mergeSort(nextToMid, pred);

    Node<T>* sortedList = merge(left, right, pred);

    if (sortedList)
        sortedList->prev = nullptr;

    return sortedList;
}

template<class T>
template<class Pred>
void DoublyLinkedList<T>::mergeSort(const Pred& pred) {
    head = mergeSort(head, pred);
    tail = head;
    if (tail) {
        while (tail->next) {
            tail = tail->next;
        }
    }
}
