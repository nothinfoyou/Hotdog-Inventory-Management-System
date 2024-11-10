#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <cmath>

using namespace std;


void mainmenu();
void quitFunction();

void quitFunction() {
    int quitInt;
    cout << "Would you like to quit?" << endl;
    cout << "Yes (1)" << endl;
    cout << "No  (0)" << endl;
    cin >> quitInt;

    if (quitInt == 0) {
        mainmenu();  
    }
    else {
        exit(0);  
    }
}

void mainmenu() {
    ifstream fin;
    ofstream fout;

    fin.open("inventory.txt");
    int input;

    cout << "***************************************************" << endl;
    cout << "*Welcome to the Hotdog Inventory Management System*" << endl;
    cout << "*Order        (6)                                 *" << endl;
    cout << "*Enter Data   (5)                                 *" << endl;
    cout << "*Remove Data  (4)                                 *" << endl;
    cout << "*Edit Data    (3)                                 *" << endl;
    cout << "*Search Data  (2)                                 *" << endl;
    cout << "*Report       (1)                                 *" << endl;
    cout << "*Quit Program (0)                                 *" << endl;
    cout << "***************************************************" << endl;
    cin >> input;
    
    system("cls"); //this command clears the terminal on windows, there should be a mac version but i havent found it yet.


    switch (input) {
    case 6:
        cout << "Unfinished Order section" << endl;
        break;
    case 5:
        cout << "Unfinished Enter Data Section" << endl;
        break;
    case 4:
        cout << "Unfinished Remove Data Section" << endl;
        break;
    case 3:
        cout << "Unfinished Edit Data Section" << endl;
        break;
    case 2:
        cout << "Unfinished Search Data Section" << endl;
        break;
    case 1:
        cout << "Unfinished Report Section" << endl;
        break;
    case 0:
        quitFunction();
        break;
    default:
        cout << "Invalid option. Please select a valid menu item." << endl;
        mainmenu();  
        break;
    }
}

int main() {
    mainmenu();
    return 0;
}
