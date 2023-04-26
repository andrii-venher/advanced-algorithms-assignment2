#ifndef ADVANCED_ALGORITHMS_ASSIGNMENT2_AUNTSNAMESDAY_H
#define ADVANCED_ALGORITHMS_ASSIGNMENT2_AUNTSNAMESDAY_H

#include <vector>
#include <string>
#include <map>

class AuntsNamesday {
    static std::tuple<std::vector<std::string>, std::vector<std::string>>
    arrange_guests(const std::vector<std::string> &guests, const std::vector<std::tuple<std::string, std::string>> &dislikes);

public:
    static void test();
};


#endif //ADVANCED_ALGORITHMS_ASSIGNMENT2_AUNTSNAMESDAY_H
