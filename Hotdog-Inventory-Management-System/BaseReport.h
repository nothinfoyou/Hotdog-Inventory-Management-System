#ifndef BaseReport_h
#define BaseReport_H

#include <vector>
#include <string>
#include <iostream>
#include "InventoryObj.cpp"

class BaseReport {
public:
    // Function to add an inventory item to the report
    void addData(const InventoryItems& item);

    // Function to generate and display the report
    void generateReport() const;
private:
    std::vector<InventoryItems> data_;  // Vector to store the inventory items
};

#endif
