#ifndef TESTBLOOMFILTER_H
#define TESTBLOOMFILTER_H

#include "utility.h"
#include "bloomFilter.h"

void testBloomFilter(float p , int m, float c , float d) {

    BloomFilter bf(p,m,c,d);
    bf.insert("hello");
    bf.insert("ola");
    bf.insert("como");
    bf.insert("ucsb");
    bf.insert("cs130a");
    bf.insert("estas");
    bf.insert("bonjour");
    bf.print();
    bf.testInsertEff();

    std::cout << "ola found: " << (bool)bf.find("ola") << " --- Expected --- " << 1 << std::endl;
    std::cout << "como found: " << (bool)bf.find("como") << " --- Expected --- " << 1 << std::endl;
    std::cout << "alo found: " << (bool)bf.find("alo") << " --- Expected --- " << 0 << std::endl;

}

#endif