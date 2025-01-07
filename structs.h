#ifndef STRUCTS_H
#define STRUCTS_H
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

struct cityStruct {
    string cityName;
    int xCoord;
	int yCoord;
	int cityID;

	inline string toString() {
		ostringstream oss;

		oss << "X Coords               : " << xCoord << endl;
		oss << "Y Coords               : " << yCoord << endl;
		oss << "City ID           : " << cityID << endl;
		oss << "City Name    : " << cityName << endl;

		return (oss.str());
	}
};

#endif