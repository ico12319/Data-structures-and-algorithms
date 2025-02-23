#pragma once
#include <iostream>
#include <list>
#include <forward_list>

namespace CONSTANTS {
constexpr double MAX_LOAD_FACTOR_DEFAULT = 0.75;
constexpr size_t GROWTH_FACTOR = 2;
constexpr size_t INITIAL_BUCKET_COUNT = 5;
}

template<class key,class hasher = std::hash<key>>
class unordered_set{
private:
    std::list<key> data;
    using list_iterator = std::list<key>::iterator;
    std::vector<std::forward_list<list_iterator>> hash_table;
    hasher hash_function;
    double max_load_factor;
    void resize();
    double current_load_factor() const;
    
    class hash_iterator{
    private:
        size_t index;
        unordered_set* context;
        using singly_linked_list_iterator = std::forward_list<list_iterator>::iterator;
        singly_linked_list_iterator it;
        friend class unordered_set<key,hasher>;
    public:
        hash_iterator() = default;
        hash_iterator(size_t index,unordered_set* context, singly_linked_list_iterator it){
            this->index = index;
            this->context = context;
            this->it = it;
        }
        hash_iterator& operator++(){
            ++it;
            if(it == context->hash_table[index].end()){
                index++;
                while(index < context->hash_table.size() && context->hash_table[index].empty())
                    index++;
                if(index < context->hash_table.size())
                    it = context->hash_table[index].begin();
            }
            return *this;
        }
        hash_iterator operator++(int dummy){
            hash_iterator copy(*this);
            ++(*this);
            return copy;
        }
        key* operator->(){
            return &(*(*it));
        }
        key& operator*(){
            return *(*it);
        }
        bool operator==(const hash_iterator& other) const{
            return this->context == other.context && this->index == other.index && this->it == other.it;
        }
        bool operator!=(const hash_iterator& other) const{
            return !(*this == other);
        }
    };
    
    class const_hash_iterator{
    private:
        size_t index;
        const unordered_set* context;
        using singly_linked_list_const_iterator = std::forward_list<list_iterator>::const_iterator;
        singly_linked_list_const_iterator const_it;
        friend class unordered_set<key,hasher>;
        
    public:
        const_hash_iterator(hash_iterator it){
            this->index = it.index;
            this->context = it.context;
            this->const_it = it.it;
        }
        const_hash_iterator(size_t index,const unordered_set* context,singly_linked_list_const_iterator const_it){
            this->index = index;
            this->context = context;
            this->const_it = const_it;
        }
        
        const_hash_iterator& operator++(){
            ++const_it;
            if(const_it == context->hash_table[index].end()){
                index++;
                while(index < context->hash_table.size() && context->hash_table[index].empty())
                    index++;
                if(index < context->hash_table.size())
                    const_it = context->hash_table[index].begin();
            }
            return *this;
        }
        
        const_hash_iterator operator++(int dummy){
            const_hash_iterator copy(*this);
            ++(*this);
            return copy;
        }
        
        const key* operator->() const{
            return &(*(*const_it));
        }
        const key& operator*() const{
            return *(*const_it);
        }
        bool operator==(const const_hash_iterator& other) const{
            return this->context == other.context && this->index == other.index && this->it == other.it;
        }
        bool operator!=(const const_hash_iterator& other) const{
            return !(*this == other);
        }
        
        
    };
    
public:
    unordered_set();
    unordered_set(double max_load_factor,const hasher& function);
    void insert(const key& _key);
    void remove(const key& _key);
    bool empty() const;
    void clear();
    hash_iterator begin();
    hash_iterator end();
    hash_iterator find(const key& _key);
    void remove(hash_iterator& it);
    void print() const;
    size_t buckets_count() const;
    size_t size() const;
    template<class predicate>
    void erase_if(const predicate& pred);
};


template<class key,class hasher>
unordered_set<key,hasher>::unordered_set(){
    this->max_load_factor = CONSTANTS::MAX_LOAD_FACTOR_DEFAULT;
    hash_table.resize(CONSTANTS::INITIAL_BUCKET_COUNT);
}


template<class key,class hasher>
unordered_set<key,hasher>::unordered_set(double max_load_factor,const hasher& function){
    this->max_load_factor = max_load_factor;
    this->hash_function = function;
    hash_table.resize(CONSTANTS::INITIAL_BUCKET_COUNT);
}

