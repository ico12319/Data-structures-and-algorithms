#pragma once
#include <iostream>
#include <optional>

template<class key,class hash = std::hash<key>>
class hash_set{
private:
    std::vector<std::optional<key>> data;
    size_t size;
    const key tombstone;
    hash hash_function;
    const double max_load_factor;
    size_t jump;
    
    double current_load_factor() const{
        return size / data.size();
    }
    void resize(size_t new_cap);
    bool contains_element_at_index(size_t index) const{
        return data[index] != std::nullopt && data[index] != tombstone;
    }
    
public:
    hash_set();
    hash_set(size_t hash_table_size,const hash& hash_function,size_t jump);
    void insert(const key& _key);
    bool contains(const key& _key) const;
    void erase(const key& _key);
    size_t get_size() const;
    bool is_empty() const;
    void print() const;
    
    class const_hash_iterator{
    private:
        int index;
        const hash_set* context;
        
    public:
        const_hash_iterator(int index,const hash_set* context) : index(index),context(context){}
        const_hash_iterator& operator++(){
            index++;
            while(index < context->data.size() && !context->contains_element_at_index(index))
                index++;
            return *this;
        }
        const_hash_iterator operator++(int){
            const_hash_iterator copy(*this);
            ++(*this);
            return copy;
        }
        const key& operator*() const{
            return *context->data[index];
        }
        bool operator==(const const_hash_iterator& other) const{
            return index == other.index && context == other.context;
        }
        bool operator!=(const const_hash_iterator& other) const{
            return !(*this == other);
        }
    };
    
    const_hash_iterator cbegin() const{
        int index = 0;
        while(index < data.size() && !contains_element_at_index(index))
            index++;
        if(index >= data.size()) return cend();
        return const_hash_iterator(index, this);
    }
    const_hash_iterator cend() const{
        return const_hash_iterator(data.size(), this);
    }
    const_hash_iterator find(const key& _key) const{
        int index = hash_function(_key) % data.size();
        while(index < data.size() && data[index] != std::nullopt){
            if(data[index] == _key)
                return const_hash_iterator(index, this);
            (index+=jump) %= data.size();
        }
        return cend();
    }
    
};

template<class key,class hash>
hash_set<key,hash>::hash_set() : size(0),jump(1),max_load_factor(0.75),tombstone(key()){
    data.resize(5);
}
template<class key,class hash>
hash_set<key,hash>::hash_set(size_t hash_table_size,const hash& hash_function,size_t jump) : hash_function(hash_function),jump(jump),tombstone(key()){
    data.resize(hash_table_size);
}

template<class key,class hash>
void hash_set<key,hash>::resize(size_t new_cap){
    std::vector<std::optional<key>> old_data(new_cap);
    old_data.swap(data);
    size = 0;
    for(int i = 0;i<old_data.size();i++){
        if(contains_element_at_index(i))
            insert(*old_data[i]);
    }
}

template<class key,class hash>
void hash_set<key,hash>::insert(const key& _key){
    if(current_load_factor() > max_load_factor)
        resize(data.size() * 2);
    int index = hash_function(_key) % data.size();
    while(index < data.size() && contains_element_at_index(index)){
        if(data[index] != tombstone && data[index] == _key)
            return;
        (index += jump) %= data.size();
    }
    data[index] = _key;
    size++;
}

template<class key,class hash>
bool hash_set<key,hash>::contains(const key& _key) const{
    int index = hash_function(_key) % data.size();
    while(index < data.size() && data[index] != std::nullopt){
        if(data[index] == _key)
            return true;
        (index+=jump) %= data.size();
    }
    return false;
}

template<class key,class hash>
void hash_set<key,hash>::erase(const key& _key){
    int index = hash_function(_key) % data.size();
    while(index < data.size() && data[index] != std::nullopt){
        if(data[index] != tombstone && data[index] == _key){
            data[index] = tombstone;
            size--;
            break;
        }
        (index+=jump) %= data.size();
    }
    
}

template<class key,class hash>
void hash_set<key,hash>::print() const{
    for(int i = 0;i<data.size();i++){
        if(contains_element_at_index(i))
            std::cout<<*data[i]<<" ";
    }
    std::cout<<std::endl;
}


