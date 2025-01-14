#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "structs.h"
#include <fstream>
#include <iomanip>
#include <vector>

using namespace std;


extern cityStruct * cityArray;
extern string ** cityMap;
extern cloudStruct * cloudArray;
extern string ** cloudMap;
extern pressureStruct * pressureArray;
extern string ** pressureMap;

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

//Pressure functions
void createPressureMap(string pressureFile, int row, int col);
void displayPressureMap(int row, int col, int rowstart, int colstart, int choice);
void deletePressureMemory(int row,int col);

//Weather
void weatherSummary(int arrayLength, int totalCity, int totalLength);

// Function to trim leading and trailing whitespace from a string
string trim(string str);

// Function to remove trailing empty lines and blank spaces in a file
void cleanFile(string filename);

//Read the last line of a .txt file assuming there is no new line spaces at the end
string readLastLine(string filename);


//Sorting the indexes
int sortIndex(int sortNo);
string sortLMH(int sortNo);

//get the rain picture
void sortRainPos(int cloudNo,int pressureNo);

#endif