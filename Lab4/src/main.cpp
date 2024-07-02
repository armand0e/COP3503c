#include <iostream>
#include <fstream>
#include <vector>
#include "extrafile.h"

using namespace std;

// global vars
vector<Starship> starshipList;

bool readShips(const vector<string>& paths) {
    starshipList.clear(); 
    for (const auto& path : paths) {
        fstream file(path, ios_base::in | ios_base::binary);
        if (file.is_open()) {
            int shipCount;
            file.read(reinterpret_cast<char*>(&shipCount), 4);
            //cout << "Ship count in file \"" << path << "\": " << shipCount << endl;
            starshipList.reserve(starshipList.size() + shipCount);
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
                	///////////////////// NAME ////////////////////
                    int weaponNameLength;
                    file.read(reinterpret_cast<char*>(&weaponNameLength), 4);
                    char* weaponNameChars = new char[weaponNameLength];
                    file.read(weaponNameChars, weaponNameLength);
                	////////////////// totalFP //////////////////
                    int rating;
                    file.read(reinterpret_cast<char*>(&rating), 4);
                	///////////////// CONSUMPTION /////////////////
                    float consumption;
                    file.read(reinterpret_cast<char*>(&consumption), 4);
					// Add weapon to starship
                    newStarship.addWeapon(string(weaponNameChars, weaponNameLength - 1), rating, consumption);
                    delete[] weaponNameChars;
                }
                // Add starship to the list
                starshipList.push_back(newStarship);
            }
            file.close();
        } else {
            // Failed to open file, throw error
            throw runtime_error("Failed to open \"" + path + "\"");
        }
    }

    return true;
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
	vector<string> files;
	if (option == 1) {
		files.push_back("friendlyships.shp");
	} else if (option == 2) {
		files.push_back("enemyships.shp");
	} else if (option == 3) {
		files.push_back("friendlyships.shp");
		files.push_back("enemyships.shp");
	} else {
		throw runtime_error("Invalid input! Please select an integer 1-3");
    }

	if (!readShips(files)) {
    	throw runtime_error("Failed to read files!"); 
    }

    cout << "1. Print all ships" << endl;
    cout << "2. Starship with the strongest weapon" << endl;
    cout << "3. Strongest starship overall" << endl;
    cout << "4. Weakest ship (ignoring unarmed)" << endl;
    cout << "5. Unarmed ships" << endl;
    
    cin >> option;
    
    // Work your magic here 
    validinput = false;

        if (option == 1) {
            for (const auto& starship : starshipList) {
                starship.printShip();
                cout << endl;
            }
        }
        else if (option == 2) {
            // find the starship with the strongest weapon
			Starship strongestWeapon = starshipList[0];
            for (int i = 0; i < starshipList.size(); i++) {
                int currentFP = starshipList[i].getStrongestWeaponFP();
                int strongestFP = strongestWeapon.getStrongestWeaponFP();
				if (currentFP > strongestFP)
					strongestWeapon = starshipList[i];
			}
            strongestWeapon.printShip();
        }
        else if (option == 3) {
            // find the strongest starship overall
			Starship strongestShip = starshipList[0];
			for (int i = 0; i < starshipList.size(); i++) {
				if (starshipList[i].totalFP > strongestShip.totalFP)
					strongestShip = starshipList[i];
			}
            strongestShip.printShip();
        }
        else if (option == 4) {
            // find the weakest ship (ignoring unarmed)
			Starship weakestShip = starshipList[0];
			for (int i = 0; i < starshipList.size(); i++) {
				if (starshipList[i].totalFP != 0 && starshipList[i].totalFP < weakestShip.totalFP)
					weakestShip = starshipList[i];
			}
            weakestShip.printShip();
            cout << endl;
		}
        else if (option == 5) {
            // find unarmed ships
			for (const auto& starship : starshipList) {
				if (starship.armaments.size() == 0) {
					starship.printShip();
					cout << endl;
				}
			}
        }
        else {
            // invalid input
            throw runtime_error("Invalid input! Please select an integer 1-5");
        }
		
	return 0;
}
