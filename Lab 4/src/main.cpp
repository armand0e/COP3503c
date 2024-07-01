#include <iostream>
#include <fstream>
#include "extrafile.h"
using namespace std;

int main()
{
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
			fstream friendlyshipsFile("friendlyships.shp", ios_base::in | ios_base::binary);
			if (friendlyshipsFile.is_open()) {
				cout << "Successfully loaded \"friendlyships.shp\"" << endl;
			}
			validinput = true;
		}
		else if (option == 2) {
			fstream enemyshipsFile("enemyships.shp", ios_base::in | ios_base::binary);
			if (enemyshipsFile.is_open()) {
				cout << "Successfully loaded \"enemyships.shp\"" << endl;
			}
			validinput = true;
		} 
		else if (option == 3) {
			fstream friendlyshipsFile("friendlyships.shp", ios_base::in | ios_base::binary);
			fstream enemyshipsFile("enemyships.shp", ios_base::in | ios_base::binary);
			validinput = true;
		} 
		else {
			cout << "Error: Invalid input!" << endl;
			validinput = false;
		}
	}

	cout << "1. Print all ships" << endl;
	cout << "2. Starship with the strongest weapon" << endl;
	cout << "3. Strongest starship overall" << endl;
	cout << "4. Weakest ship (ignoring unarmed)" << endl;
	cout << "5. Unarmed ships" << endl;
	
	cin >> option;
	
	// Work your magic here 
	
return 0;
}