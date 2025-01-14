#include "functions.h"
#include "structs.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>


using namespace std;


//for storing the different files in the config.txt
string gridXRange, gridYRange, cityFile, cloudFile, pressureFile;
int main() {
    
    string config;
    string choice;
    int cleaned_choice = 0;
    string error_message;
    int xMax, yMax;
    int xMin, yMin;

    do {
        cout << endl;
        cout << "Student ID   " << ": 9071180" << endl;
	    cout << "Student Name " << ": Ooi Jun Kang" << endl;
        cout << setfill('*') << setw(29) << "*" << endl;
        cout << "Welcome to Weather Information Processing System" << endl;
        cout << endl;
        cout << "1)" <<  "   Read in and process a configuration file" << endl;
        cout << "2)" <<  "   Display city map" << endl;
        cout << "3)" <<  "   Display cloud coverage map (cloudiness index)" << endl;
        cout << "4)" <<  "   Display cloud coverage map (LMH symbols)" << endl;
        cout << "5)" <<  "   Display atmospheric pressure map (pressure index)" << endl;
        cout << "6)"  << "   Display atmospheric pressure map (LMH Symbols)" << endl;
        cout << "7)"  << "   Show weather forecast summary report" << endl;
        cout << "8)"  << "   Quit" << endl;
        cout << endl;
        //Display error message below the menu
        if(!error_message.empty()){
            cout << error_message << endl;
            error_message.clear();
        }

        cout << "Please enter your choice : ";
        getline(cin, choice);
        cout << endl;


        // Check if the input is not empty and is a single character
        if (!choice.empty() && choice.length() == 1 && isdigit(choice[0])){
            //convert the character to integer
            int digit = choice[0] - '0';

            if (digit >= 1 && digit <= 8) {
                cleaned_choice = digit;
            } else {  
                error_message = "Invalid input. Please enter only one of the options above.";
                continue;
            }
        } else {
            error_message = "Invalid input. Please enter a single digit only.";
            continue;
        }

        
        
        switch(cleaned_choice){
            //Option 1: Read config file by user
            case 1:{
                cout << "[Read in and process a configuration file]" << endl;
                cout << "Please enter a config filename : ";
                getline(cin, config);
                cout << endl;

                //Check for empty input
                if (config.empty()) {
                    cout << "Empty config file input." << endl;
                    cout << "Press <enter> to go back to main menu..." << endl;
                    cin.get(); //wait for enter
                    break;
                }

                string line;
                int lineCount = 0;
                cleanFile(config);
                ifstream configData(config);
                if (configData.is_open()) {

                    while(getline(configData, line)) {

                        //Skip empty lines or lines starting with //
                        if(line.empty() || line.substr(0,2) == "//"){
                            continue;
                        } else if(line.find(".txt") != string::npos || line.find("=") != string::npos) {
                            
                            //Store lines in specific variables
                            if (lineCount == 0) {
                                gridXRange = line;
                            } else if (lineCount == 1) {
                                gridYRange = line;
                            } else if (lineCount == 2) {
                                cityFile = line;
                            } else if (lineCount == 3) {
                                cloudFile = line;
                            } else if (lineCount == 4) {
                                pressureFile = line;
                            }
                            lineCount++;
                            
                        }
                    }
                    configData.close();

                    //read the maximum City [x,y] and compare it to the given gridX and gridY
                    string lastLineCityFile = readLastLine(cityFile); //last line of citylocation.txt
                    vector<string> lastLineCityFileSplit = tokenizeString(lastLineCityFile, "-"); //[n,n]   cityid    cityname
                    vector<string> lastValueSplit = tokenizeString(lastLineCityFileSplit[0], ",");
                    lastValueSplit[0].erase(lastValueSplit[0].begin()); //Remove [ from [n
                    lastValueSplit[1].pop_back(); //Remove ] from n]
                    lastValueSplit[1].erase(lastValueSplit[1].begin());
                    lastLineCityFileSplit.clear();

                    //Split the strings up according to the delimiter
                    vector<string> gridXSplit = tokenizeString(gridXRange, "=");
                    vector<string> xValues = tokenizeString(gridXSplit[1], "-"); //The n1 and n2 for X is stored here
                    vector<string> gridYSplit = tokenizeString(gridYRange, "="); //The n1 and n2 for Y is stored here
                    vector<string> yValues = tokenizeString(gridYSplit[1], "-");

                    //Compare City[X,Y] to the Grid X and Grid Y
                    if (lastValueSplit[0] == xValues[1] && lastValueSplit[1] == yValues[1]) {
                        error_message = "Grid X and Y is out of range for your cities! Re-adjust your ranges in: " + config;
                        
                        break;
                        
                    } else if (lastValueSplit[0] == xValues[1]) {
                        error_message = "Grid X: " + xValues[1] + " is out of range for your cities! Re-adjust your X range in: " + config;
                        
                       
                        break;
                    } else if (lastValueSplit[1] == yValues[1]) {
                        error_message = "Grid Y: " + yValues[1] + " is out of range for your cities! Re-adjust your Y range in: " + config;

                        break;
                    }


                    //assign the individual value to a variable
                    //also add + 1 because 0 is included
                    xMax = stoi(xValues[1]) + 1; //7 + 1 (End)
                    yMax = stoi(yValues[1]) + 1; //7 + 1 (End)
                    xMin = stoi(xValues[0]); //Start
                    yMin = stoi(yValues[0]); //Start


                    //called function to generate map respectively
                    createCityMap(cityFile, xMax, yMax);
                    createCloudMap(cloudFile, xMax, yMax);
                    createPressureMap(pressureFile, xMax, yMax);
                    cout << endl;
                    cout << "Getting X axis " << gridXRange << "...completed!" << endl;
                    cout << "Getting Y axis " << gridYRange << "...completed!" << endl;
                    cout << endl << "Storing data from input file:" << endl;
                    cout << cityFile << "...completed!" << endl;
                    cout << cloudFile << "...completed!" << endl;
                    cout << pressureFile << "...completed!" << endl;
                    cout << endl << "All records successfully stored. Going back to main menu...<enter>" << endl;
                    
                    cin.get();

                    break;
                   
                }
                else {
                    //check if user inputted something else
                    cerr << "Error: Could not open the file: " << config << endl;;
                    cout << "Press <enter> to go back to main menu..." << endl;
                    cin.get();
                    break;
                }
            }
            //Option 2: Display city map  
            case 2:
                if (cityFile.empty()){
                    cout << "You have not entered a valid config file with a city text file" << endl;
                    cout << "Press <enter> to go back to main menu..." << endl;
                    cin.get();
                    break;
                } else {
                    displayCityMap(xMax, yMax, xMin, yMin);
                    cout << endl;
					cout << "Press <enter> to go back to main menu..." << endl;
					cin.get();
					break;
                }
                
            case 3:
                if (cloudFile.empty()){
                    cout << "You have not entered a valid config file with a cloud text file" << endl;
                    cout << "Press <enter> to go back to main menu..." << endl;
                    cin.get();
                    break;
                } else {
                    displayCloudMap(xMax,yMax, xMin, yMin, 3);
                    cout << endl;
					cout << "Press <enter> to go back to main menu..." << endl;
					cin.get();
					break;
                }
            case 4:
                if (cloudFile.empty()){
                    cout << "You have not entered a valid config file with a cloud text file" << endl;
                    cout << "Press <enter> to go back to main menu..." << endl;
                    cin.get();
                    break;
                } else {
                    displayCloudMap(xMax,yMax, xMin, yMin, 4);
                    cout << endl;
					cout << "Press <enter> to go back to main menu..." << endl;
					cin.get();
					break;
                }
            case 5:
                if (pressureFile.empty()){
                    cout << "You have not entered a valid config file with a pressure text file" << endl;
                    cout << "Press <enter> to go back to main menu..." << endl;
                    cin.get();
                    break;
                } else {
                    displayPressureMap(xMax,yMax, xMin, yMin, 5);
                    cout << endl;
					cout << "Press <enter> to go back to main menu..." << endl;
					cin.get();
					break;
                }
            case 6:
                if (pressureFile.empty()){
                    cout << "You have not entered a valid config file with a pressure text file" << endl;
                    cout << "Press <enter> to go back to main menu..." << endl;
                    cin.get();
                    break;
                } else {
                    displayPressureMap(xMax,yMax, xMin, yMin, 6);
                    cout << endl;
					cout << "Press <enter> to go back to main menu..." << endl;
					cin.get();
					break;
                }
            case 7:
                if(cloudFile.empty()) {
                    cout << "Cannot calculate summary: config file with a cloud text file does not exist." << endl;
                    cout << "Press <enter> to go back to main menu..." << endl;
                    cin.get();
                    break;
                } else if(pressureFile.empty()) {
                    cout << "Cannot calculate summary: config file with a pressure text file does not exist." << endl;
                    cout << "Press <enter> to go back to main menu..." << endl;
                    cin.get();
                    break;
                } else {
                    int arrayLength = 0;
                    int totalCity = 0;
                    string line;
                    ifstream cityData(cityFile);
                    while (getline(cityData,line))
                    {
                        vector<string> cityDataVector = tokenizeString(line, "-");
                        if (stoi(cityDataVector[1]) > totalCity)
                        {
                            totalCity = stoi(cityDataVector[1]);
                        }
                        arrayLength++;
                    }
                    int lengthOfMap = xMax * yMax;
                    weatherSummary(arrayLength, totalCity, lengthOfMap);
                    cout << "Press <enter> to go back to main menu..." << endl;
                    cin.get();
                    break;
                }
                
        }
        cout << endl;

    }
    while (cleaned_choice != 8); //Quits
    

    //deallocate memory
    deleteCityMemory(xMax,yMax);
    deleteCloudMemory(xMax, yMax);
    deletePressureMemory(xMax, yMax);
    cout << "Exiting..." << endl;
    

    return (0);
}
