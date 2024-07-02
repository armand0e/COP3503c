#include <iostream>
#include <fstream>
#include <vector>
#include "extrafile.h"

using namespace std;

// global vars
vector<Starship> starshipList;

bool readShips(string path, string path2 = "N/A") {
    // open file
    fstream file(path, ios_base::in | ios_base::binary);
    if (path2 == "N/A") {
        // check if open
        if (file.is_open()) {
            // first find the number of ships in the file (first 4 bytes)
            int shipCount;
            file.read(reinterpret_cast<char*>(&shipCount), 4);
            cout << "Ship count: " << shipCount << endl;

            // dynamically allocate an array of starships
            starshipList.resize(shipCount);

            // then for every ship in the file...
            for (int i = 0; i < shipCount; i++) {
                Starship newStarship;

                ////////////////////// NAME ///////////////////////
                int nameLength;
                file.read(reinterpret_cast<char*>(&nameLength), 4);
                char* nameChars = new char[nameLength];
                file.read(nameChars, nameLength);
                newStarship.name = string(nameChars, nameLength - 1);
                delete[] nameChars;

                ////////////////////// CLASS //////////////////////
                int classLength;
                file.read(reinterpret_cast<char*>(&classLength), 4);
                char* classChars = new char[classLength];
                file.read(classChars, classLength);
                newStarship.shipclass = string(classChars, classLength - 1);
                delete[] classChars;

                ////////////////////// LENGTH /////////////////////
                short len;
                file.read(reinterpret_cast<char*>(&len), 2);
                newStarship.length = len;

                /////////////////// SHIELD CAPACITY ///////////////
                int shieldCap;
                file.read(reinterpret_cast<char*>(&shieldCap), 4);
                newStarship.shieldCapacity = shieldCap;

                /////////////////// MAX WARP SPEED ////////////////
                float warp;
                file.read(reinterpret_cast<char*>(&warp), 4);
                newStarship.maxWarpSpeed = warp;

                //////////////////// ARMAMENTS ////////////////////
                int weaponCount;
                file.read(reinterpret_cast<char*>(&weaponCount), 4);
                for (int j = 0; j < weaponCount; j++) {
                    // weapon name
                    int weaponNameLength;
                    file.read(reinterpret_cast<char*>(&weaponNameLength), 4);
                    char* weaponNameChars = new char[weaponNameLength];
                    file.read(weaponNameChars, weaponNameLength);
                    // power rating
                    int rating;
                    file.read(reinterpret_cast<char*>(&rating), 4);
                    // power consumption
                    float consumption;
                    file.read(reinterpret_cast<char*>(&consumption), 4);
                    // add weapons
                    newStarship.addWeapon(string(weaponNameChars, weaponNameLength - 1), rating, consumption);
                    delete[] weaponNameChars;
                }

                // add to the list of starships
                starshipList[i] = newStarship;
            }
            return true;
        }
        else {
            // failed to open, throw error
            cout << "Failed to open \"" << path << "\"" << endl;
            return false;
        }
    }
    return false;
}

int main() {
    cout << "Which file(s) to open?\n";
    cout << "1. friendlyships.shp" << endl;
    cout << "2. enemyships.shp" << endl;
    cout << "3. Both files" << endl;
    int option;
    cin >> option;

    // Load files here 
    bool validinput = false;
    while (!validinput) {
        if (option == 1) {
            if (readShips("friendlyships.shp"))
                validinput = true;
        }
        else if (option == 2) {
            if (readShips("enemyships.shp")) 
                validinput = true;
        } 
        else if (option == 3) {
            if (readShips("friendlyships.shp", "enemyships.shp"))
                    validinput = true;
        } 
        else {
            // invalid input
            cout << "Invalid input! Please select an integer 1-3" << endl;
            cin >> option; 
        }
    }

    cout << "1. Print all ships" << endl;
    cout << "2. Starship with the strongest weapon" << endl;
    cout << "3. Strongest starship overall" << endl;
    cout << "4. Weakest ship (ignoring unarmed)" << endl;
    cout << "5. Unarmed ships" << endl;
    
    cin >> option;
    
    // Work your magic here 
    validinput = false;
    while (!validinput) {
        if (option == 1) {
            for (const auto& starship : starshipList) {
                starship.printShip();
                cout << endl;
            }
            validinput = true;
        }
        else if (option == 2) {
            // find the starship with the strongest weapon
            validinput = true;
        }
        else if (option == 3) {
            // find the strongest starship overall
            validinput = true;
        }
        else if (option == 4) {
            // find the weakest ship (ignoring unarmed)
            validinput = true;
        }
        else if (option == 5) {
            // find unarmed ships
            validinput = true;
        }
        else {
            // invalid input
            cout << "Invalid input! Please select an integer 1-5" << endl;
            cin >> option; 
        }
    }

    return 0;
}
