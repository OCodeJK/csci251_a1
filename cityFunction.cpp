#ifndef cityFunction_cpp
#define cityFunction_cpp
#include "structs.h"
#include "functions.h"

using namespace std;

// initialize the array structure and map
cityStruct * cityArray;
string ** cityMap = nullptr;


void createCityMap(string cityFile, int row, int col) {
    cleanFile(cityFile);

    ifstream cityData(cityFile);
    string line;
    int totalLength = 0;

    if (cityData.is_open()) {
        while (getline(cityData, line)) {
            if (!line.empty()) {
                totalLength++;
            }
        }
        cityData.close();

        cityArray = new cityStruct[totalLength];

        ifstream cityData(cityFile);
        int lineCount = 0;
        while (getline(cityData, line)) {
            vector<string> cityDataSplit = tokenizeString(line, "-"); //Split [n,n]  cityid  name
            vector<string> cityCoordsSplit = tokenizeString(cityDataSplit[0], ","); //Split [n    n]
            cityCoordsSplit[0].erase(cityCoordsSplit[0].begin()); //Erase [
            cityArray[lineCount].x = stoi(cityCoordsSplit[0]); //parse info into array
            cityArray[lineCount].y = stoi(cityCoordsSplit[1]);
            cityArray[lineCount].cityId = stoi(cityDataSplit[1]);
            cityArray[lineCount].name = cityDataSplit[2];
            lineCount++;
        }
        cityData.close();

		cout << "Initializing city map with dimensions: " << row << "x" << col << endl;

        cityMap = new string*[row];
        for (int i = 0; i < row; i++) {
            cityMap[i] = new string[col];
        }

        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                cityMap[i][j] = " ";
            }
        }

        for (int k = 0; k < totalLength; k++) {
            ostringstream oss;
			oss << cityArray[k].cityId;
			cityMap[row - 1 - cityArray[k].y][cityArray[k].x] = oss.str();
        }
    } else {
        cerr << "Error: Unable to open this file: " << cityFile << endl;
    }
}


//Display map in a simple UI
void displayCityMap(int row, int col, int rowstart, int colstart) {

	//Draw the top border of the grid
    cout << "  #";
    for (int i = 0; i < col; i++) {
        cout << " " << "#";
    }
    cout << " #" << endl;

	//Draw the rows of the grid
    for (int i = colstart; i < row; i++) {
		//Draw the row number on the left side
        cout << (row - i - 1 + colstart) << " #"; //Row number and left border

		//Draw the cells in the row
        for (int j = 0; j < col; j++) {
            cout << " " << cityMap[i][j]; //Content of each cell
        }
        cout << " #" << endl; //Right border of the grid
    }

	//Draw the bottom of the grid
    cout << "  #";
    for (int i = 0; i < col; i++) {
        cout << " " << "#";
    }
	//Draw the column numbers below the grid
    cout << " #" << endl << "   ";
    for (int i = rowstart; i < col + rowstart; i++) {
        cout << " " << i; //Column numbers
    }
    cout << endl;
}


//delete the allocated memory
void deleteCityMemory(int row, int col){
    if (cityMap != nullptr) {
        for (int i = 0; i < row; i++) {
            delete[] cityMap[i];
        }
        delete[] cityMap;
        cityMap = nullptr;
    }
}

#endif