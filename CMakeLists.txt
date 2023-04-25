cmake_minimum_required(VERSION 3.25)
project(advanced_algorithms_assignment2)

set(CMAKE_CXX_STANDARD 14)

add_executable(advanced_algorithms_assignment2
        main.cpp
        AuntsNamesday.cpp MeSpellRite.h)

file(GLOB files "static_assets/*.txt")
foreach(file ${files})
    configure_file(${file}
            ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
endforeach()
