#include <iostream>
using namespace std;

#include "ProductDatabase.h"
int main()
{
    ProductDatabase *PD = new ProductDatabase();

    while (true)
    {
        cout << "Enter A Command: " << endl;
        string command;
        cin >> command;
        if (command == "save_product")
        {
            string productId;
            cin >> productId;
            string productName;
            cin >> productName;
            int productPrice;
            cin >> productPrice;
            PD->saveProduct(productId, productName, productPrice);
        }
        if (command == "purchase_product")
        {
            string productId;
            cin >> productId;
            int priceQuantity;
            cin >> priceQuantity;
            int productPrice;
            cin >> productPrice;
            PD->purchaseProduct(productId, priceQuantity, productPrice);
        }
        if (command == "order_product")
        {
            string productId;
            cin >> productId;
            int quantity;
            cin >> quantity;

            PD->orderProduct(productId, quantity);
        }
        if (command == "get_quantity_of_product")
        {
            string productId;
            cin >> productId;
            cout << PD->getQuantityOfProduct(productId) << endl;
        }
        if (command == "get_average_price")
        {
            string productId;
            cin >> productId;
            cout << PD->getAveragePrice(productId) << endl;
        }
        if (command == "get_product_profit")
        {
            string productId;
            cin >> productId;
           cout <<  PD->getProductProfit(productId) << endl;
        }
        if (command == "get_fewest_product")
        {
            cout << PD->getFewestProduct() << endl;

        }
        if(command=="export")
        {
            string path;
            cin >> path;
            PD->exportOrders(path);
        }
        if (command == "get_most_popular_product") { cout << PD->getMostPopularProduct() << endl; }
        if(command =="exit") exit(0);
    }
}