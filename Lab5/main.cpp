#include <iostream>
#include <string>
#include <vector>
#include "BankAccount.h"

using namespace std;

int main() {
    InvestmentAccount newAcc(82743.24, 8642351, "Fidelity Roth IRA");
    newAcc.Display();
    CheckingAccount tempAcc(0, newAcc.getID(), newAcc.getName());
    newAcc.Transfer(tempAcc, 5000);
    SavingsAccount savings(250, newAcc.getID(), newAcc.getName());
    savings.Transfer(tempAcc, 50);
    savings.Display();
    tempAcc.Display();
    savings.Transfer(tempAcc, 500);
    savings.Display();
    newAcc.Display();

}