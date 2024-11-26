#pragma once
#include <iostream>

class ternary_heap{
public:
    std::vector<int> heap;
    
    void heapify(size_t index);
    static size_t get_left_child_index(size_t parent_index);
    static size_t get_right_child_index(size_t parent_index);
    static size_t get_middle_child_index(size_t parent_index);
    static size_t get_parent_index(size_t child_index);
public:
    ternary_heap() = default;
    ternary_heap(std::vector<int>& v);
    void push(int el);
    void pop();
    int top() const;
    bool is_empty() const;
    size_t size() const;
};
