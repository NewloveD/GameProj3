#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

vector<string> getAndValidateMazeInput(const string& mazeFilePath) {
    ifstream file(mazeFilePath);
    vector<string> maze;

    if (!file.is_open()) {
        cerr << "Error: Could not open maze file." << endl;
        return maze;
    }

    int rows, cols;
    file >> rows >> cols;
    file.ignore();

    string line;
    for (int i = 0; i < rows; ++i) {
        getline(file, line);
        stringstream ss(line);
        string token;
        string row = "";
        int tokenCount = 0;

        while (ss >> token) {
            if (token != "H" && token != "B") {
                cerr << "Error: Invalid character '" << token << "' in maze." << endl;
                maze.clear();
                return maze;
            }
            row += token;
            ++tokenCount;
        }

        if (tokenCount != cols) {
            cerr << "Error: Incorrect number of columns in row " << i + 1 << endl;
            maze.clear();
            return maze;
        }

        maze.push_back(row);
    }

    file.close();

    cout << "Content-type: text/html\n\n";
    cout << "<p>Maze file successfully validated!</p>" << endl;

    return maze;
}
