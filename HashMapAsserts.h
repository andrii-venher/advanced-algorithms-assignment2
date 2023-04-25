#ifndef ADVANCED_ALGORITHMS_ASSIGNMENT2_HASHMAPASSERTS_H
#define ADVANCED_ALGORITHMS_ASSIGNMENT2_HASHMAPASSERTS_H

#include "HashMap.h"
#include <iostream>

class HashMapAsserts {
    static float get_bucket_size() { return 100; }

    static void run_one(HashMap *hash_map) {
        assert(0 == hash_map->size());
        assert(0 == hash_map->load_factor());

        hash_map->put("key1", "value1");
        hash_map->put("key2", "value2");

        assert(2 == hash_map->size());
        assert(2 / get_bucket_size() == hash_map->load_factor());

        assert(true == hash_map->contains("key1"));
        assert(false == hash_map->contains("key0"));

        assert("value1" == hash_map->get("key1"));

        hash_map->erase("key1");

        assert(false == hash_map->contains("key1"));
        assert(1 == hash_map->size());
        assert(1 / get_bucket_size() == hash_map->load_factor());

        try {
            hash_map->get("key1");
        } catch (const std::out_of_range &e) {
            assert("Key does not exist." == std::string(e.what()));
        }

        try {
            hash_map->erase("key1");
        } catch (const std::out_of_range &e) {
            assert("Key does not exist." == std::string(e.what()));
        }

        try {
            hash_map->put("key2", "dummy");
        } catch (const std::out_of_range &e) {
            assert("Key already exists." == std::string(e.what()));
        }
    }

public:
    static void run() {
        std::cout << "Hash map asserts started." << std::endl;

        std::vector<HashMap *> hash_maps{new SeparateChainingHashMap((int) get_bucket_size())};

        for (const auto &hash_map: hash_maps) {
            run_one(hash_map);
            delete hash_map;
        }

        std::cout << "Hash map asserts passed." << std::endl;
    }
};

#endif //ADVANCED_ALGORITHMS_ASSIGNMENT2_HASHMAPASSERTS_H
