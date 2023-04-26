#ifndef ADVANCED_ALGORITHMS_ASSIGNMENT2_HASHMAP_H
#define ADVANCED_ALGORITHMS_ASSIGNMENT2_HASHMAP_H

#include <string>
#include <limits>
#include <utility>

// string - string hash map interface
class HashMap {
protected:
    static int hash(const std::string &data, int bucket_size) {
        int index = 0;
        int factor = 31;
        int q = 7993;

        for (const char &i: data) {

            index = ((index % bucket_size)
                     + (((int) i) * factor) % bucket_size)
                    % bucket_size;

            factor = ((factor % q) * 31) % q;
        }

        return index;
    }

    int _size = 0;
    int _bucket_size;

public:
    explicit HashMap(int bucket_size) : _bucket_size(bucket_size) {}

    virtual ~HashMap() = default;

    virtual bool contains(std::string key) const = 0;

    virtual std::string get(std::string key) const = 0;

    virtual void put(std::string key, std::string value) = 0;

    virtual void erase(std::string key) = 0;

    int size() const { return _size; }

    float load_factor() const { return _size / (float) _bucket_size; }

    virtual std::string get_name() = 0;
};

class SeparateChainingHashMap : public HashMap {
    class Node {
        std::string _key;
        std::string _value;
        Node *_next = nullptr;
    public:
        Node(std::string key, std::string value) : _key(std::move(key)), _value(std::move(value)) {}

        std::string get_key() const { return _key; }

        std::string get_value() const { return _value; }

        Node *get_next() const { return _next; }

        void set_next(Node *next) { _next = next; }
    };

    Node **_map;

public:
    explicit SeparateChainingHashMap(int bucket_size);

    ~SeparateChainingHashMap() override;

    bool contains(std::string key) const override;

    std::string get(std::string key) const override;

    void put(std::string key, std::string value) override;

    void erase(std::string key) override;

    std::string get_name() override;
};

class LinearProbingHashMap : public HashMap {
    std::pair<std::string, std::string> *_map;

    int getIndex(const std::string &key) const;

public:
    explicit LinearProbingHashMap(int bucket_size);

    ~LinearProbingHashMap() override;

    bool contains(std::string key) const override;

    std::string get(std::string key) const override;

    void put(std::string key, std::string value) override;

    void erase(std::string key) override;

    std::string get_name() override;
};


class DoubleHashingHashMap : public HashMap {
    std::pair<std::string, std::string> *_map;

    int getIndex(const std::string &key) const;

    static int doubleHash(const std::string &data, int bucket_size) {
        int index = 0;

        for (const char &i: data) {
            index += (int) i;
        }

        return (index * bucket_size - 1) % bucket_size;
    }

public:
    explicit DoubleHashingHashMap(int bucket_size);

    ~DoubleHashingHashMap() override;

    bool contains(std::string key) const override;

    std::string get(std::string key) const override;

    void put(std::string key, std::string value) override;

    void erase(std::string key) override;

    std::string get_name() override;
};

#endif //ADVANCED_ALGORITHMS_ASSIGNMENT2_HASHMAP_H
