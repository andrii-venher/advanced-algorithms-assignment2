#ifndef ADVANCED_ALGORITHMS_ASSIGNMENT2_MESPELLRITE_H
#define ADVANCED_ALGORITHMS_ASSIGNMENT2_MESPELLRITE_H

#include "spell_checking/SpellCheckingAlgorithm.h"
#include "common/TextBuilder.h"

class MeSpellRite {
    static void measure_one(const std::string& spellCheckerName);
public:
    static void test();

    static void measure();
};

#endif //ADVANCED_ALGORITHMS_ASSIGNMENT2_MESPELLRITE_H
