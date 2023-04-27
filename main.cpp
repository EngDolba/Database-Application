#include <iostream>

using namespace std;

#include "ProductDatabase.h"
#include <limits>

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
            double productPrice;
            cin >> productPrice;
            PD->saveProduct(productId, productName, productPrice);
        }
        else if (command == "purchase_product")
        {
            string productId;
            cin >> productId;
            int priceQuantity;
            cin >> priceQuantity;
            int productPrice;
            cin >> productPrice;
            PD->purchaseProduct(productId, priceQuantity, productPrice);
        }
        else if (command == "order_product")
        {
            string productId;
            cin >> productId;
            int quantity;
            cin >> quantity;

            PD->orderProduct(productId, quantity);
        }
        else if (command == "get_quantity_of_product")
        {
            string productId;
            cin >> productId;
            cout << PD->getQuantityOfProduct(productId) << endl;
        }
        else if (command == "get_average_price")
        {
            string productId;
            cin >> productId;
            cout << PD->getAveragePrice(productId) << endl;
        }
        else if (command == "get_product_profit")
        {
            string productId;
            cin >> productId;
            cout << PD->getProductProfit(productId) << endl;
        }
        else if (command == "get_fewest_product")
        {
            cout << PD->getFewestProduct() << endl;

        }
        else if (command == "generate_orders_report")
        {
            PD->printOrders();
        }
        else if (command == "export_orders_report")
        {
            string path;
            cin >> path;
            PD->exportOrders(path);
        }
        else if (command == "get_most_popular_product") { cout << PD->getMostPopularProduct() << endl; }
        else if (command == "exit") exit(0);
        else
        {
            cout << "COMMAND TERMINATED: COMMAND NON-EXISTENT" << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}