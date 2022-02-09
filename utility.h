#ifndef UTILITY_H
#define UTILITY_H

#include <list>
#include <iostream>
#include <string>
#include <math.h>

// Node class to be used for hashtable's array of linkedlist
struct Node {
    int value;
    Node* next;
};

// Compute the bloom filter size based on the false positive probability desired ,
// and the expected number of strings to be inserted.
// Scale the computed size by 'c' (for experimental purposes).
// p := probability of false positives
// m := expected number of strings to be inserted
// c := scale factor of bloom filter size
int BloomFilterSize( float p , int m, int c ) {
    int bfSize = - (m * log(p)) / (pow(log(2),2));
    return bfSize * c;
}

// Compute the number of hash functions to use based on the bloom filter size, 
// and the expected number of strings to be inserted
// Scale the computed size by 'd' (for experimental purposes).
// n := bloom filter size
// m := expected number of strings to be inserted
// d := scale factor of bloom filter size
int numHashFunctions ( int n , int m, int d ) {
    int hashSize = (int)((float)n/(float)m) * log(2);
    return hashSize * d;
}

// Family of hash functions
// The index specifies which hash functions should be used
int hash (unsigned int element , int index, int bfSize ) {
    int a = (7 * index + 5) % 11;
    int b = (3* index + 2) % 13;
    int hk = (a * element + b) % bfSize;
    return hk;
}

// String to integer conversion
// Needed for running the elements on the above hash function
unsigned int strToInt ( std::string element ) {
    
    unsigned int stringValue(0);
    for ( int i = 0 ; i < element.size() ; i++ )
        stringValue += element[i] * pow(3,0.75*i);
    
    return stringValue;
}

#endif