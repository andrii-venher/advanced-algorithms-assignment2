#include "SpellCheckingAlgorithm.h"
#include "common/TextBuilder.h"


void TrieSpellCheckingAlgorithm::buildDictionary() {
    std::vector<std::string> english_words = TextBuilder::read_words_from_english_dictionary(_dict_size);

    for (const auto &english_word: english_words) {
        TrieNode *tmp = root;

        for (char character: english_word) {
            int index = character - 'a';
            if (index < 0)
            {
                index = 'z' - 'a' + 1;
            }
            if (!tmp->children[index])
                tmp->children[index] = new TrieNode();

            tmp = tmp->children[index];
        }

        tmp->isEndOfWord = true;
    }
}

void TrieSpellCheckingAlgorithm::clear(TrieSpellCheckingAlgorithm::TrieNode *node) {
    for (auto &child: node->children) {
        if (child) {
            clear(child);
        }
    }
    delete node;
}


TrieSpellCheckingAlgorithm::TrieSpellCheckingAlgorithm(int dict_size) : SpellCheckingAlgorithm(dict_size) {

}

TrieSpellCheckingAlgorithm::~TrieSpellCheckingAlgorithm() {
    clear(root);
}

int TrieSpellCheckingAlgorithm::spellCheck(std::string filename) {
    int wrongSpelledWords = 0;
    buildDictionary();
    std::vector<std::string> text_vector = read_words(filename);

    for (const auto &word: text_vector) {
        TrieNode *tmp = root;

        for (char character: word) {
            int index = character - 'a';
            if (!tmp->children[index]) {
                ++wrongSpelledWords;
                break;
            }

            tmp = tmp->children[index];
        }

        if (!tmp->isEndOfWord) {
            ++wrongSpelledWords;
        }
    }

    return wrongSpelledWords;
}

std::string TrieSpellCheckingAlgorithm::getName() {
    return "Trie";
}
