#include "HashMap.h"
#include <stdexcept>
#include <utility>

DoubleHashingHashMap::DoubleHashingHashMap(int bucket_size) : HashMap(bucket_size) {
    _map = new std::pair<std::string, std::string>[_bucket_size];
}

int DoubleHashingHashMap::getIndex(const std::string &key) const {
    int index = hash(key, _bucket_size);

    if (_map[index].first == key) {
        return index;
    } else {
        int step = doubleHash(key, _bucket_size);
        int next_index = (index + step) % _bucket_size;

        while (!_map[next_index].first.empty() && next_index != index) {
            if (_map[next_index].first == key) {
                return next_index;
            }

            next_index = (next_index + step) % _bucket_size;
        }
    }

    return -1;
}

bool DoubleHashingHashMap::contains(std::string key) const {
    int index = getIndex(key);

    if (index == -1) {
        return false;
    }

    return true;
}

std::string DoubleHashingHashMap::get(std::string key) const {
    int index = getIndex(key);

    if (index == -1) {
        throw std::out_of_range("Key does not exist.");
    }

    return _map[index].second;
}

void DoubleHashingHashMap::put(std::string key, std::string value) {
    if (_size >= _bucket_size) {
        throw std::runtime_error("The hash map is full");
    }

    if (contains(key)) {
        throw std::out_of_range("Key already exists.");
    }

    int index = hash(key, _bucket_size);

    if (_map[index].first.empty()) {
        _map[index] = std::pair<std::string, std::string>(key, value);
    } else {
        int step = doubleHash(key, _bucket_size);;

        int new_index = (index + step) % _bucket_size;
        while (!_map[new_index].first.empty()) {
            new_index = (new_index + step) % _bucket_size;
        }
        _map[new_index] = std::pair<std::string, std::string>(key, value);
    }

    _size++;
}

void DoubleHashingHashMap::erase(std::string key) {
    int index = getIndex(key);

    if (index == -1) {
        throw std::out_of_range("Key does not exist.");
    }

    _map[index].first = "";
    _map[index].second = "";
    --_size;
}

DoubleHashingHashMap::~DoubleHashingHashMap() {
    delete[] _map;
}

std::string DoubleHashingHashMap::get_name() {
    return "DoubleHashing";
}
