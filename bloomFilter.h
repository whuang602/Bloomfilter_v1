#ifndef BLOOMFILTER_H
#define BLOOMFILTER_H

#include "utility.h"
#include "hash.h"

// Main API of the bloom filter
// p := probability of a false positive
// m := expected number of strings to be inserted
// c := scale factor of bloom filter size
// d := scale factor of number of hash functions
class BloomFilter {
    public:
        BloomFilter (float p , int m, float c , float d);
        void insert(std::string element);
        void remove(std::string element);
        bool find(std::string element);
        void print();
        void testInsertEff();

    private:
        float prob;
        int strSize;
        int insertedNum;
        float bfScaleFactor;
        float hashScaleFactor;

        int bfSize;
        int numHash;
        bool* bfArray;
        HashTable *removedList = new HashTable(97);
};

BloomFilter::BloomFilter(float p , int m, float c , float d) {
    prob = p;
    strSize = m;
    bfScaleFactor = c;
    hashScaleFactor = d;
    insertedNum = 0;
    bfSize = BloomFilterSize(prob,strSize,bfScaleFactor);
    numHash = numHashFunctions(bfSize, strSize, hashScaleFactor);
    bfArray = new bool[bfSize];
    for ( int i = 0 ; i < bfSize ; i++ )
    {
        bfArray[i] = false;
    }
}

// Insert a string into the bloom filter .
void BloomFilter::insert ( std::string element ) {
    int elementVal(strToInt(element));
    for (int i = 0 ; i < numHash; i++ )
    {
        bfArray[hash(elementVal,i, bfSize)] = true;
    }
    insertedNum++;
}

// Delete an element from the bloom filter.
// This will use an auxiliary hash table defined below.
void BloomFilter::remove ( std::string element ) {
    removedList->insert(element);
}

// Return true if the element is in the bloom filter,
// otherwise return false.
bool BloomFilter::find ( std::string element ) {
    int elementVal(strToInt(element));
    bool flag(true);

    for (int i = 0 ; i < numHash; i++ )
    {
        if (!bfArray[hash(elementVal,i, bfSize)])
            flag = false;
    }
    
    return flag;
}

// Testing
void BloomFilter::print() {
    
    for ( int i = 0 ; i < bfSize ; i++ )
    {
        std::cout << i << ": " << bfArray[i] << std::endl;
    }
}

void BloomFilter::testInsertEff() {
    int count(0);
    for ( int i = 0 ; i < bfSize ; i++ )
    {
        if (bfArray[i])
            count++;
    }

    std::cout << "Number of inserted: " << insertedNum << "(" << insertedNum*numHash << ")" << std::endl;
    std::cout << "Number of 1s: " << count << std::endl;
}



#endif