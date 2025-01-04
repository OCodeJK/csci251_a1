#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <cctype>
#include <limits>

using namespace std;

int main() {
    
    string config;
    string choice;
    int cleaned_choice;

    do {
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
                cout << "Invalid input. Please enter only one of the options above." << endl;
            }
        } else {
            cout << "Invalid input. Please enter a single digit only." << endl;
        }
        
        switch(cleaned_choice){
            //Option 1
            case 1:{
                cout << "[Read in and process a configuration file]" << endl;
                cout << "Please enter a config filename : ";
                getline(cin, config);
                cout << endl;

                ifstream configData(config);
                    if (configData.is_open()){

                        configData.close();
                        //implement function to take all the specific string out of the file here

                        break; 
                    }
                    //check if user enter empty string
                    else if (config.empty()){
                        cout << "Empty config file input." << endl;
                        cout << "Press <enter> to go back to main menu." << endl;
						cin.ignore(numeric_limits<int>::max(),'\n');
                        break;
                    }
                    else {
                        cout << "Invalid config file entered." << endl;;
						cout << "Press <enter> to go back to main menu." << endl;
						cin.ignore(numeric_limits<int>::max(),'\n');
                        break;
                    }
            }  
            case 2:
                cout << "You have selected option 2" << endl;
                break;
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