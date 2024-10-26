// InventoryInq.cpp
// Taha Zeeshan

#include <iostream>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <string>
#include <ctime>  // For getting the current date

using namespace std;

// Function prototypes
void alphamenu();
void programGreeting();
void validChoice(char& choice);
void validValues(float& value);
void addInventory(float **inventory, int inventorySize);
void editInventory(float **inventory, int inventorySize);
void showInventory(float **inventory, int inventorySize);

// Date class
class date {
    int month; // variable for month
    int day;   // variable for day
    int year;  // variable for year
public:
    // Default constructor: initializes with the current date
    date() {
        time_t now = time(0);
        tm *ltm = localtime(&now);
        month = 1 + ltm->tm_mon;
        day = ltm->tm_mday;
        year = 1900 + ltm->tm_year;
    }

    // Constructor with parameters for custom date (optional)
    date(int m, int d, int y) : month(m), day(d), year(y) {}

    // Overload operator <<
    friend ostream& operator<<(ostream& result, const date& dte) {
        result << dte.month << '/' << dte.day << '/' << dte.year;
        return result;
    }

    // Overload operator >>
    friend istream &operator>>(istream& input, date& dte) {
        cout << "Enter month: ";
        input >> dte.month;
        cout << "Enter day: ";
        input >> dte.day;
        cout << "Enter year: ";
        input >> dte.year;
        return input;
    }

    // ComponentTest method in Date
    void selfTest() {
        cout << "Date set is: " << month << "/" << day << "/" << year << endl;
    }
};

int main() {
    char choice;
    int inventorySize = 0;
    const int x = 4;
    float **inventory = nullptr;
    bool runProgram = true;

    // Dynamic Array
    inventory = new float * [x];
    for (int i = 0; i < x; i++) {
        inventory[i] = new float[inventorySize];
    }

    // Program greeting
    programGreeting();

    // Initialize date with the current date
    date today;

    // Display the current date without user input
    cout << "Today's date is: " << today << endl;

    today.selfTest();

    cout << endl;

    // Main program loop
    while (runProgram) {
        alphamenu();
        // menu Input Validation
        validChoice(choice);

        if (choice == 'A') {
            // Resize Array - add to end
            inventorySize += 1;
            addInventory(inventory, inventorySize);
        }
        if (choice == 'D') {
            // Resize Array - subtract from end
            inventorySize -= 1;
        }
        if (choice == 'E') {
            // Edit Inventory
            editInventory(inventory, inventorySize);
        }
        if (choice == 'S') {
            // Displays the inventory
            showInventory(inventory, inventorySize);
        }
        if (choice == 'Q') {
            runProgram = false;
        }
    }

    cout << "Thanks for using my program!" << endl;

    return 0;
}

// Greeting function
void programGreeting() {
    cout << "Welcome to the inventory inquisitor\n";
    cout << "by Taha Zeeshan\n";
    cout << "March 13, 2022\n";
}

// Menu function
void alphamenu() {
    cout << endl;
    cout << "<A>dd Inventory\n";
    cout << "<D>elete Inventory\n";
    cout << "<E>dit Inventory\n";
    cout << "<S>how Inventory\n";
    cout << "<Q>uit Program\n";
}

// Function to only allow input from first letter of menu options
void validChoice(char& choice) {
    bool invalidChoice = true;
    while (invalidChoice) {
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore();
        }
        if (choice == 'A' || choice == 'D' || choice == 'E' || choice == 'S' || choice == 'Q') {
            invalidChoice = false;
        }
         if (invalidChoice) {
            cout << "Invalid choice! Please choose from first letter of menu options: ";
            cout << endl;
        }
    }
}

// Function for 5 digit ID number(won't accept values less than 10000 though)
void validNumber(float& number) {
    bool invalidResponse = true;
    while (invalidResponse) {
        cin >> number;
        if (cin.fail()) {
            cin.clear();
            cin.ignore();
        }
        else if (number <= 99999 && number >= 10000) {
            invalidResponse = false;
        }
        else if (invalidResponse) {
            cout << "\nInvalid, please enter a 5 digit value: ";
        }
    }
}

// Function to only allow positive input
void validValues(float& value) {
    bool invalidResponse = true;
    while (invalidResponse) {
        cin >> value;
        if (cin.fail()) {
            cin.clear();
            cin.ignore();
        }
        else if (value >= 0) {
            invalidResponse = false;
        }
        if (invalidResponse) {
            cout << "\nInvalid, please enter a positive value: ";
        }
    }
}

// Function to add to inventory
void addInventory(float **inventory, int inventorySize) {
    int x = inventorySize - 1;
    cout << "\nItem ID Number: ";
    validNumber(inventory[x][0]);
    cout << "\nQuantity at Hand: ";
    validValues(inventory[x][1]);
    cout << "\nWholesale Cost: ";
    validValues(inventory[x][2]);
    inventory[x][3] = inventory[x][2] * 2;
    cout << "\nRetail Cost: " << inventory[x][3];
    cout << "\nDate Added: " << endl;
}

// Function to edit the inventory
void editInventory(float **inventory, int inventorySize) {
    float editNumber;
    float editCategory;

    cout << "Choose an ID number to edit, enter the corresponding number(1, 2, 3...)\n";
    for (int i = 0; i < inventorySize; i++) {
        cout << i + 1 << ". Item ID Number: " << inventory[i][0] << endl;
    }
    validValues(editNumber);
    int i = editNumber - 1;

    cout << "Choose a category to edit 1 or 2:\n";
    cout << "\n1. Quantity at Hand: " << inventory[i][1];
    cout << "\n2. Wholesale Cost: " << inventory[i][2];
    cout << endl;
    validValues(editCategory);

    if (editCategory == 1) {
        cout << "Enter new quantity: ";
        validValues(inventory[i][1]);
    }
    if (editCategory == 2) {
        cout << "Enter new wholesale cost: ";
        validValues(inventory[i][2]);
        inventory[i][3] = inventory[i][2] * 2;
    }
    cout << endl;
}

// Function to display the entire inventory
void showInventory(float **inventory, int inventorySize) {
    for (int i = 0; i < inventorySize; i++) {
        cout << "Item ID Number: " << inventory[i][0];
        cout << "\nQuantity at Hand: " << inventory[i][1];
        cout << "\nWholesale Cost: " << inventory[i][2];
        cout << "\nRetail Cost: " << inventory[i][3];
        cout << "\nDate Added: " << endl;
    }
}
