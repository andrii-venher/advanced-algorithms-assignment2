cmake_minimum_required(VERSION 3.25)
project(advanced_algorithms_assignment2)

set(CMAKE_CXX_STANDARD 14)

add_executable(advanced_algorithms_assignment2
        main.cpp
        common/TextBuilder.cpp
        hash_map/SeparateChainingHashMap.cpp
        hash_map/LinearProbingHashMap.cpp
        hash_map/DoubleHashingHashMap.cpp
        spell_checking/SpellCheckingAlgorithm.cpp
        spell_checking/NaiveSpellCheckingAlgorithm.cpp
        spell_checking/BBSTSpellCheckingAlgorithm.cpp
        spell_checking/TrieSpellCheckingAlgorithm.cpp
        spell_checking/HashMapSpellCheckingAlgorithm.cpp
        tasks/MeSpellRite.cpp
        tasks/TriwizardTournament.cpp
        tasks/AuntsNamesday.cpp
        tasks/FullHouse.cpp)

target_include_directories(advanced_algorithms_assignment2 PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB files "static_assets/*.txt")
foreach (file ${files})
    configure_file(${file}
            ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
endforeach ()