#include "HashMap.h"
#include <stdexcept>
#include <utility>

DoubleHashingHashMap::DoubleHashingHashMap(int bucket_size) : HashMap(bucket_size) {
    _map = new std::pair<std::string, std::string>[_bucket_size];
}

int DoubleHashingHashMap::getIndex(const std::string& key) const{
    int index = hash(key, _bucket_size);

    if (_map[index].first == key) {
        return index;
    } else {
        int next_index = (index + index) % _bucket_size;
        while (!_map[next_index].first.empty() && next_index != index) {
            if (_map[next_index].first == key) {
                return next_index;
            }
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

    if (index == -1)
    {
        throw std::out_of_range("Key does not exist.");
    }

    return _map[index].second;
}

void DoubleHashingHashMap::put(std::string key, std::string value) {
    if (contains(key)) {
        throw std::out_of_range("Key already exists.");
    }

    if (_size >= _bucket_size) {
        throw std::runtime_error("The hash map is full");
    }

    int index = hash(key, _bucket_size);
    if (_map[index].first.empty()) {
        _map[index] = std::pair<std::string, std::string>(key, value);
    } else {
        int new_index = (index + index) % _bucket_size;
        while (!_map[index].first.empty()) {
            new_index = (new_index + 1) % _bucket_size;
        }
        _map[new_index] = std::pair<std::string, std::string>(key, value);
    }

    _size++;
}

void DoubleHashingHashMap::erase(std::string key) {
    int index = getIndex(key);

    if (index == -1)
    {
        throw std::out_of_range("Key does not exist.");
    }

    _map[index].first = "";
    _map[index].second = "";
    --_size;
}

DoubleHashingHashMap::~DoubleHashingHashMap() {
    delete[] _map;
}
