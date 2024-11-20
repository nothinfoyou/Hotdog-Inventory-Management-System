#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <cmath>
#include <string>
#include <vector>
#include "InventoryObj.cpp"
#include "ExpiredReport.h"
#include "LowStockReport.h"
#include "OverStockReport.h"

using namespace std;

void mainmenu();
void returnToMainMenu(string confirmation);
void quitFunction(string dispArg);
void loadData(vector<InventoryItems>& inventory);
void displayItem(const InventoryItems& item);
void searchItem(const vector<InventoryItems>& inventory);
void enterData(vector<InventoryItems>& inventory);
void removeItem(vector<InventoryItems>& inventory);
void editData(vector<InventoryItems>& inventory);

//function that gives users option to return to main menu from other functions
void returnToMainMenu(string confirmation) {
    while (true) {
        int input;
        cout << "***************************************************" << endl;
        cout << "* " << confirmation << endl;
        cout << "* Yes (1)" << endl;
        cout << "* No  (0)" << endl;
        cout << "***************************************************" << endl;
        cin >> input;

        if (input == 0) {
            cout << "Returning to current action..." << endl;
            break;
        }
        if (input == 1) {
            cout << "Returning to main menu..." << endl;
            system("cls"); //clear screen
            mainmenu();
            break;
        }
        else {
            cin.clear(); //clears input if invalid
            cout << "Invalid input. Please enter 1 for Yes or 0 for No.";
            break;
        }
    }
 }


//function to quit program
void quitFunction(string dispArg) {
    int quitInt;
    cout << "***************************************************" << endl;
    cout << "*" << dispArg << endl;
    cout << "* Yes (1)" << endl;
    cout << "* No  (0)" << endl;
    cout << "***************************************************" << endl;
    cin >> quitInt;

    if (quitInt == 0) {
        system("cls");
        mainmenu();
    }
    else {
        exit(0);
    }
}

//function that reads from file
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

// this func takes a generic report arg and inventory arg to build and display whichever report was sent
// DEVNOTE: the report can be one of 4 options, BaseReport, ExpiredReport, LowStockReport,OverStockReport
template <typename T>
void displayReport(T& report, const vector<InventoryItems>& inventory) {
    if (inventory.empty()) {
        cout << "No inventory items to display." << endl;
        return;
    }

    for (const auto& item : inventory) {
        report.addData(item);
    }

    report.generateReport();
}

// this func is the report menu section
void reportMenu(const vector<InventoryItems>& inventory) {
    system("cls");

    int input;

    cout << "***************************************************" << endl;
    cout << "* Welcome to the Report Section                   *" << endl;
    cout << "* General Report (1)                              *" << endl;
    cout << "* Expired Report (2)                              *" << endl;
    cout << "* Understocked Report (3)                         *" << endl;
    cout << "* Overstocked Report (4)                          *" << endl;
    cout << "* Return to Menu (0)                              *" << endl;
    cout << "***************************************************" << endl;

    cin >> input;
    ExpiredReport expiredReport;
    BaseReport baseReport;
    LowStockReport lsReport(5);
    OverStockReport osReport(20);
    switch (input) {
    case 4:
        displayReport(osReport, inventory);
        quitFunction("Would you like to close the program?");
        break;
    case 3:
        displayReport(lsReport, inventory);
        quitFunction("Would you like to close the program?");
        break;
    case 2:
        displayReport(expiredReport, inventory);
        quitFunction("Would you like to close the program?");
        break;
    case 1:
        displayReport(baseReport, inventory);
        quitFunction("Would you like to close the program?");
        break;
    case 0:
        system("cls");
        mainmenu();
        break;
    default:
        cout << "Invalid option. Please select a valid menu item." << endl;
        reportMenu(inventory);
        break;
    }
}

