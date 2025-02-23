#pragma once
#include "traversal_comparator.h"
#include <set>

class dfs_traversals{
private:
    std::set<dfs_traversal,compare_traversals> traversals;// i am using set in order to avoid including the same path multiple times
    void generate_all_traversals(oriented_graph& graph,int src,std::vector<std::vector<int>>& adjecency_list,size_t index);
    
    class const_dfs_traversal_iterator{
    private:
        std::set<dfs_traversal,compare_traversals>::const_iterator it;
        
    public:
        const_dfs_traversal_iterator(std::set<dfs_traversal,compare_traversals>::const_iterator it) : it(it){}
        const_dfs_traversal_iterator& operator++(){
            ++it;
            return *this;
        }
        const_dfs_traversal_iterator operator++(int dummy){
            const_dfs_traversal_iterator copy(*this);
            ++(*this);
            return copy;
        }
        const dfs_traversal& operator*() const{
            return *it;
        }
        const dfs_traversal* operator->() const{
            return &(*it);
        }
        
        bool operator==(const const_dfs_traversal_iterator& other) const{
            return other.it == it;
        }
        bool operator!=(const const_dfs_traversal_iterator& other) const{
            return !(*this == other);
        }
    };
    
public:
    dfs_traversals(oriented_graph& graph,int starting_node);
    friend std::ostream& operator<<(std::ostream& os,const dfs_traversals& obj);
    const const_dfs_traversal_iterator cbegin() const;
    const const_dfs_traversal_iterator cend() const;
};
