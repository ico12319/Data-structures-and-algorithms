#pragma once
#include <iostream>
#include <list>
#include <forward_list>

template<class Key,class Value,class Hash = std::hash<Key>>
class map{
private:
    using pair_type = std::pair<Key,Value>;
    using iterator_type = std::list<pair_type>::iterator;
    std::list<pair_type> data;
    std::vector<std::forward_list<iterator_type>> hash_map;
    Hash hash;
    
public:
    map();
    void insert(const Key& key,const Value& value);
    bool contains(const Key& key) const;
    void erase(const Key& key);
    void print() const;
    size_t size() const;
    bool empty() const;
};

template<class Key,class Value,class Hash>
map<Key,Value,Hash>::map(){
    hash_map.resize(10);
}

template<class Key,class Value,class Hash>
void map<Key,Value,Hash>::insert(const Key& key, const Value& value){
    auto hash_code = hash(key) % hash_map.size();
    auto& current_bucket = hash_map[hash_code];
    auto lambda = [&key](const iterator_type& iter){return iter->first == key;};
    auto it = std::find_if(current_bucket.begin(),current_bucket.end(),lambda);
    if(it != current_bucket.end()) return;
    
    data.push_back(std::make_pair(key,value));
    current_bucket.push_front(--data.end());
}

template<class Key,class Value,class Hash>
void map<Key,Value,Hash>::print() const{
    for(auto it = data.begin();it!=data.end();it++){
        std::cout<<it->first<<" " << it->second;
        std::cout<<std::endl;
    }
}

template<class Key,class Value,class Hash>
bool map<Key,Value,Hash>::contains(const Key& key) const{
    auto hash_code = hash(key) % hash_map.size();
    auto& current_bucket = hash_map[hash_code];
    auto lambda = [&key](const iterator_type& iter){return iter->first == key;};
    auto it = std::find_if(current_bucket.begin(),current_bucket.end(),lambda);
    if(it != current_bucket.end()) return true;
    return false;
}

template<class Key,class Value,class Hash>
void map<Key,Value,Hash>::erase(const Key& key){
    auto hash_code = hash(key) % hash_map.size();
    auto& current_bucket = hash_map[hash_code];
    current_bucket.remove_if([this,&key](const iterator_type& iter)
                            {
                                if(iter->first == key)
                                {     
                                    data.erase(iter);
                                    return true;
                                }
                                return false;
                            });
}


template<class Key,class Value,class Hash>
size_t map<Key,Value,Hash>::size() const{
    return data.size();
}

template<class Key,class Value,class Hash>
bool map<Key,Value,Hash>::empty() const{
    size() == 0;
}




