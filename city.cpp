#ifndef city_cpp
#define city_cpp
#include "structs.h"
#include "tokenizer.h"

using namespace std;

cityStruct * cityArray;
string ** arrayMap = nullptr;

void createCityMap(string cityFile, int row, int col){
    //read city file
    ifstream cityData(cityFile); 
    cout << cityFile << endl;
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
            cityArray[lineNo].xCoord = stoi(cityCoordsVector[0]);
			cityArray[lineNo].yCoord = stoi(cityCoordsVector[1]);
			cityArray[lineNo].cityID = stoi(cityDataVector[1]);
			cityArray[lineNo].cityName = cityDataVector[2];
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
        //
        for (int k = 0; k < totalLength; k++)
		{
			ostringstream oss;
			oss << cityArray[k].cityID;
			arrayMap[col-1-cityArray[k].yCoord][cityArray[k].xCoord] = oss.str();
		}

    } else {
        cerr << "Unable to open file" << endl;
    }
}

//Display map in a simple UI
void displayCityMap(int row,int col)
{
	cout << "  #";
	for (int i=0;i<col;i++)
	{
		cout << " " << "#";
	}
	cout << " #" << endl;
	for (int i=0;i<row;i++)
	{	
		cout << (row - i - 1) << " #" ;	
		for (int j=0;j<col;j++)
		{	
			cout << " " << arrayMap[i][j];
		}
		cout << " #" << endl;
	}
	cout << "  #";
	for (int i=0;i<col;i++)
	{
		cout << " " << "#";
	}
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