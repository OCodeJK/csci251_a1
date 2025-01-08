#ifndef cityFunction_cpp
#define cityFunction_cpp
#include "functions.h"
#include "structs.h"

using namespace std;


cityStruct * cityArray;
string ** arrayMap = nullptr;


void createCityMap(string cityFile,int row,int col)
{
	//Clean the file then ifstream it
	cleanFile(cityFile);
	ifstream cityData(cityFile.c_str());
	string line;
	// This variable helps find out the amount of cities squares are in the document for array creation.
	int arrayLength = 0;
	if (cityData.is_open())
	{	
		while (getline(cityData,line))
		{   
			//count the lines only if they are not empty spaces
			if (!line.empty()) {
                arrayLength++;
            }
			
		}
		cityData.close();
		ifstream cityData(cityFile);
		
		// Dynamic array allocation using arrayLength
		cityArray = new cityStruct[arrayLength];
		int lineCount = 0;
		// Break down each line using tokenizeString.cpp
		while (getline(cityData,line))
		{	
			vector<string> cityDataSplit = tokenizeString(line, "-"); //split [x,y] cityID cityName
			vector<string> cityCoordsSplit = tokenizeString(cityDataSplit[0], ","); //split [x,y] into [x    y]
			cityDataSplit[0].erase(cityDataSplit[0].begin()); //erase the [
			cityArray[lineCount].x = stoi(cityDataSplit[0]); //store x in cityArray[n].x
			cityArray[lineCount].y = stoi(cityDataSplit[1]); //store y in cityArray[n].y
			cityArray[lineCount].cityId = stoi(cityDataSplit[1]); //store cityId in cityArray[n].cityId
			cityArray[lineCount].name = cityDataSplit[2]; //store city name in cityArray[n].name
			lineCount++;

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

		//extract city ID to store in the arrayMap
		for (int k=0; k < arrayLength; k++)
		{
			ostringstream oss;
			oss << cityArray[k].cityId;
			arrayMap[col-1-cityArray[k].y][cityArray[k].x] = oss.str();
		}
	}
	else 
	{
		cerr << "Error could not open file : " << cityFile << endl;
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
