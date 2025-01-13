#ifndef STRUCTS_H
#define STRUCTS_H

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

struct cityStruct {
    int x, y;
	int cityId;
	string name;

    string toString();
};



struct cloudStruct 
{
	int x, y;
	int cloudLvl;
	string toString();
};



struct pressureStruct 
{
	int x, y;
	int pressureLvl;
	string toString();
};




#endif