#pragma once
#include <iostream>
#include <string>

using namespace std;

class BankAccount {
private: 
    // variables must be defined with these names for check 2 to work properly!
    int id;
    std::string name;
public:
    // Parameterized constructor (makes your life easier but not required)
    BankAccount(int newID, string newName) {
        id = newID;
        name = newName;
    }
    // Necessary getters: getName(), getID()
    string getName() {return name;}
    int getID() {return id;}
    // The following pure virtual functions: Display(), Deposit(float), getAmount()
    virtual void Display() = 0;
    virtual void Deposit(float num) = 0;
    virtual float getAmount() = 0;
};

class CheckingAccount : virtual public BankAccount { 
private:
    // this variable must have this name for the implementation check to work properly!
    float amount = 0; 
protected:
    // this function must have this name for the implementation check to work properly!
    void setAmount(float amnt) {amount = amnt;} 
public:
    // Parameterized constructor (float, int, string)
    CheckingAccount(float amnt, int newID, string newName):BankAccount(newID, newName) {
        Deposit(amnt);
    }
    // Behavioral function(s): Withdraw(float)
    bool Withdraw(float num) {
        if (amount - num < 0) {
            cout << "Overdraft Protection! Transaction Failed." << endl;
            return false;
        }
        amount -= num;
        return true;
    }
    // all three overrides
    void Deposit(float num) override {
        setAmount(amount+num);
    }
    float getAmount() override {return amount;}
    void Display() override {
        cout << "\nChecking Account Info" << endl;
        cout << "ID: " << BankAccount::getID() << endl;
        cout << "Name: " << BankAccount::getName() << endl;
        cout << "Amount: " << getAmount() << endl;
    }
}; 

class SavingsAccount : virtual public BankAccount {
private:
    // this variable must have this name for the implementation check to work properly!
    float amount = 0; 
protected:
    void setAmount(float amnt) {amount = amnt;} 
public:
    // Parameterized constructor (float, int, string)
    SavingsAccount(float amnt, int newID, string newName):BankAccount(newID, newName) {Deposit(amnt);}
    // Behavioral function(s): Transfer(CheckingAccount, float), CompoundEarnings(float)
    virtual bool Transfer(CheckingAccount& checking = CheckingAccount(static_cast<float>(amount), 0, "temp"), float num = 0) {
        if (amount - num < 0) {
            cout << "\nError, Transaction Failed. Insufficient Funds." << endl;
            return false;
        }
        checking.Deposit(num);
        amount -= num;
        return true;
    }
    void CompoundEarnings(float num) {amount = amount*(1+(num/100));}
    // all three overrides
    void Deposit(float num) override {amount += num;}
    void Display() override {
        cout << "\nSavings Account Info" << endl;
        cout << "ID: " << BankAccount::getID() << endl;
        cout << "Name: " << BankAccount::getName() << endl;
        cout << "Amount: " << amount << endl;
    }
    float getAmount() override {return amount;}
};

class InvestmentAccount : public CheckingAccount, private SavingsAccount {
private:
    float savingsAmount = 0;
    float amount = 0;
protected:
    void setAmount(float amnt) {savingsAmount = amnt;}
public:
    InvestmentAccount(float amnt, int newID, string newName):BankAccount(newID, newName), CheckingAccount(amnt, newID, newName), SavingsAccount(amnt, newID, newName) {Deposit(amnt);}
    bool Transfer(CheckingAccount& checking = CheckingAccount(static_cast<float>(amount), 0, "temp"), float num = 0) override {
        if (savingsAmount - num < 0) {
            cout << "\nError, Transaction Failed. Insufficient Funds." << endl;
            return false;
        }
        amount += num;
        savingsAmount -= num;
        return true;
    }
    void Deposit(float num) override {
        savingsAmount += num;
    }
    float getAmount() override {return savingsAmount + amount;}
    void Display() override {
        cout << "\nInvestment Account Info" << endl;
        cout << "ID: " << BankAccount::getID() << endl;
        cout << "Name: " << BankAccount::getName() << endl;
        cout << "Amount: " << getAmount() << endl;
        cout << "Amount in investments: " << savingsAmount << endl;
        cout << "Available to withdraw: " << amount << endl;
    }   
    
};