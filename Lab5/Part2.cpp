#include<iostream>
#include<fstream>
#include<vector>
#include<map>
#include"BankAccount.h"
using namespace std;

struct AccountReader{
    ////// Your two maps here as member variables
    map<int, BankAccount*> idMap;
    map<string, BankAccount*> nameMap;

    void operator()(string filePath) {
        ////// Load all accounts into the two maps!
        
        ifstream file(filePath);
        string line;
        if (file.is_open()) {
            // first line is not data
            getline(file, line);
            // now we got what we need
            while (getline(file, line)) {
                vector<string> accountInfo;
                for (int i = 0; i < 4; i++) {
                    int commaIndex = line.find(',');
                    string info = line.substr(0, commaIndex);
                    accountInfo.push_back(info);
                    line = line.substr(commaIndex+1, line.size());
                }
                // accountInfo = [Type, Name, Amount, ID]

                // types 1,2,3 = Checking,Savings,Investment
                int type = stoi(accountInfo[0]);
                string name = accountInfo[1];
                float amount = stof(accountInfo[2]);
                int id = stoi(accountInfo[3]);
                // create account pointer
                BankAccount* accptr = nullptr;
                if (type == 1) {
                    accptr = new CheckingAccount(amount, id, name);
                }
                if (type == 2) {
                    accptr = new SavingsAccount(amount, id, name);
                }
                if (type == 3) {
                    accptr = new InvestmentAccount(amount, id, name);
                }
                if (accptr != nullptr) {
                    // add to idMap [id:acc, id:acc, ...]
                    idMap[id] = accptr;
                    // add to nameMap [name:acc, name:acc, ...]
                    nameMap[name] = accptr;
                }
            }
        }

        cout << "1. Display all accounts" << endl;
        cout << "2. Display all of account type" << endl;
        cout << "3. Find account" << endl;
        string optionS;
        int option;
        getline(cin, optionS);
        option = stoi(optionS);

        ////// Work with maps to complete tasks above!
        if (option == 1) {
            // for every account.
            for (auto it = idMap.begin(); it != idMap.end(); it++) {
                it->second->Display();
            }
        }
        else if (option == 2) {
            getline(cin, optionS);
            int option2 = stoi(optionS);
            // make sure type is valid
            if (1 <= option2 <= 3) {
                // for every account
                for (auto it = idMap.begin(); it != idMap.end(); it++) {
                    BankAccount* acc = it->second;
                    if (acc->type == option2) {
                        acc->Display();
                    }
                }
            }
        }
        else if (option == 3) {
            string input;
            getline(cin, input);
            try {
                int id = stoi(input);
                // input is id
                for (auto it = idMap.begin(); it != idMap.end(); it++) {
                    BankAccount* acc = it->second;
                    if (acc->type == option2) {
                        acc->Display();
                    }
                }
            }
            catch (invalid_argument) {
                string name = input;
                try {
                    nameMap[name]->Display();
                }
                catch (...) {
                    cout << "Account Name: " << input << " not found." << endl;
                }
                

            }
        }

    }       
};

void Help(){
    cout << "Error!" << endl;
}

int main(int argc, char** argv) {
    ////// Use your functor here
    AccountReader accReader;
    if (argc == 1) {Help(); return -1;}
    string path = argv[1];
    accReader(path)
}