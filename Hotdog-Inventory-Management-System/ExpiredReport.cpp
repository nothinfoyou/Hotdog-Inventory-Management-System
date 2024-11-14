//#include "ExpiredReport.h"
//#include <iostream>
//#include <ctime>
//
//bool ExpiredReport::isExpired(const std::string& expirationDate) const {
//    // Convert expiration date to time_t for comparison
//    struct tm expDate = {};
//    strptime(expirationDate.c_str(), "%Y-%m-%d", &expDate);
//    time_t expirationTime = mktime(&expDate);
//
//    // Get current time
//    time_t currentTime = time(nullptr);
//
//    // If expiration time is earlier than the current time, it's expired
//    return expirationTime < currentTime;
//}
//
//void ExpiredReport::generateReport() const {
//    std::cout << "----- Expired Inventory Report -----\n";
//    for (const auto& item : data_) {
//        if (isExpired(item.expirationDate)) {
//            // Only display the items that are expired
//            std::cout << "Order Number: " << item.orderNumber << std::endl;
//            std::cout << "Product Name: " << item.productName << std::endl;
//            std::cout << "Quantity: " << item.quantity << std::endl;
//            std::cout << "Arrived On: " << item.arrivedOn << std::endl;
//            std::cout << "Expiration Date: " << item.expirationDate << std::endl;
//            std::cout << "Weight: " << item.weight << " kg" << std::endl;
//            std::cout << "Supplier: " << item.supplier << std::endl;
//            std::cout << "---------------------------\n";
//        }
//    }
//}
