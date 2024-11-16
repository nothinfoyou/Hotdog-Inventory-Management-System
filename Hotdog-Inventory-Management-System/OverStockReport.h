#ifndef OVERSTOCKREPORT_H
#define OVERSTOCKREPORT_H

#include "BaseReport.h"
/*  This class is a child class of BaseReport
*       and is used to show items that exist within the store's inventory that are over stocked
*   Sean Armstrong 901 81 1616
*/
class OverStockReport : public BaseReport {
public:
    OverStockReport(int highThreshold);
    void generateReport() const;

private:
    int highThreshold_;
};

#endif