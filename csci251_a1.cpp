#include "functions.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <limits>

using namespace std;


void createCityMap(string, int, int);


//for storing the different files in the config.txt
string gridXRange, gridYRange, cityFile, cloudFile, pressureFile;
int main() {
    
    string config;
    string choice;
    int cleaned_choice = 0;
    string error_message;
    int xMax, yMax;

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
                    cout << "Press <enter> to go back to main menu." << endl;
                    cin.get(); //wait for enter
                    break;
                }

                string line;
                int lineCount = 0;
                cleanFile(config);
                ifstream configData(config.c_str());
                if (configData.is_open()) {

                    while(getline(configData, line)) {

                        //Skip empty lines or lines starting with //
                        if(line.empty() || line.substr(0,2) == "//"){
                            continue;
                        } else if(line.find(".txt") != string::npos || line.find("=") != string::npos) {
                            // cout << line << endl;
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
                    //Split the strings up according to the delimiter
                    vector<string> tokenStringVector = tokenizeString(gridXRange, "=");
                    vector<string> xValues = tokenizeString(tokenStringVector[1], "-"); //so the n1 and n2 is stored here
                    tokenStringVector.clear();
                    tokenStringVector = tokenizeString(gridYRange, "=");
                    vector<string> yValues = tokenizeString(tokenStringVector[1], "-");
                    tokenStringVector.clear();
                    //assign the individual value to a variable
                    //also add + 1 because 0 is included
                    xMax = stoi(xValues[1]) + 1;
                    yMax = stoi(yValues[1]) + 1;
                    createCityMap(cityFile,xMax,yMax);
                    cout << "Reading in " << gridXRange << "...done!" << endl;
                    cout << "Reading in " << gridYRange << "...done!" << endl;
                    cout << endl << "Storing data from input file:" << endl;
                    cout << cityFile << "...done!" << endl;
                    cout << cloudFile << "...done!" << endl;
                    cout << pressureFile << "...done!" << endl;
                    cout << endl << "All records successfully stored. Going back to main menu...<enter>" << endl;
                    
                    cin.ignore(numeric_limits<int>::max(),'\n');

                    break;
                   
                }
                else {
                    //check if user inputted something else
                    cerr << "Error: Could not open the file: " << config << endl;;
                    cout << "Press <enter> to go back to main menu." << endl;
                    cin.get();
                    break;
                }
            }
            //Option 2: Display city map  
            case 2:
                if (cityFile.empty()){
                    cout << "You have not entered a valid config file with a city text file" << endl;
                    cout << "Press <enter> to go back to main menu." << endl;
                    cin.get();
                    break;
                } else {
                    displayCityMap(xMax,yMax);
                    cout << endl;
					cout << "Press <enter> to go back to main menu..." << endl;
					cin.ignore(numeric_limits<int>::max(),'\n');
					break;
                }
                
            case 3:
                cout << "You have selected option 3" << endl;
                break;
            case 4:
                cout << "You have selected option 4" << endl;
                break;
            case 5:
                cout << "You have selected option 5" << endl;
                break;
            case 6:
                cout << "You have selected option 6" << endl;
                break;
            case 7:
                cout << "You have selected option 7" << endl;
                break;
        }
        cout << endl;

    }
    while (cleaned_choice != 8); //Quits
    

    //deallocate memory
    deleteCityMemory(xMax,yMax);
    cout << "Exiting..." << endl;
    

    return (0);
}