cmake_minimum_required(VERSION 3.25)
project(advanced_algorithms_assignment2)

set(CMAKE_CXX_STANDARD 14)

add_executable(advanced_algorithms_assignment2
        main.cpp
        common/TextBuilder.cpp
        common/SeparateChainingHashMap.cpp
        common/LinearProbingHashMap.cpp
        common/DoubleHashingHashMap.cpp
        me_spell_rite/SpellCheckingAlgorithm.cpp
        me_spell_rite/NaiveSpellCheckingAlgorithm.cpp
        me_spell_rite/BBSTSpellCheckingAlgorithm.cpp
        me_spell_rite/TrieSpellCheckingAlgorithm.cpp
        me_spell_rite/HashMapSpellCheckingAlgorithm.cpp
        AuntsNamesday.cpp
        TriwizardTournament.cpp
        FullHouse.cpp)

target_include_directories(advanced_algorithms_assignment2 PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB files "static_assets/*.txt")
foreach (file ${files})
    configure_file(${file}
            ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
endforeach ()