//function to add new item to inventory
void enterData(vector<InventoryItems>& inventory) {
    InventoryItems newItem;

    cout << "**************************************************************" << endl;
    cout << "*Welcome to the Add Item Section                             *" << endl;
    cout << "*Enter the order number of the item you would like to add,   *" << endl;
    cout << "* or type 0 to return to the main menu:                      *" << endl;
    cout << "**************************************************************" << endl;
    cin >> newItem.orderNumber;
    cin.ignore();

    if (newItem.orderNumber == 0) {
        system("cls");
        cout << "Returning to main menu." << endl;
        mainmenu();
    }

    cout << "**************************************************************" << endl;
    cout << "*Enter the product name of the item you would like to add:   *" << endl;
    cout << "*                                                            *" << endl;
    cout << "**************************************************************" << endl;
    getline(cin, newItem.productName);

    cout << "**************************************************************" << endl;
    cout << "*Enter the quantity of the item you would like to add:       *" << endl;
    cout << "*                                                            *" << endl;
    cout << "**************************************************************" << endl;
    cin >> newItem.quantity;
    cin.ignore();
    
    cout << "*******************************************************************" << endl;
    cout << "*Enter the arrival date of the new item in the format MM-DD-YYYY: *" << endl;
    cout << "*                                                                 *" << endl;
    cout << "*******************************************************************" << endl;
    getline(cin, newItem.arrivedOn);

    cout << "**********************************************************************" << endl;
    cout << "*Enter the expiration date of the new item in the format MM-DD-YYYY: *" << endl;
    cout << "*                                                                    *" << endl;
    cout << "**********************************************************************" << endl;
    getline(cin, newItem.expirationDate);

    cout << "**************************************************************" << endl;
    cout << "*Enter the weight of the item you would like to add:         *" << endl;
    cout << "*                                                            *" << endl;
    cout << "**************************************************************" << endl;
    cin >> newItem.weight;
    cin.ignore();

    cout << "**************************************************************" << endl;
    cout << "*Enter the supplier of the item you would like to add:       *" << endl;
    cout << "*                                                            *" << endl;
    cout << "**************************************************************" << endl;
    getline(cin, newItem.supplier);
    //add to vector
    inventory.push_back(newItem);

    ofstream fout("../inventory.txt");
    if (!fout) {
        cout << "Error updating file." << endl;
        return;
    }
    for (const auto& item : inventory) {
        fout << item.orderNumber << " " << item.productName << " " << item.quantity << " "
            << item.arrivedOn << " " << item.expirationDate << " " << item.weight << " "
            << item.supplier << endl;
    }
    fout.close();
    cout << "\nNew item added successfully!\n" << endl;
    displayItem(newItem);
    quitFunction("Would you like to exit the application?");
}

//function to remove items based on order number
void removeItem(vector<InventoryItems>& inventory) {
    if (inventory.empty()) {
        cout << "No inventory items to remove." << endl;
        return;
    }

    int removeNumber;
    cout << "****************************************************************" << endl;
    cout << "* Welcome to the Remove Item Section                           *" << endl;
    cout << "* Enter the order number of the item you would like to remove, *" << endl;
    cout << "* or type 0 to return to the main menu:                        *"<<endl;
    cout << "****************************************************************" << endl;

    cin >> removeNumber;
    bool found = false;

    if (removeNumber == 0) {
        system("cls");
        cout << "Returning to main menu." << endl;
        mainmenu();
    }

    for (size_t i = 0; i < inventory.size(); ++i) {
        if (inventory[i].orderNumber == removeNumber) {
            found = true;

            cout << "*****************************************************" << endl;
            cout << "* Item Found!                                       *" << endl;
            cout << "*****************************************************" << endl;
            displayItem(inventory[i]);

            cout << "Are you sure you want to remove this item?" << endl;
            cout << "Yes (1) / No (0): ";
            int confirm;
            cin >> confirm;

            if (confirm == 1) {
                inventory.erase(inventory.begin() + i);
                cout << "Item removed from inventory successfully." << endl;
                returnToMainMenu("Would you like to return to the main menu?");

                ofstream fout("../inventory.txt");
                if (!fout) {
                    cout << "Error updating file." << endl;
                    return;
                }

                for (const auto& item : inventory) {
                    fout << item.orderNumber << " " << item.productName << " " << item.quantity << " "
                        << item.arrivedOn << " " << item.expirationDate << " " << item.weight << " "
                        << item.supplier << endl;
                }

                fout.close();
                system("cls");
                cout << "Inventory file updated. Returning to main menu." << endl;
                mainmenu(); 
            }
            else {
                system("cls");
                cout << "Item was not removed." << endl;
                removeItem(inventory);
            }
            break;
        }
    }

    if (!found) {
        cout << "No item found with that order number." << endl;
        cout << "Would you like to try removing another item?" << endl;
        cout << "Yes (1)" << endl;
        cout << "No  (0)" << endl;

        int choice;
        cin >> choice;

        if (choice == 1) {
            system("cls");
            removeItem(inventory);
        }
        else if (choice == 0) {
            system("cls");
            cout << "Returning to main menu." << endl;
            mainmenu();
        }
        else {
            system("cls");
            cout << "Invalid selection. Returning to remove item section." << endl;
            removeItem(inventory);
        }
    }
}



