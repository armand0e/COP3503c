#include "extrafile.h"

void Starship::addWeapon(string weaponName, int weaponFP, float consumption) {
    Armament newWeapon;
    newWeapon.name = weaponName;
    newWeapon.firepower = weaponFP;
    newWeapon.powerConsumption = consumption;
    armaments.push_back(newWeapon);
    totalFP += newWeapon.firepower;
}

void Starship::printArmaments() const {
    // loop through all armaments and print their details
    for (const auto& weapon : armaments) {
        cout << weapon.name << ", " << weapon.firepower << ", " << weapon.powerConsumption << endl;
    }
}

int Starship::getStrongestWeaponFP() {
    if (armaments.size() != 0) {
        Armament strongestWeapon = armaments[0];
        for (const auto& weapon : armaments) {
            if (weapon.firepower > strongestWeapon.firepower)
                strongestWeapon = weapon;
        }
        return strongestWeapon.firepower;
    }
    return 0;
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
    if (!totalFP == 0) {
        printArmaments();
        cout << "Total firepower: " << totalFP << endl;
    }
    else {
        cout << "Unarmed" << endl;
    }
}
