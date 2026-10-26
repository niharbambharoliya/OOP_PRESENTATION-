#include <iostream>
#include <vector>
#include <string>

using namespace std;

// ========================================================
// Base Class: Product (Abstract Class)
// ========================================================
class Product {
protected:
    int id;
    string name;
    double price;
    int stock;

public:
    // Constructor to initialize product details
    Product(int i, string n, double p, int s) {
        id = i;
        name = n;
        price = p;
        stock = s;
    }

    // Pure virtual function: Each product type must provide its own discount
    virtual double getDiscount() = 0;

    // Virtual function to display product information
    virtual void display() {
        cout << "ID: " << id
             << " | Name: " << name
             << " | Price: $" << price
             << " | Stock: " << stock
             << " | Discount: " << getDiscount() << "%"
             << endl;
    }

    // Virtual destructor for safe cleanup
    virtual ~Product() {}

    // Friend function: allows printBillLine to access protected members (name, price)
    friend void printBillLine(Product &p, int qty);
};

// ========================================================
// Derived Class: Grocery (Child of Product)
// ========================================================
class Grocery : public Product {
public:
    // Call the base class constructor
    Grocery(int i, string n, double p, int s)
        : Product(i, n, p, s) {}

    // Grocery has a 5% discount
    double getDiscount() override {
        return 5.0;
    }
};

// ========================================================
// Derived Class: Electronics (Child of Product)
// ========================================================
class Electronics : public Product {
public:
    // Call the base class constructor
    Electronics(int i, string n, double p, int s)
        : Product(i, n, p, s) {}

    // Electronics has a 10% discount
    double getDiscount() override {
        return 10.0;
    }
};

// ========================================================
// Friend Function: Calculates total and prints a bill line
// ========================================================
void printBillLine(Product &p, int qty) {
    double total = p.price * qty;
    double discount = total * (p.getDiscount() / 100.0);
    double finalAmount = total - discount;

    cout << p.name << "\t\t"
         << "$" << p.price << "\t"
         << qty << "\t"
         << p.getDiscount() << "%\t\t"
         << "$" << finalAmount << endl;
}

// ========================================================
// Main Function: Program execution starts here
// ========================================================
int main() {
    // Polymorphism: A vector of Product pointers holding different child objects
    vector<Product*> items;

    // Add items (Grocery and Electronics)
    items.push_back(new Grocery(1, "Rice", 60.0, 50));
    items.push_back(new Electronics(3, "Bulb", 120.0, 20));

    // 1. Display Product Catalog
    cout << "========================================" << endl;
    cout << "             PRODUCT CATALOG            " << endl;
    cout << "========================================" << endl;
    for (Product* p : items) {
        p->display(); // Calls the appropriate display() method
    }

    // 2. Print a Sample Bill
    cout << "\n========================================" << endl;
    cout << "               SAMPLE BILL              " << endl;
    cout << "========================================" << endl;
    cout << "Item\t\tPrice\tQty\tDiscount\tTotal" << endl;
    cout << "--------------------------------------------------------" << endl;

    printBillLine(*items[0], 2); // Buy 2 units of Rice
    printBillLine(*items[1], 3); // Buy 3 units of Bulb

    cout << "--------------------------------------------------------" << endl;

    // 3. Clean up allocated memory
    for (Product* p : items) {
        delete p;
    }
    items.clear();

    return 0;
}
