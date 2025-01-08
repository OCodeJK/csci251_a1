#ifndef cityFunction_cpp
#define cityFunction_cpp
#include "functions.h"

using namespace std;

struct cityStruct {
    int x, y;
	int cityId;
	string name;

    string toString();
};

string cityStruct::toString()
{
	ostringstream oss;

	oss << "X Coords               : " << x << endl;
	oss << "Y Coords               : " << y << endl;
	oss << "City ID           : " << cityId << endl;
	oss << "City Name    : " << name << endl;

	return (oss.str());
}


cityStruct * cityArray;
string ** arrayMap = nullptr;


void createCityMap(string cityFile,int row,int col)
{
	//Clean the file the ifstream it
	cleanFile(cityFile);
	ifstream cityData(cityFile.c_str());
	string line;
	// This variable helps find out the amount of cities squares are in the document for array creation.
	int arrayLength = 0;
	if (cityData.is_open())
	{	
		while (getline(cityData,line))
		{   
			if (!line.empty()) {
                arrayLength++;
            }
			
		}
		cityData.close();
		ifstream cityData(cityFile);
		// Dynamic array allocation
		cityArray = new cityStruct[arrayLength];
		int lineNo = 0;
		// Break down each line using tokenizeString.cpp
		while (getline(cityData,line))
		{	
			vector<string> cityDataVector = tokenizeString(line, "-");
			vector<string> cityCoordsVector = tokenizeString(cityDataVector[0], ",");
			cityCoordsVector[0].erase(cityCoordsVector[0].begin());
			cityArray[lineNo].x = stoi(cityCoordsVector[0]);
			cityArray[lineNo].y = stoi(cityCoordsVector[1]);
			cityArray[lineNo].cityId = stoi(cityDataVector[1]);
			cityArray[lineNo].name = cityDataVector[2];
			lineNo++;

		}
		cityData.close();
		
		// generate an empty map for display later on
		arrayMap = new string*[row];
		for (int i=0; i < col; i++)
		{
			arrayMap[i] = new string [col];
		}
		for (int i=0;i<row;i++)
		{
			for (int j=0;j<col;j++)
				{
					ostringstream oss;
					oss << " ";

					arrayMap[i][j] = oss.str();
				}
		}
		// go through each of the structure array in order to extract the ID and store it in the appropriate location
		for (int k=0; k < arrayLength; k++)
		{
			ostringstream oss;
			oss << cityArray[k].cityId;
			arrayMap[col-1-cityArray[k].y][cityArray[k].x] = oss.str();
		}
	}
	else 
	{
		cout << "Unable to open file" << endl;
	}
	
}

// Display map with city inside it
void displayCityMap(int row,int col)
{
	//draws the first row (from the top)
	cout << "  #";
	for (int i=0; i<col; i++)
	{
		cout << " " << "#";
	}
	cout << " #" << endl;


	for (int i=0; i<row; i++)
	{	
		//this is for the column number
		cout << (row - i - 1) << " #" ;	

		//this creates the column and populate the grid with city
		for (int j=0; j<col; j++)
		{	
			cout << " " << arrayMap[i][j];
		}
		cout << " #" << endl;
	}

	//draws the last row (at the bottom)
	cout << "  #";
	for (int i=0; i<col; i++)
	{
		cout << " " << "#";
	}
	cout << " #" << endl << "   ";


	//this is for row number
	for (int i=0; i<col; i++)
	{
		cout << " " << i;
	}
	
	cout << endl;
}

// Delete memory allocation for city grid map when they quit program
void deleteCityMemory(int row,int col)
{
	if (col<=0)
		return;

	for (int i=0;i<row;i++)
	{
		delete[] arrayMap[i];
	}
	
	delete[] arrayMap;
}

#endif
