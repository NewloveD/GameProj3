#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include "function.h" // Declares findAllPaths and displayPaths
using namespace std;

// Declare prototype (since there's no header for it yet)
vector<string> getAndValidateMazeInput(const string& mazeFilePath);

int main() {
    // CGI output header
    cout << "Content-type: text/html\n\n";
    cout << "<html><head><title>Maze Game Results</title></head><body>";

    // Step 1: Get the filename from environment variable (you may adjust if using POST)
    char* qs = getenv("QUERY_STRING");
    if (!qs) {
        cout << "<p>Error: No input file specified.</p></body></html>";
        return 1;
    }

    // Expected format: file=maze.txt
    string query = qs;
    size_t pos = query.find("file=");
    if (pos == string::npos) {
        cout << "<p>Error: Invalid query string format.</p></body></html>";
        return 1;
    }

    string filename = query.substr(pos + 5); // Extract filename after 'file='

    // Step 2: Load and validate the maze
    vector<string> maze = getAndValidateMazeInput(filename);
    if (maze.empty()) {
        cout << "<p>Maze input validation failed.</p></body></html>";
        return 1;
    }

    // Step 3: Process the maze to find all valid paths
    vector<Path> paths = findAllPaths(maze);

    // Step 4: Display the paths
    displayPaths(paths);

    cout << "</body></html>";
    return 0;
}
