#pragma once
#include "iterators.hpp"

namespace
{
    constexpr size_t GROWTH_FACTOR = 2;
}


template<class T>
class vector{
private:
    T* data;
    size_t _size;
    size_t _capacity;
    
    void copy(const vector<T>& other);
    size_t calculate_capacity() const;
    void move(vector<T>&& other);
    void destroy();
    void resize(size_t newCap);
    void reserve(size_t cap);
    
public:
    using iterator = vector_iterator<T>;
    using const_iterator = const_vector_iterator<T>;
    using reverse_iterator = reverse_vector_iterator<T>;
    
    vector();
    vector(size_t count);
    vector(size_t count,const T& initial);
    vector(const vector& other);
    vector& operator=(const vector& other);
    vector(vector&& other);
    vector& operator=(vector&& other);
    void push_back(const T& element);
    void push_back(T&& element);
    void pop_back();
    
    void erase(const_iterator position);
    void erase(const_iterator first,const_iterator last);
    
    template<class... Args>
    void emplace_back(Args&&... args);
    
    void clear();
    size_t size() const;
    size_t capacity() const;
    bool empty() const;
    void shrink_to_fit();
    T& operator[](size_t index);
    const T& operator[](size_t index) const;

    
    iterator begin(){
        return iterator(data);
    }
    
    iterator end(){
        return iterator(data + _size);
    }
    
    const_iterator c_begin() const{
        return const_iterator(data);
    }
    
    const_iterator c_end() const{
        return const_iterator(data + _size);
    }
    
    reverse_iterator rbegin() const{
        return _size > 0 ? reverse_iterator(data + _size - 1) : reverse_iterator(nullptr);
    }
    reverse_iterator rend() const{
        return _size > 0 ? reverse_iterator(data - 1) : reverse_iterator(nullptr);
    }
    
    const T& front() const{
        return data[0];
    }
    T& front(){
        return data[0];
    }
    const T& back() const{
        return data[_size - 1];
    }
    T& back(){
        return data[_size - 1];
    }
    ~vector();
};

template<class T>
vector<T>::vector(size_t count){
    data = operator new(sizeof(T) * count);
    _size = count;
    _capacity = count;
    
    for(int i = 0;i<_size;i++)
        new(&data[i]) T();
}

template<class T>
vector<T>::vector(){
    this->data = nullptr;
    this->_size = 0;
    this->_capacity = 0;
}

template<class T>
vector<T>::vector(size_t count,const T& initial){
    data = operator new(sizeof(T) * count);
    _size = count;
    _capacity = count;
    
    for(int i = 0;i<_size;i++)
        new (&data[i]) T(initial);
}

template<class T>
vector<T>::vector(const vector& other){
    copy(other);
}

template<class T>
vector<T>& vector<T>::operator=(const vector& other){
    if(this!=&other){
        destroy();
        copy(other);
    }
    return *this;
}

template<class T>
vector<T>::vector(vector&& other){
    move(std::move(other));
}

template<class T>
vector<T>& vector<T>::operator=(vector&& other){
    if(this!=&other){
        destroy();
        move(std::move(other));
    }
    return *this;
}

template<class T>
void vector<T>::copy(const vector& other){
    data = operator new(sizeof(T) * other._size);
    
    for(int i = 0;i<other._size;i++)
        new (&data[i]) T(other.data[i]);
    
    _size = other._size;
    _capacity = other._capacity;
}

template<class T>
void vector<T>::destroy(){
    for(int i = 0;i<_size;i++)
        data[i].~T();
    
    operator delete(data,sizeof(T)*_capacity);
}

template<class T>
void vector<T>::move(vector&& other){
    this->data = other.data;
    this->_size = other._size;
    this->_capacity = other._capacity;
    
    other.data = nullptr;
    other._size = other._capacity = 0;
}


template<class T>
vector<T>::~vector(){
    destroy();
}

template<class T>
const T& vector<T>::operator[](size_t index) const{
    return data[index];
}

template<class T>
T& vector<T>::operator[](size_t index){
    return data[index];
}

template<class T>
void vector<T>::clear(){
    for(int i = 0;i<_size;i++)
        data[i].~T();
    _size = 0;
}

template<class T>
void vector<T>::push_back(const T& element){
    if(_size == _capacity)
        reserve(calculate_capacity());
    new (&data[_size++]) T(element);
}

template<class T>
void vector<T>::push_back(T&& element){
    if(_size == _capacity)
        reserve(calculate_capacity());
    new (&data[_size++]) T(std::move(element));
}

template<class T>
void vector<T>::pop_back(){
    if(empty())
        return;
    erase(--end());
}


template<class T>
bool vector<T>::empty() const{
    return _size == 0;
}

template<class T>
size_t vector<T>::size() const{
    return _size;
}

template<class T>
size_t vector<T>::capacity() const{
    return _capacity;
}

template<class T>
void vector<T>::erase(const_iterator first,const_iterator last){
    int deleted_count = last - first;
    
    if(deleted_count <= 0)
        return;
    
    int begin_offset = first - begin();
    int end_offset = last - begin();
    
    if(last != end()){
        for(int i = end_offset;i<_size;i++)
            new (&data[begin_offset++]) T(std::move(data[i]));
    }
    for(int i = end_offset;i<_size;i++)
        data[i].~T();
    _size-=deleted_count;
}

template<class T>
void vector<T>::erase(const_iterator position){
    erase(position,position + 1);
}

template<class T>
template<class... Args>
void vector<T>::emplace_back(Args&&... args){
    if(_size == _capacity)
        reserve(calculate_capacity());
    
    new(&data[_size++]) T(std::forward<Args>(args)...);
}


template<class T>
void vector<T>::reserve(size_t cap){
    if(cap <= _capacity)
        return;
    
    T* tempData = static_cast<T*>(operator new(cap * sizeof(T)));
    for(int i = 0;i<_size;i++){
        new (&tempData[i]) T(std::move(data[i]));
        data[i].~T();
    }
    operator delete(data,_capacity * sizeof(T));
    data = tempData;
    _capacity = cap;
}

template<class T>
void vector<T>::resize(size_t newCap){
    if(newCap < _size){
        for(int i = newCap;i<_size;i++)
            data[i].~T();
        _size = newCap;
    }
    else if(newCap > _size){
        if(newCap <= _capacity){
            for(int i = _size;i<newCap;i++)
                new (&data[i]) T();
            _size = newCap;
        }
        else{
            T* tempData = operator new(newCap * sizeof(T));
            for(int i = 0;i<_size;i++){
                new (&tempData[i]) T(std::move(data[i]));
                data[i].~T();
            }
            operator delete(data,sizeof(T) * _capacity);
            data = tempData;
            _capacity = newCap;
            _size = newCap;
    
        }
    }
    
}

template<class T>
void vector<T>::shrink_to_fit(){
    if(_capacity == _size)
        return;
    
    T* newData = operator new(sizeof(T) * _size);
    for(int i = 0;i<_size;i++){
        new (&newData[i]) T(std::move(data[i]));
        data[i].~T();
    }
    operator delete(data,sizeof(T) * _capacity);
    _capacity = _size;
    data = newData;
}

template<class T>
size_t vector<T>::calculate_capacity() const{
    if(_capacity == 0)
        return 1;
    return _capacity * GROWTH_FACTOR;
}
