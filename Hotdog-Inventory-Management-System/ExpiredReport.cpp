#include "ExpiredReport.h"
#include <iostream>
#include <sstream>
#include <ctime>

using namespace std;
/*  This class is a child class of BaseReport
*       and is used to show expired items that exist within the store's inventory
*   Sean Armstrong 901 81 1616
*/

// this func takes the expiration date from an item, convert it to a localized time64 and compare it to the local current date to determine if the item is expired or not
// DEVNOTE: false = unexpired | true = expired
bool ExpiredReport::isExpired(const std::string& expirationDate) const {
    __time64_t timestamp = time(NULL);
    struct tm currentTime;
    gmtime_s(&currentTime, &timestamp);

    struct tm expDate = {}; 

    // parse expirationDate str into expDate obj
    std::istringstream ss(expirationDate);
    ss >> get_time(&expDate, "%m/%d/%Y");

    // converts expDate to UTC
    __time64_t expirationTime = mktime(&expDate);

    if (expirationTime == (time_t)-1) {
        return false;
    }

    // gets current time in UTC
    __time64_t currentTime_t = mktime(&currentTime);

    if (currentTime_t == (time_t)-1) {
        return false;
    }

    return expirationTime < currentTime_t;
}

// this func iterates through each item and prints out the item description if it is expired
void ExpiredReport::generateReport() const {

    cout << "***************************************************" << endl;
    cout << "* Expired Inventory Report                        *" << endl;
    for (const auto& item : getData()) {
        if (isExpired(item.expirationDate)) {
            cout << "* Order Number: " << item.orderNumber << std::endl;
            cout << "* Product Name: " << item.productName << std::endl;
            cout << "* Quantity: " << item.quantity << std::endl;
            cout << "* Expiration Date: " << item.expirationDate << std::endl;
            cout << "*--------------------------------------------------" << endl;
        }
    }
    cout << "***************************************************" << endl;
}