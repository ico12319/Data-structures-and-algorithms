#include "ternary_heap.h"

size_t ternary_heap::get_left_child_index(size_t parent_index){
    return 3 * parent_index + 1;
}

size_t ternary_heap::get_right_child_index(size_t parent_index){
    return 3 * parent_index + 3;
}

size_t ternary_heap::get_middle_child_index(size_t parent_index){
    return 3 * parent_index + 2;
}

size_t ternary_heap::get_parent_index(size_t child_index){
    return (child_index - 1) / 3;
}

int ternary_heap::top() const{
    return heap[0];
}

bool ternary_heap::is_empty() const{
    return heap.size() == 0;
}

size_t ternary_heap::size() const{
    return heap.size();
}

void ternary_heap::push(int el){
    heap.push_back(el);
    size_t index = heap.size() - 1;
    size_t parent_index = get_parent_index(index);
    while(index > 0 && heap[parent_index] > heap[index]){
        std::swap(heap[parent_index], heap[index]);
        index = parent_index;
        parent_index = get_parent_index(index);
    }
}


void ternary_heap::heapify(size_t index){
    while(true){
        size_t left_index = get_left_child_index(index);
        size_t right_index = get_right_child_index(index);
        size_t middle_index = get_middle_child_index(index);
        
        int smallest = index;
        if(left_index < heap.size() && heap[left_index] < heap[smallest])
            smallest = left_index;
        if(right_index < heap.size() && heap[right_index] < heap[smallest])
            smallest = right_index;
        if(middle_index < heap.size() && heap[middle_index] < heap[smallest])
            smallest = middle_index;
        
        if(smallest != index){
            std::swap(heap[index],heap[smallest]);
            index = smallest;
        }
        else
            break;
    }
}

void ternary_heap::pop(){
    if(heap.empty()) return;
    std::swap(heap[0], heap[heap.size() - 1]);
    heap.pop_back();
    heapify(0);
}


ternary_heap::ternary_heap(std::vector<int>& v){
    this->heap = v;
    for(int i = heap.size() / 3 - 1;i>=0;i--)
        heapify(i);
}
