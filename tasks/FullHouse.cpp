#include <chrono>
#include "FullHouse.h"

int FullHouse::bucket_size = 1000;

void FullHouse::measure_one(HashMap *hash_map) {
    using clock = std::chrono::steady_clock;

    std::ofstream output_file;
    output_file.open(hash_map->get_name() + "_measurement.txt");

    std::vector<std::string> data = TextBuilder::read_words_from_english_dictionary(bucket_size);

    for (const auto &word: data) {
        auto start = clock::now();
        hash_map->put(word, word);
        auto end = clock::now();
        auto diff = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        output_file << hash_map->load_factor() << ' ' << diff.count() << std::endl;
    }

    output_file.close();
}

void FullHouse::measure() {
    std::cout << "------ Full House ------" << std::endl << std::endl;

    std::vector<HashMap *> hash_maps{
            new SeparateChainingHashMap(bucket_size),
            new LinearProbingHashMap(bucket_size),
            new DoubleHashingHashMap(bucket_size),
    };

    for (const auto &hash_map: hash_maps) {
        measure_one(hash_map);
        std::cout << "Measured " << hash_map->get_name() << std::endl;
        delete hash_map;
    }

    std::cout << std::endl;
}
