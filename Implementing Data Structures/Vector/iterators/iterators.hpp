#pragma once
#include <iostream>

template<class T>
class const_vector_iterator{
private:
    T* memPointer;
    
public:
    const_vector_iterator(T* memPointer){this->memPointer = memPointer;};
    const_vector_iterator(T* passedValue,size_t push) : memPointer(passedValue + push){}
    
    const_vector_iterator<T> operator+(size_t push) const{
        return {memPointer + push};
    }
    
    const_vector_iterator<T> operator-(size_t push) const{
        return memPointer - push;
    }
    
    int operator+(const const_vector_iterator<T>& other) const{
        return memPointer + other.memPointer;
    }
    
    int operator-(const const_vector_iterator<T>& other) const{
        return memPointer - other.memPointer;
    }
    
    const T* operator->() const{
        return memPointer;
    }
    
    const T& operator*() const{
        return *memPointer;
    }
    
    bool operator==(const const_vector_iterator<T>& other) const{
        return memPointer == other.memPointer;
    }
    
    bool operator!=(const const_vector_iterator<T>& other) const{
        return !(memPointer == other.memPointer);
    }
    
};


template<class T>
class vector_iterator{
private:
    T* memPointer;
    
public:
    vector_iterator(T* passedValue){this->memPointer = passedValue;}
    vector_iterator(T* passedValue,size_t push) : memPointer(passedValue + push){}
    
    vector_iterator<T> operator+(size_t push) const{
        return memPointer + push;
    }
    
    vector_iterator<T> operator-(size_t push) const{
        return memPointer - push;
    }
    
    T* operator->() const{
        return memPointer;
    }
    
    const T* operator*() const{
        return *memPointer;
    }
    
    vector_iterator<T>& operator++(){
        memPointer++;
        return *this;
    }
    vector_iterator<T> operator++(int){//dummy parameter
        vector_iterator original = *this;
        ++(*this);
        return original;
    }
    vector_iterator<T>& operator--(){
        memPointer--;
        return *this;
    }
    vector_iterator<T> operator--(int){
        vector_iterator original = *this;
        --(*this);
        return original;
    }
    operator const_vector_iterator<T>() const{
        return const_vector_iterator<T>(memPointer);
    }
    
    bool operator==(const vector_iterator<T>& other) const {
        return memPointer == other.memPointer;
    }
    bool operator!=(const vector_iterator<T>& other) const{
        return !(memPointer == other.memPointer);
    }
    
};

template<class T>
class reverse_vector_iterator{
private:
    T* memPointer;
    
public:
    reverse_vector_iterator(T* passedValue){this->memPointer = passedValue;}
    reverse_vector_iterator(T* passedValue,size_t push) : memPointer(passedValue + push){}
    
    reverse_vector_iterator<T>& operator++(){
        memPointer--;
        return *this;
    }
    reverse_vector_iterator<T> operator++(int){
        reverse_vector_iterator original = *this;
        ++(*this);
        return original;
    }
    reverse_vector_iterator<T>& operator--(){
        memPointer++;
        return *this;
    }
    reverse_vector_iterator<T> operator--(int){
        reverse_vector_iterator original = *this;
        --(*this);
        return original;
    }
    
    reverse_vector_iterator<T> operator+(size_t push) const{
        return {memPointer + push};
    }
    reverse_vector_iterator<T> operator-(size_t push) const{
        return {memPointer - push};
    }
    int operator+(reverse_vector_iterator<T>& other){
        return memPointer + other.memPointer;
    }
    int operator-(reverse_vector_iterator<T>& other){
        return memPointer - other.memPointer;
    }
    bool operator==(const reverse_vector_iterator<T>& other) const{
        return memPointer == other.memPointer;
    }
    bool operator!=(const reverse_vector_iterator<T>& other) const{
        return !(memPointer == other.memPointer);
    }
    const T& operator*() const{
        return *memPointer;
    }
    const T* operator->() const{
        return memPointer;
    }
};

