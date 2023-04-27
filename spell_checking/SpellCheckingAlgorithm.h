#ifndef ADVANCED_ALGORITHMS_ASSIGNMENT2_SPELLCHECKINGALGORITHM_H
#define ADVANCED_ALGORITHMS_ASSIGNMENT2_SPELLCHECKINGALGORITHM_H

#include "hash_map/HashMap.h"
#include <fstream>
#include <string>
#include <utility>
#include <vector>
#include <random>
#include <iostream>
#include <set>

class SpellCheckingAlgorithm {
protected:
    static std::vector<std::string> read_words(const std::string &filename);

    int _dict_size;
public:
    explicit SpellCheckingAlgorithm(int dict_size);

    virtual ~SpellCheckingAlgorithm() = default;

    virtual int spellCheck(std::string filename) = 0;

    virtual std::string getName() = 0;
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

    void buildDictionary();

public:
    explicit NaiveSpellCheckingAlgorithm(int dict_size);

    std::string getName() override;

    int spellCheck(std::string filename) override;

    ~NaiveSpellCheckingAlgorithm() override;
};

class BBSTSpellCheckingAlgorithm : public SpellCheckingAlgorithm {
private:
    std::set<std::string, std::greater<>> buildDictionary();

public:
    explicit BBSTSpellCheckingAlgorithm(int dict_size);

    ~BBSTSpellCheckingAlgorithm() override = default;

    int spellCheck(std::string filename) override;

    std::string getName() override;
};

class TrieSpellCheckingAlgorithm : public SpellCheckingAlgorithm {
private:
    struct TrieNode {
        struct TrieNode *children[27] = {};
        bool isEndOfWord = false;

        TrieNode() {
            for (auto &child: children) {
                child = nullptr;
            }
        }
    };

    TrieNode *root = new TrieNode();

    void buildDictionary();

    void clear(TrieNode *node);

public:
    explicit TrieSpellCheckingAlgorithm(int dict_size);

    ~TrieSpellCheckingAlgorithm() override;

    int spellCheck(std::string filename) override;

    std::string getName() override;
};

class HashMapSpellCheckingAlgorithm : public SpellCheckingAlgorithm {
private:
    HashMap* _hashMap;

    void buildDictionary();

public:
    explicit HashMapSpellCheckingAlgorithm(int dict_size);

    ~HashMapSpellCheckingAlgorithm() override;

    int spellCheck(std::string filename) override;

    std::string getName() override;
};

#endif //ADVANCED_ALGORITHMS_ASSIGNMENT2_SPELLCHECKINGALGORITHM_H
