#pragma once

template<class T>
struct Node{
    T data;
    Node* next;
    Node* prev;
    
    Node(const T& data) : data(data),next(nullptr),prev(nullptr){}
    Node(const T& data,Node* next,Node* prev) : data(data),next(next),prev(prev){}
};
