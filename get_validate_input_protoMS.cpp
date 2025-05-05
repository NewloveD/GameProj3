#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm> // for std::remove_if
#include <limits>    // for std::numeric_limits

using namespace std;

vector<string> getAndValidateMazeInput(const string& mazeFilePath) {
    ifstream file(mazeFilePath);
    cout << "<p>Trying to open file: " << mazeFilePath << "</p>" << endl;

    vector<string> maze;

    if (!file.is_open()) {
        cout << "<p>Error: Could not open maze file: " << mazeFilePath << "</p></body></html>";
        return maze;
    }

    int rows, cols;
    file >> rows >> cols;
    file.ignore(numeric_limits<streamsize>::max(), '\n');  // Safely skip to next line

    string line;
    for (int i = 0; i < rows; ++i) {
        getline(file, line);

        // Remove whitespace
        line.erase(remove_if(line.begin(), line.end(), ::isspace), line.end());

        // Validate length
        if (line.length() != static_cast<size_t>(cols)) {
            cout << "<p>Error: Incorrect number of columns in row " << i + 1 << "</p>" << endl;
            maze.clear();
            return maze;
        }

        // Validate characters
        for (char ch : line) {
            if (ch != 'H' && ch != 'B') {
                cout << "<p>Error: Invalid character '" << ch << "' in row " << i + 1 << "</p>" << endl;
                maze.clear();
                return maze;
            }
        }

        maze.push_back(line);
    }

    file.close();

    // Display the maze visually on the webpage with style
    cout << "<h3>Maze:</h3>";
    for (const string& row : maze) {
        cout << "<p>";
        for (char ch : row) {
            if (ch == 'H') {
                cout << "<strong>" << ch << "</strong> ";  // Make 'H' bold
            } else if (ch == 'B') {
                cout << "<span style='color:darkgreen;'>" << ch << "</span> ";  // 'B' in dark green
            }
        }
        cout << "</p>";
    }

    cout << "<p>Maze file '" << mazeFilePath << "' successfully validated!</p>" << endl;
    return maze;
}
