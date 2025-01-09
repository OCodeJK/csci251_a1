#ifndef cityFunction_cpp
#define cityFunction_cpp
#include "structs.h"
#include "functions.h"

using namespace std;

// initialize the array structure and map
cityStruct * cityArray;
string ** cityMap = nullptr;


void createCityMap(string cityFile, int row, int col){
	//clean the file
	cleanFile(cityFile);
    //read city file
    ifstream cityData(cityFile); 
    string line;
    //This part is to find out how much city is in the text file
    int totalLength = 0;
    if(cityData.is_open()) {

        while(getline(cityData, line)){

			if(!line.empty()) {
				totalLength++;
			}
			
        }

        ifstream cityData(cityFile);
        //create dynamic array to store the actual city coordinates
        cityArray = new cityStruct[totalLength];
        int lineCount = 0;
        // Go through each line, tokenize each of them and store in a respective variable
        while(getline(cityData, line)){
            vector<string> cityDataSplit = tokenizeString(line, "-"); //Split according to - so eg. [1, 1], 3, Big_City
			vector<string> cityCoordsSplit = tokenizeString(cityDataSplit[0], ","); //Split again for the coords eg. ([1), (1])
            cityCoordsSplit[0].erase(cityCoordsSplit[0].begin()); //Get the rid of the [
            cityArray[lineCount].x = stoi(cityCoordsSplit[0]); //Stores the x coord in cityArray[n].x
			cityArray[lineCount].y = stoi(cityCoordsSplit[1]); //Stores the y coord in cityArray[n].y
			cityArray[lineCount].cityId = stoi(cityDataSplit[1]); //Store the city id in cityArray[n].cityId
			cityArray[lineCount].name = cityDataSplit[2]; //Store the city name in cityArray[n].name
			lineCount++;
        }
        cityData.close();

        //generate empty map for display later
        cityMap = new string * [row];
        for (int i = 0; i < col; i++){
            cityMap[i] = new string [col];
        }

        for (int i = 0; i < row; i++){
            for (int j = 0; j < col; j++){
                ostringstream oss;
                oss << " ";

                cityMap[i][j] = oss.str();
            }
        }
		
        //Get the city ID and put into the map
        for (int k = 0; k < totalLength; k++)
		{
			ostringstream oss;
			oss << cityArray[k].cityId;
			cityMap[col-1-cityArray[k].y][cityArray[k].x] = oss.str();
		}

    } else {
        cerr << "Error: Unable to open this file: " << cityFile << endl;
    }
}

//Display map in a simple UI
void displayCityMap(int row,int col)
{
	//This draws the first row
	cout << "  #";
	for (int i=0;i<col;i++)
	{
		cout << " " << "#";
	}
	cout << " #" << endl;

	//This draws the column
	for (int i=0;i<row;i++)
	{	
		//Column number
		cout << (row - i - 1) << " #" ;	
		//The city numbers inside the grid
		for (int j=0;j<col;j++)
		{	
			cout << " " << cityMap[i][j];
		}
		cout << " #" << endl;
	}

	//This draws the bottom row
	cout << "  #";
	for (int i=0;i<col;i++)
	{
		cout << " " << "#";
	}
	//Row number
	cout << " #" << endl << "   ";
	for (int i=0;i<col;i++)
	{
		cout << " " << i;
	}
	
	cout << endl;
}

//delete the allocated memory
void deleteCityMemory(int row, int col){
    if (col <= 0)
        return;

    for (int i = 0; i < row; i++){
        delete[] cityMap[i];
    }
    delete[] cityMap;
}

#endif