#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <cmath>
#include <string>
#include <vector>

using namespace std;

struct InventoryItem {
    int orderNumber;
    string productName;
    int quantity;
    string arrivedOn;
    string expirationDate;
    double weight;
    string supplier;
};

void mainmenu();
void quitFunction();
void loadData(vector<InventoryItem>& inventory);

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
    vector<InventoryItem> inventory;
    loadData(inventory);  // Load data from file into the inventory vector

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

    system("cls");  // Clears the console screen on Windows; for Mac/Linux, use "clear"

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
        cout << "Report Section:" << endl;
        for (const auto& item : inventory) {
            cout << "Order Number: " << item.orderNumber << ", Product: " << item.productName
                << ", Quantity: " << item.quantity << ", Arrived On: " << item.arrivedOn
                << ", Expiration Date: " << item.expirationDate << ", Weight: " << item.weight
                << ", Supplier: " << item.supplier << endl;
        }
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

void loadData(vector<InventoryItem>& inventory) {
    ifstream fin("inventory.txt");
    if (!fin) {
        cout << "Error opening file." << endl;
        return;
    }

    InventoryItem item;
    while (fin >> item.orderNumber >> item.productName >> item.quantity
        >> item.arrivedOn >> item.expirationDate >> item.weight >> item.supplier) {
        inventory.push_back(item);
    }
    fin.close();
}

int main() {
    mainmenu();
    return 0;
}
