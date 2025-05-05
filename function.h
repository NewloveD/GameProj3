// Function.h
#ifndef FUNCTION_H
#define FUNCTION_H

#include <vector>
#include <string>
#include <utility>

struct Path {
    std::vector<std::pair<int, int>> steps;
    bool reachedExit;
};

// Declared in function.cpp
std::vector<Path> findAllPaths(const std::vector<std::string>& maze);
void displayPaths(const std::vector<Path>& paths);

#endif
