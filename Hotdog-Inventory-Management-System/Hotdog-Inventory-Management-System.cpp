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
void quitFunction(string dispArg);
void loadData(vector<InventoryItems>& inventory);
void displayItem(const InventoryItems& item);
void searchItem(const vector<InventoryItems>& inventory);
void enterData(vector<InventoryItems>& inventory);
void removeItem(vector<InventoryItems>& inventory);
void editData(vector<InventoryItems>& inventory);

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

void enterData(vector<InventoryItems>& inventory) {
    InventoryItems newItem;
    cout << "Please enter the new item's order number: ";
    cin >> newItem.orderNumber;
    cin.ignore();

    cout << "Please enter the product name of the new item (case specific): ";
    getline(cin, newItem.productName);

    cout << "Enter quantity: ";
    cin >> newItem.quantity;
    cin.ignore();

    cout << "Enter the arrival date of the new item in the format MM-DD-YYYY: ";
    getline(cin, newItem.arrivedOn);

    cout << "Enter the expiration date of the new item: ";
    getline(cin, newItem.expirationDate);

    cout << "Enter the weight of the new item in lbs: ";
    cin >> newItem.weight;
    cin.ignore();

    cout << "Enter supplier: ";
    getline(cin, newItem.supplier);

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
}

void removeItem(vector<InventoryItems>& inventory) {
    if (inventory.empty()) {
        cout << "No inventory items to remove." << endl;
        return;
    }
    int orderNumber;
    cout << "Enter the order number of the item you would like to remove: ";
    cin >> orderNumber;

    bool found = false;
    for (size_t i = 0; i < inventory.size(); ++i) {
        if (inventory[i].orderNumber == orderNumber) {
            found = true;
            cout << "Are you sure you want to remove this item?" << endl;
            displayItem(inventory[i]);
            cout << "Yes (1) / No (0): ";
            int confirm;
            cin >> confirm;
            if (confirm == 1) {
                inventory.erase(inventory.begin() + i);
                cout << "Item removed from inventory." << endl;

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
                cout << "Inventory file updated." << endl;
            }
            else {
                cout << "Item was not removed." << endl;
            }
            break;
        }
    }
    if (!found) {
        cout << "No item found with that order number." << endl;
    }
}

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
}

void editData(vector<InventoryItems>& inventory) {
    if (inventory.empty()) {
        cout << "No inventory items to edit" << endl;
        return;
    }
    int getOrderNumber;
    cout << "Enter the order number of the item you would like to edit: ";
    cin >> getOrderNumber;

    bool found = false;
    for (auto& item : inventory) {
        if (item.orderNumber == getOrderNumber) {
            found = true;
            cout << "*****************************************************" << endl;
            cout << "*Item Found!                                        *" << endl;
            cout << "*Which field would you like to edit?                *" << endl;
            cout << "*Product Name   (5)                                 *" << endl;
            cout << "*Quantity       (4)                                 *" << endl;
            cout << "*Arrived On     (3)                                 *" << endl;
            cout << "*Expiration Date(2)                                 *" << endl;
            cout << "*Weight         (1)                                 *" << endl;
            cout << "*Supplier       (0)                                 *" << endl;
            cout << "Enter your selection:                               *" << endl;
            cout << "*****************************************************" << endl;
            int field;
            cin >> field;
            cin.ignore();

            switch (field) {
            case 0:
                cout << "Enter a new supplier: ";
                getline(cin, item.productName);
                break;
            case 1:
                cout << "Enter a new weight: ";
                cin >> item.weight;
                break;
            case 2:
                cout << "Enter new expiration date (MM-DD-YYYY): ";
                getline(cin, item.expirationDate);
                break;
            case 3:
                cout << "Enter new arrival date (MM-DD-YYYY): ";
                getline(cin, item.arrivedOn);
                break;
            case 4:
                cout << "Enter new quantity: ";
                cin >> item.quantity;
                break;
            case 5:
                cout << "Enter new product name: ";
                getline(cin, item.productName);
                break;
            default:
                cout << "Invalid field. No chages made.";
                return;
            }
            cout << "Item updated successfully!" << endl;
            displayItem(item);

            ofstream fout("../inventory.txt");
            if (!fout) {
                cout << "Error updating file" << endl;
                return;
            }
            for (const auto& updatedItem : inventory) {
                fout << updatedItem.orderNumber << " " << updatedItem.productName << " " << updatedItem.quantity << " "
                    << updatedItem.arrivedOn << " " << updatedItem.expirationDate << " " << updatedItem.weight << " "
                    << updatedItem.supplier << endl;
            }
            fout.close();
            cout << "Inventory file updated" << endl;
            break;
        }
    }
    if (!found) {
        cout << "No item found with that order number" << endl;
        cout << "Would you like to edit another entry?" << endl;
        cout << "Yes (1)" << endl;
        cout << "No  (0)" << endl;
        int choice;
        cin >> choice;
        if (choice == 1) {
            system("cls");
            editData(inventory);
        }
    }
}

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
        cout << "Report Section" << endl;
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
