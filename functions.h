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
void displayCityMap(int row, int col, int rowstart, int colstart);
void deleteCityMemory(int row, int col);

//Cloud functions
void createCloudMap(string cloudFile, int row, int col);
void displayCloudMap(int row, int col, int rowstart, int colstart, int choiceNo);
void deleteCloudMemory(int row, int col);

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
            // Trim the line and add non-empty lines
            line = trim(line);
			lines.push_back(line);

        }
        inputFile.close();
    } else {
        cerr << "Failed to open the file for reading." << endl;
        return;
    }

	//Remove trailing empty lines from the vector
	while (!lines.empty() && lines.back().empty()) {
		lines.pop_back();
	}

    // Rewrite the file with cleaned lines
    ofstream outputFile(filename, ios::trunc);
    if (outputFile.is_open()) {
        for (size_t i=0; i < lines.size(); ++i) {
			//Avoid adding an extra newline at the end of the file
			outputFile << lines[i];
			if (i < lines.size() - 1){
				outputFile << endl;
			}
		}
        outputFile.close();
    } else {
        cerr << "Failed to open the" << filename << "file for writing." << endl;
    }
}

//Read the last line of a .txt file assuming there is no new line spaces at the end
inline string readLastLine(const string& filename) {
    ifstream file(filename, ios::in);
    if (!file.is_open()) {
        throw runtime_error("Could not open file");
    }

    file.seekg(0, ios::end); // Move to the end of the file

    auto fileSize = file.tellg();
    if (fileSize == 0) { // Check if the file is empty
        return ""; // Return empty string for empty file
    }

    // Move backward to find the start of the last line
    char ch;
    long long pos = static_cast<long long>(fileSize) - 1; // Explicit cast to signed type
    while (pos >= 0) {
        file.seekg(pos);
        file.get(ch);

        if (ch == '\n' && pos != static_cast<long long>(fileSize) - 1) {
            break; // Found the beginning of the last line
        }
        pos--;
    }

    // Read the last line
    string lastLine;
    getline(file, lastLine);

    return lastLine;
}

inline int sortIndex(int sortNo)
{
	if(sortNo < 10)
	{
		return 0;
	}
	else if(sortNo < 20)
	{
		return 1;
	}
	else if(sortNo < 30)
	{
		return 2;
	}
	else if(sortNo < 40)
	{
		return 3;
	}
	else if(sortNo < 50)
	{
		return 4;
	}
	else if(sortNo < 60)
	{
		return 5;
	}
	else if(sortNo < 70)
	{
		return 6;
	}
	else if(sortNo < 80)
	{
		return 7;
	}
	else if(sortNo < 90)
	{
		return 8;
	}
	else if(sortNo < 100)
	{
		return 9;
	}
	else if(sortNo < 0)
	{
		cout << "Invalid number found";
		return(0);
	}
	else
	{
		cout << "Invalid number found";
		return(0);
	}
}

inline string sortLMH(int sortNo)
{
	if(sortNo < 35)
	{
		return "L";
	}
	else if(sortNo< 65)
	{
		return "M";
	}
	else if(sortNo < 100)
	{
		return "H";
	}
	else
	{
		cout << "Invalid number found";
		return(0);
	}
}

#endif