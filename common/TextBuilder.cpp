#include "TextBuilder.h"
#include <iostream>

std::string TextBuilder::input_file_name = "english_words.txt";
std::string TextBuilder::sample_file_name = "text.txt";
std::vector<std::string> TextBuilder::dictionary = {};

std::vector<std::string> TextBuilder::read_words_from_english_dictionary(int dict_size) {
    if (dict_size > max_dict_size()) {
        dict_size = max_dict_size();
    }

    if (dict_size == 0) {
        return {};
    }

    return {dictionary.begin(), dictionary.begin() + dict_size};;
}

void TextBuilder::sample_english_dictionary_with_errors(int dict_size, int sample_size) {
    std::vector<std::string> english_words = read_words_from_english_dictionary(dict_size);

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist_word(0, english_words.size() - 1);
    std::uniform_int_distribution<std::mt19937::result_type> dist_spelling(1, 100);

    std::string text;
    std::ofstream file_out;
    file_out.open(get_sample_file_name());

    for (int i = 0; i < sample_size; ++i) {
        if (dist_spelling(rng) <= 75) {
            //spelt right 75% chance
            file_out << english_words[dist_word(rng)] << '\n';
        } else {
            //spelt wrong (extra z in the end) 25% chance
            file_out << english_words[dist_word(rng)] << "z\n";
        }
    }
}

void TextBuilder::init() {
    std::string tmp;
    std::ifstream file_in;
    std::vector<std::string> english_words;
    file_in.open(input_file_name);

    while (getline(file_in, tmp)) {
        dictionary.push_back(tmp);
    }

    file_in.close();
    std::cout << "TextBuilder initialized." << std::endl;
}
