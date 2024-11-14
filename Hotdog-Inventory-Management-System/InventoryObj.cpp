#ifndef INVENTORYITEMS_H
#define INVENTORYITEMS_H

#include <string>
#include <iomanip>
using std::string;

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