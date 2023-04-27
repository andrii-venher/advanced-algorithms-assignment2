#include "MeSpellRite.h"
#include <string>
#include <chrono>
#include <fstream>

void MeSpellRite::test() {
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
        std::cout << spellChecker->getName() << ": " << spellChecker->spellCheck(TextBuilder::get_sample_file_name());
        delete spellChecker;
    }

    std::cout << std::endl;
}

void MeSpellRite::measure_one(const std::string& spellCheckerName)
{
    int step = 100;
    int maxSize = 10000;
    int max_times = 10;

    std::ofstream file_out;
    file_out.open(spellCheckerName + "_measurement.txt");

    using clock = std::chrono::steady_clock;
    using ns = std::chrono::nanoseconds;

    for (int size = step; size <= maxSize; size += step)
    {
        ns total_time_taken = ns(0);
        for (int times = 1; times <= max_times; ++times)
        {
            SpellCheckingAlgorithm* spellChecker;
            switch (spellCheckerName[0])
            {
                case 'N': spellChecker = new NaiveSpellCheckingAlgorithm(size); break;
                case 'B': spellChecker = new BBSTSpellCheckingAlgorithm(size); break;
                case 'T': spellChecker = new TrieSpellCheckingAlgorithm(size); break;
                default: spellChecker = new HashMapSpellCheckingAlgorithm(size);
            }

            auto start = clock::now();
            spellChecker->spellCheck(TextBuilder::get_sample_file_name());
            auto end = clock::now();
            total_time_taken += std::chrono::duration_cast<ns>(end - start);

            delete spellChecker;
        }


        file_out << size << ' ' << total_time_taken.count() / max_times << std::endl;
        //std::cout << size << ": " << total_time_taken.count() / max_times << std::endl;
    }

    file_out.close();
}

void MeSpellRite::measure()
{
    std::cout << "------ Me Spell Rite ------" << std::endl << std::endl;

    std::vector<SpellCheckingAlgorithm *> spellCheckers = {
            new NaiveSpellCheckingAlgorithm(1),
            new BBSTSpellCheckingAlgorithm(1),
            new TrieSpellCheckingAlgorithm(1),
            new HashMapSpellCheckingAlgorithm(1)
    };

    for (const auto &spellChecker: spellCheckers) {
        measure_one(spellChecker->getName());
        std::cout << "Measured " << spellChecker->getName() << std::endl;
        delete spellChecker;
    }

    std::cout << std::endl;
}