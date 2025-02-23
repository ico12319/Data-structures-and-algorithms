#include <stdio.h>
#include "BooleanSet.h"

size_t BooleanSet::getBucketIndex(size_t index) const{
    return index / bits_per_bucket;
}

size_t BooleanSet::getBitIndex(size_t index) const{
    return index % bits_per_bucket;
}

BooleanSet::BooleanSet(size_t size){
    buckets = allocator.allocate(size/bits_per_bucket + 1);
    
    for(int i = 0;i<(size/bits_per_bucket + 1);i++)
        std::allocator_traits<std::allocator<uint8_t>>::construct(allocator, buckets + i,0);
    
    this->currentElements = size;
    this->capacity = size;
    this->bucketsCount = size/bits_per_bucket + 1;
}

void BooleanSet::setBit(size_t bucket_index, size_t bit_index, bool value){
    
    if (value)
           buckets[bucket_index] |= (1 << bit_index);
       else
           buckets[bucket_index] &= ~(1 << bit_index);
}

bool BooleanSet::getBit(size_t bucketIndex, size_t bitIndex) const{
    uint8_t mask = 1 << bitIndex;
    return buckets[bucketIndex] & mask;
}


bool BooleanSet::get(size_t index) const{
    size_t totalBits = getSize();
    if(index >= totalBits)
        throw std::out_of_range("Invalid index");
    
    size_t bucketIndex = getBucketIndex(index);
    size_t bitIndex = getBitIndex(index);
    
    return getBit(bucketIndex, bitIndex);
}

size_t BooleanSet::getSize() const{
    return currentElements;
}

void BooleanSet::print() const{
    auto it = c_begin();
    for(;it!=c_end();it++)
        std::cout<<*it<<" ";
    std::cout<<std::endl;
}

void BooleanSet::push_back(bool value){
    if (currentElements == capacity)
        resize(capacity == 0 ? 1 : capacity * CONSTANTS::GROWTH_FACTOR);
    
    setBit(getBucketIndex(currentElements),getBitIndex(currentElements),value);
    currentElements++;
}


BooleanSet::BooleanSet(const BooleanSet& other){
    copy(other);
}

BooleanSet::BooleanSet(BooleanSet&& other){
    move(std::move(other));
}

BooleanSet& BooleanSet::operator=(const BooleanSet& other){
    if(this!=&other){
        destroy();
        copy(other);
    }
    return *this;
}

BooleanSet& BooleanSet::operator=(BooleanSet&& other){
    if(this!=&other){
        destroy();
        move(std::move(other));
    }
    return *this;
}

BooleanSet::~BooleanSet(){
    destroy();
}

void BooleanSet::destroy(){
    allocator.deallocate(buckets, capacity);
}

void BooleanSet::copy(const BooleanSet& other){
    buckets = allocator.allocate(other.bucketsCount);
    
    for(int i = 0;i<other.bucketsCount;i++)
        std::allocator_traits<std::allocator<uint8_t>>::construct(allocator, buckets + i,other.buckets[i]);
    
    capacity = other.capacity;
    currentElements = other.currentElements;
    bucketsCount = other.bucketsCount;
}

void BooleanSet::move(BooleanSet&& other){
    buckets = other.buckets;
    bucketsCount = other.bucketsCount;
    capacity = other.capacity;
    currentElements = other.currentElements;
    
    other.buckets = nullptr;
    other.currentElements = other.capacity = other.bucketsCount = 0;
}

void BooleanSet::resize(size_t newCap){
    uint8_t* newData = allocator.allocate(newCap/bits_per_bucket + 1);
    for(int i = 0;i<bucketsCount;i++)
        std::allocator_traits<std::allocator<uint8_t>>::construct(allocator, newData + i, buckets[i]);
    
    allocator.deallocate(buckets, capacity);
    buckets = newData;
    capacity = newCap;
    bucketsCount = newCap/bits_per_bucket + 1;
}


const bool BooleanSet::operator[](size_t index) const{
    if(index >= getSize())
        throw std::out_of_range("Invalid index");
    return get(index);
}


void BooleanSet::pop_back(){
    if(currentElements == 0)
        throw std::invalid_argument("Not enough elements");
    
    currentElements--;
}


typename BooleanSet::proxy_modifier BooleanSet::operator[](size_t index) {
    if (index >= getSize())
        throw std::out_of_range("Index out of range");
    return proxy_modifier(*this, index);
}

void BooleanSet::insert(const typename BooleanSet::const_iterator& it, bool value){
    size_t position = it.currentBit;
    
    if(it == c_end()){
        push_back(value);
        return;
    }
    if(position >= getSize())
            throw std::out_of_range("Iterator out of range");
    
    if(getSize() >= capacity)
        resize(capacity == 0 ? 1 : capacity * CONSTANTS::GROWTH_FACTOR);
    
   
        size_t bucketIndex = getBucketIndex(position);
        size_t bitIndex = getBitIndex(position);

        size_t totalBits = currentElements;
        size_t totalBuckets = (totalBits + bits_per_bucket - 1) / bits_per_bucket;

        uint8_t carry = 0;
    
        for (int i = bucketIndex; i < bucketsCount; i++) {
            uint8_t currentBucket = buckets[i];
            uint8_t lowerMask = (1 << bitIndex) - 1;
            uint8_t flippedMask = ~lowerMask;
            uint8_t lowerBits = currentBucket & lowerMask;
            uint8_t upperBits = currentBucket & flippedMask;
            uint8_t shiftedUpperBits = (upperBits << 1) | carry;
            carry = (upperBits >> (bits_per_bucket - 1)) & 1;

            buckets[i] = lowerBits | shiftedUpperBits;

            bitIndex = 0;
        }

        setBit(getBucketIndex(position), getBitIndex(position), value);

        currentElements++;
}

void BooleanSet::remove(const typename BooleanSet::const_iterator& it){
    size_t position = it.currentBit;
    
    if(it == c_end()){
        pop_back();
        return;
    }
    
    if(position >= getSize())
            throw std::out_of_range("Iterator out of range");

    for(int i = position; i < getSize() - 1; i++){
        bool nextValue = get(i + 1);
        setBit(getBucketIndex(i),getBitIndex(i), nextValue);
    }
    currentElements--;
}

void BooleanSet::pop_front(){
    if(currentElements == 0)
        throw std::out_of_range("Trying to access invalid element");
    
    remove(c_begin());
}
