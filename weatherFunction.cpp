#ifndef weatherFunction_cpp
#define weatherFunction_cpp
#include "functions.h"
#include "structs.h"
#include <iomanip>

using namespace std;

void weatherSummary(int arrayLength, int totalCity, int totalLength){
    // created vector to store approriate data/numbers
	vector<double> avgCloud(totalCity);
	vector<double> avgPressure(totalCity);
	// create a counter vector in order to be used in average calculation later
	vector<int> cityCounter(totalCity);
	// create a string vector to store the names of the city for display later
	vector<string> cityName(totalCity);
	cout << "Weather Forecast Summary Report" << endl;
	cout << setfill('-') << setw(32) << "-";
	for (int i=0; i<arrayLength; i++)
	{
		for (int j=0; j<totalLength; j++)
		{
			// Check if cloudArray[j] is within the surrounding area of cityArray[i]
            if (abs(cityArray[i].x - cloudArray[j].x) <= 1 && abs(cityArray[i].y - cloudArray[j].y) <= 1) {
                // City ID always starts from 1, so subtract 1
                avgCloud[cityArray[i].cityId - 1] += cloudArray[j].cloudLvl;
                avgPressure[cityArray[i].cityId - 1] += pressureArray[j].pressureLvl;
                cityCounter[cityArray[i].cityId - 1] += 1;
                cityName[cityArray[i].cityId - 1] = cityArray[i].name;
            }
		}	
	}

	for (int i=0; i<totalCity; i++)
	{
		// calculate average of cloud and pressure
		if(cityCounter[i] > 0) {
			avgCloud[i] /= cityCounter[i];
			avgPressure[i] /= cityCounter[i];
		}
		cout << endl;
		cout << "City Name : " << cityName[i] << endl;
		cout << "City ID   : " << i+1 << endl;
		cout << "Ave. Cloud Cover (ACC)" << "  : " << avgCloud[i] << setprecision(2) << "(" << sortLMH(avgCloud[i]) << ")" << endl;
		cout << "Ave. Pressure    (AP) " << "  : " << avgPressure[i] << setprecision(2) << "(" << sortLMH(avgPressure[i]) << ")";
		sortRainPos(avgCloud[i],avgPressure[i]);
		cout << endl;
	}	
}



#endif
