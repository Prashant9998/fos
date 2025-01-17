#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <iomanip>
#include <fstream>
#include <algorithm>

using namespace std;

// Define a class to represent a menu item
class MenuItem {
public:
    string name;
    double price;

    MenuItem(string n, double p) : name(std::move(n)), price(p) {}

    bool operator<(const MenuItem& other) const {
        return price < other.price; // Sort by price
    }
};

// Define a class to represent the food ordering system
class FoodOrderingSystem {
private:
    vector<MenuItem> menu;
    vector<MenuItem> order;

public:
    // Constructor to initialize the menu
    FoodOrderingSystem() {
        loadMenuFromFile("menu.txt"); // Load menu from a file
    }

    // Function to load menu items from a file
    void loadMenuFromFile(const string& filename) {
        ifstream file(filename);
        if (file.is_open()) {
            string name;
            double price;
            while (file >> ws && getline(file, name, ',') && file >> price) {
                menu.emplace_back(name, price);
            }
            file.close();
        } else {
            // Fallback: Default menu
            menu.push_back(MenuItem("Burger", 199.99));
            menu.push_back(MenuItem("Pizza", 159.99));
            menu.push_back(MenuItem("Pasta", 149.99));
            menu.push_back(MenuItem("Salad", 59.99));
            menu.push_back(MenuItem("Soda", 49.99));
        }
    }

    // Function to display the menu
    void displayMenu() const {
        cout << "\nMenu:\n";
        cout << left << setw(4) << "No" << setw(20) << "Item" << setw(10) << "Price" << endl;
        cout << string(34, '-') << endl;
        for (size_t i = 0; i < menu.size(); ++i) {
            cout << left << setw(4) << i + 1 << setw(20) << menu[i].name 
                 << "$" << fixed << setprecision(2) << menu[i].price << endl;
        }
    }

    // Function to sort the menu
    void sortMenu() {
        cout << "Sort menu by:\n1. Name\n2. Price\nChoice: ";
        int choice;
        cin >> choice;
        if (choice == 1) {
            sort(menu.begin(), menu.end(), [](const MenuItem& a, const MenuItem& b) {
                return a.name < b.name;
            });
        } else if (choice == 2) {
            sort(menu.begin(), menu.end());
        } else {
            cout << "Invalid choice. Sorting by price by default.\n";
            sort(menu.begin(), menu.end());
        }
        cout << "Menu sorted.\n";
    }

    // Function to take the order
    void takeOrder() {
        int choice;
        cout << "\nEnter the number of the item you want to order (0 to finish):\n";
        while (true) {
            cout << "> ";
            cin >> choice;

            // Validate input
            if (cin.fail() || choice < 0 || choice > static_cast<int>(menu.size())) {
                cin.clear(); // Clear error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                cout << "Invalid input. Please enter a valid number.\n";
                continue;
            }

            if (choice == 0) break;

            order.push_back(menu[choice - 1]);
            cout << "Added " << menu[choice - 1].name << " to your order.\n";
        }
    }

    // Function to display the order and calculate the total
    void displayOrder() const {
        double total = 0;
        cout << "\nYour order:\n";
        if (order.empty()) {
            cout << "No items ordered.\n";
            return;
        }

        cout << left << setw(20) << "Item" << setw(10) << "Price" << endl;
        cout << string(30, '-') << endl;
        for (const auto& item : order) {
            cout << left << setw(20) << item.name 
                 << "$" << fixed << setprecision(2) << item.price << endl;
            total += item.price;
        }
        cout << string(30, '-') << endl;
        cout << left << setw(20) << "Total" 
             << "$" << fixed << setprecision(2) << total << endl;
    }

    // Function to add a new item to the menu
    void addMenuItem() {
        string name;
        double price;
        cout << "\nEnter the name of the new item: ";
        cin.ignore(); // Clear buffer
        getline(cin, name);
        cout << "Enter the price of the item: ";
        cin >> price;
        menu.emplace_back(name, price);
        cout << "Item added to the menu.\n";
    }

    // Function to remove an item from the menu
    void removeMenuItem() {
        int choice;
        displayMenu();
        cout << "\nEnter the number of the item to remove: ";
        cin >> choice;

        if (choice > 0 && choice <= static_cast<int>(menu.size())) {
            cout << "Removed " << menu[choice - 1].name << " from the menu.\n";
            menu.erase(menu.begin() + (choice - 1));
        } else {
            cout << "Invalid choice.\n";
        }
    }
};

int main() {
    FoodOrderingSystem system;

    while (true) {
        cout << "\nFood Ordering System\n";
        cout << "1. Display Menu\n2. Take Order\n3. Display Order\n4. Add Menu Item\n5. Remove Menu Item\n6. Sort Menu\n7. Exit\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                system.displayMenu();
                break;
            case 2:
                system.takeOrder();
                break;
            case 3:
                system.displayOrder();
                break;
            case 4:
                system.addMenuItem();
                break;
            case 5:
                system.removeMenuItem();
                break;
            case 6:
                system.sortMenu();
                break;
            case 7:
                cout << "Exiting. Thank you!\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}
