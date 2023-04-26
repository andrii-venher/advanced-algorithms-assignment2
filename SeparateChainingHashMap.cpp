#include "HashMap.h"
#include <stdexcept>

SeparateChainingHashMap::SeparateChainingHashMap(int bucket_size) : HashMap(bucket_size) {
    _map = new Node *[_bucket_size];
    for (int i = 0; i < _bucket_size; ++i) {
        _map[i] = nullptr;
    }
}

SeparateChainingHashMap::~SeparateChainingHashMap() {
    for (int i = 0; i < _bucket_size; ++i) {
        while (_map[i] != nullptr) {
            Node *next = _map[i]->get_next();
            delete _map[i];
            _map[i] = next;
        }
    }
    delete[] _map;
}

bool SeparateChainingHashMap::contains(std::string key) const {
    int index = hash(key, _bucket_size);

    Node *node = _map[index];
    while (node != nullptr) {
        if (node->get_key() == key) {
            return true;
        }
        node = node->get_next();
    }

    return false;
}

std::string SeparateChainingHashMap::get(std::string key) const {
    int index = hash(key, _bucket_size);

    Node *node = _map[index];
    while (node != nullptr) {
        if (node->get_key() == key) {
            return node->get_value();
        }
        node = node->get_next();
    }

    throw std::out_of_range("Key does not exist.");
}

void SeparateChainingHashMap::put(std::string key, std::string value) {
    if (contains(key)) {
        throw std::out_of_range("Key already exists.");
    }

    int index = hash(key, _bucket_size);
    Node *new_node = new Node(key, value);

    if (_map[index] == nullptr) {
        _map[index] = new_node;
    } else {
        new_node->set_next(_map[index]);
        _map[index] = new_node;
    }
    _size++;
}

void SeparateChainingHashMap::erase(std::string key) {
    int index = hash(key, _bucket_size);
    Node *prev = nullptr;
    Node *node = _map[index];
    while (node != nullptr) {
        if (node->get_key() == key) {
            if (prev == nullptr) {
                _map[index] = node->get_next();
            } else {
                prev->set_next(node->get_next());
            }
            delete node;
            _size--;
            return;
        }
        prev = node;
        node = node->get_next();
    }
    throw std::out_of_range("Key does not exist.");
}

std::string SeparateChainingHashMap::get_name() {
    return "SeparateChaining";
}
