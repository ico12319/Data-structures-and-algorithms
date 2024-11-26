#include "ternary_heap.h"

void test_insert_and_top() {
    ternary_heap heap;
    heap.push(10);
    if (heap.top() != 10)
        std::cerr << "Test failed: top element should be 10 after inserting 10."<<std::endl;;

    heap.push(5);
    if (heap.top() != 5)
        std::cerr << "Test failed: top element should be 20 after inserting 20."<<std::endl;

    heap.push(0);
    if (heap.top() != 0)
        std::cerr << "Test failed: top element should remain 20 after inserting 5."<<std::endl;

    std::cout << "test_insert_and_top passed.\n";
}

void test_pop_and_order() {
    ternary_heap heap;
    std::vector<int> elements = {15, 10, 20, 17, 8, 25};
    for (int el : elements) {
        heap.push(el);
    }

    std::vector<int> expected_order = {8,10,15,17,20,25};
    for (int expected : expected_order) {
        if (heap.top() != expected) {
            std::cerr << "Test failed: expected top " << expected << ", got " << heap.top() << ".\n";
        }
        heap.pop();
    }

    if (!heap.is_empty()) {
        std::cerr << "Test failed: heap should be empty after popping all elements.\n";
    }

    std::cout << "test_pop_and_order passed.\n";
}

void test_is_empty_and_size() {
    ternary_heap heap;
    if (!heap.is_empty()) {
        std::cerr << "Test failed: heap should be empty initially.\n";
    }

    if (heap.size() != 0) {
        std::cerr << "Test failed: heap size should be 0 initially.\n";
    }

    heap.push(30);
    if (heap.is_empty()) {
        std::cerr << "Test failed: heap should not be empty after insertion.\n";
    }

    if (heap.size() != 1) {
        std::cerr << "Test failed: heap size should be 1 after one insertion.\n";
    }

    heap.pop();
    if (!heap.is_empty()) {
        std::cerr << "Test failed: heap should be empty after popping the only element.\n";
    }

    if (heap.size() != 0) {
        std::cerr << "Test failed: heap size should be 0 after popping all elements.\n";
    }

    std::cout << "test_is_empty_and_size passed.\n";
}

void test_ternary_heap_build(){
    std::vector<int> v = {10,85,30,7,3,15,40,63,1,15};
    std::sort(v.begin(),v.end());
    ternary_heap h(v);
    int index = 0;
    while(!h.is_empty()){
        if(h.top() != v[index++]){
            std::cout<<"test_ternary_heap_build failed."<<std::endl;
            return;
        }
        h.pop();
    }
    std::cout<<"test_ternary_heap_build passed."<<std::endl;
}

int main() {
    test_insert_and_top();
    test_pop_and_order();
    test_is_empty_and_size();
    test_ternary_heap_build();

    std::cout << "All tests completed."<<std::endl;
        
}

