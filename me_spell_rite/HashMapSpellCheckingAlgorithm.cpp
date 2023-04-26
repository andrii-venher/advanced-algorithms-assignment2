#include "SpellCheckingAlgorithm.h"
#include "common/TextBuilder.h"


void HashMapSpellCheckingAlgorithm::buildDictionary() {
    std::vector<std::string> english_words = TextBuilder::read_words_from_english_dictionary(_dict_size);

    for (const auto &english_word: english_words) {
        _hashMap->put(english_word, english_word);
    }
}

HashMapSpellCheckingAlgorithm::HashMapSpellCheckingAlgorithm(int dict_size) : SpellCheckingAlgorithm(dict_size) {
    _hashMap = new LinearProbingHashMap(_dict_size + _dict_size * 0.25);
}

HashMapSpellCheckingAlgorithm::~HashMapSpellCheckingAlgorithm() {
    delete _hashMap;
    _hashMap = nullptr;
}

int HashMapSpellCheckingAlgorithm::spellCheck(std::string filename) {
    int wrongSpelledWords = 0;
    buildDictionary();
    std::vector<std::string> text_vector = read_words(filename);

    for (const auto &word: text_vector) {
        if (!_hashMap->contains(word)) {
            ++wrongSpelledWords;
        }
    }

    std::cout << getName() << ": " << wrongSpelledWords << std::endl;

    return wrongSpelledWords;
}

std::string HashMapSpellCheckingAlgorithm::getName() {
    return "HashMap";
}

