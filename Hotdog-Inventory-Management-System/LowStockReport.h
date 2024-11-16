#ifndef LOWSTOCKREPORT_H
#define LOWSTOCKREPORT_H

#include "BaseReport.h"
/*  This class is a child class of BaseReport
*       and is used to show items that exist within the store's inventory that are under stocked
*   Sean Armstrong 901 81 1616
*/
class LowStockReport : public BaseReport {
public:
    LowStockReport(int lowThreshold);
    void generateReport() const;

private:
    int lowThreshold_;
};

#endif