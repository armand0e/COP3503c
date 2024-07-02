#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

struct Armament {
    string name;
    int firepower;
    float powerConsumption;
};

struct Starship {
    string name;
    string shipclass;
    short length = 0;
    int shieldCapacity;
    float maxWarpSpeed;
    vector<Armament> armaments;

    void addWeapon(string weaponName, int weaponFP, float consumption);
    void printArmaments() const;
    void printShip() const;
};
