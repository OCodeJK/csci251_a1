#ifndef pressureFunction_cpp
#define pressureFunction_cpp
#include "functions.h"
#include "structs.h"


using namespace std;


// initialize the array structure and map
pressureStruct * pressureArray;
string ** pressureMap = nullptr;

void createPressureMap(string pressureFile, int row, int col)
{
    cleanFile(pressureFile);
    ifstream pressureData(pressureFile);
    string line;

    // Variable to initialize the array dynamically later
    int totalLength = 0;
    int lineNumber = 0;

    // Correctly create the 2D array for pressureMap with row and col
    pressureMap = new string* [row];
    for (int i = 0; i < row; i++)  // Ensure row is used here
    {
        pressureMap[i] = new string[col];  // Ensure col is used here
    }

    if (pressureData.is_open()) {
        while (getline(pressureData, line)) {
            if (!line.empty()) {
                totalLength++;
            }
        }
        pressureData.close();

        // Re-open the file and populate the pressure data
        ifstream pressureData(pressureFile);
        pressureArray = new pressureStruct[totalLength];

        while (getline(pressureData, line)) {
            vector<string> pressureDataSplit = tokenizeString(line, "-"); //Split [n,n]   pressureIndex
            vector<string> pressureCoordsSplit = tokenizeString(pressureDataSplit[0], ","); //Split [n     n]
            
            // Remove brackets and spaces from coordinates
            pressureCoordsSplit[0].erase(pressureCoordsSplit[0].begin());  // Remove '['
            pressureCoordsSplit[1].erase(pressureCoordsSplit[1].end()-1);  // Remove ']'

            pressureArray[lineNumber].x = stoi(pressureCoordsSplit[0]); //parse info into array
            pressureArray[lineNumber].y = stoi(pressureCoordsSplit[1]);
            pressureArray[lineNumber].pressureLvl = stoi(pressureDataSplit[1]);
            lineNumber++;
        }

        // Populate pressureMap with pressure levels
        for (int k = 0; k < totalLength; k++) {
            ostringstream oss;
            oss << pressureArray[k].pressureLvl;
            // Adjust the index logic for proper placement in the map
            pressureMap[row - 1 - pressureArray[k].y][pressureArray[k].x] = oss.str();
        }


    } else {
        cout << "Error: Unable to open this file: " << pressureFile << endl;
    }
}


// function to display the map of pressure level depending on how the user wants it in.
void displayPressureMap(int row, int col, int rowstart, int colstart, int choice)
{
	//Top border of the grid
	cout << "  #";
	for (int i=0;i<col;i++)
	{
		cout << " " << "#";
	}
	cout << " #" << endl;

	//Draw the rows of the grid
	for (int i=colstart; i<row; i++)
	{	
		//Row number on the left side (in reverse order)
		cout << (row - i - 1 + colstart) << " #" ;	

		//
		for (int j=0;j<col;j++)
		{	
			// Display the map in index form (option 3 selected)
			if (choice == 5)
			{
				if (pressureMap[i][j] == ""){
					cout << " " << "?";
				} else {
					cout << " " << sortIndex(stoi(pressureMap[i][j]));
				}
				
			}
			// Display the map in LMH form (option 4 selected)
			if (choice == 6)
			{
				if (pressureMap[i][j] == ""){
					cout << " " << "?";
				} else {
					cout << " " << sortLMH(stoi(pressureMap[i][j]));
				}	
			}	
		}
		cout << " #" << endl;
	}

	//Bottom border of the grid
	cout << "  #";
	for (int i=0;i<col;i++)
	{
		cout << " " << "#";
	}
	cout << " #" << endl << "   ";

	//Print the column numbers at the bottom
	for (int i=rowstart; i<col+rowstart; i++)
	{
		cout << " " << i;
	}
	
	cout << endl;
}


//delete map array after use to save space
void deletePressureMemory(int row,int col)
{
	if (pressureMap != nullptr) {
        for (int i = 0; i < row; i++) {
            delete[] pressureMap[i];
        }
        delete[] pressureMap;
        pressureMap = nullptr;
    }
}

#endif