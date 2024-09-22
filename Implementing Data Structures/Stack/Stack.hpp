#include "DoublyLinkedList.hpp"

template<class T>
class Stack{
private:
    LinkedList<T> list;
    int count = 0;
    
public:
    Stack() = default;
    int size() const;
    const T& top() const;
    void pop();
    void push(const T& element);
    bool empty() const;
    void print() const;
};

template<class T>
int Stack<T>::size() const{
    return count;
}

template<class T>
bool Stack<T>::empty() const{
    return count == 0;
}

template<class T>
const T& Stack<T>::top() const{
    return list.getHeadValue();
}

template<class T>
void Stack<T>::push(const T& element){
    list.addFirst(element);
    count++;
}

template<class T>
void Stack<T>::pop(){
    try{
        list.removeFirst();
        count--;
    }
    catch(...){
        std::cout<<"Empty List!"<<std::endl;
    }
}

template<class T>
void Stack<T>::print() const{
    list.print();
}
