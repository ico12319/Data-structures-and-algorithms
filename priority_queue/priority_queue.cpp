#include "priority_queue.h"

size_t priority_queue::get_parent_index(size_t child_index){
    return (child_index - 1) / 2;
}

size_t priority_queue::get_left_child_index(size_t parent_index){
    return 2 * parent_index + 1;
}

size_t priority_queue::get_right_child_index(size_t parent_index){
    return 2 * parent_index + 2;
}

void priority_queue::heapify(size_t index){
    while(true){
        size_t left_index = get_left_child_index(index);
        size_t right_index = get_right_child_index(index);
        
        bool go_left = left_index < heap.size() && heap[left_index] > heap[index];
        bool go_right = right_index < heap.size() && heap[right_index] > heap[index];
        
        if(go_left && !go_right){
            std::swap(heap[left_index], heap[index]);
            index = left_index;
        }
        else if(!go_left && go_right){
            std::swap(heap[right_index], heap[index]);
            index = right_index;
        }
        else if(go_left && go_right){
            if(heap[left_index] > heap[right_index]){
                std::swap(heap[left_index], heap[index]);
                index = left_index;
            }
            else{
                std::swap(heap[right_index], heap[index]);
                index = right_index;
            }
        }
        else
            break;
    }
}

void priority_queue::push(int el){
    heap.push_back(el);
    int index = heap.size() - 1;
    int parent_index = get_parent_index(index);
    while(index > 0 && heap[index] > heap[parent_index]){
        std::swap(heap[index], heap[parent_index]);
        index = parent_index;
        parent_index = get_parent_index(index);
    }
}

void priority_queue::pop(){
    if(heap.empty()) return;
    std::swap(heap[0], heap[heap.size() - 1]);
    heap.pop_back();
    heapify(0);
}

int priority_queue::top() const{
    return heap[0];
}

bool priority_queue::is_empty() const{
    return heap.size() == 0;
}

size_t priority_queue::size() const{
    return heap.size();
}
