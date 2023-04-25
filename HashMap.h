#ifndef ADVANCED_ALGORITHMS_ASSIGNMENT2_HASHMAP_H
#define ADVANCED_ALGORITHMS_ASSIGNMENT2_HASHMAP_H

#include <string>

// string - string hash map interface
class HashMap {
public:
    virtual bool contains(std::string key) = 0;

    virtual std::string get(std::string key) = 0;

    virtual void put(std::string key, std::string value) = 0;

    virtual void erase(std::string key, std::string value) = 0;

    virtual int size() = 0;

    virtual float load_factor() = 0;
};

#endif //ADVANCED_ALGORITHMS_ASSIGNMENT2_HASHMAP_H
