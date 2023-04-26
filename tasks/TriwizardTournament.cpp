#include "TriwizardTournament.h"
#include <iostream>
#include <deque>
#include <limits>
#include <fstream>
#include <unordered_map>
#include <iomanip>


std::tuple<int, float>
TriwizardTournament::find_fastest_wizard(const std::vector<std::vector<LabyrinthObject>> &labyrinth, const std::vector<Wizard> &wizards) {
    // Assume labyrinth is a rectangle
    int height = labyrinth.size();
    if (height == 0) {
        throw std::logic_error("Labyrinth must have at least one-line height.");
    }
    int width = labyrinth[0].size();
    if (width == 0) {
        throw std::logic_error("Labyrinth must have at least one-column width.");
    }

    // Set exit at right bottom corner
    int exit_y = height - 1;
    int exit_x = width - 1;

    // position, path length wizard id, wizard speed
    std::deque<std::tuple<std::pair<int, int>, int, int, int>> bfs_deque;
    // id -> (path, speed)
    std::unordered_map<int, std::pair<int, int>> shortest_paths;

    for (const auto &wizard: wizards) {
        bfs_deque.emplace_back(wizard.initial_position, 0, wizard.id, wizard.speed);
    }

    std::vector<std::pair<int, int>> adjacent_cell_deltas{{1,  0},
                                                          {-1, 0},
                                                          {0,  1},
                                                          {0,  -1}};

    while (!bfs_deque.empty()) {
        // first - y, second - x
        std::pair<int, int> position;
        int path_length;
        int id;
        int speed;
        std::tie(position, path_length, id, speed) = bfs_deque.front();
        bfs_deque.pop_front();

        if (position.first == exit_y && position.second == exit_x) {
            if (shortest_paths.find(id) == shortest_paths.end() || path_length < shortest_paths[id].first) {
                shortest_paths[id] = {path_length, speed};
            }

            if (shortest_paths.size() == wizards.size()) {
                break;
            }

            continue;
        }

        for (const std::pair<int, int> &delta: adjacent_cell_deltas) {
            int adjacent_y = position.first + delta.first;
            int adjacent_x = position.second + delta.second;
            if (0 <= adjacent_y && adjacent_y < height && 0 <= adjacent_x && adjacent_x < width && labyrinth[adjacent_y][adjacent_x] == Path) {
                bfs_deque.push_back({{adjacent_y, adjacent_x}, path_length + 1, id, speed});
            }
        }
    }

    float min_path = std::numeric_limits<float>::max();
    int min_path_wizard_id = -1;
    for (const auto &shortest_path: shortest_paths) {
        int path_length;
        int speed;
        std::tie(path_length, speed) = shortest_path.second;
        float scaled_shortest_path = (float) path_length / speed;
        if (scaled_shortest_path < min_path) {
            min_path_wizard_id = shortest_path.first;
            min_path = scaled_shortest_path;
        }
    }

    return {min_path_wizard_id, min_path};
}

std::vector<std::vector<TriwizardTournament::LabyrinthObject>> TriwizardTournament::get_labyrinth_from_file(std::string file_name) {
    std::vector<std::vector<LabyrinthObject>> labyrinth;

    std::string line;
    std::ifstream labyrinth_file("labyrinth.txt");

    while (std::getline(labyrinth_file, line)) {
        std::vector<LabyrinthObject> row;
        for (const auto &c: line) {
            if (c == '#') {
                row.push_back(Wall);
            } else {
                row.push_back(Path);
            }
        }
        labyrinth.push_back(row);
    }

    return labyrinth;
}

std::vector<std::vector<TriwizardTournament::LabyrinthObject>>
TriwizardTournament::get_labyrinth_from_char_matrix(std::vector<std::vector<char>> labyrinth_as_char_matrix) {
    std::vector<std::vector<LabyrinthObject>> labyrinth;

    for (const auto &row: labyrinth_as_char_matrix) {
        std::vector<LabyrinthObject> mapped_row;
        for (const auto &c: row) {
            if (c == '#') {
                mapped_row.push_back(Wall);
            } else {
                mapped_row.push_back(Path);
            }
        }
        labyrinth.push_back(mapped_row);
    }

    return labyrinth;
}


void TriwizardTournament::test() {
    std::cout << "------ Triwizard Tournament ------" << std::endl << std::endl;

//    std::vector<std::vector<LabyrinthObject>> labyrinth = get_labyrinth_from_file("labyrinth.txt");
    std::vector<std::vector<LabyrinthObject>> labyrinth = get_labyrinth_from_char_matrix({
                                                                                                 {' ', ' ', '#', ' ', ' ', '#',},
                                                                                                 {'#', ' ', ' ', ' ', ' ', ' ',},
                                                                                                 {'#', '#', ' ', ' ', '#', ' ',},
                                                                                                 {' ', ' ', ' ', '#', ' ', ' ',},
                                                                                                 {' ', '#', ' ', ' ', ' ', ' ',},
                                                                                                 {' ', ' ', ' ', '#', ' ', ' ',},
                                                                                                 {'#', '#', ' ', ' ', ' ', ' ',},
                                                                                                 {' ', ' ', ' ', ' ', '#', ' ',},
                                                                                         });

    for (const auto &row: labyrinth) {
        for (const auto &cell: row) {
            if (cell == Wall) {
                std::cout << "#";
            } else if (cell == Path) {
                std::cout << "_";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    std::vector<Wizard> wizards{
            Wizard(1, {0, 0}, 1),
            Wizard(2, {0, 1}, 2),
            Wizard(3, {5, 2}, 1),
    };

    for (const auto &wizard: wizards) {
        std::cout << "[" << wizard.id << "] starts from (y = " << wizard.initial_position.first << ", x = " << wizard.initial_position.second << ") with speed "
                  << wizard.speed << std::endl;
    }

    std::cout << std::endl;

    int fastest_wizard_id;
    float fastest_wizard_path;
    std::tie(fastest_wizard_id, fastest_wizard_path) = find_fastest_wizard(labyrinth, wizards);

    std::cout << "The fastest wizard is [" << fastest_wizard_id << "] whose path is " << std::fixed << std::setprecision(2) << fastest_wizard_path << std::endl
              << std::endl;
}
