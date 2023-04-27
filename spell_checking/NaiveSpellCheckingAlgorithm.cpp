#include "SpellCheckingAlgorithm.h"
#include "common/TextBuilder.h"

void NaiveSpellCheckingAlgorithm::buildDictionary() {
    std::vector<std::string> english_words = TextBuilder::read_words_from_english_dictionary(_dict_size);

    for (const auto &english_word: english_words) {
        Node **tmp = &root;
        while (*tmp != nullptr) {
            tmp = &((*tmp)->next);
        }
        *tmp = new Node(english_word);
    }
}

NaiveSpellCheckingAlgorithm::NaiveSpellCheckingAlgorithm(int dict_size) : SpellCheckingAlgorithm(dict_size) {

}

NaiveSpellCheckingAlgorithm::~NaiveSpellCheckingAlgorithm() {
    Node *tmp = root;
    Node *destroy = tmp;
    while (tmp != nullptr) {
        tmp = tmp->next;
        delete destroy;
        destroy = tmp;
    }
}

int NaiveSpellCheckingAlgorithm::spellCheck(std::string filename) {
    int wrongSpelledWords = 0;
    buildDictionary();
    std::vector<std::string> text_vector = read_words(filename);

    bool word_found;
    for (const auto &word: text_vector) {
        word_found = false;
        Node *tmp = root;
        while (tmp != nullptr) {
            if (tmp->word == word) {
                word_found = true;
                break;
            } else {
                tmp = tmp->next;
            }
        }

        if (!word_found) {
            ++wrongSpelledWords;
        }
    }

    return wrongSpelledWords;
}

std::string NaiveSpellCheckingAlgorithm::getName() {
    return "Naive";
}