// function to search items based on field
void searchItem(const vector<InventoryItems>& inventory) {
    int field;
    cout << "*****************************************************" << endl;
    cout << "*Search Items By:                                   *" << endl;
    cout << "*Order Number   (7)                                 *" << endl;
    cout << "*Product Name   (6)                                 *" << endl;
    cout << "*Quantity       (5)                                 *" << endl;
    cout << "*Arrived On     (4)                                 *" << endl;
    cout << "*Expiration Date(3)                                 *" << endl;
    cout << "*Weight         (2)                                 *" << endl;
    cout << "*Supplier       (1)                                 *" << endl;
    cout << "*Back           (0)                                 *" << endl;
    cout << "Enter your selection:                               *" << endl;
    cout << "*****************************************************" << endl;
    cin >> field;
    bool found = false;

    if (field == 7) {
        int orderNumber;
        cout << "Enter Order Number: ";
        cin >> orderNumber;
        for (const auto& item : inventory) {
            if (item.orderNumber == orderNumber) {
                displayItem(item);
                found = true;
                quitFunction("Would you like to exit the application?");
            }
        }
    }
    else if (field == 6) {
        string productName;
        cout << "Enter Product Name: ";
        cin.ignore();
        getline(cin, productName);
        for (const auto& item : inventory) {
            if (item.productName == productName) {
                displayItem(item);
                found = true;
                quitFunction("Would you like to exit the application?");
            }
        }
    }
    else if (field == 5) {
        int quantity;
        cout << "Enter Quantity: ";
        cin >> quantity;
        for (const auto& item : inventory) {
            if (item.quantity == quantity) {
                displayItem(item);
                found = true;
                quitFunction("Would you like to exit the application?");
            }
        }
    }
    else if (field == 4) {
        string arrivedOn;
        cout << "Enter Arrived On date: ";
        cin >> arrivedOn;
        for (const auto& item : inventory) {
            if (item.arrivedOn == arrivedOn) {
                displayItem(item);
                found = true;
                quitFunction("Would you like to exit the application?");
            }
        }
    }
    else if (field == 3) {
        string expirationDate;
        cout << "Enter Expiration Date: ";
        cin >> expirationDate;
        for (const auto& item : inventory) {
            if (item.expirationDate == expirationDate) {
                displayItem(item);
                found = true;
                quitFunction("Would you like to exit the application?");
            }
        }
    }
    else if (field == 2) {
        double weight;
        cout << "Enter Weight: ";
        cin >> weight;
        for (const auto& item : inventory) {
            if (item.weight == weight) {
                displayItem(item);
                found = true;
                quitFunction("Would you like to exit the application?");
            }
        }
    }
    else if (field == 1) {
        string supplier;
        cout << "Enter Supplier: ";
        cin.ignore();
        getline(cin, supplier);
        for (const auto& item : inventory) {
            if (item.supplier == supplier) {
                displayItem(item);
                found = true;
                quitFunction("Would you like to exit the application?");
            }
        }
    }
    else if (field == 0) {
        system("cls");
        returnToMainMenu("Would you like to return to the main menu?");
    }
    else {
        system("cls");
        cout << "Invalid field. Please try again." << endl;
        searchItem(inventory);
    }
    if (!found) {
        system("cls");
        cout << "No items found with the given search criteria." << endl;
        searchItem(inventory);
    }
}

