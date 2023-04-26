#include "FullHouse.h"

void FullHouse::measure_one(HashMap *hash_map) {
    using clock = std::chrono::steady_clock;

    std::ofstream output_file;
    output_file.open(hash_map->get_name() + "_measurement.txt");

    std::vector<std::string> data = TextBuilder::getListOfWords(100000);

    for (const auto &word: data) {
        auto start = clock::now();
        hash_map->put(word, "dummy");
        auto end = clock::now();
        auto diff = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        output_file << hash_map->load_factor() << ' ' << diff.count() << std::endl;
    }

    output_file.close();
}

int FullHouse::get_bucket_size() {
    return 100000;
}

void FullHouse::measure() {
    std::cout << "------ Full House ------" << std::endl << std::endl;

    std::vector<HashMap *> hash_maps{new LinearProbingHashMap(get_bucket_size())};

    for (const auto &hash_map: hash_maps) {
        std::cout << "Measuring " << hash_map->get_name() << std::endl;
        measure_one(hash_map);
        delete hash_map;
    }

    std::cout << std::endl;
}
