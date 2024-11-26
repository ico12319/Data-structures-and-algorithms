#pragma once
#include <iostream>

class priority_queue{
private:
    std::vector<int> heap;
    
    static size_t get_parent_index(size_t child_index);
    static size_t get_left_child_index(size_t parent_index);
    static size_t get_right_child_index(size_t parent_index);
    void heapify(size_t index);
public:
    priority_queue() = default;
    void push(int el);
    void pop();
    int top() const;
    bool is_empty() const;
    size_t size() const;
};
