#include "BaseReport.h"
/*  This class is used to build a BaseReport
*       that is then used in child classes to build a more narrowed final report
*   Sean Armstrong 901 81 1616
*/
// this func adds a "item" to the collection
void BaseReport::addData(const InventoryItems& item) {
    data_.push_back(item); 
}

// this func prints a basic report consisting of all items
void BaseReport::generateReport() const {
    std::cout << "----- Inventory Report -----\n";
    for (const auto& item : data_) {
        std::cout << "Order Number: " << item.orderNumber << std::endl;
        std::cout << "Product Name: " << item.productName << std::endl;
        std::cout << "Quantity: " << item.quantity << std::endl;
        std::cout << "Arrived On: " << item.arrivedOn << std::endl;
        std::cout << "Expiration Date: " << item.expirationDate << std::endl;
        std::cout << "Weight: " << item.weight << " kg" << std::endl;
        std::cout << "Supplier: " << item.supplier << std::endl;
        std::cout << "---------------------------\n";
    }
}