#include "AuntsNamesday.h"
#include <iostream>
#include <stdexcept>
#include <unordered_map>
#include <algorithm>

void dfs(const std::string &current_guest,
         std::unordered_map<std::string, std::vector<std::string>> &graph, std::unordered_map<std::string, int> &tables,
         std::unordered_map<std::string, bool> &visited) {
    visited[current_guest] = true;
    for (const auto &disliked_guest: graph[current_guest]) {
        if (!visited[disliked_guest]) {
            tables[disliked_guest] = (1 - tables[current_guest]);
            dfs(disliked_guest, graph, tables, visited);
        }
    }
}

std::tuple<std::vector<std::string>, std::vector<std::string>>
AuntsNamesday::arrange_guests(const std::vector<std::string> &guests, const std::vector<std::tuple<std::string, std::string>> &dislikes) {
    if (guests.empty()) {
        return {};
    }

    // Map guests to their lists of disliked people
    std::unordered_map<std::string, std::vector<std::string>> graph;

    // Initialize every guest with an empty list
    for (const auto &guest: guests) {
        graph[guest] = std::vector<std::string>();
    }

    // For every pair of people that dislike each other, add each one to the other's list
    for (const auto &dislike: dislikes) {
        std::string person1;
        std::string person2;
        std::tie(person1, person2) = dislike;
        if (graph.find(person1) == graph.end() || graph.find(person2) == graph.end()) {
            std::string error_message = "Both people from a dislike pair must be present on the guest list which is not true for the pair { ";
            error_message.append(person1);
            error_message.append(", ");
            error_message.append(person2);
            error_message.append(" }.");
            throw std::logic_error(error_message);
        }
        auto &person1_list = graph[person1];
        if (std::find(person1_list.begin(), person1_list.end(), person2) == person1_list.end()) {
            person1_list.push_back(person2);
        }
        auto &person2_list = graph[person2];
        if (std::find(person2_list.begin(), person2_list.end(), person1) == person2_list.end()) {
            person2_list.push_back(person1);
        }
    }

    // Maps guests to the tables
    // 0 - guest sits at the first table
    // 1 - guest sits at the second table
    std::unordered_map<std::string, int> tables;

    std::unordered_map<std::string, bool> visited;

    for (const auto &guest: guests) {
        // Assign all guests to the first table by default
        tables[guest] = 0;
        visited[guest] = false;
    }

    for (const auto &guest: guests) {
        if (!visited[guest]) {
            dfs(guest, graph, tables, visited);
        }
    }

    std::vector<std::string> table1;
    std::vector<std::string> table2;

    for (const auto &table_assignment: tables) {
        std::string guest;
        int table;
        std::tie(guest, table) = table_assignment;
        if (table == 0) {
            table1.push_back(guest);
        } else if (table == 1) {
            table2.push_back(guest);
        }
    }

    return {table1, table2};
}

void AuntsNamesday::test() {
    std::cout << "------ Aunt's Namesday ------" << std::endl << std::endl;

    std::vector<std::string> guests({"Alice", "Bob", "Charlie", "Dave", "Eve"});
    std::vector<std::tuple<std::string, std::string>> dislikes({
                                                                       {"Alice", "Charlie"},
                                                                       {"Bob",   "Dave"},
                                                                       {"Eve",   "Bob"},
                                                                       {"Alice", "Bob"},
                                                               });

    std::vector<std::string> table1;
    std::vector<std::string> table2;

    try {
        std::tie(table1, table2) = arrange_guests(guests, dislikes);
    }
    catch (std::logic_error &e) {
        std::cout << "Exception thrown: " << e.what() << std::endl;
        return;
    }

    std::cout << "------ Table 1 ------" << std::endl;
    for (const auto &guest: table1) {
        std::cout << guest << std::endl;
    }
    std::cout << std::endl;

    std::cout << "------ Table 2 ------" << std::endl;
    for (const auto &guest: table2) {
        std::cout << guest << std::endl;
    }
    std::cout << std::endl;
}
