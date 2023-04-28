#include "ProductDatabase.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>


#ifndef NDEBUG
#define DBGPRINT cout << ProductDatabase::mapToString() << endl;
#else
#define DBGPRINT
#endif

ProductDatabase::ProductDatabase() = default;

ProductDatabase::~ProductDatabase() = default;

void ProductDatabase::saveProduct(const string &productID, string productName, double productPrice)
{
    if (productPrice <= 0)
    {
        cout << "COMMAND TERMINATED: INVALID PRICE" << endl;
        return;
    }
    if (products.count(productID) == 0)
    {

        product a;
        a.id = productID;
        a.balance = 0;
        a.price = productPrice;
        a.soldNumber = 0;
        a.name = productName;
        products.insert(make_pair(productID, a));
    }
    else
    {
        product a = products[productID];
        a.name = productName;
        a.price = productPrice;
        products[productID] = a;
    }
    DBGPRINT;
}

void ProductDatabase::purchaseProduct(string productID, int quantity, double price)
{
    if (products.count(productID) == 0)
    {
        cout << "COMMAND TERMINATED: INVALID ID" << endl;
        return;
    }
    if (quantity <= 0)
    {
        cout << "COMMAND TERMINATED: INVALID QUANTITY" << endl;
        return;
    }
    if (price <= 0)
    {
        cout << "COMMAND TERMINATED: INVALID PRICE" << endl;
        return;
    }
    product a = products[productID];
    a.balance += quantity;
    if (a.purchasedPrices.count(price) == 0)
    {
        a.purchasedPrices.insert(make_pair(price, quantity));
    }
    else
    {
        a.purchasedPrices[price] += quantity;
    }
    products[productID] = a;
    DBGPRINT;
}

void ProductDatabase::orderProduct(string productID, int quantity)
{
    if (products.count(productID) == 0)
    {
        cout << "COMMAND TERMINATED: INVALID ID" << endl;
        return;
    }
    if (quantity <= 0)
    {
        cout << "COMMAND TERMINATED: INVALID QUANTITY" << endl;
        return;
    }
    product a = products[productID];
    if (quantity > a.balance)
    {
        cout << "COMMAND TERMINATED: NOT ENOUGH BALANCE" << endl;
        return;
    }
    double price = products[productID].price;
    if (a.soldPrices.count(price) == 0)
    {
        a.soldPrices.insert(make_pair(price, quantity));
    }
    else
    {
        a.soldPrices[price] += quantity;
    }
    a.balance -= quantity;
    a.soldNumber += quantity;
    products[productID] = a;
    generateOrder(productID, quantity, a, price);
    DBGPRINT;
}

void
ProductDatabase::generateOrder(const string &productID, int quantity, const ProductDatabase::product &a, double price)
{
    order b;
    b.quantity = quantity;
    b.productID = productID;
    b.productName = a.name;
    b.sellingPrice = a.price;
    b.COGS = price * quantity;
    orders.push_back(b);
}

int ProductDatabase::getQuantityOfProduct(string productID)
{
    if (products.count(productID) == 0)
    {
        cout << "COMMAND TERMINATED: INVALID ID" << endl;
        return -1;
    }
    return products[productID].balance;
}

double ProductDatabase::getAveragePrice(string productId)
{
    if (products.count(productId) == 0)
    {
        cout << "COMMAND TERMINATED: INVALID ID" << endl;
        return -1;
    }
    map<double, int>::iterator iter = products[productId].purchasedPrices.begin();
    double sum = 0;
    int count = 0;
    for (iter; iter != products[productId].purchasedPrices.end(); iter++)
    {
        sum += iter->second * iter->first;
        count += iter->second;
    }
    return sum / count;
}


double ProductDatabase::getProductProfit(string productId)
{
    if (products.count(productId) == 0)
    {
        cout << "COMMAND TERMINATED: INVALID ID" << endl;
        return -1;
    }
    double a = ProductDatabase::getAveragePrice(productId);
    double b = ProductDatabase::calculateAverageSoldPrice(productId);
    return products[productId].soldNumber * (b - a);
}

string ProductDatabase::getFewestProduct()
{
    map<string, product>::iterator iter = products.begin();
    int min = INT16_MAX;
    string maxId;
    if(products.empty()) return "we don't have any kind of product";
    for(iter; iter != products.end(); iter++)
    {
        product a = iter->second;
        if (a.balance < min)
        {
            min = a.balance;
            maxId = a.id;
        }
    }
   return products[maxId].name;
}

string ProductDatabase::getMostPopularProduct()
{
    map<string, product>::iterator iter = products.begin();
    int max = -1;
    if(products.empty()) return "we don't have any kind of product";
    string maxId;
    for (iter; iter != products.end(); iter++)
    {
        product a = iter->second;
        if (a.soldNumber > max)
        {
            max = a.soldNumber;
            maxId = a.id;
        }
    }
  return products[maxId].name;
}


double ProductDatabase::calculateAverageSoldPrice(const string &productId)
{
    if (products.count(productId) == 0)
    {
        cout << "COMMAND TERMINATED: INVALID ID" << endl;
        return -1;
    }
    map<double, int>::iterator iter = products[productId].soldPrices.begin();
    double sum = 0;
    int count = 0;
    for (iter; iter != products[productId].soldPrices.end(); iter++)
    {
        sum += iter->second * iter->first;
        count += iter->second;
    }
    return sum / count;

}


string ProductDatabase::mapToString()
{
    stringstream ss;
    ss << "{ ";
    for (const auto &kv: products)
    {
        ss << kv.first << ": {id: " << kv.second.id << ", name: " << kv.second.name << ", price: " << kv.second.price
           << ", balance: " << kv.second.balance << ", soldNumber: " << kv.second.soldNumber << ", purchasedPrices: "
           << mapToString(kv.second.purchasedPrices) << ", soldPrices: " << mapToString(kv.second.soldPrices) << "}, ";
    }
    ss.seekp(-2, ios_base::end); // remove the last ", "
    ss << " }";
    return ss.str();
}


string ProductDatabase::mapToString(const map<double, int> &m)
{
    stringstream ss;
    ss << "{ ";
    for (const auto &kv: m)
    {
        ss << kv.first << ": " << kv.second << ", ";
    }
    ss.seekp(-2, ios_base::end); // remove the last ", "
    ss << " }";
    return ss.str();
}

void ProductDatabase::exportOrders(string filePath)
{
    ofstream file(filePath);
    if (!file.is_open())
    {
        cout << "COMMAND TERMINATED: INVALID PATH" << endl;
        return;
    }

    file << "Quantity,ProductID,ProductName,SellingPrice,COGS\n";
    for (order order: orders)
    {
        file << order.quantity << "," << order.productID << "," << order.productName << "," << order.sellingPrice << ","
             << order.COGS << "\n";
    }
    file.close();
}

void ProductDatabase::printOrders()
{
    cout << left << setw(15) << "Product ID" << left << setw(25) << "Product Name" << left << setw(10) << "Quantity"
         << left << setw(10) << "COGS" << left << setw(15) << "Selling Price" << endl;
    cout << setfill('-') << setw(75) << "" << endl;
    cout << setfill(' ');
    for (auto o: orders)
    {
        cout << left << setw(15) << o.productID << left << setw(25) << o.productName << left << setw(10) << o.quantity
             << left << setw(10) << fixed << setprecision(2) << o.COGS << left << setw(15) << fixed << setprecision(2)
             << o.sellingPrice << endl;
    }
}



