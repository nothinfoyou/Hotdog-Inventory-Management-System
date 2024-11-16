#include "BaseReport.h"
using namespace std;
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

    cout << "***************************************************" << endl;
    cout << "* Inventory Report                                *" << endl;
    for (const auto& item : data_) {
        cout << "* Order Number: " << item.orderNumber << endl;
        cout << "* Product Name: " << item.productName << endl;
        cout << "* Quantity: " << item.quantity << endl;
        cout << "* Arrived On: " << item.arrivedOn << endl;
        cout << "* Expiration Date: " << item.expirationDate << endl;
        cout << "* Weight: " << item.weight << " kg" << endl;
        cout << "* Supplier: " << item.supplier << endl;
        cout << "*--------------------------------------------------" << endl;
    }
    cout << "***************************************************" << endl;
}