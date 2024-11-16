#include "OverStockReport.h"
#include <iostream>
using namespace std;
/*  This class is a child class of BaseReport
*       and is used to show items that exist within the store's inventory that are over stocked
*   Sean Armstrong 901 81 1616
*/
OverStockReport::OverStockReport(int highThreshold)
    : highThreshold_(highThreshold) {}

// this func checks for over stocked items
void OverStockReport::generateReport() const {

    cout << "***************************************************" << endl;
    cout << "* Over Stock Report" << endl;
    cout << "*--------------------------------------------------" << endl;

    bool foundAny = false;

    for (const auto& item : data_) {
        if (item.quantity > highThreshold_) {
            cout << "* High Quantity: " << item.productName << " - Quantity: " << item.quantity << endl;
            foundAny = true;
        }
    }

    cout << "***************************************************" << endl;

    if (!foundAny) {
        system("cls");
        cout << "No items in inventory are currently overstocked." << endl;
    }
}
