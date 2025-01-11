#ifndef cloudFunction_cpp
#define cloudFunction_cpp
#include "functions.h"
#include "structs.h"

using namespace std;


// initialize the array structure and map
cloudStruct * cloudArray;
string ** cloudMap = nullptr;

void createCloudMap(string cloudFile, int row, int col)
{
    cleanFile(cloudFile);
    ifstream cloudData(cloudFile);
    string line;

    // Variable to initialize the array dynamically later
    int totalLength = 0;
    int lineNumber = 0;

    // Correctly create the 2D array for cloudMap with row and col
    cloudMap = new string* [row];
    for (int i = 0; i < row; i++)  // Ensure row is used here
    {
        cloudMap[i] = new string[col];  // Ensure col is used here
    }

    if (cloudData.is_open()) {
        while (getline(cloudData, line)) {
            if (!line.empty()) {
                totalLength++;
            }
        }
        cloudData.close();

        // Re-open the file and populate the cloud data
        ifstream cloudData(cloudFile);
        cloudArray = new cloudStruct[totalLength];

        while (getline(cloudData, line)) {
            vector<string> cloudDataSplit = tokenizeString(line, "-"); //Split [n,n]   cloudIndex
            vector<string> cloudCoordsSplit = tokenizeString(cloudDataSplit[0], ","); //Split [n     n]
            
            // Remove brackets and spaces from coordinates
            cloudCoordsSplit[0].erase(cloudCoordsSplit[0].begin());  // Remove '['
            cloudCoordsSplit[1].erase(cloudCoordsSplit[1].end()-1);  // Remove ']'

            cloudArray[lineNumber].x = stoi(cloudCoordsSplit[0]); //parse info into array
            cloudArray[lineNumber].y = stoi(cloudCoordsSplit[1]);
            cloudArray[lineNumber].cloudLvl = stoi(cloudDataSplit[1]);
            lineNumber++;
        }

        // Populate cloudMap with cloud levels
        for (int k = 0; k < totalLength; k++) {
            ostringstream oss;
            oss << cloudArray[k].cloudLvl;
            // Adjust the index logic for proper placement in the map
            cloudMap[row - 1 - cloudArray[k].y][cloudArray[k].x] = oss.str();
        }


    } else {
        cout << "Error: Unable to open this file: " << cloudFile << endl;
    }
}


// function to display the map of cloud level depending on how the user wants it in.
void displayCloudMap(int row, int col, int rowstart, int colstart, int choice)
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
			if (choice == 3)
			{
				if (cloudMap[i][j] == ""){
					cout << " " << "?";
				} else {
					cout << " " << sortIndex(stoi(cloudMap[i][j]));
				}
				
			}
			// Display the map in LMH form (option 4 selected)
			if (choice == 4)
			{
				if (cloudMap[i][j] == ""){
					cout << " " << "?";
				} else {
					cout << " " << sortLMH(stoi(cloudMap[i][j]));
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
void deleteCloudMemory(int row,int col)
{
	if (cloudMap != nullptr) {
        for (int i = 0; i < row; i++) {
            delete[] cloudMap[i];
        }
        delete[] cloudMap;
        cloudMap = nullptr;
    }
}

#endif
