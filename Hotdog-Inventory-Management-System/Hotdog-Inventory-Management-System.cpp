#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <cmath>
#include <string>
#include <vector>
#include <algorithm> //for transform

using namespace std;

struct InventoryItems {
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
void loadData(vector<InventoryItems>& inventory);
void displayItem(const InventoryItems& item);
void displayAllItems(const vector<InventoryItems>& inventory);
void searchItem(const vector<InventoryItems>& inventory);

void quitFunction() {
    int quitInt;
    cout << "Are you sure you would you like to quit?" << endl;
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

void loadData(vector<InventoryItems>& inventory) {
    ifstream fin("../inventory.txt");
    if (!fin) {
        cout << "Error opening file" << endl;
        return;
    }

    InventoryItems item;
    while (fin >> item.orderNumber >> item.productName >> item.quantity >> item.arrivedOn >> item.expirationDate >> item.weight >> item.supplier) {
        inventory.push_back(item);
    }
    fin.close();
}

// Function to display a single inventory item
void displayItem(const InventoryItems& item) {
    cout << "Order Number: " << item.orderNumber << endl;
    cout << "Product Name: " << item.productName << endl;
    cout << "Quantity: " << item.quantity << endl;
    cout << "Arrived On: " << item.arrivedOn << endl;
    cout << "Expiration Date: " << item.expirationDate << endl;
    cout << "Weight: " << fixed << setprecision(2) << item.weight << " lbs" << endl;
    cout << "Supplier: " << item.supplier << endl;
    cout << "-----------------------------------" << endl;
}

// Function to display all inventory items
void displayAllItems(const vector<InventoryItems>& inventory) {
    if (inventory.empty()) {
        cout << "No inventory items to display." << endl;
        return;
    }

    for (const auto& item : inventory) {
        displayItem(item);
    }
}

//Function to search for items by product name
void searchItem(const vector<InventoryItems>& inventory) {
    int field;
    cout << "*****************************************************" << endl;
    cout << "*Search Section                                     *" << endl;
    cout << "*Order Number   (6)                                 *" << endl;
    cout << "*Product Name   (5)                                 *" << endl;
    cout << "*Quantity       (4)                                 *" << endl;
    cout << "*Arrived On     (3)                                 *" << endl;
    cout << "*Expiration Date(2)                                 *" << endl;
    cout << "*Weight         (1)                                 *" << endl;
    cout << "*Supplier       (0)                                 *" << endl;
    cout << "Enter your selection:                               *" << endl;
    cout << "*****************************************************" << endl;
    cin >> field;
    bool found = false;

    if (field == 6) {
        int orderNumber;
        cout << "Enter Order Number: ";
        cin >> orderNumber;
        for (const auto& item : inventory) {
            if (item.orderNumber == orderNumber) {

                displayItem(item);
                found = true;
            }
        }
    }
    else if (field == 5) {
        string productName;
        cout << "Enter Product Name: ";
        cin.ignore();
        getline(cin, productName);
        for (const auto& item : inventory) {
            if (item.productName == productName) {
                displayItem(item);
                found = true;
            }
        }
    }
    else if (field == 4) {
        int quantity;
        cout << "Enter Quantity: ";
        cin >> quantity;
        for (const auto& item : inventory) {
            if (item.quantity == quantity) {
                displayItem(item);
                found = true;
            }
        }
    }
    else if (field == 3) {
        string arrivedOn;
        cout << "Enter Arrived On date: ";
        cin >> arrivedOn;
        for (const auto& item : inventory) {
            if (item.arrivedOn == arrivedOn) {
                displayItem(item);
                found = true;
            }
        }
    }
    else if (field == 2) {
        string expirationDate;
        cout << "Enter Expiration Date: ";
        cin >> expirationDate;
        for (const auto& item : inventory) {
            if (item.expirationDate == expirationDate) {
                displayItem(item);
                found = true;
            }
        }
    }
    else if (field == 1) {
        double weight;
        cout << "Enter Weight: ";
        cin >> weight;
        for (const auto& item : inventory) {
            if (item.weight == weight) {
                displayItem(item);
                found = true;
            }
        }
    }
    else if (field == 0) {
        string supplier;
        cout << "Enter Supplier: ";
        cin.ignore();
        getline(cin, supplier);
        for (const auto& item : inventory) {
            if (item.supplier == supplier) {
                displayItem(item);
                found = true;
            }
        }
    }
    else {
        cout << "Invalid field. Please try again." << endl;
    }
    if (!found) {
        cout << "No items found with the given search criteria." << endl;
    }
    
    
    
    if (inventory.empty()) {
        cout << "No inventory items to search." << endl;
        return;
    }

    //string searchTerm;
    //cout << "Enter the name of the item you are searching for (case specific): " << endl;
    //cin >> ws; //clears whitespace
    //getline(cin, searchTerm);

    //bool found = false;
    //for (const auto& item : inventory) {
    //    if (item.productName.find(searchTerm) != string::npos) {
    //        displayItem(item);
    //        found = true;
    //    }
    //}
    //if (!found) {
    //    cout << "No items matched '" << searchTerm << "'." << endl;
    //}
}

void mainmenu() {
    vector<InventoryItems> inventory;
    loadData(inventory);

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
    cout << "Enter your selection:                             *" << endl;
    cout << "***************************************************" << endl;
    cin >> input;


    system("cls"); // Clear the screen (Windows-specific)

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
        cout << "Search Section" << endl;
        searchItem(inventory);
        break;
    case 1:
        cout << "Report Section" << endl;
        displayAllItems(inventory);
        break;
    case 0:
        quitFunction();
        break;
    default:
        cout << "Invalid option. Please select a valid menu item." << endl;
        mainmenu();
        break; //breaks
    }
}

int main() {
    mainmenu();
    return 0;
}
