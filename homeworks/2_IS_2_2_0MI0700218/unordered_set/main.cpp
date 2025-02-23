#include "unordered_set.hpp"

bool test_insert(){
    unordered_set<int> set;
    set.insert(10);
    set.insert(20);
    set.insert(30);
    set.insert(20);
    bool passed_test = (set.find(10) != set.end()) && (set.find(20) != set.end()) && (set.find(30) != set.end()) && (set.find(40) == set.end()) && (set.buckets_count() >= 3);

    return passed_test;
}

bool test_remove_by_key(){
    unordered_set<int> set;
    set.insert(10);
    set.insert(20);
    set.insert(30);
    set.remove(20);

    bool passed_test = (set.find(20) == set.end()) && (set.find(10) != set.end()) && (set.find(30) != set.end()) && (set.size() == 2);

    return passed_test;
}

bool test_find(){
    unordered_set<int> set;
    set.insert(10);
    set.insert(20);
    set.insert(30);

    auto it1 = set.find(20);
    auto it2 = set.find(40);

    bool testPass = (it1 != set.end() && *it1 == 20) &&
                    (it2 == set.end());

    return testPass;
}

bool test_erase_if(){
    unordered_set<int> set;
    set.insert(10);
    set.insert(20);
    set.insert(30);
    set.insert(40);
    set.insert(50);

    set.erase_if([](const int& x) { return x > 25; });

    bool passed_test = (set.find(10) != set.end()) && (set.find(20) != set.end()) && (set.find(30) == set.end()) && (set.find(40) == set.end()) && (set.find(50) == set.end()) && (set.size() == 2);

    return passed_test;
}


bool test_empty(){
    unordered_set<int> set;
    bool empty_before = set.empty();
    set.insert(10);
    bool not_empty_after = !set.empty();
    set.remove(10);
    bool empty_after = set.empty();

    return empty_before && not_empty_after && empty_after;
}

bool test_clear(){
    unordered_set<int> set;
    set.insert(10);
    set.insert(20);
    set.insert(30);

    set.clear();

    bool passed_test = set.empty() && (set.size() == 0) && (set.find(10) == set.end()) && (set.find(20) == set.end()) && (set.find(30) == set.end());
    return passed_test;
}

bool test_iterator(){
    unordered_set<int> set;
    set.insert(10);
    set.insert(20);
    set.insert(30);

    int sum = 0;
    for(auto it = set.begin(); it != set.end(); ++it)
        sum += *it;

    return sum == 60;
}

bool test_insert_unique(){
    unordered_set<int> set;
    set.insert(10);
    set.insert(10);
    set.insert(20);

    bool passed_test = (set.size() == 2) && (set.find(10) != set.end()) && (set.find(20) != set.end());

    return passed_test;
}

bool test_remove_by_iterator(){
    unordered_set<int> set;
    set.insert(10);
    set.insert(20);
    set.insert(30);

    auto it = set.find(20);
    if(it == set.end())
        return false;

    set.remove(it);

    bool passed_test = (set.find(20) == set.end()) && (set.size() == 2) && (set.find(10) != set.end()) && (set.find(30) != set.end());

    return passed_test;
}

bool test_erase_all(){
    unordered_set<int> set;
    set.insert(10);
    set.insert(20);
    set.insert(30);

    set.erase_if([](const int& x) { return true; });

    bool testPass = set.empty() && (set.size() == 0);

    return testPass;
}


bool test_erase_if_condition(){
    unordered_set<int> set;
    set.insert(5);
    set.insert(10);
    set.insert(15);
    set.insert(20);
    set.insert(25);

    set.erase_if([](const int& x) { return x % 10 == 0; });

    bool passed_test = (set.find(10) == set.end()) && (set.find(20) == set.end()) && (set.find(5) != set.end()) && (set.find(15) != set.end()) && (set.find(25) != set.end()) && (set.size() == 3);

    return passed_test;
}



int main(int argc, const char * argv[]) {
    std::cout << "Test Insert: " << (test_insert() ? "Passed" : "Failed") << std::endl;
    std::cout << "Test Remove By Key: " << (test_remove_by_key() ? "Passed" : "Failed") << std::endl;
    std::cout << "Test Find: " << (test_find() ? "Passed" : "Failed") << std::endl;
    std::cout << "Test Erase If: " << (test_erase_if() ? "Passed" : "Failed") << std::endl;
    std::cout << "Test Empty: " << (test_empty() ? "Passed" : "Failed") << std::endl;
    std::cout << "Test Clear: " << (test_clear() ? "Passed" : "Failed") << std::endl;
    std::cout << "Test Iterator: " << (test_iterator() ? "Passed" : "Failed") << std::endl;
    
    std::cout << "Test Insert Unique: " << (test_insert_unique() ? "Passed" : "Failed") << std::endl;
    std::cout << "Test Remove By Iterator: " << (test_remove_by_iterator() ? "Passed" : "Failed") << std::endl;
    std::cout << "Test Erase All: " << (test_erase_all() ? "Passed" : "Failed") << std::endl;
}
