#include "SpellCheckingAlgorithm.h"


SpellCheckingAlgorithm::SpellCheckingAlgorithm(int dict_size) : _dict_size(dict_size) {

}


std::vector<std::string> SpellCheckingAlgorithm::read_words(const std::string &filename) {
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