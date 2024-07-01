#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

struct Armament {
    string name;
    int firepower;
    float rate;
};

struct Starship {
    string name;
    string shipclass;
    short length;
    int shieldCapacity;
    float maxWarpSpeed;
    vector<Armament> armaments;

    void addWeapon(string weaponName, int weaponFP, float weaponROF) {
        Armament newWeapon;
        newWeapon.name = weaponName;
        newWeapon.firepower = weaponFP;
        newWeapon.rate = weaponROF;
        armaments.push_back(newWeapon);
    }

    void printWeapons() {
        for (int i = 0; i < armaments.size(); i++) {
            Armament weapon = armaments[i];
            cout << weapon.name << ", " << weapon.firepower << ", " << weapon.rate << endl;
        }
    }
};