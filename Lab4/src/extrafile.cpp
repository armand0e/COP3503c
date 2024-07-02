#include "extrafile.h"

void Starship::addWeapon(string weaponName, int weaponFP, float consumption) {
    Armament newWeapon;
    newWeapon.name = weaponName;
    newWeapon.firepower = weaponFP;
    newWeapon.powerConsumption = consumption;
    armaments.push_back(newWeapon);
}

void Starship::printArmaments() const {
    // loop through all armaments and print their details
    for (const auto& weapon : armaments) {
        cout << weapon.name << ", " << weapon.firepower << ", " << weapon.powerConsumption << endl;
    }
}

void Starship::printShip() const {
    cout << "Name: " << name << endl;
    cout << "Class: " << shipclass << endl;
    if (length != 0) {
        cout << "Length: " << length << endl; 
    }
    cout << "Shield capacity: " << shieldCapacity << endl;
    cout << "Maximum Warp: " << maxWarpSpeed << endl;
    cout << "Armaments:" << endl;
    if (armaments.size() == 0) {
        cout << "Unarmed" << endl;
    }
    else {
        printArmaments();
        int totalFP = 0;
        // calculate total firepower of all armaments
        for (const auto& weapon : armaments) {
            totalFP += weapon.firepower;
        }
        cout << "Total firepower: " << totalFP << endl;
    }
}
