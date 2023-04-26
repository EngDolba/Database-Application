/*******************************************************
 * File: ProductDatabase.h
 *
 * Console-Based Application for Europebet.
 */
#pragma once

#include <string>
#include <map>

#include <vector>

using namespace std;

/* A class representing a ecommerce app logic.
 */
class ProductDatabase {
public:
    /* Constructs a new, empty priority queue backed by a doubly-linked list. */
    ProductDatabase();

    /* Cleans up all memory allocated by this priority queue. */
    ~ProductDatabase();

    /* Add a new product to the catalog or modify an existing one. */
    void saveProduct(const string &productID, string productName, int productPrice);

    /*Purchase a product, increasing its balance based on the specified quantity.*/
    void purchaseProduct(string productID, int quantity, double price);

    /* Return the remaining quantity of a specific product. */
    int getQuantityOfProduct(string productID);

    /*Place an order for the product, decreasing its balance according to the specified quantity.*/
    void orderProduct(string productID, int quantity);

    /*
        Calculate and display the average price of a specific product
        based on its purchase history. Scenario: You purchased 10 phone001 for 2000 and later
        purchased 30 more phone001 for 3000. The average price of phone001 is 2750 based on the
        purchase history.
     */
    double getAveragePrice(string productId);

    /* 
        Calculate and display the profit earned from a specific product
        by comparing the average purchase price with the average order price. Scenario: Scenario: You
        purchased 10 phones for 2000 and later purchased 30 more phones for 3000. Then, you sold 5
        phones for 3500, 10 phones for 3800, and 15 phones for 4000. Average purchase price – 2750;
        average order price – 4500; profit per unit – 1750; total profit - 52500.
     */
    double getProductProfit(string product_id);

    /*
        Return the name of the product with the lowest remaining quantity.
    */
    string getFewestProduct();

    /* */
    void printOrders();

    /* exports CSV-type orders to specified filepath */
    void exportOrders(string filepath);

    /*
     get_most_popular_product: Return the name of the product with the highest number of
     orders.
    */
    string getMostPopularProduct();


private:
    struct product {
        string id;
        string name;
        double price;
        int balance;
        int soldNumber;
        map<double, int> purchasedPrices;
        map<double, int> soldPrices;
    };
    struct order {
        string productID;
        string productName;
        int quantity;
        double COGS;
        double sellingPrice;
    };
    map<string, product> products;
    vector<order> orders;

    double calculateAverageSoldPrice(const string &product_id);

    string mapToString();

    string mapToString(const map<double, int> &m);

    void generateOrder(const string &productID, int quantity, const product &a, double price);


};