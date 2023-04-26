#ifndef ADVANCED_ALGORITHMS_ASSIGNMENT2_FULLHOUSE_H
#define ADVANCED_ALGORITHMS_ASSIGNMENT2_FULLHOUSE_H

#include "HashMap.h"
#include "MeSpellRite.h"
#include <fstream>

class FullHouse {
    static void measure_one(HashMap *hash_map);

    static int get_bucket_size();

public:
    static void measure();
};


#endif //ADVANCED_ALGORITHMS_ASSIGNMENT2_FULLHOUSE_H