//edit function to edit inventory item fields 
void editData(vector<InventoryItems>& inventory) {
    if (inventory.empty()) {
        cout << "No inventory items to edit" << endl;
        return;
    }
    int getOrderNumber;

    cout << "*************************************************************" << endl;
    cout << "*Edit Item Section                                          *" << endl;
    cout << "*Enter the order number of the item you would like to edit: *" << endl;
    cout << "*                                                           *" << endl;
    cout << "*************************************************************" << endl;
    cin >> getOrderNumber;

    bool found = false;
    for (auto& item : inventory) {
        if (item.orderNumber == getOrderNumber) {
            found = true;
            cout << "*****************************************************" << endl;
            cout << "*Item Found!                                        *" << endl;
            cout << "*Which field would you like to edit?                *" << endl;
            cout << "*Product Name   (6)                                 *" << endl;
            cout << "*Quantity       (5)                                 *" << endl;
            cout << "*Arrived On     (4)                                 *" << endl;
            cout << "*Expiration Date(3)                                 *" << endl;
            cout << "*Weight         (2)                                 *" << endl;
            cout << "*Supplier       (1)                                 *" << endl;
            cout << "*Back           (0)                                 *" << endl;
            cout << "Enter your selection:                               *" << endl;
            cout << "*****************************************************" << endl;
            int editField;
            cin >> editField;
            cin.ignore();

            switch (editField) {
            case 0:
                system("cls");
                returnToMainMenu("Would you like to return to the main menu?");

            case 1:
                cout << "Enter a new supplier: ";
                getline(cin, item.productName);
                break;
            case 2:
                cout << "Enter a new weight: ";
                cin >> item.weight;
                break;
            case 3:
                cout << "Enter new expiration date (MM-DD-YYYY): ";
                getline(cin, item.expirationDate);
                break;
            case 4:
                cout << "Enter new arrival date (MM-DD-YYYY): ";
                getline(cin, item.arrivedOn);
                break;
            case 5:
                cout << "Enter new quantity: ";
                cin >> item.quantity;
                break;
            case 6:
                cout << "Enter new product name: ";
                getline(cin, item.productName);
                break;
            default:
                cout << "Invalid field. No chages made.";
                return;
                returnToMainMenu("Would you like to return to the main menu?");
            }
            cout << "Item updated successfully!" << endl;
            displayItem(item);

            ofstream fout("../inventory.txt");
            if (!fout) {
                cout << "Error updating file" << endl;
                return;
                returnToMainMenu("Would you like to return to the main menu?");
            }
            for (const auto& updatedItem : inventory) {
                fout << updatedItem.orderNumber << " " << updatedItem.productName << " " << updatedItem.quantity << " "
                    << updatedItem.arrivedOn << " " << updatedItem.expirationDate << " " << updatedItem.weight << " "
                    << updatedItem.supplier << endl;
            }
            fout.close();
            break;
            system("cls");
            cout << "Inventory file updated. Returning to main menu." << endl;
            mainmenu();
        }
    }
    if (!found) {
        cout << "No item found with that order number." << endl;
        cout << "Would you like to edit another entry?" << endl;
        cout << "Yes (1)" << endl;
        cout << "No  (0)" << endl;
        int choice;
        cin >> choice;
        if (choice == 1) {
            system("cls");
            editData(inventory);
        }
        if (choice == 0) {
            system("cls");
            cout << "Returning to main menu." << endl;
            mainmenu();
        }
        else {
            system("cls");
            cout << "Invalid selection. Returning to edit section." << endl;
            editData(inventory);
        }
    }
}

//main menu function where users can select different options
void mainmenu() {
    vector<InventoryItems> inventory;
    loadData(inventory);

    int input;

    cout << "***************************************************" << endl;
    cout << "*Welcome to the Hotdog Inventory Management System*" << endl;
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
    case 5:
        enterData(inventory);
        break;
    case 4:
        removeItem(inventory);
        break;
    case 3:
        editData(inventory);
        break;
    case 2:
        searchItem(inventory);
        break;
    case 1:
        reportMenu(inventory);
        break;
    case 0:
        quitFunction("Are you sure you would you like to quit?");
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
