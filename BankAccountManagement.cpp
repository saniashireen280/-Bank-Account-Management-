
#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

// Base Class
class BankAccount
{
private:
    string name;
    int accountNumber;

protected:
    double balance;

public:
    // Constructor
    BankAccount(string n, int acc, double b)
    {
        name = n;
        accountNumber = acc;
        balance = b;
    }

    // Deposit function
    void deposit(double amount)
    {
        if (amount <= 0)
            throw invalid_argument("Invalid deposit amount!");

        balance += amount;
        cout << "Amount deposited successfully!\n";
    }

    // Virtual withdrawal function
    virtual void withdraw(double amount)
    {
        if (amount <= 0)
            throw invalid_argument("Invalid amount!");

        if (amount > balance)
            throw runtime_error("Insufficient balance!");

        balance -= amount;
        cout << "Withdrawal successful!\n";
    }

    // Virtual display function
    virtual void display()
    {
        cout << "\nAccount Holder: " << name;
        cout << "\nAccount Number: " << accountNumber;
        cout << "\nBalance: Rs. " << balance << endl;
    }

    double getBalance()
    {
        return balance;
    }

    virtual ~BankAccount() {}
};

// Derived Class 1
class SavingsAccount : public BankAccount
{
public:
    SavingsAccount(string n, int acc, double b)
        : BankAccount(n, acc, b)
    {
    }

    void withdraw(double amount) override
    {
        if (amount <= 0)
            throw invalid_argument("Invalid amount!");

        if (amount > balance)
            throw runtime_error("Insufficient balance in savings account!");

        balance -= amount;
        cout << "Savings account withdrawal successful!\n";
    }

    void display() override
    {
        cout << "\n--- Savings Account ---";
        BankAccount::display();
    }
};

// Derived Class 2
class CurrentAccount : public BankAccount
{
private:
    double overdraftLimit;

public:
    CurrentAccount(string n, int acc, double b)
        : BankAccount(n, acc, b)
    {
        overdraftLimit = 5000;
    }

    void withdraw(double amount) override
    {
        if (amount <= 0)
            throw invalid_argument("Invalid amount!");

        if (amount > balance + overdraftLimit)
            throw runtime_error("Overdraft limit exceeded!");

        balance -= amount;
        cout << "Current account withdrawal successful!\n";
    }

    void display() override
    {
        cout << "\n--- Current Account ---";
        BankAccount::display();
        cout << "Overdraft Limit: Rs. "
             << overdraftLimit << endl;
    }
};

// Main Function
int main()
{
    string name;
    int acc, choice;

    double balance;

    cout << "===== BANK ACCOUNT MANAGEMENT SYSTEM =====\n";

    cout << "Enter Account Holder Name: ";
    getline(cin, name);

    cout << "Enter Account Number: ";
    cin >> acc;

    cout << "Enter Initial Balance: ";
    cin >> balance;

    if (balance < 0)
    {
        cout << "Initial balance cannot be negative!\n";
        return 0;
    }

    cout << "\nSelect Account Type:\n";
    cout << "1. Savings Account\n";
    cout << "2. Current Account\n";
    cout << "Enter choice: ";
    cin >> choice;

    SavingsAccount savings(name, acc, balance);
    CurrentAccount current(name, acc, balance);

    BankAccount *account = nullptr;

    if (choice == 1)
        account = &savings;
    else if (choice == 2)
        account = &current;
    else
    {
        cout << "Invalid account type!\n";
        return 0;
    }

    int option;
    double amount;

    do
    {
        cout << "\n===== BANK MENU =====\n";
        cout << "1. Display Account Details\n";
        cout << "2. Deposit Money\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Check Balance\n";
        cout << "5. Exit\n";

        cout << "Enter your choice: ";
        cin >> option;

        try
        {
            switch (option)
            {
                case 1:
                    account->display();
                    break;

                case 2:
                    cout << "Enter amount to deposit: ";
                    cin >> amount;
                    account->deposit(amount);
                    break;

                case 3:
                    cout << "Enter amount to withdraw: ";
                    cin >> amount;
                    account->withdraw(amount);
                    break;

                case 4:
                    cout << "Current Balance: Rs. "
                         << account->getBalance() << endl;
                    break;

                case 5:
                    cout << "Thank you for using our bank!\n";
                    break;

                default:
                    cout << "Invalid choice!\n";
            }
        }
        catch (const exception &e)
        {
            cout << "Error: " << e.what() << endl;
        }

    } while (option != 5);

    return 0;
}
