#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

// A structure to hold the input data temporarily
struct StateData {
    string state;
    vector<string> fields;
};

// Function declarations
bool validateUploadedFiles(const string& dataFilePath, const string& stateFilePath);
vector<StateData> parseCSV(const string& filePath, int expectedColumns);
void printValidationResult(bool isValid);

// Main validation function
vector<StateData> getAndValidateInput(const string& dataFilePath, const string& stateFilePath) {
    vector<StateData> validatedData;

    bool filesValid = validateUploadedFiles(dataFilePath, stateFilePath);
    printValidationResult(filesValid);

    if (!filesValid) {
        cerr << "Error: Uploaded files are invalid." << endl;
        return validatedData; // return empty
    }

    // Assume data file expects at least 4 columns: state + 3 fields
    validatedData = parseCSV(dataFilePath, 4);
    vector<StateData> validatedStates = parseCSV(stateFilePath, 2); // state file has 2 columns

    if (validatedData.empty() || validatedStates.empty()) {
        cerr << "Error: Failed to parse input files correctly." << endl;
    }

    return validatedData;
}

// Validate the existence and basic size of the files
bool validateUploadedFiles(const string& dataFilePath, const string& stateFilePath) {
    ifstream dataFile(dataFilePath);
    ifstream stateFile(stateFilePath);

    if (!dataFile.is_open() || !stateFile.is_open()) {
        return false;
    }

    // Check if files are not empty
    dataFile.seekg(0, ios::end);
    stateFile.seekg(0, ios::end);
    if (dataFile.tellg() == 0 || stateFile.tellg() == 0) {
        return false;
    }

    dataFile.close();
    stateFile.close();
    return true;
}

// Parse CSV and store data
vector<StateData> parseCSV(const string& filePath, int expectedColumns) {
    ifstream file(filePath);
    vector<StateData> data;
    string line;

    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filePath << endl;
        return data;
    }

    while (getline(file, line)) {
        stringstream ss(line);
        string item;
        vector<string> tokens;

        while (getline(ss, item, ',')) {
            tokens.push_back(item);
        }

        if (tokens.size() < expectedColumns) {
            cerr << "Error: Invalid column count in line: " << line << endl;
            continue; // skip invalid rows
        }

        StateData entry;
        entry.state = tokens[0];
        for (size_t i = 1; i < tokens.size(); ++i) {
            entry.fields.push_back(tokens[i]);
        }
        data.push_back(entry);
    }

    file.close();
    return data;
}

// Print the validation result
void printValidationResult(bool isValid) {
    if (isValid) {
        cout << "Content-type: text/html\n\n";
        cout << "<p>File upload and basic validation successful!</p>" << endl;
    } else {
        cout << "Content-type: text/html\n\n";
        cout << "<p>File upload or validation failed. Please try again.</p>" << endl;
    }
}