#include <iostream>
#include <vector>
#include <string>
using namespace std;

const char PATH = 'H';
const char BLOCK = 'B';

struct Path {
    vector<pair<int, int>> steps;
    bool reachedExit;
};

bool isValidMove(int x, int y, const vector<string>& maze, const vector<vector<bool>>& visited) {
    int rows = maze.size();
    int cols = maze[0].size();
    return x >= 0 && y >= 0 && x < rows && y < cols &&
           maze[x][y] == PATH && !visited[x][y];
}

void dfs(int x, int y, const vector<string>& maze, vector<vector<bool>>& visited,
         vector<Path>& allPaths, Path currentPath) {
    visited[x][y] = true;
    currentPath.steps.push_back({x, y});

    if (x == maze.size() - 1) {
        currentPath.reachedExit = true;
        allPaths.push_back(currentPath);
    } else {
        const int dx[] = {-1, 1, 0, 0};
        const int dy[] = {0, 0, -1, 1};

        for (int i = 0; i < 4; ++i) {
            int newX = x + dx[i];
            int newY = y + dy[i];

            if (isValidMove(newX, newY, maze, visited)) {
                dfs(newX, newY, maze, visited, allPaths, currentPath);
            }
        }
    }

    visited[x][y] = false; // backtrack
}

vector<Path> findAllPaths(const vector<string>& maze) {
    vector<Path> allPaths;

    if (maze.empty()) return allPaths;  // ADDED SAFETY CHECK

    int rows = maze.size();
    int cols = maze[0].size();
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));

    for (int col = 0; col < cols; ++col) {
        if (maze[0][col] == PATH) {
            Path newPath;
            dfs(0, col, maze, visited, allPaths, newPath);
        }
    }

    return allPaths;
}

void displayPaths(const vector<Path>& paths) {
    cout << "<h3>Total paths to exit: " << paths.size() << "</h3>";
    int count = 1;
    for (const Path& path : paths) {
        cout << "<p><strong>Path " << count++ << ":</strong> ";
        for (auto step : path.steps) {
            cout << "(" << step.first << "," << step.second << ") ";
        }
        cout << "</p>" << endl;
    }
}
