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

inline string cityStruct::toString()
{
	ostringstream oss;

	oss << "X Coords               : " << x << endl;
	oss << "Y Coords               : " << y << endl;
	oss << "City ID           : " << cityId << endl;
	oss << "City Name    : " << name << endl;

	return (oss.str());
}

struct cloudStruct 
{
	int x, y;
	int cloudLvl;
	string toString();
};

inline string cloudStruct::toString()
{
	ostringstream oss;

	oss << "X Coords               : " << x << endl;
	oss << "Y Coords               : " << y << endl;
	oss << "Cloud Level            : " << cloudLvl << endl;

	return (oss.str());
}


#endif