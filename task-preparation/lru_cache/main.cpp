#include <iostream>
#include <list>


class lru_cache{
private:
    std::list<std::pair<int,int>> list;
    using iterator = std::list<std::pair<int,int>>::iterator;
    std::unordered_map<int,iterator> map;
    size_t capacity;
    
    void mark_as_most_recently_used(std::unordered_map<int,iterator>::iterator it){
        list.splice(list.end(), list,it->second);
        it->second = --list.end();
    }
    
public:
    lru_cache(size_t capacity) : capacity(capacity){}
    std::optional<int> find_in_cache(int key){
        auto it = map.find(key);
        if(it == map.end())
            return std::nullopt;
        auto value_to_return = it->second->second;
        mark_as_most_recently_used(it);
        return value_to_return;
    }
    
    void add_in_cache(int key,int value){
        auto it = map.find(key);
        if(it != map.end()){
            it->second->second = value;
            mark_as_most_recently_used(it);
        }
        else{
            list.push_back({key,value});
            map[key] = --list.end();
            if(list.size() == capacity){
                map.erase(list.front().first);
                list.pop_front();
                return;
            }
            
        }
    }
    
};

int main(int argc, const char * argv[]) {
    lru_cache cache(3);
    cache.add_in_cache(1, 1);
    cache.add_in_cache(2, 2);
    cache.add_in_cache(3, 3);
    cache.add_in_cache(2, 15);
    cache.add_in_cache(4,6);
    
    std::cout<<cache.find_in_cache(3).has_value()<<std::endl;
    
    
}
