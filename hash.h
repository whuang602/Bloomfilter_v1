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

    private:
        int size;
        Node** table;
};

// constructor with one input
// q := the size of the hash table (prime number)
HashTable::HashTable(int q) {
    size = q;
    table = new Node*[size];

    for ( int i = 0 ; i < size ; i++ )
    {
        Node* newNode = new Node;
        newNode->value = -1;
        newNode->next = NULL;
        table[i] = newNode;
    }
}

// Insert a string into the hash table.
void HashTable::insert ( std::string element ) {
    int elementVal(strToInt(element));

    Node* newNode = new Node;
    newNode->value = elementVal;
    newNode->next = NULL;

    Node* current = table[elementVal % size];

    if ( current->value == -1 )
    {
        table[elementVal % size] = newNode;
        return;
    }

    while (current->next != NULL)
        current = current->next;

    current->next = newNode;
}

// Delete an element from the hash table.
void HashTable :: remove ( std::string element ) {
    int elementVal(strToInt(element));
    Node* current = table[elementVal % size];
    
    // if bucket is empty, there's nothing to be removed
    if ( current == NULL )
        return;

    // if there is only one item in the bucket, check to see if the item is
    // the value we want to remove
    if ( current->next == NULL )
    {
        if (current->value = elementVal )
        {
            table[elementVal % size] = current->next;
            delete current;
            return;
        }
        return;
    }

    // assuming there are at least two items in a bucket, check if the first
    // item is the value we want to remove
    if (current->value = elementVal )
    {
        table[elementVal % size] = current->next;
        delete current;
        return;
    }

    // The following checks the rest of the bucket to see if the desired item
    // can be found
    Node* prev = current;
    current = current->next;

    while (current->next != NULL)
    {
        if ( current->value == elementVal ) {
            Node* temp = current;
            prev->next = current->next;
            delete temp;
            return;
        }
        prev = current;
        current = current->next;
    }

}

// Return true if the element is in the hash table,
// otherwise return false.
bool HashTable::find ( std::string element ) {
    int elementVal(strToInt(element));
    Node* current = table[elementVal % size];
    
    // if there are no items in the bucket, the desired item
    // cannot be found
    if ( current == NULL )
        return false;

    // there is at least one item in the bucket, check to see 
    // if any of the items is the one we want
    while (current != NULL)
    {
        if ( current->value == elementVal ) {
            return true;
        }
        current = current->next;
    }
    
    return false;
}

// print function for testing
void HashTable::print() {

    Node* current;

    // iterate through each bucket and print out each node in an organized
    // manner
    for ( int i = 0 ; i < size ; i++ ) {
        std::cout << i << ": ";
        current = table[i];
        while ( current != NULL )
        {
            std::cout << current->value << " -> ";
            current = current->next;
        }
        std::cout << std::endl;
    }

}


#endif
