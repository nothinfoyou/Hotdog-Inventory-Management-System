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

    struct tm expDate;
    localtime_s(&expDate, &timestamp);

    char output[50];
    strftime(output, 50, "%m/%d/%Y", &expDate);

    istringstream ss(expirationDate);

    ss >> std::get_time(&expDate, "%m/%d/%Y");
    
    __time64_t expirationTime = mktime(&expDate);

    __time64_t currentTime = time(nullptr);

    return expirationTime < currentTime;
}

// this func iterates through each item and prints out the item description if it is expired
void ExpiredReport::generateReport() const {
    std::cout << "----- Expired Inventory Report -----\n";
    for (const auto& item : getData()) {
        if (isExpired(item.expirationDate)) {
            std::cout << "Order Number: " << item.orderNumber << std::endl;
            std::cout << "Product Name: " << item.productName << std::endl;
            std::cout << "Quantity: " << item.quantity << std::endl;
            //std::cout << "Arrived On: " << item.arrivedOn << std::endl;
            std::cout << "Expiration Date: " << item.expirationDate << std::endl;
            //std::cout << "Weight: " << item.weight << " kg" << std::endl;
            //std::cout << "Supplier: " << item.supplier << std::endl;
            std::cout << "---------------------------\n";
        }
    }
}