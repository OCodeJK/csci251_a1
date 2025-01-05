#include "tokenizer.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <cctype>
#include <limits>

using namespace std;

//for storing the different files in the config.txt
string gridXRange, gridYRange, cityFile, cloudFile, pressureFile;
int main() {
    
    string config;
    string choice;
    int cleaned_choice = 0;    

    do {
        cout << endl;
        cout << "Student ID   " << ": 8963822" << endl;
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
        cout << "Please enter your choice : ";
        
        getline(cin, choice);

        // Check if the input is not empty and is a single character
        if (!choice.empty() && choice.length() == 1 && isdigit(choice[0])){
            //convert the character to integer
            int digit = choice[0] - '0';

            if (digit >= 1 && digit <= 8) {
                cleaned_choice = digit;
            } else {  
                cout << "Invalid input. Please enter only one of the options above.";
            }
        } else {
            cout << "Invalid input. Please enter a single digit only." << endl;
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
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }

                string line;
                int lineCount = 0;
                ifstream configData(config);
                if (configData.is_open()) {

                    while(getline(configData, line)) {
                        //Trim leading/trailing whitespaces from the line
                        line.erase(0, line.find_first_not_of("\t"));
                        line.erase(line.find_last_not_of(" \t") + 1);

                        //Skip empty lines or lines starting with //
                        if(line.empty() || line.substr(0,2) == "//"){
                            continue;
                        }

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
                    
                    //Split the strings up according to the delimiter
                    vector<string> tokenStringVector = tokenizeString(gridXRange, "=");
                    vector<string> xValues = tokenizeString(tokenStringVector[1], "-");
                    cout << "GridX before -: " << xValues[0] << endl;
                    cout << "GridX after -: " << xValues[1] << endl;


                    configData.close();
                    break; 
                }
                //check if user inputted something else
                else {
                    cerr << "Error: Could not open the file: " << config << endl;;
                    cout << "Press <enter> to go back to main menu." << endl;
                    cin.ignore(numeric_limits<int>::max(),'\n');
                    break;
                }
            }
            //Option 2: Display city map  
            case 2:
                if (config.empty()){
                    cout << "You have not entered a valid config file with a city text file" << endl;
                    cout << "Press <enter> to go back to main menu." << endl;
                    cin.ignore(numeric_limits<int>::max(),'\n');
                    break;
                } else {
                    cout << "You have selected option 2" << endl;
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
    while (cleaned_choice != 8);

    

    return 0;
}