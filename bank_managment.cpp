#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<time.h>
using namespace std;

class BankAccount {
    int accNo;           // Account number
    char name[25];       // Name of the user
    float balance;       // Current balance in the account

public:
    int searchAccNo;     // Account number used for searching

    void createAccount();  // Function to create an account
    void deposit();        // Function to deposit money
    void withdraw();       // Function to withdraw money
    void checkInfo();      // Function to check account info
};

// Main function to interact with the user
int main() {
    BankAccount user;
    char choice;

    cout << "Welcome to the Bank Management System\n";
    cout << "Press 1 to Login\n";
    cout << "Press 2 to Create Account\n";
    cout << "Press 0 to Exit\n";
    cin >> choice;

    switch(choice) {
        case '1':
            cout << "Enter your account number: ";
            cin >> user.searchAccNo;
            while (true) {
                cout << "1. Deposit\n2. Withdraw\n3. Check Info\n0. Exit\n";
                cin >> choice;
                switch(choice) {
                    case '1':
                        user.deposit();
                        break;
                    case '2':
                        user.withdraw();
                        break;
                    case '3':
                        user.checkInfo();
                        break;
                    case '0':
                        return 0;
                    default:
                        cout << "Invalid choice\n";
                }
            }
            break;

        case '2':
            user.createAccount();
            break;

        case '0':
            return 0;

        default:
            cout << "Invalid choice\n";
    }

    return 0;
}

// Function to create a new account
void BankAccount::createAccount() {
    srand(time(0));  // Seed the random number generator
    accNo = rand();  // Generate a random account number

    cout << "Enter your name: ";
    cin >> name;

    cout << "Enter initial deposit: ";
    cin >> balance;

    // Display the generated account number
    cout << "Your account number is: " << accNo << endl;

    // Open the file in append mode to save the new account data
    ofstream file("accounts.txt", ios::app);
    file << accNo << " " << name << " " << balance << endl;
    file.close();
}

// Function to deposit money into the account
void BankAccount::deposit() {
    float depositAmount;
    cout << "Enter amount to deposit: ";
    cin >> depositAmount;

    // Open the file to read the account data
    ifstream inFile("accounts.txt");
    ofstream outFile("temp.txt", ios::app);

    while (inFile >> accNo >> name >> balance) {
        if (accNo == searchAccNo) {
            balance += depositAmount;
            cout << "Updated balance: " << balance << endl;
        }
        outFile << accNo << " " << name << " " << balance << endl;
    }

    inFile.close();
    outFile.close();
    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");
}

// Function to withdraw money from the account
void BankAccount::withdraw() {
    float withdrawAmount;
    cout << "Enter amount to withdraw: ";
    cin >> withdrawAmount;

    // Open the file to read the account data
    ifstream inFile("accounts.txt");
    ofstream outFile("temp.txt", ios::app);

    while (inFile >> accNo >> name >> balance) {
        if (accNo == searchAccNo) {
            if (balance >= withdrawAmount) {
                balance -= withdrawAmount;
                cout << "Updated balance: " << balance << endl;
            } else {
                cout << "Insufficient balance\n";
            }
        }
        outFile << accNo << " " << name << " " << balance << endl;
    }

    inFile.close();
    outFile.close();
    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");
}

// Function to check account information
void BankAccount::checkInfo() {
    ifstream file("accounts.txt");

    while (file >> accNo >> name >> balance) {
        if (accNo == searchAccNo) {
            cout << "Account Number: " << accNo << endl;
            cout << "Name: " << name << endl;
            cout << "Balance: " << balance << endl;
            return;
        }
    }

    cout << "Account not found\n";
    file.close();
}
