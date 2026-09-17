#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Base Class: Person (Inheritance concept)
class Person {
public:
    char name[30];
    char phone[15];
    int age;

    void inputPersonDetails() {
        cout << "Enter Member Name: ";
        cin.ignore();
        cin.getline(name, 30);
        cout << "Enter Phone Number: ";
        cin >> phone;
        cout << "Enter Age: ";
        cin >> age;
    }
};

// Derived Class: GymMember (Inherits Person)
class GymMember : public Person {
public:
    int memberID;
    int planChoice;
    float totalFee;
    string planName;

    void registerMember() {
        cout << "Enter Member ID: ";
        cin >> memberID;
        
        // Input base details from Person class
        inputPersonDetails();

        cout << "\n--- Select Membership Plan ---\n";
        cout << "1. Monthly Plan (Rs. 1000)\n";
        cout << "2. Quarterly Plan - 3 Months (Rs. 2700 - 10% Off)\n";
        cout << "3. Yearly Plan - 12 Months (Rs. 9600 - 20% Off)\n";
        cout << "Enter Plan Choice (1-3): ";
        cin >> planChoice;

        // Calculate Fee based on Plan
        if (planChoice == 1) {
            planName = "Monthly";
            totalFee = 1000.0;
        } else if (planChoice == 2) {
            planName = "Quarterly";
            totalFee = 2700.0;
        } else if (planChoice == 3) {
            planName = "Yearly";
            totalFee = 9600.0;
        } else {
            cout << "Invalid choice! Setting default Monthly plan.\n";
            planName = "Monthly";
            totalFee = 1000.0;
        }

        displayReceipt();
        saveToFile();
    }

    void displayReceipt() {
        cout << "\n================ MEMBER BILL RECEIPT ================\n";
        cout << "Member ID    : " << memberID << endl;
        cout << "Name         : " << name << endl;
        cout << "Phone        : " << phone << endl;
        cout << "Age          : " << age << endl;
        cout << "Selected Plan: " << planName << endl;
        cout << "Total Amount : Rs. " << totalFee << endl;
        cout << "======================================================\n";
    }

    // File Handling: Save details to members.txt
    void saveToFile() {
        ofstream outFile("gym_members.txt", ios::app);
        if (outFile.is_open()) {
            outFile << "ID: " << memberID 
                    << " | Name: " << name 
                    << " | Phone: " << phone 
                    << " | Plan: " << planName 
                    << " | Amount: Rs." << totalFee << endl;
            outFile.close();
            cout << "Member record saved to gym_members.txt successfully!\n";
        } else {
            cout << "Error opening file to save data!\n";
        }
    }
};

// Manager Class to View File Records
class GymManager {
public:
    void viewAllMembers() {
        ifstream inFile("gym_members.txt");
        if (!inFile.is_open()) {
            cout << "\nNo gym records found yet!\n";
            return;
        }

        string line;
        cout << "\n================ REGISTERED GYM MEMBERS ================\n";
        while (getline(inFile, line)) {
            cout << line << endl;
        }
        cout << "========================================================\n";
        inFile.close();
    }
};

int main() {
    GymMember member;
    GymManager manager;
    int choice;

    do {
        cout << "\n===== GYM MANAGEMENT & BILLING SYSTEM =====\n";
        cout << "1. Register New Member & Generate Bill\n";
        cout << "2. View All Saved Member Records\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "\n--- New Member Registration ---\n";
            member.registerMember();
            break;
        case 2:
            manager.viewAllMembers();
            break;
        case 3:
            cout << "Exiting Program. Thank you!\n";
            break;
        default:
            cout << "Invalid choice! Please enter 1, 2, or 3.\n";
        }
    } while (choice != 3);

    return 0;
}
