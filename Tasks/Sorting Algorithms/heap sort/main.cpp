#include <iostream>

size_t get_left_child_index(size_t parent_index){
    return 2 * parent_index + 1;
}

size_t get_right_child_index(size_t parent_index){
    return 2 * parent_index + 2;
}

void heapify(std::vector<int>& heap_candiadate,size_t index,size_t size){
    while(true){
        size_t left_child_index = get_left_child_index(index);
        size_t right_child_index = get_right_child_index(index);
        
        bool go_left = left_child_index < size && heap_candiadate[index] < heap_candiadate[left_child_index];
        bool go_right = right_child_index < size && heap_candiadate[index] < heap_candiadate[right_child_index];
        
        if(go_left && !go_right){
            std::swap(heap_candiadate[left_child_index],heap_candiadate[index]);
            index = left_child_index;
        }
        else if(!go_left && go_right){
            std::swap(heap_candiadate[right_child_index],heap_candiadate[index]);
            index = right_child_index;
        }
        else if(go_left && go_right){
            if(heap_candiadate[left_child_index] > heap_candiadate[right_child_index]){
                std::swap(heap_candiadate[left_child_index],heap_candiadate[index]);
                index = left_child_index;
            }
            else{
                std::swap(heap_candiadate[right_child_index],heap_candiadate[index]);
                index = right_child_index;
            }
        }
        else
            break;
    }
}


void heap_sort(std::vector<int>& v){
    if(!v.empty()) return;
    for(int i = v.size() / 2 - 1;i>=0;i--)
        heapify(v, i, v.size());
    
    for(int i = v.size();i>1;i--){
        std::swap(v[0],v[i - 1]);
        heapify(v, 0, i - 1);
    }
}

int main(int argc, const char * argv[]) {
    std::vector<int> v = {6,1,0,1,4,3};
    heap_sort(v);
    for(const auto& el : v)
        std::cout<<el<<" ";
}
