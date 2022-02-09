#ifndef HASH_H
#define HASH_H

#include "utility.h"

// Separate Chaining Hash Table
// This will be used for your removed elements of the bloom filter .
// q := the size of the hash table ( prime number )
class HashTable {
    public:
        HashTable(int q);
        void insert(std::string element);
        void remove(std::string element);
        bool find(std::string element);
        void print();
        ~HashTable();

    private:
        int size;
        std::list<int> *table;
};

// constructor with one input
// q := the size of the hash table (prime number)
HashTable::HashTable(int q) {
    size = q;
    table = new std::list<int>[size];
}

// Insert a string into the hash table.
void HashTable :: insert ( std::string element ) {
    int elementVal(strToInt(element));
    table[elementVal % size].push_back(elementVal);
}

// Delete an element from the hash table.
void HashTable :: remove ( std::string element ) {
    int elementVal(strToInt(element));
    table[elementVal % size].remove(elementVal);
}

// Return true if the element is in the hash table,
// otherwise return false.
bool HashTable :: find ( std::string element ) {
    int elementVal(strToInt(element));
    bool flag(false);

    for ( auto val : table[elementVal % size] ) {
        if ( val == elementVal )
            flag = true;
    }
    return flag;
}

// print function for testing
void HashTable::print() {
    for ( int index = 0 ; index < this->size ; index++ ) {
        std::cout << index << ": ";
        for ( auto val : table[index]) {
            std::cout << val << " -> ";
        }
        std::cout << std::endl;
    }
}

// destructor to remove the list on heap
HashTable::~HashTable() {
    delete[] table;
}

#endif