#pragma once
#include <iostream>

template<class value,class comparator = std::less<value>>
class k_ary_heap{
private:
    std::vector<value> heap;
    size_t k;
    comparator cmp;
    
    void heapify(size_t index);
    size_t parent_index(size_t child_index) const;
    size_t most_left_child_index(size_t parent_index) const;
    size_t most_right_child_index(size_t parent_index) const;
    
public:
    k_ary_heap(size_t k,const comparator& cmp = comparator());
    k_ary_heap(size_t k,const std::vector<value>& v,const comparator& cmp = comparator());
    void push(const value& _value);
    void pop();
    const value& top() const;
    size_t size() const;
    bool empty() const;
};

template<class value,class comparator>
k_ary_heap<value,comparator>::k_ary_heap(size_t k,const comparator& cmp) : k(k),cmp(cmp){}

template<class value,class comparator>
void k_ary_heap<value,comparator>::heapify(size_t index){
    while(true){
        size_t first_child_index = most_left_child_index(index);
        size_t last_child_index = most_right_child_index(index);
        
        if(first_child_index < heap.size()){
            auto max_value_index = first_child_index;
            for(int i = first_child_index;i<=last_child_index && i < heap.size();i++){
                if(cmp(heap[max_value_index],heap[i]))
                    max_value_index = i;
            }
            
            if(cmp(heap[index],heap[max_value_index])){
                std::swap(heap[index],heap[max_value_index]);
                index = max_value_index;
            }
            else
                break;
        }
        else
            break;
    }
}


template<class value,class comparator>
const value& k_ary_heap<value,comparator>::top() const{
    if(heap.empty())
        throw std::invalid_argument("Empty heap!");
    return heap[0];
}

template<class value,class comparator>
void k_ary_heap<value,comparator>::pop(){
    if(heap.empty())
        throw std::invalid_argument("Empty heap");
    std::swap(heap[0],heap[heap.size() - 1]);
    heap.pop_back();
    heapify(0);
}

template<class value,class comparator>
void k_ary_heap<value,comparator>::push(const value& _value){
    heap.push_back(_value);
    size_t index = heap.size() - 1;
    size_t parent = parent_index(index);
    while(index > 0 && cmp(heap[parent],heap[index])){
        std::swap(heap[index],heap[parent]);
        index = parent;
        parent = parent_index(index);
    }
}

template<class value,class comparator>
bool k_ary_heap<value,comparator>::empty() const{
    return heap.empty();
}

template<class value,class comparator>
size_t k_ary_heap<value,comparator>::size() const{
    return heap.size();
}

template<class value,class comparator>
size_t k_ary_heap<value,comparator>::most_left_child_index(size_t parent_index) const{
    return k * parent_index + 1;
}

template<class value,class comparator>
size_t k_ary_heap<value,comparator>::most_right_child_index(size_t parent_index) const{
    return k * parent_index + k;
}

template<class value,class comparator>
size_t k_ary_heap<value,comparator>::parent_index(size_t child_index) const{
    return (child_index - 1) / k;
}

template<class value,class comparator>
k_ary_heap<value,comparator>::k_ary_heap(size_t k,const std::vector<value>& v,const comparator& cmp) : k(k),cmp(cmp){
    heap = v;
    for(int i = heap.size() / 2 - 1;i>=0;i--)
        heapify(i);
}
