#ifndef INVENTORYITEMS_H
#define INVENTORYITEMS_H

#include <string>
#include <iomanip>
using std::string;
/*  This struct was moved to its own file to better let it be used in other classes/files
*   Sean Armstrong 901 81 1616
*/
struct InventoryItems {
    int orderNumber;
    string productName;
    int quantity;
    string arrivedOn;
    string expirationDate;
    double weight;
    string supplier;
};

#endif