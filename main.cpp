#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include "function.h" // Your other logic goes here

using namespace std;

vector<string> getAndValidateMazeInput(const string& mazeFilePath); // As before

int main() {
    cout << "Content-type: text/html\n\n";
    cout << "<html><head><title>Maze Upload</title></head><body>";

    // Get content length (from POST header)
    char* clen = getenv("CONTENT_LENGTH");
    if (!clen) {
        cout << "<p>Error: No content length provided.</p></body></html>";
        return 1;
    }

    int length = atoi(clen);
    string postData;
    postData.resize(length);

    // Read POST data from stdin
    cin.read(&postData[0], length);

    // Extract the actual file content (simplified, assumes only one file field)
    size_t fileStart = postData.find("\r\n\r\n");
    if (fileStart == string::npos) {
        cout << "<p>Error: Invalid POST format.</p></body></html>";
        return 1;
    }

    fileStart += 4; // skip over \r\n\r\n
    size_t fileEnd = postData.find("\r\n------", fileStart); // boundary after file
    if (fileEnd == string::npos) {
        cout << "<p>Error: Could not find end of file data.</p></body></html>";
        return 1;
    }

    string fileContent = postData.substr(fileStart, fileEnd - fileStart);

    // Save to a file
    string filePath = "/tmp/maze.txt";
    ofstream outFile(filePath);
    if (!outFile.is_open()) {
        cout << "<p>Error: Could not save uploaded file.</p></body></html>";
        return 1;
    }

    outFile << fileContent;
    outFile.close();

    // Now validate and process the maze file
    vector<string> maze = getAndValidateMazeInput(filePath);
    if (maze.empty()) {
        cout << "<p>Maze input validation failed.</p></body></html>";
        return 1;
    }

    vector<Path> paths = findAllPaths(maze);
    displayPaths(paths);

    cout << "</body></html>";
    return 0;
}
