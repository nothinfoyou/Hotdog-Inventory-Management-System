#ifndef EXPIREDREPORT_H
#define EXPIREDREPORT_H

#include "BaseReport.h"
/*  This class is a child class of BaseReport
*       and is used to show expired items that exist within the store's inventory
*   Sean Armstrong 901 81 1616
*/
class ExpiredReport : public BaseReport {
public:
    void generateReport() const;
private:
    bool isExpired(const std::string& expirationDate) const;
};

#endif 
