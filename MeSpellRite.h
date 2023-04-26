#ifndef ADVANCED_ALGORITHMS_ASSIGNMENT2_MESPELLRITE_H
#define ADVANCED_ALGORITHMS_ASSIGNMENT2_MESPELLRITE_H

#include "HashMap.h"
#include <fstream>
#include <string>
#include <utility>
#include <vector>
#include <random>
#include <iostream>
#include <set>

const int dict_size = 10000;
const int text_size = 1000;

class TextBuilder {
public:
    static std::vector<std::string> getListOfWords() {
        std::string tmp;
        std::ifstream file_in;
        std::vector<std::string> english_words;
        file_in.open("english_words.txt");
        int size = 0;

        while (getline(file_in, tmp) && size++ < dict_size) {
            english_words.push_back(tmp);
        }

        file_in.close();

        return english_words;
    }

    static void buildText() {
        std::vector<std::string> english_words = getListOfWords();

        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> dist_word(0, english_words.size() - 1);
        std::uniform_int_distribution<std::mt19937::result_type> dist_spelling(1, 100);

        std::string text;
        std::ofstream file_out;
        file_out.open(get_output_file_name());

        for (int i = 0; i < text_size; ++i) {
            if (dist_spelling(rng) <= 75) {
                //spelt right 75% chance
                file_out << english_words[dist_word(rng)] << '\n';
            } else {
                //spelt wrong (extra z in the end) 25% chance
                file_out << english_words[dist_word(rng)] << "z\n";
            }
        }
    }

    static std::string get_output_file_name() { return "text.txt"; }
};

class SpellCheckingAlgorithm {
public:
    virtual std::string getName() = 0;

    virtual int spellCheck(std::string filename) = 0;

    virtual ~SpellCheckingAlgorithm() = default;

protected:
    static std::vector<std::string> textFileToVector(const std::string &filename) {
        std::ifstream file_in;
        file_in.open(filename);
        std::vector<std::string> words;
        std::string tmp;

        while (getline(file_in, tmp)) {
            words.push_back(tmp);
        }

        file_in.close();

        return words;
    }
};

class NaiveSpellCheckingAlgorithm : public SpellCheckingAlgorithm {
private:
    struct Node {
        std::string word;
        Node *next;

        explicit Node(std::string _word) :
                word(std::move(_word)),
                next(nullptr) {

        }
    };

    Node *root = nullptr;

    void buildDictionary() {
        std::vector<std::string> english_words = TextBuilder::getListOfWords();

        for (const auto &english_word: english_words) {
            Node **tmp = &root;
            while (*tmp != nullptr) {
                tmp = &((*tmp)->next);
            }
            *tmp = new Node(english_word);
        }
    }

public:
    std::string getName() override {
        return "Naive";
    }

    int spellCheck(std::string filename) override {
        int wrongSpelledWords = 0;
        buildDictionary();
        std::vector<std::string> text_vector = textFileToVector(filename);

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
        std::cout << getName() << ": " << wrongSpelledWords << std::endl;

        return wrongSpelledWords;
    }

    ~NaiveSpellCheckingAlgorithm() override {
        Node *tmp = root;
        Node *destroy = tmp;
        while (tmp != nullptr) {
            tmp = tmp->next;
            delete destroy;
            destroy = tmp;
        }
    }
};

class BBSTSpellCheckingAlgorithm : public SpellCheckingAlgorithm {
private:
    static std::set<std::string, std::greater<>> buildDictionary() {
        std::vector<std::string> english_words = TextBuilder::getListOfWords();
        std::set<std::string, std::greater<>> dictionary;

        for (const auto &english_word: english_words) {
            dictionary.insert(english_word);
        }

        return dictionary;
    }

public:
    std::string getName() override {
        return "BBST";
    }

    int spellCheck(std::string filename) override {
        int wrongSpelledWords = 0;
        std::set<std::string, std::greater<>> dictionary = buildDictionary();
        std::vector<std::string> text_vector = textFileToVector(filename);

        for (const auto &word: text_vector) {
            if (dictionary.find(word) == dictionary.end()) {
                ++wrongSpelledWords;
            }
        }

        std::cout << getName() << ": " << wrongSpelledWords << std::endl;

        return wrongSpelledWords;
    }

    ~BBSTSpellCheckingAlgorithm() override = default;
};

class TrieSpellCheckingAlgorithm : public SpellCheckingAlgorithm {
private:
    struct TrieNode {
        struct TrieNode *children[26] = {};
        bool isEndOfWord = false;

        TrieNode() {
            for (auto &child: children) {
                child = nullptr;
            }
        }
    };

    TrieNode *root = new TrieNode();

    void buildDictionary() {
        std::vector<std::string> english_words = TextBuilder::getListOfWords();

        for (const auto &english_word: english_words) {
            TrieNode *tmp = root;

            for (char character: english_word) {
                int index = character - 'a';
                if (!tmp->children[index])
                    tmp->children[index] = new TrieNode();

                tmp = tmp->children[index];
            }

            tmp->isEndOfWord = true;
        }
    }

    void clear(TrieNode *node) {
        for (auto &child: node->children) {
            if (child) {
                clear(child);
            }
        }
        delete node;
    }

public:
    std::string getName() override {
        return "Trie";
    }

    int spellCheck(std::string filename) override {
        int wrongSpelledWords = 0;
        buildDictionary();
        std::vector<std::string> text_vector = textFileToVector(filename);

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

        std::cout << getName() << ": " << wrongSpelledWords << std::endl;

        return wrongSpelledWords;
    }

    ~TrieSpellCheckingAlgorithm() override {
        clear(root);
    }
};

class HashMapSpellCheckingAlgorithm : public SpellCheckingAlgorithm {
private:
    LinearProbingHashMap hashMap = LinearProbingHashMap(dict_size + dict_size * 0.25);

    void buildDictionary()
    {
        std::vector<std::string> english_words = TextBuilder::getListOfWords();

        for (const auto &english_word: english_words) {
            hashMap.put(english_word, english_word);
        }
    }

public:
    std::string getName() override {
        return "Hash Map";
    }

    int spellCheck(std::string filename) override {
        int wrongSpelledWords = 0;
        buildDictionary();
        std::vector<std::string> text_vector = textFileToVector(filename);

        for (const auto & word: text_vector)
        {
            if (!hashMap.contains(word))
            {
                ++wrongSpelledWords;
            }
        }

        std::cout << getName() << ": " << wrongSpelledWords << std::endl;

        return wrongSpelledWords;
    }

    ~HashMapSpellCheckingAlgorithm() override = default;
};


class MeSpellRite {
public:
    static void test() {
        TextBuilder::buildText();

        std::cout << "------ Me Spell Rite ------" << std::endl << std::endl;

        std::vector<SpellCheckingAlgorithm *> spellCheckers = {new NaiveSpellCheckingAlgorithm(),
                                                               new BBSTSpellCheckingAlgorithm(),
                                                               new TrieSpellCheckingAlgorithm(),
                                                               new HashMapSpellCheckingAlgorithm()};
        for (const auto &spellChecker: spellCheckers) {
            spellChecker->spellCheck(TextBuilder::get_output_file_name());
        }

        std::cout << std::endl;
    }
};

#endif //ADVANCED_ALGORITHMS_ASSIGNMENT2_MESPELLRITE_H
