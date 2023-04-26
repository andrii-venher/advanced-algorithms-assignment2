#include "SpellCheckingAlgorithm.h"
#include "common/TextBuilder.h"


std::set<std::string, std::greater<>> BBSTSpellCheckingAlgorithm::buildDictionary() {
    std::vector<std::string> english_words = TextBuilder::read_words_from_english_dictionary(_dict_size);
    std::set<std::string, std::greater<>> dictionary;

    for (const auto &english_word: english_words) {
        dictionary.insert(english_word);
    }

    return dictionary;
}

BBSTSpellCheckingAlgorithm::BBSTSpellCheckingAlgorithm(int dict_size) : SpellCheckingAlgorithm(dict_size) {

}

int BBSTSpellCheckingAlgorithm::spellCheck(std::string filename) {
    int wrongSpelledWords = 0;
    std::set<std::string, std::greater<>> dictionary = buildDictionary();
    std::vector<std::string> text_vector = read_words(filename);

    for (const auto &word: text_vector) {
        if (dictionary.find(word) == dictionary.end()) {
            ++wrongSpelledWords;
        }
    }

    std::cout << getName() << ": " << wrongSpelledWords << std::endl;

    return wrongSpelledWords;
}


std::string BBSTSpellCheckingAlgorithm::getName() {
    return "BBST";
}