#include "BooleanSet.h"

bool test_end_iterator(){
    BooleanSet set;
    set.push_back(1);
    set.push_back(0);
    set.push_back(0);
    set.push_back(1);
    auto it = set.end();
    --it;
    bool res1 = (*it == 1);
    --it;
    bool res2 = (*it == 0);
    --it;
    bool res3 = (*it == 0);
    --it;
    bool res4 = (*it == 1);
    
    return res1 && res2 && res3 && res4;
}

bool test_index_operator_and_equal_operator(){
    BooleanSet set1;
    set1.push_back(1);
    set1.push_back(0);
    set1.push_back(1);
    set1.push_back(1);
    set1.push_back(1);
    set1.push_back(1);
    
    return set1[0] == 1 && set1[1] == 0 && set1[2] == 1 && set1[3] == 1 && set1[4] == 1 && set1[5] == 1;
}


bool test_iterator_values(){
    BooleanSet set;
    set.push_back(0);
    set.push_back(1);
    set.push_back(1);
    set.push_back(1);
    
    auto it = set.begin();
    auto const_it = set.c_begin();
    
    bool res1 = *it == *const_it;
    it++;
    const_it++;
    bool res2 = *it == *const_it;
    
    return res1 && res2;
}

bool test_pop_front_function() {
    BooleanSet set;
    for (int i = 0; i < 5; i++) {
        set.push_back(1);
    }
    set.pop_front();
    
    bool res1 = (set.getSize() == 4);
    bool res2 = true;
    
    for (size_t i = 0; i < set.getSize(); i++) {
        if (set[i] != 1) {
            res2 = false;
            break;
        }
    }
    
    return res1 && res2;
}

bool test_insert_end_function() {
    BooleanSet set;
    set.push_back(0);
    set.push_back(1);
    set.push_back(0);

    auto it = set.end();
    set.insert(it, 1);

    bool res1 = (set.getSize() == 4);
    bool res2 = (set[3] == 1);

    return res1 && res2;
}

bool test_remove_function() {
    BooleanSet set;
    for (int i = 0; i < 10; i++)
        set.push_back(i % 2);

    auto it = set.begin();
    it++;
    it++;
    it++;
    it++;
    it++;
    set.remove(it);
    
    
    bool res1 = (set.getSize() == 9);
    bool res2 = (set[5] == 0);
    bool res3 = true;

    bool expected_values[9] = {0, 1, 0, 1, 0, 0, 1, 0, 1};
    for (size_t i = 0; i < set.getSize(); i++) {
        if (set[i] != expected_values[i]) {
            res3 = false;
            break;
        }
    }
    
    BooleanSet set2;
    set2.push_back(1);
    set2.push_back(0);
    set2.push_back(1);
    set2.push_back(1);
    
    auto iter = set2.end();
    set.remove(iter);
    iter--;
    set.remove(iter);
    bool res4 = (set2[set2.getSize() - 1] == 1);

    return res1 && res2 && res3 && res4;
}

bool test_insert_function() {
    BooleanSet set;
    for (int i = 0; i < 80; i++) {
        set.push_back(1);
        set.push_back(0);
    }
    bool res1 = (set[1] == 0);

    auto it = set.c_begin();
    ++it;
    set.insert(it, 1);

    bool res2 = (set[1] == 1 && set[2] == 0);
    
    
    BooleanSet set2;
    set2.push_back(1);
    set2.push_back(1);
    set2.push_back(0);
    set2.push_back(1);
    
    set2.insert(set2.begin(), 1);
    bool res3 = (set[0] == 1);
    
    auto it2 = set2.begin();
    it2++;
    it2++;
    it2++;
    set2.insert(it, 1);
    
    bool expectedValues[6] = {1,1,1,1,0,1};
    for(int i = 0;i<set2.getSize();i++){
        if(set2[i] != expectedValues[i])
            return false;
    }
    
    auto it3 = set2.begin();
    it3++;
    it3++;
    it3++;
    it3++;
    set2.insert(it3, 0);
    bool res4 = (set2[set2.getSize() - 3] == 0);
    
    auto it4 = set2.end();
    set2.insert(it4, 1);
    bool res5 = (set2[set2.getSize() - 2] == 1);
    
    return res1 && res2 && res3 && res4 && res5;
}

bool test_insert_and_remove_function(){
    BooleanSet set;
    for(int i = 0;i<8;i++){
        set.push_back(1);
        set.push_back(0);
    }
    auto it = set.c_begin();
    set.insert(it, false);
    bool res1 = (set[0] == false);
    it++;
    it++;
    set.insert(it, true);
    bool res2 = (set[2] == true);
    auto it2 = set.c_end();
    it2--;
    set.insert(it2, false);
    bool res3 = (set[set.getSize() - 2] == false);
   
    return res1 && res2 && res3;
}

bool test_reverse_iterator(){
    BooleanSet set;
    set.push_back(1);
    set.push_back(0);
    set.push_back(0);
    
    auto it = set.rbegin();
    bool res1 = (*it == 0);
    it++;
    bool res2 = (*it == 0);
    it++;
    bool res3 = (*it == 1);
    
    auto it2 = set.rend();
    it2--;
    bool res4 = (*it2 == 1);
    it2--;
    bool res5 = (*it2 == 0);
    it2--;
    bool res6 = (*it2 == 0);
    
    return res1 && res2 && res3 && res4 && res5 && res6;
}


int main() {
    
    int testsPassed = 0;
    if (test_insert_function())
        std::cout << "Insert test passed." << std::endl;
    else
        std::cout << "Insert test failed." << std::endl;

    if(test_remove_function())
        std::cout << "Remove test passed." << std::endl;
    
    else
        std::cout << "Remove test failed." << std::endl;
    

    if (test_pop_front_function())
        std::cout << "Pop front test passed." << std::endl;
        
    else
        std::cout << "Pop front test failed." << std::endl;
        

    if (test_insert_end_function())
        std::cout << "Insert at end test passed." << std::endl;
    else
        std::cout << "Insert at end test failed." << std::endl;
    
    if(test_index_operator_and_equal_operator())
        std::cout<<"Index operator and equal operator test passed."<<std::endl;
    
    else
        std::cout<<"Index operator and equal operator test failed."<<std::endl;

    
    if(test_end_iterator())
        std::cout<<"End iterator test passed."<<std::endl;
    else
        std::cout<<"End iterator test failed."<<std::endl;

    if(test_iterator_values())
        std::cout<<"iterator value test passed."<<std::endl;
    else
        std::cout<<"iterator value test failed."<<std::endl;
    
    if(test_insert_and_remove_function())
        std::cout<<"Insert and remove test passed."<<std::endl;
    else
        std::cout<<"Insert and remove test failed."<<std::endl;
    
    if(test_reverse_iterator())
        std::cout<<"Reverse iterator test passed."<<std::endl;
    else
        std::cout<<"Reverse iterator test failed."<<std::endl;
    
    testsPassed+=test_insert_function();
    testsPassed+=test_end_iterator();
    testsPassed+=test_iterator_values();
    testsPassed+=test_remove_function();
    testsPassed+=test_reverse_iterator();
    testsPassed+=test_pop_front_function();
    testsPassed+=test_insert_end_function();
    testsPassed+=test_insert_and_remove_function();
    testsPassed+=test_index_operator_and_equal_operator();
    
    std::cout<<testsPassed<<" out of 9 tests passed."<<std::endl;
    

}


