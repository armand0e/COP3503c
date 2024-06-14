#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;

string formatprice(float price) {
    string pricestr;
    bool decimalfound = false;
    bool addchar = true;
    bool roundup = false;
    int decimalplaces = 2;
    for (char i : to_string(price)) {
        if (decimalfound) {
            if (decimalplaces == 0)
                addchar = false;
            if (decimalplaces == -1)
                if ((int)i >= 5)
                    roundup = true;
            decimalplaces -= 1;
        }
        if (i == '.') {
            decimalfound = true;
        }
        if (addchar) {
            pricestr += i;
        }
    }
    

}

class Vehicle
{
    string make;
    string model;
    unsigned int year;
    float price;
    unsigned int mileage;
public:
    // default constructor, initializes variables to default values
    Vehicle() {
        this->make = "COP3503";
        this->model = "Rust Bucket";
        this->year = 1900;
        this->price = 0.00;
        this->mileage = 0;
    }
    Vehicle(string make, string model, int year, float price, int mileage) {
        this->make = make;
        this->model = model;
        this->year = year;
        this->price = price;
        this->mileage = mileage;
    }

    // print out vehicle details in a single line
    // year make model $price mileage
    void Display() {
        cout << to_string(this->year) << " " << this->make << " " << this->model;
        cout << " $" << formatprice(this->price) << " " << to_string(this->mileage) << endl;
    }

    // create and return a string in the form "year make model"
    string GetYearMakeModel() {
        return to_string(this->year) + " " + this->make + " " + this->model;
    }

    // return price
    float GetPrice() {
        return this->price;
    }
};

class Showroom
{
    string name;
    unsigned int capacity;
    vector<Vehicle> vehicles;

public:
    Showroom(string name = "Unamed Showroom", unsigned int capacity = 0) {
        this->name = name;
        this->capacity = capacity;
        this->vehicles = vehicles;
        
    }

    // Accessor
    vector<Vehicle> GetVehicleList() {
        return this->vehicles;
    }
    

    // Behaviors
    void AddVehicle(Vehicle v) {
        if (this->vehicles.size() < this->capacity) this->vehicles.push_back(v);
        else cout << "Showroom is full! Cannot add " << v.GetYearMakeModel() << endl;
    }

    void ShowInventory() {
        if (this->vehicles.size() > 0) {
            cout << "Vehicles in " << this->name << endl;
            for(int i=0; i < vehicles.size(); i++) {
                this->vehicles[i].Display();
            }
        } else {
            cout << this->name << " is empty!" << endl;
        }
    }
    
    float GetInventoryValue() {
        float value = 0;
        for( Vehicle vehicle : this->vehicles) {
            value += vehicle.GetPrice();
        }
        return value;
    }

};


class Dealership 
{
    string name;
    unsigned int capacity;
    vector<Showroom> showrooms;

public:
    Dealership(string name = "Generic Dealership", unsigned int capacity = 0) {
        this->name = name;
        this->capacity = capacity;
        this->showrooms = showrooms;
    }

    void AddShowroom(Showroom s) {
        if (this->showrooms.size() < this->capacity) {
            this->showrooms.push_back(s);
        }
        else { 
            cout << "Dealership is full, can't add another showroom!" << endl;
        }
    }

    float GetAveragePrice() {
        float totalValue = 0;
        float totalQuantity = 0;
        for(Showroom showroom : this->showrooms) {
            for(Vehicle vehicle : showroom.GetVehicleList()) {
                totalValue += vehicle.GetPrice();
                totalQuantity += 1;
            }
        }
        return totalValue/totalQuantity;

    }

    void ShowInventory() {
        if (this->showrooms.size() > 0) {
            for(Showroom showroom : this->showrooms) {
                showroom.ShowInventory();
            }
        } else {
            cout << this->name << " is empty!" << endl;
        }
        cout << "Average car price: $" << formatprice(this->GetAveragePrice()) << endl;
    }

};