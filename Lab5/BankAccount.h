#pragma once
#include <iostream>
#include <string>

using namespace std;

class BankAccount {
private: // variables must be defined with these names for check 2 to work properly!
    int id;
    std::string name;
public:
// Parameterized constructor (makes your life easier but not required)
    BankAccount(int newID, string newName) {
        this->id = newID;
        this->name = newName;
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
    float amount; 
protected:
    // this function must have this name for the implementation check to work properly!
    void setAmount(float amnt) {this->amount = amnt;} 
public:
    // Parameterized constructor (float, int, string)
    CheckingAccount(float amnt, int newID, string newName):BankAccount(newID, newName) {
        setAmount(amnt);
    }
    // Behavioral function(s): Withdraw(float)
    bool Withdraw(float num) {
        if (this->amount - num < 0) {
            cout << "Overdraft Protection! Transaction Failed." << endl;
            return false;
        }
        this->amount -= num;
        return true;
    }
    // all three overrides
    void Deposit(float num) override {
        setAmount(this->amount+num);
    }
    void Display() override {
        cout << "\nChecking Account Info" << endl;
        cout << "ID: " << getID() << endl;
        cout << "Name: " << getName() << endl;
        cout << "Amount: " << getAmount() << endl;
    }
    float getAmount() override {return this->amount;}
}; 

class SavingsAccount : virtual public BankAccount {
private:
    // this variable must have this name for the implementation check to work properly!
    float amount; 
protected:
    // this function must have this name for the implementation check to work properly!
    void setAmount(float amount); 
public:
    // Parameterized constructor (float, int, string)
    SavingsAccount(float amnt, int newID, string newName):BankAccount(newID, newName) {
        this->amount = amnt;
    }
    // Behavioral function(s): Transfer(CheckingAccount, float), CompoundEarnings(float)
    bool Transfer(CheckingAccount& checking, float num) {
        if (this->amount - num < 0) {
            cout << "\nError, Transaction Failed. Insufficient Funds." << endl;
            return false;
        }
        checking.Deposit(num);
        this->amount -= num;
        return true;
    }
    void CompoundEarnings(float num) {
        this->amount = this->amount*(1+num);
    }
    // all three overrides
    void Deposit(float num) override {
        this->amount += num;
    }
    void Display() override {
        cout << "\nSavings Account Info" << endl;
        cout << "ID: " << getID() << endl;
        cout << "Name: " << getName() << endl;
        cout << "Amount: " << this->amount << endl;
    }
    float getAmount() override {return this->amount;}
};

//class InvestmentAccount: public CheckingAccount, private SavingsAccount {};