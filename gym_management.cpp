#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Base Class: Vehicle (Single / Multilevel Inheritance Style)
class Vehicle {
public:
    char vnumber[20];
    char vname[20];
    float baseRate;

    void inputVehicleDetails() {
        cout << "Enter Vehicle Number (e.g., MH12AB1234): ";
        cin >> vnumber;
        cout << "Enter Vehicle Name (e.g., Swift/R15/Activa): ";
        cin >> vname;
        cout << "Enter Base Rent Rate per Day (Rs.): ";
        cin >> baseRate;
    }
};

// Derived Class: Car (Inherits Vehicle)
class Car : public Vehicle {
public:
    int seatingCapacity;

    void inputCar() {
        inputVehicleDetails();
        cout << "Enter Seating Capacity: ";
        cin >> seatingCapacity;
    }

    float calculateCarRent(int days) {
        // Simple logic: Base rate * days + Fixed Rs. 500 Insurance
        return (baseRate * days) + 500;
    }
};

// Derived Class: Bike (Inherits Vehicle)
class Bike : public Vehicle {
public:
    int engineCC;

    void inputBike() {
        inputVehicleDetails();
        cout << "Enter Engine CC: ";
        cin >> engineCC;
    }

    float calculateBikeRent(int days) {
        // Simple logic: Base rate * days
        return (baseRate * days);
    }
};

// Rental Transaction & Billing Class (Handles Files)
class RentalBilling {
public:
    char customerName[30];
    int days;
    float totalBill;

    void generateCarBill(Car c) {
        cout << "\nEnter Customer Name: ";
        cin >> customerName;
        cout << "Enter Number of Rental Days: ";
        cin >> days;

        totalBill = c.calculateCarRent(days);

        // Print Bill to Screen
        cout << "\n================ RENTAL RECEIPT ================\n";
        cout << "Customer Name : " << customerName << endl;
        cout << "Vehicle Type  : Car (" << c.vname << ")" << endl;
        cout << "Vehicle No.   : " << c.vnumber << endl;
        cout << "Rental Days   : " << days << endl;
        cout << "Total Bill    : Rs. " << totalBill << endl;
        cout << "================================================\n";

        // File Handling: Save bill to rentals.txt
        ofstream outFile("rentals.txt", ios::app);
        if (outFile.is_open()) {
            outFile << "Customer: " << customerName 
                    << " | Vehicle: " << c.vname 
                    << " (" << c.vnumber << ")"
                    << " | Days: " << days 
                    << " | Total: Rs." << totalBill << endl;
            outFile.close();
            cout << "Receipt saved to rentals.txt successfully!\n";
        }
    }

    void generateBikeBill(Bike b) {
        cout << "\nEnter Customer Name: ";
        cin >> customerName;
        cout << "Enter Number of Rental Days: ";
        cin >> days;

        totalBill = b.calculateBikeRent(days);

        // Print Bill to Screen
        cout << "\n================ RENTAL RECEIPT ================\n";
        cout << "Customer Name : " << customerName << endl;
        cout << "Vehicle Type  : Bike (" << b.vname << ")" << endl;
        cout << "Vehicle No.   : " << b.vnumber << endl;
        cout << "Rental Days   : " << days << endl;
        cout << "Total Bill    : Rs. " << totalBill << endl;
        cout << "================================================\n";

        // File Handling: Save bill to rentals.txt
        ofstream outFile("rentals.txt", ios::app);
        if (outFile.is_open()) {
            outFile << "Customer: " << customerName 
                    << " | Vehicle: " << b.vname 
                    << " (" << b.vnumber << ")"
                    << " | Days: " << days 
                    << " | Total: Rs." << totalBill << endl;
            outFile.close();
            cout << "Receipt saved to rentals.txt successfully!\n";
        }
    }

    void viewAllRecords() {
        ifstream inFile("rentals.txt");
        if (!inFile.is_open()) {
            cout << "\nNo rental records found yet!\n";
            return;
        }

        string line;
        cout << "\n================ ALL RENTAL RECORDS ================\n";
        while (getline(inFile, line)) {
            cout << line << endl;
        }
        cout << "====================================================\n";
        inFile.close();
    }
};

int main() {
    Car c1;
    Bike b1;
    RentalBilling system;
    int choice;

    do {
        cout << "\n===== VEHICLE RENTAL & BILLING SYSTEM =====\n";
        cout << "1. Add Car & Rent\n";
        cout << "2. Add Bike & Rent\n";
        cout << "3. View All Saved Rental Records\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "\n--- Enter Car Details ---\n";
            c1.inputCar();
            system.generateCarBill(c1);
            break;
        case 2:
            cout << "\n--- Enter Bike Details ---\n";
            b1.inputBike();
            system.generateBikeBill(b1);
            break;
        case 3:
            system.viewAllRecords();
            break;
        case 4:
            cout << "Exiting Program. Thank you!\n";
            break;
        default:
            cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}