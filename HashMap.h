#ifndef ADVANCED_ALGORITHMS_ASSIGNMENT2_HASHMAP_H
#define ADVANCED_ALGORITHMS_ASSIGNMENT2_HASHMAP_H

#include <string>
#include <limits>

// string - string hash map interface
class HashMap {
protected:
    static int hash(const std::string &data, int bucket_size) {
        int index = 0;
        int factor = 31;

        for (const char &i: data) {

            index = ((index % bucket_size)
                     + (((int) i) * factor) % bucket_size)
                    % bucket_size;

            factor = ((factor % std::numeric_limits<int>::max())
                      * (31 % std::numeric_limits<int>::max()))
                     % std::numeric_limits<int>::max();
        }

        return index;
    }

public:
    virtual bool contains(std::string key) const = 0;

    virtual std::string get(std::string key) const = 0;

    virtual void put(std::string key, std::string value) = 0;

    virtual void erase(std::string key, std::string value) = 0;

    virtual int size() const = 0;

    virtual float load_factor() const = 0;
};

class SeparateChainingHashMap : public HashMap {
public:
    bool contains(std::string key) const override;

    std::string get(std::string key) const override;

    void put(std::string key, std::string value) override;

    void erase(std::string key, std::string value) override;

    int size() const override;

    float load_factor() const override;
};

class LinearProbingHashMap : public HashMap {
public:
    bool contains(std::string key) const override;

    std::string get(std::string key) const override;

    void put(std::string key, std::string value) override;

    void erase(std::string key, std::string value) override;

    int size() const override;

    float load_factor() const override;
};


class DoubleHashingHashMap : public HashMap {
public:
    bool contains(std::string key) const override;

    std::string get(std::string key) const override;

    void put(std::string key, std::string value) override;

    void erase(std::string key, std::string value) override;

    int size() const override;

    float load_factor() const override;
};

#endif //ADVANCED_ALGORITHMS_ASSIGNMENT2_HASHMAP_H
