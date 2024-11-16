#include "LowStockReport.h"
#include <iostream>
using namespace std;
/*  This class is a child class of BaseReport
*       and is used to show items that exist within the store's inventory that are under stocked
*   Sean Armstrong 901 81 1616
*/
LowStockReport::LowStockReport(int lowThreshold)
    : lowThreshold_(lowThreshold) {}

// this func checks for over stocked items
void LowStockReport::generateReport() const {
    cout << "***************************************************" << endl;
    cout << "* Low Stock Report" << endl;
    cout << "*--------------------------------------------------" << endl;

    bool foundAny = false;

    for (const auto& item : data_) {
        if (item.quantity < lowThreshold_) {
            cout << "* Low Quantity: " << item.productName << " - Quantity: " << item.quantity << endl;
            foundAny = true;
        }
    }

    cout << "***************************************************" << endl;

    if (!foundAny) {
        system("cls");
        cout << "No items in inventory are currently understocked." << endl;
    }
}
