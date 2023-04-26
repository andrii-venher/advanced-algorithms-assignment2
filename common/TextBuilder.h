#ifndef ADVANCED_ALGORITHMS_ASSIGNMENT2_TEXTBUILDER_H
#define ADVANCED_ALGORITHMS_ASSIGNMENT2_TEXTBUILDER_H

#include <vector>
#include <string>
#include <fstream>
#include <random>

class TextBuilder {
    static std::string input_file_name;
    static std::string sample_file_name;
    static std::vector<std::string> dictionary;
public:
    static void init();

    static std::vector<std::string> read_words_from_english_dictionary(int dict_size);

    static void sample_english_dictionary_with_errors(int dict_size, int sample_size);

    static std::string get_sample_file_name() { return sample_file_name; }

    static int max_dict_size() { return dictionary.size(); }
};


#endif //ADVANCED_ALGORITHMS_ASSIGNMENT2_TEXTBUILDER_H
