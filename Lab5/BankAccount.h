#pragma once
#include <iostream>
#include <string>
#include <cmath>
using namespace std;

float rounded(float num) {
    num *= 100;
    num += 0.5;
    int bigNum = num;
    return bigNum/100.00f;
}

class BankAccount {
private: 
    // variables must be defined with these names for check 2 to work properly!
    int id;
    string name;
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
            //cout << "Overdraft Protection! Transaction Failed." << endl;
            return false;
        }
        amount -= num;
        return true;
    }
    // all three overrides
    void Deposit(float num) override {
        amount += num;
    }
    float getAmount() override {return amount;}
    void Display() override {
        cout << getName() << " (" << BankAccount::getID() << "):" << endl;
        cout << "\tChecking Account: $" << rounded(getAmount()) << endl;        
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
    virtual bool Transfer(CheckingAccount& checking, float num) {
        if (amount - num < 0) {
            //cout << "\nError, Transaction Failed. Insufficient Funds." << endl;
            return false;
        }
        checking.Deposit(num);
        amount -= num;
        return true;
    }
    virtual void CompoundEarnings(float num) {amount *= (1+(num/100));}
    // all three overrides
    void Deposit(float num) override {amount += num;}
    void Display() override {
        cout << getName() << " (" << BankAccount::getID() << "):" << endl;
        cout << "\tSavings Account: $" << rounded(getAmount()) << endl;
    }
    float getAmount() override {return amount;}
};

class InvestmentAccount : public CheckingAccount, private SavingsAccount {
private:
    float savingsAmount;
    float amount;
protected:
    void setAmount(float amnt) {savingsAmount = amnt;}
public:
    InvestmentAccount(float amnt, int newID, string newName):BankAccount(newID, newName), CheckingAccount(amnt, newID, newName), SavingsAccount(amnt, newID, newName) {Deposit(amnt); amount = 0;}
    bool Transfer(CheckingAccount& checking, float num) override {
        if (savingsAmount - num < 0) {
            //cout << "\nError, Transaction Failed. Insufficient Funds." << endl;
            return false;
        }
        amount += num;
        savingsAmount -= num;
        return true;
    }
    void CompoundEarnings(float num) override {savingsAmount *= (1+(num/100));}
    void Deposit(float num) override {
        savingsAmount += num;
    }
    float getAmount() override {return savingsAmount + amount;}
    void Display() override {
        cout << getName() << " (" << BankAccount::getID() << "):" << endl;
        cout << "\tTotal: $" << rounded(getAmount()) << endl;
        cout << "\t\tImmediate Funds: $" << rounded(amount) << endl;
        cout << "\t\tInvestment: $" << rounded(savingsAmount) << endl;
    }   
    
};