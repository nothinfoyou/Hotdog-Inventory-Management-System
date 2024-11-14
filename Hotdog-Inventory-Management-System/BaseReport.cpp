#include "BaseReport.h"

// Add an inventory item to the report
void BaseReport::addData(const InventoryItems& item) {
    data_.push_back(item);  // Push the inventory item to the vector
}

// Generate and print the report
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