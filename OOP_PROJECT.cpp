#include <iostream>
#include <string>
using namespace std;

class Product {
public:
    int id, stock;
    string name;
    float price;

    void getProduct(int i) {
        id = i;

        if (i == 101) {
            name = "Rice";
            price = 60;
            stock = 50;
        }
        else if (i == 102) {
            name = "Sugar";
            price = 45;
            stock = 40;
        }
        else if (i == 103) {
            name = "Bulb";
            price = 120;
            stock = 20;
        }
        else {
            id = -1;
        }
    }
};

class Grocery : public Product {
public:
    float discount() { return 5; }
};

class Electronics : public Product {
public:
    float discount() { return 10; }
};

int main() {
    int id, qty;
    float total, grandTotal = 0;
    char choice;

    cout << "===== SHOP COUNTER MANAGEMENT =====\n";
    cout << "101 - Rice | 102 - Sugar | 103 - Bulb\n";

    do {
        cout << "\nEnter Product ID: ";
        cin >> id;

        Product p;
        p.getProduct(id);

        if (p.id == -1) {
            cout << "Product not found!\n";
        }
        else {
            cout << "Product: " << p.name << endl;
            cout << "Price: Rs." << p.price << endl;
            cout << "Enter Quantity: ";
            cin >> qty;

            if (qty <= 0 || qty > p.stock) {
                cout << "Invalid quantity or insufficient stock!\n";
            }
            else {
                float discount;

                if (id == 103) {
                    Electronics e;
                    discount = e.discount();
                }
                else {
                    Grocery g;
                    discount = g.discount();
                }

                total = p.price * qty;
                float finalAmount = total - total * discount / 100;
                grandTotal += finalAmount;

                cout << "Amount: Rs." << total << endl;
                cout << "Discount: " << discount << "%\n";
                cout << "Item Total: Rs." << finalAmount << endl;
            }
        }

        cout << "\nAdd another product? (y/n): ";
        cin >> choice;

    } while (choice == 'y' || choice == 'Y');

    cout << "\n========== FINAL BILL ==========\n";
    cout << "Grand Total: Rs." << grandTotal << endl;
    cout << "================================\n";
    cout << "Thank you for shopping!\n";

    return 0;
}
