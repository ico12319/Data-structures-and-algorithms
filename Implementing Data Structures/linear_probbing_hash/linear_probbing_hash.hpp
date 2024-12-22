#pragma once
#include <iostream>
#include <optional>

template<class key,class value,class hash = std::hash<key>>
class linear_probbing_hash{
private:
    using element = std::pair<key,value>;
    std::vector<std::optional<element>> data;
    size_t actual_size;
    hash hash_function;
    size_t step;
    element tombstone;
    double load_factor;
    
    bool contains_at_index(size_t index) const;
    void resize(size_t new_capacity);
    double current_load_factor() const;
    
    class iterator{
    private:
        int index;
        const linear_probbing_hash<key,value>& context;
        friend class linear_probbing_hash;
        
    public:
        iterator(int index,const linear_probbing_hash<key,value>& context) : index(index),context(context){}
        const element& operator*() const{
            return *context.data[index];
        }
        iterator& operator++(){
            while(index++ < context.data.size() && !context.contains_at_index(index));
            if(index == context.data.size())
                index = -1;
            return *this;
        }
        iterator operator++(int dummy){
            int old_index = index;
            while(index++ < context.data.size() && !context.contains_at_index(index));
            if(index == context.data.size())
                index = -1;
            return iterator(old_index, context);
        }
        bool operator==(const iterator& other) const{
            return context.data == other.context.data && index == other.index;
        }
        bool operator!=(const iterator& other) const{
            return !(*this == other);
        }
    };
public:
    linear_probbing_hash();
    linear_probbing_hash(size_t size,size_t step);
    void insert(const key& _key,const value& _value);
    bool contains(const key& _key) const;
    iterator find(const key& _key);
    void erase(const key& _key);
    void print() const;
    iterator begin();
    iterator end();
 };

template<class key,class value,class hash>
linear_probbing_hash<key, value,hash>::linear_probbing_hash() : tombstone(std::make_pair(key(),value())){
    this->data.resize(8);
    this->actual_size = 0;
    this->load_factor = 0.75;
    this->step = 1;
}

template<class key,class value,class hash>
linear_probbing_hash<key, value,hash>::linear_probbing_hash(size_t size,size_t step) : tombstone(std::make_pair(key(), value())){
    this->data.resize(size);
    this->step = step;
}

template<class key,class value,class hash>
bool linear_probbing_hash<key,value,hash>::contains_at_index(size_t index) const{
    return data[index] != std::nullopt && data[index] != tombstone;
}

template<class key,class value,class hash>
double linear_probbing_hash<key,value,hash>::current_load_factor() const{
    return static_cast<double>(actual_size) / data.size();
}

template<class key,class value,class hash>
void linear_probbing_hash<key,value,hash>::insert(const key& _key,const value& _value){
    if(current_load_factor() > load_factor)
        resize(data.size() * 2);
    int correct_index = hash_function(_key) % data.size();
    while(contains_at_index(correct_index)){
        if(data[correct_index]->first == _key)
            return;
        (correct_index+=step) %= data.size();
    }
    data[correct_index] = std::make_pair(_key,_value);
    actual_size++;
}

template<class key,class value,class hash>
bool linear_probbing_hash<key,value,hash>::contains(const key& _key) const{
    auto correct_index = hash_function(_key) % data.size();
    while(data[correct_index] != std::nullopt){
        if(data[correct_index] != tombstone && data[correct_index]->first == _key)
            return true;
        (correct_index+=step) % data.size();
    }
    return false;
}

template<class key,class value,class hash>
class linear_probbing_hash<key,value,hash>::iterator linear_probbing_hash<key,value,hash>::find(const key& _key){
    auto correct_index = hash_function(_key) % data.size();
    while(data[correct_index] != std::nullopt){
        if(data[correct_index] != tombstone && data[correct_index]->first == _key)
            return iterator(correct_index, *this);
        (correct_index+=step) %= data.size();
    }
    return end();
}

template<class key,class value,class hash>
void linear_probbing_hash<key,value,hash>::erase(const key& _key){
    if(actual_size == 0)
        return;
    auto correct_index = hash_function(_key) % data.size();
    while(data[correct_index] != std::nullopt){
        if(data[correct_index] != tombstone && data[correct_index]->first == _key){
            data[correct_index] = tombstone;
            actual_size--;
            break;
        }
        (correct_index+=step) %= data.size();
    }
}

template<class key,class value,class hash>
class linear_probbing_hash<key,value,hash>::iterator linear_probbing_hash<key,value,hash>::begin(){
    if(actual_size == 0)
        return end();
    for(int i = 0; ; i++){
        if(contains_at_index(i))
            return iterator(i, *this);
    }
}

template<class key,class value,class hash>
class linear_probbing_hash<key,value,hash>::iterator linear_probbing_hash<key,value,hash>::end(){
    return iterator(-1, *this);
}


template<class key,class value,class hash>
void linear_probbing_hash<key,value,hash>::resize(size_t new_cap){
    std::vector<std::optional<element>> old_data(new_cap);
    old_data.swap(data);
    actual_size = 0;
    for(int i = 0;i<old_data.size();i++){
        if(contains_at_index(i))
            insert(old_data[i]->first, old_data[i]->second);
    }
}

template<class key,class value,class hash>
void linear_probbing_hash<key,value,hash>::print() const{
    for(int i = 0;i<data.size();i++){
        if(contains_at_index(i))
            std::cout<<data[i]->first<<" "<<data[i]->second<<std::endl;
    }
    
}