template<class key,class hasher>
void unordered_set<key,hasher>::insert(const key& _key){
    if(current_load_factor() >= max_load_factor)
        resize();
    auto hash_index = hash_function(_key) % hash_table.size();
    auto& current_bucket = hash_table[hash_index];
    auto lambda = [&_key](list_iterator it){return *it == _key;};
    auto it = std::find_if(current_bucket.begin(),current_bucket.end(),lambda);
    if(it != current_bucket.end())
        return;
    data.push_back(_key);
    current_bucket.push_front(--data.end());
}

template<class key,class hasher>
void unordered_set<key,hasher>::remove(const key& _key){
    auto hash_index = hash_function(_key) % hash_table.size();
    auto& current_bucket = hash_table[hash_index];
    current_bucket.remove_if([&_key,this](list_iterator it){
        if(*it == _key){
            data.erase(it);
            return true;
        }
        return false;
    });
}

template<class key,class hasher>
bool unordered_set<key,hasher>::empty() const{
    return data.empty();
}

template<class key,class hasher>
double unordered_set<key,hasher>::current_load_factor() const{
    return static_cast<double>(data.size()) / hash_table.size();
}

template<class key,class hasher>
void unordered_set<key,hasher>::resize(){
    const size_t new_capacity = hash_table.size() * CONSTANTS::GROWTH_FACTOR;
    std::vector<std::forward_list<list_iterator>> new_table(new_capacity);
    for(auto it = data.begin();it!=data.end();it++){
        auto hash_index = hash_function(*it) % new_capacity;
        new_table[hash_index].push_front(it);
    }
    hash_table = std::move(new_table);
}

template<class key,class hasher>
void unordered_set<key,hasher>::clear(){
    data.clear();
    for(auto& bucket : hash_table)
        bucket.clear();
}

template<class key,class hasher>
typename unordered_set<key,hasher>::hash_iterator unordered_set<key,hasher>::begin(){
    int index = 0;
    while(index < hash_table.size() && hash_table[index].empty())
        index++;
    if(index < hash_table.size())
        return hash_iterator(index, this, hash_table[index].begin());
    return end();
}

template<class key,class hasher>
typename unordered_set<key,hasher>::hash_iterator unordered_set<key,hasher>::end(){
    return hash_iterator(hash_table.size(), this, hash_table[hash_table.size() - 1].end());
}

template<class key,class hasher>
typename unordered_set<key,hasher>::hash_iterator unordered_set<key,hasher>::find(const key& _key){
    auto hash_index = hash_function(_key) % hash_table.size();
    auto& current_bucket = hash_table[hash_index];
    int index = 0;
    bool is_found = false;
    while(index < hash_table.size()){
        if(!hash_table[index].empty()){
            for(const auto& iterator_to_list : hash_table[index]){
                if(*iterator_to_list == _key){
                    is_found = true;
                    break;
                }
            }
            if(is_found)
                break;
        }
        index++;
    }
    auto lambda = [&_key](list_iterator it){return *it == _key;};
    auto iterator = std::find_if(current_bucket.begin(),current_bucket.end(),lambda);
    if(iterator == current_bucket.end())
        return end();
    return hash_iterator(index, this, iterator);
}

template<class key,class hasher>
void unordered_set<key,hasher>::print() const{
    for(const auto& el : data)
        std::cout<<el<<" ";
    std::cout<<std::endl;
}


template<class key,class hasher>
size_t unordered_set<key,hasher>::buckets_count() const{
    return hash_table.size();
}

template<class key,class hasher>
void unordered_set<key,hasher>::remove(typename unordered_set<key,hasher>::hash_iterator& it){
    if(it.context != this)
        throw std::invalid_argument("The iterator does not belong to this container!");
    auto hash_index = it.index;
    auto it_to_remove_from_hash_table = it.it;
    auto it_to_remove_from_data = *(it_to_remove_from_hash_table);
    auto& current_bucket = hash_table[hash_index];
    data.erase(it_to_remove_from_data);
    current_bucket.remove(*it_to_remove_from_hash_table);
    it = end();
}

template<class key,class hasher>
template<class predicate>
void unordered_set<key,hasher>::erase_if(const predicate& pred){
    for(int i = 0;i<hash_table.size();i++){
        auto& current_bucket = hash_table[i];
        current_bucket.remove_if([pred,this](list_iterator it){
            if(pred(*it)){
                data.erase(it);
                return true;
            }
            return false;
        });
    }
}

template<class key,class hasher>
size_t unordered_set<key,hasher>::size() const{
    return data.size();
}
