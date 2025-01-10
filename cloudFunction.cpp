#ifndef cloudFunction_cpp
#define cloudFunction_cpp
#include "functions.h"
#include "structs.h"

using namespace std;


// initialize the array structure and map
cloudStruct * cloudArray;
string ** cloudMap = nullptr;

void createCloudMap(string cloudFile,int row,int col)
{
    cleanFile(cloudFile);
	// read the file inputted by the user
	ifstream cloudData(cloudFile);
	string line;

	// variable to initalize the array dynamically later
	int totalLength = 0;
	int lineNumber = 0;

	// creating the 2D array to display the cloud level for user
	cloudMap = new string * [row];
	for (int i=0;i<col;i++)
	{
		cloudMap[i] = new string [col];
	}

	if (cloudData.is_open())
	{
		while (getline(cloudData,line))
		{
            if(!line.empty()) {
                totalLength++;
            }
		}
		cloudData.close();
		ifstream cloudData(cloudFile);
		cloudArray = new cloudStruct[totalLength];
		// split the string in the line of the data to store in the appropriate structure location
		while (getline(cloudData,line))
		{
			vector<string> cloudDataVector = tokenizeString(line, "-");
			vector<string> cloudCoordsVector = tokenizeString(cloudDataVector[0], ",");
			cloudCoordsVector[0].erase(cloudCoordsVector[0].begin());
			cloudArray[lineNumber].x = stoi(cloudCoordsVector[0]);
			cloudArray[lineNumber].y = stoi(cloudCoordsVector[1]);
			cloudArray[lineNumber].cloudLvl = stoi(cloudDataVector[1]);
			lineNumber++;
			
		}

		for (int k=0; k < totalLength; k++){
			// insert the cloud level into the map for the specific coordinate
			ostringstream oss;
			oss << cloudArray[k].cloudLvl;
			cloudMap[col-1-cloudArray[k].y][cloudArray[k].x] = oss.str();
			
		}
        
	}
	else 
	{
		cout << "Error: Unable to open this file: " << cloudFile << endl;
	}
}

// function to display the map of cloud level depending on how the user wants it in.
void displayCloudMap(int row, int col, int rowstart, int colstart, int choice)
{
	cout << "  #";
	for (int i=0;i<col;i++)
	{
		cout << " " << "#";
	}
	cout << " #" << endl;
	for (int i=colstart; i<row; i++)
	{	
		//Column number
		cout << (row - i - 1 + colstart) << " #" ;	
		for (int j=0;j<col;j++)
		{	
			// display the map in index form
			if (choice == 3)
			{
				if (cloudMap[i][j] == ""){
					cout << " " << "?";
				} else {
					cout << " " << sortIndex(stoi(cloudMap[i][j]));
				}
				
			}
			// display the map in LMH form
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
	cout << "  #";
	for (int i=0;i<col;i++)
	{
		cout << " " << "#";
	}
	//Row number
	cout << " #" << endl << "   ";
	for (int i=rowstart; i<col+rowstart; i++)
	{
		cout << " " << i;
	}
	
	cout << endl;
}


//delete map array after use to save space
void deleteCloudMemory(int row,int col)
{
	if (col<=0)
		return;

	for (int i=0;i<row;i++)
	{
		delete[] cloudMap[i];
	}
	
	delete[] cloudMap;
}

#endif
