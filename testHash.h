#ifndef TESTHASH_H
#define TESTHASH_H

#include "utility.h"
#include "hash.h"

void testHash(int size) {

    std::cout << " --- Hash Test Begins --- " << std::endl;
    HashTable hsh(size);

    std::cout << " --- Hash Test: Inserting Elements --- " << std::endl;
    hsh.insert("hello");
    hsh.insert("ola");
    hsh.insert("bonjour");
    hsh.insert("UCSB");
    hsh.insert("cs130a");
    hsh.insert("cs130b");
    hsh.print();

    std::cout << std::endl << " --- Hash Test: Deleting Element --- " << std::endl;
    hsh.remove("hello");
    hsh.remove("bonjour");
    hsh.print();

    std::cout << std::endl << " --- Hash Test: Finding Element --- " << std::endl;
    std::cout << "hello found: " << hsh.find("hello") << " --- Expected: 0" << std::endl;
    std::cout << "ola found: " << hsh.find("ola") << " --- Expected: 1" << std::endl;
    std::cout << "bonjour found: " << hsh.find("bonjour") << " --- Expected: 0" << std::endl;
    std::cout << "UCSB found: " << hsh.find("UCSB") << " --- Expected: 1" << std::endl;
    std::cout << "cs130a found: " << hsh.find("cs130a") << " --- Expected: 1" << std::endl;
    std::cout << "cs130b found: " << hsh.find("cs130b") << " --- Expected: 1" << std::endl;

    std::cout << std::endl << " --- Hash Tested Successfully --- " << std::endl;

}

#endif