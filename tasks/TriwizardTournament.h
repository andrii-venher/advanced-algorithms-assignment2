#ifndef ADVANCED_ALGORITHMS_ASSIGNMENT2_TRIWIZARDTOURNAMENT_H
#define ADVANCED_ALGORITHMS_ASSIGNMENT2_TRIWIZARDTOURNAMENT_H

#include <utility>
#include <vector>
#include <string>

class TriwizardTournament {
    enum LabyrinthObject {
        Path, Wall
    };

    struct Wizard {
        std::string id;
        // first - y, second - x
        std::pair<int, int> initial_position = {};
        int speed = 0;

        Wizard(std::string id, std::pair<int, int> initial_position, int speed) : id(std::move(id)), initial_position(std::move(initial_position)), speed(speed) {}
    };

    static std::tuple<std::string, float> find_fastest_wizard(const std::vector<std::vector<LabyrinthObject>> &labyrinth, const std::vector<Wizard> &wizards);

    static std::vector<std::vector<LabyrinthObject>> get_labyrinth_from_file(const std::string& file_name);

    static std::vector<std::vector<LabyrinthObject>> get_labyrinth_from_char_matrix(const std::vector<std::vector<char>>& labyrinth_as_char_matrix);

public:
    static void test();
};


#endif //ADVANCED_ALGORITHMS_ASSIGNMENT2_TRIWIZARDTOURNAMENT_H
