#ifndef ADVANCED_ALGORITHMS_ASSIGNMENT2_MESPELLRITE_H
#define ADVANCED_ALGORITHMS_ASSIGNMENT2_MESPELLRITE_H

#include "SpellCheckingAlgorithm.h"
#include "common/TextBuilder.h"

class MeSpellRite {
public:
    static void test() {
        int dict_size = 10000;
        int sample_size = 1000;

        TextBuilder::sample_english_dictionary_with_errors(dict_size, sample_size);

        std::cout << "------ Me Spell Rite ------" << std::endl << std::endl;

        std::vector<SpellCheckingAlgorithm *> spellCheckers = {
                new NaiveSpellCheckingAlgorithm(dict_size),
                new BBSTSpellCheckingAlgorithm(dict_size),
                new TrieSpellCheckingAlgorithm(dict_size),
                new HashMapSpellCheckingAlgorithm(dict_size)
        };

        for (const auto &spellChecker: spellCheckers) {
            spellChecker->spellCheck(TextBuilder::get_sample_file_name());
            delete spellChecker;
        }

        std::cout << std::endl;
    }
};

#endif //ADVANCED_ALGORITHMS_ASSIGNMENT2_MESPELLRITE_H
