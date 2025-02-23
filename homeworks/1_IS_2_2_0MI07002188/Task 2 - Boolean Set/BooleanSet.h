#pragma once
#include <iostream>
#include <memory>

namespace CONSTANTS{
constexpr size_t GROWTH_FACTOR = 2;
}

class BooleanSet{
private:
    uint8_t* buckets = nullptr;
    static const size_t bits_per_bucket = sizeof(uint8_t) * 8;
    size_t currentElements = 0;
    size_t capacity = 0;
    size_t bucketsCount = 0;
    std::allocator<uint8_t> allocator;
    
    void copy(const BooleanSet& other);
    void move(BooleanSet&& other);
    void destroy();
    void resize(size_t newCap);
    void setBit(size_t bucket_index, size_t bit_index, bool value);
    bool getBit(size_t bucketIndex,size_t bitIndex) const;
    bool get(size_t index) const;
    size_t getBucketIndex(size_t index) const;
    size_t getBitIndex(size_t index) const;
    
    class proxy_modifier{
    private:
        friend class BooleanSet;
        BooleanSet& set;
        size_t index;

        proxy_modifier(BooleanSet& set, size_t index) : set(set), index(index) {}

        public:
        operator bool() const{
            return set.get(index);
        }
        
        proxy_modifier& operator=(bool value) {
            size_t bitIndex = set.getBitIndex(index);
            size_t bucketIndex = set.getBucketIndex(index);
            set.setBit(bucketIndex,bitIndex,value);
            return *this;
        }
    };
    
public:
    BooleanSet() = default;
    BooleanSet(size_t size);
    BooleanSet(const BooleanSet& other);
    BooleanSet(BooleanSet&& other);
    ~BooleanSet();
    BooleanSet& operator=(const BooleanSet& other);
    BooleanSet& operator=(BooleanSet&& other);
    
    class iterator{
    private:
        friend class BooleanSet;
        BooleanSet* set;
        size_t currentBit;
        
    public:
        iterator(BooleanSet* set,size_t start) : set(set),currentBit(start){}
        iterator& operator++(){
            currentBit++;
            return *this;
        }
        iterator operator++(int){
            iterator copy(*this);
            ++(*this);
            return copy;
        }
        iterator& operator--(){
            currentBit--;
            return *this;
        }
        iterator operator--(int){
            iterator copy(*this);
            --(*this);
            return copy;
        }
        proxy_modifier operator*() {
            return proxy_modifier(*set, currentBit);
        }
        
        bool operator==(const iterator& other) const {return currentBit == other.currentBit && set == other.set;}
        bool operator!=(const iterator& other) const {return !(*this == other);}
    };
    
    class const_iterator{
    private:
        friend class BooleanSet;
        const BooleanSet* set;
        size_t currentBit;
        
    public:
        const_iterator(const BooleanSet* set,size_t start) : set(set),currentBit(start){}
        const_iterator(const iterator& other) : set(other.set),currentBit(other.currentBit){}
        
        const_iterator& operator++(){
            currentBit++;
            return *this;
        }
        const_iterator operator++(int){
            const_iterator copy(*this);
            ++(*this);
            return copy;
        }
        const_iterator& operator--(){
            if(currentBit!=0)
                currentBit--;
            return *this;
        }
        const_iterator operator--(int){
            const_iterator copy(*this);
            --(*this);
            return copy;
        }
        
        const bool operator*() const{
            return set->get(currentBit);
        }
        
        bool operator==(const const_iterator& other) const {return currentBit == other.currentBit && set == other.set;}
        bool operator!=(const const_iterator& other) const {return !(*this==other);}
    };
    
    class reverse_iterator{
    private:
        friend class BooleanSet;
        BooleanSet* set;
        int currentBit;
        
    public:
        reverse_iterator(BooleanSet* set,int end) : set(set),currentBit(end){}
        
        reverse_iterator& operator++(){
            if(currentBit != 0)
                currentBit--;
            return *this;
        }
        reverse_iterator operator++(int){
            reverse_iterator copy(*this);
            ++(*this);
            return copy;
        }
        reverse_iterator& operator--(){
            currentBit++;
            return *this;
        }
        reverse_iterator operator--(int){
            reverse_iterator copy(*this);
            --(*this);
            return copy;
        }
        proxy_modifier operator*(){
            return proxy_modifier(*set, currentBit);
        }
        bool operator==(const reverse_iterator& other) const {return currentBit == other.currentBit && set == other.set;}
        bool operator!=(const reverse_iterator& other) const {return !(*this==other);}
    };
    
    class const_reverse_iterator{
    private:
        friend class BooleanSet;
        const BooleanSet* set;
        int currentBit;
        
    public:
        const_reverse_iterator(const BooleanSet* set,int end) : set(set),currentBit(end){}
        const_reverse_iterator(const reverse_iterator& other) : set(other.set),currentBit(other.currentBit){}
        
        const_reverse_iterator& operator++(){
            if(currentBit != 0)
                currentBit--;
            return *this;
        }
        const_reverse_iterator operator++(int){
            const_reverse_iterator copy(*this);
            ++(*this);
            return copy;
        }
        const_reverse_iterator& operator--(){
            currentBit++;
            return *this;
        }
        const_reverse_iterator operator--(int){
            const_reverse_iterator copy(*this);
            --(*this);
            return copy;
        }
        
        const bool operator*() const{
            return set->get(currentBit);
        }
        
        bool operator==(const const_iterator& other) const {return currentBit == other.currentBit && set == other.set;}
        bool operator!=(const const_iterator& other) const {return !(*this == other);}
    };
    
    void push_back(bool value);
    void pop_back();
    void insert(const const_iterator& it,bool value);
    void remove(const const_iterator& it);
    void pop_front();
    
    
    const bool operator[](size_t index) const;
    proxy_modifier operator[](size_t index);
    
    void print() const;
    size_t getSize() const;
    
    
    iterator begin(){return iterator(this, 0);}
    iterator end() {return iterator(this, getSize());}
    const_iterator c_begin() const {return const_iterator(this, 0);}
    const_iterator c_end() const {return const_iterator(this, getSize());}
    reverse_iterator rbegin() {return reverse_iterator(this, getSize() - 1);}
    reverse_iterator rend() {return reverse_iterator(this, -1);}
    const_reverse_iterator c_rbegin() const{return const_reverse_iterator(this, getSize() - 1);}
    const_reverse_iterator c_rend() const{return const_reverse_iterator(this, -1);}
};
