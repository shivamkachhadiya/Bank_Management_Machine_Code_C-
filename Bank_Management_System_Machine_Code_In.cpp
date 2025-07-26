#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Account {
public:
    int accNumber;
    string name;
    double balance;

    Account(int number, string userName, double initialBalance) {
        accNumber = number;
        name = userName;
        balance = initialBalance;
    }

    void display() const {  // fixed: added const here
        cout << "Account Number: " << accNumber << "\n";
        cout << "Name: " << name << "\n";
        cout << "Balance: ₹" << balance << "\n";
    }
};

class BankSystem {
private:
    vector<Account> accounts;

    Account* findAccount(int accNumber) {
        for (auto &acc : accounts) {
            if (acc.accNumber == accNumber)
                return &acc;
        }
        return nullptr;
    }

public:
    void createAccount() {
        int accNumber;
        string name;
        double initialBalance;

        cout << "Enter Account Number: ";
        cin >> accNumber;
        if (findAccount(accNumber)) {
            cout << "Account already exists!\n";
            return;
        }

        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, name);

        cout << "Enter Initial Balance: ₹";
        cin >> initialBalance;

        accounts.push_back(Account(accNumber, name, initialBalance));
        cout << "Account Created Successfully!\n";
    }

    void viewAccount() {
        int accNumber;
        cout << "Enter Account Number: ";
        cin >> accNumber;

        Account* acc = findAccount(accNumber);
        if (acc) {
            acc->display();
        } else {
            cout << "Account not found!\n";
        }
    }

    void depositMoney() {
        int accNumber;
        double amount;

        cout << "Enter Account Number: ";
        cin >> accNumber;

        Account* acc = findAccount(accNumber);
        if (acc) {
            cout << "Enter amount to deposit: ₹";
            cin >> amount;
            if (amount <= 0) {
                cout << "Invalid amount!\n";
                return;
            }
            acc->balance += amount;
            cout << "Deposit Successful! New Balance: ₹" << acc->balance << "\n";
        } else {
            cout << "Account not found!\n";
        }
    }

    void withdrawMoney() {
        int accNumber;
        double amount;

        cout << "Enter Account Number: ";
        cin >> accNumber;

        Account* acc = findAccount(accNumber);
        if (acc) {
            cout << "Enter amount to withdraw: ₹";
            cin >> amount;
            if (amount <= 0) {
                cout << "Invalid amount!\n";
                return;
            }
            if (amount > acc->balance) {
                cout << "Insufficient Balance!\n";
            } else {
                acc->balance -= amount;
                cout << "Withdrawal Successful! Remaining Balance: ₹" << acc->balance << "\n";
            }
        } else {
            cout << "Account not found!\n";
        }
    }

    void transferMoney() {
        int fromAcc, toAcc;
        double amount;

        cout << "Enter Sender Account Number: ";
        cin >> fromAcc;
        cout << "Enter Receiver Account Number: ";
        cin >> toAcc;
        cout << "Enter Amount to Transfer: ₹";
        cin >> amount;

        Account* sender = findAccount(fromAcc);
        Account* receiver = findAccount(toAcc);

        if (!sender || !receiver) {
            cout << "One or both accounts not found!\n";
            return;
        }

        if (amount <= 0) {
            cout << "Invalid transfer amount!\n";
            return;
        }

        if (sender->balance < amount) {
            cout << "Insufficient Balance in sender's account!\n";
            return;
        }

        sender->balance -= amount;
        receiver->balance += amount;
        cout << "Transfer Successful!\n";
    }

    void deleteAccount() {
        int accNumber;
        cout << "Enter Account Number to Delete: ";
        cin >> accNumber;

        for (auto it = accounts.begin(); it != accounts.end(); ++it) {
            if (it->accNumber == accNumber) {
                accounts.erase(it);
                cout << "Account Deleted Successfully!\n";
                return;
            }
        }

        cout << "Account not found!\n";
    }

    void viewAllAccounts() {
        if (accounts.empty()) {
            cout << "No accounts found!\n";
            return;
        }

        for (const auto &acc : accounts) {
            acc.display();  // works now because display() is const
            cout << "-------------------------\n";
        }
    }
};

int main() {
    BankSystem bank;
    int choice;

    while (true) {
        cout << "\n===== Bank Management System =====\n";
        cout << "1. Create Account\n";
        cout << "2. View Account\n";
        cout << "3. Deposit Money\n";
        cout << "4. Withdraw Money\n";
        cout << "5. Transfer Money\n";
        cout << "6. Delete Account\n";
        cout << "7. View All Accounts\n";
        cout << "0. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
            case 1: bank.createAccount(); break;
            case 2: bank.viewAccount(); break;
            case 3: bank.depositMoney(); break;
            case 4: bank.withdrawMoney(); break;
            case 5: bank.transferMoney(); break;
            case 6: bank.deleteAccount(); break;
            case 7: bank.viewAllAccounts(); break;
            case 0: cout << "Exiting...\n"; return 0;
            default: cout << "Invalid choice! Try again.\n";
        }
    }

    return 0;
}
