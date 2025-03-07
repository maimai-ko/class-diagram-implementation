#include <iostream>
#include <vector>
#include <iomanip>
#include <math.h>
using namespace std;

int getValidInput(int min, int max)
{
    int value;
    while (true)
    {
        cin >> value;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number between " << min << " and " << max << ": ";
        }
        else if (value < min || value > max)
        {
            cout << "Invalid input! Please enter a number between " << min << " and " << max << ": ";
        }
        else
        {
            break;
        }
    }
    return value;
}

class Product
{
public:
    int productId;
    string productName;
    double productPrice;
    int stockQuantity;

    Product(int id, string name, double price, int stock)
        : productId(id), productName(name), productPrice(price), stockQuantity(stock) {}
};

class ShoppingCart
{
public:
    vector<pair<Product, int>> cart;
    double totalAmount = 0;

    void addProductToCart(Product product)
    {
        for (auto &item : cart)
        {
            if (item.first.productId == product.productId)
            {
                item.second++;
                calculateTotalAmount();
                return;
            }
        }
        cart.push_back({product, 1});
        calculateTotalAmount();
    }

    void displayCart()
    {
        cout << "\nShopping Cart:\n";
        cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(10) << "Price" << "Quantity\n";
        for (auto &item : cart)
        {
            cout << setw(10) << item.first.productId << setw(20) << item.first.productName << "$" << setw(10) << item.first.productPrice << item.second << "\n";
        }
        cout << "Total: $" << totalAmount << "\n";
    }

    void calculateTotalAmount()
    {
        totalAmount = 0;
        for (auto &item : cart)
        {
            totalAmount += item.first.productPrice * item.second;
        }
    }
};

class Order
{
public:
    int orderId;
    ShoppingCart shoppingCart;
    string status;
    string orderDate;

    Order(int id, ShoppingCart cart, string date)
        : orderId(id), shoppingCart(cart), status("Placed"), orderDate(date) {}

    void displayOrder()
    {
        cout << "\nOrder ID: " << orderId << "\n";
        cout << "Total Amount: " << shoppingCart.totalAmount << "\n";
        cout << "Order Details:\n";
        cout << left << setw(15) << "Product ID" << setw(20) << "Name" << setw(10) << "Price" << "Quantity\n";
        for (auto &item : shoppingCart.cart)
        {
            cout << setw(15) << item.first.productId << setw(20) << item.first.productName << "$" << setw(10) << item.first.productPrice << item.second << "\n";
        }
    }
};

vector<Product> products = {
    {1, "Laptop", 999.99, 10},
    {2, "Smartphone", 499.99, 20},
    {3, "Headphones", 79.99, 30},
    {4, "Mouse", 29.99, 50},
    {5, "Keyboard", 49.99, 40}};

ShoppingCart userCart;
vector<Order> orders;
int orderCounter = 1;

void viewProducts()
{
    cout << "\nAvailable Products:\n";
    cout << left << setw(10) << "ID" << setw(20) << "Name" << "Price\n";
    for (auto &product : products)
    {
        cout << setw(10) << product.productId << setw(20) << product.productName << "$" << product.productPrice << "\n";
    }

    while (true)
    {
        int choice;
        cout << "Enter Product ID to add to cart (0 to return): ";
        choice = getValidInput(0, 5);
        if (choice == 0)
            break;
        bool found = false;
        for (auto &product : products)
        {
            if (product.productId == choice)
            {
                userCart.addProductToCart(product);
                cout << "Product added successfully!\n";
                found = true;
                break;
            }
        }
        if (!found)
            cout << "Invalid Product ID. Try again.\n";
    }
}

void viewCart()
{
    userCart.displayCart();
    char choice;
    cout << "Do you want to checkout? (Y/N): ";
    cin >> choice;
    if (choice == 'Y' || choice == 'y')
    {
        orders.push_back(Order(orderCounter++, userCart, "2025-03-01"));
        cout << "You have successfully checked out the products!\n";
        userCart = ShoppingCart();
    }
    else
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input! ";
    }
}

void viewOrders()
{
    cout << "\nOrders:\n";
    for (auto &order : orders)
    {
        order.displayOrder();
    }
}

int main()
{
    while (true)
    {
        cout << "\nMenu:\n";
        cout << "1. View Products\n";
        cout << "2. View Shopping Cart\n";
        cout << "3. View Orders\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        int choice;
        choice = getValidInput(1, 4);
        switch (choice)
        {
        case 1:
            viewProducts();
            break;
        case 2:
            viewCart();
            break;
        case 3:
            viewOrders();
            break;
        case 4:
            cout << "Exiting...\n";
            return 0;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    }
}
