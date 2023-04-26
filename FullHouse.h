#ifndef ADVANCED_ALGORITHMS_ASSIGNMENT2_FULLHOUSE_H
#define ADVANCED_ALGORITHMS_ASSIGNMENT2_FULLHOUSE_H

#include "common/HashMap.h"
#include "MeSpellRite.h"
#include <fstream>

class FullHouse {
    static int bucket_size;

    static void measure_one(HashMap *hash_map);

public:
    static void measure();
};


#endif //ADVANCED_ALGORITHMS_ASSIGNMENT2_FULLHOUSE_H
