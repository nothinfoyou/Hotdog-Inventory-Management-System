#ifndef BaseReport_h
#define BaseReport_H

#include <vector>
#include <string>
#include <iostream>
#include "InventoryObj.cpp"
/*  This class is used to build a BaseReport 
*       that is then used in child classes to build a more narrowed final report
*   Sean Armstrong 901 81 1616
*/
class BaseReport {
public:
    void addData(const InventoryItems& item);
    void generateReport() const;
    const std::vector<InventoryItems>& getData() const { return data_; }

protected:
    std::vector<InventoryItems> data_;
};

#endif
