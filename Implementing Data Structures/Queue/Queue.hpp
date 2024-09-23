#pragma once
#include "LinkedList.hpp"

template<class T>
class Queue{
private:
    LinkedList<T> list;
    int count;
    
public:
    Queue() = default;
    void print() const;
    void enqueue(const T& element);
    void dequeue();
    const T& top() const;
    bool empty() const;
    int size() const;
};

template<class T>
void Queue<T>::print() const{
    list.print();
}

template<class T>
void Queue<T>::enqueue(const T& element){
    list.addLast(element);
    count++;
}

template<class T>
void Queue<T>::dequeue(){
    if(count != 0){
        list.removeFirst();
        count--;
        return;
    }
    throw "Empty queue";
}

template<class T>
const T& Queue<T>::top() const{
    if(count != 0)
        return list.getHeadValue();
    throw "Empty queue";
        
}

template<class T>
bool Queue<T>::empty() const{
    return count == 0;
}

template<class T>
int Queue<T>::size() const{
    return count;
}
