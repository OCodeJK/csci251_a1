#ifndef FUNCTIONS_H
#define FUNCTIONS_H

using namespace std;

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

//tokenizer function for strings
vector<string> tokenizeString(string input, string delimiter);

//City functions
void createCityMap(string cityFile, int row, int col);
void displayCityMap(int row, int col);
void deleteCityMemory(int row, int col);

// Function to trim leading and trailing whitespace from a string
inline string trim(const string& str) {
    auto start = str.find_first_not_of(" \t\r\n");
    auto end = str.find_last_not_of(" \t\r\n");
    return (start == string::npos) ? "" : str.substr(start, end - start + 1);
}

// Function to remove trailing empty lines and blank spaces in a file
inline void cleanFile(const string& filename) {
    ifstream inputFile(filename);
    vector<string> lines; // To store non-empty lines
    string line;

    if (inputFile.is_open()) {
        // Read the file line by line
        while (getline(inputFile, line)) {
            // Trim the line
            line = trim(line);

            // Add non-empty lines to the list
            if (!line.empty()) {
                lines.push_back(line);
            }
        }
        inputFile.close();
    } else {
        cerr << "Failed to open the file for reading." << endl;
        return;
    }

    // Rewrite the file with cleaned lines
    ofstream outputFile(filename, ios::trunc);
    if (outputFile.is_open()) {
        for (const auto& cleanedLine : lines) {
            outputFile << cleanedLine << endl;
        }
        outputFile.close();
        cout << "File cleaned successfully." << endl;
    } else {
        cerr << "Failed to open the file for writing." << endl;
    }
}

#endif