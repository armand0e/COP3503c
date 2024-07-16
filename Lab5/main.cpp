#include <iostream>
#include <string>
#include <vector>
#include "BankAccount.h"

using namespace std;

int main() {
    CheckingAccount newChecking(500, 1234, "First Checkin");
    newChecking.Display();
    SavingsAccount newSavings(1000, 321, "First savings");
    newSavings.Display();

    newSavings.Transfer(newChecking, 25);
    newSavings.CompoundEarnings();
    newChecking.Withdraw(100);
    newChecking.Display();
    newSavings.Display();


}