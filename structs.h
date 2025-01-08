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

string cityStruct::toString()
{
	ostringstream oss;

	oss << "X Coords               : " << x << endl;
	oss << "Y Coords               : " << y << endl;
	oss << "City ID           : " << cityId << endl;
	oss << "City Name    : " << name << endl;

	return (oss.str());
}


#endif