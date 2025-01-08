#ifndef cityFunction_cpp
#define cityFunction_cpp
#include "structs.h"
#include "functions.h"

using namespace std;

cityStruct * cityArray;
string ** arrayMap = nullptr;

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
            totalLength++;
        }

        ifstream cityData(cityFile.c_str());
        //create dynamic array to store the actual city coordinates
        cityArray = new cityStruct[totalLength];
        int lineNo = 0;
        // Go through each line, tokenize each of them and store in a respective variable
        while(getline(cityData, line)){
            vector<string> cityDataVector = tokenizeString(line, "-"); //Split according to - so eg. [1, 1], 3, Big_City
			vector<string> cityCoordsVector = tokenizeString(cityDataVector[0], ","); //Split again for the coords eg. ([1), (1])
            cityCoordsVector[0].erase(cityCoordsVector[0].begin()); //Get the rid of the [
            cityArray[lineNo].x = stoi(cityCoordsVector[0]);
			cityArray[lineNo].y = stoi(cityCoordsVector[1]);
			cityArray[lineNo].cityId = stoi(cityDataVector[1]);
			cityArray[lineNo].name = cityDataVector[2];
			lineNo++;
        }
        cityData.close();

        //generate empty map for display later
        arrayMap = new string * [row];
        for (int i = 0; i < col; i++){
            arrayMap[i] = new string [col];
        }
        for (int i = 0; i < row; i++){
            for (int j = 0; j < col; j++){
                ostringstream oss;
                oss << " ";

                arrayMap[i][j] = oss.str();
            }
        }
        //Get the city ID and put into the map
        for (int k = 0; k < totalLength; k++)
		{
			ostringstream oss;
			oss << cityArray[k].cityId;
			arrayMap[col-1-cityArray[k].y][cityArray[k].x] = oss.str();
		}

    } else {
        cerr << "Unable to open file" << endl;
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
			cout << " " << arrayMap[i][j];
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
        delete[] arrayMap[i];
    }
    delete[] arrayMap;
}

#endif