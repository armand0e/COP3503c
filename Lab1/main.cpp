#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iomanip>
using namespace std;

// global vars
vector<string> dataStrings;
vector<int> dataIntegers;

// return true for everything, return false if input = "-1"
bool addDataPoint() {
  // get data point
  bool valid = false;
  while (!valid) {
    // get data point from user in form: string, integer
    cout << "Enter a data point (-1 to stop input):" << endl;
    string dataPoint;
    getline(cin, dataPoint);
    // check if they entered "-1"
    if (dataPoint == "-1") {
        //if (dataStrings.size() == 0) cout << "Error: No data entered." << endl;
        //else if (dataStrings.size() > 0) return false;             
        return false;
    } 
    // if input is not "-1"
    else {
      // find commas
      int numOfCommas = 0;
      for (char i : dataPoint) {
        if (i == ',') numOfCommas += 1;
      }
      if (numOfCommas == 1) {
        // 1 comma found, split string
        stringstream ss(dataPoint);
        vector<string> point;
        while (ss.good()) {
          string splitstr;
          getline(ss, splitstr, ',');
          point.push_back(splitstr);
        }
        // save first half into dataString
        string dataString = point[0].substr();
        
        // save second half into dataInteger, and delete whitespace
        string dataInteger = point[1].substr();
        dataInteger.erase(remove(dataInteger.begin(), dataInteger.end(), ' '), dataInteger.end());
        
        // check if dataInteger is actually an integer
        try {
          int dataInt = stoi(dataInteger);
          dataStrings.push_back(dataString);
          dataIntegers.push_back(dataInt);
          valid = true;
        } 
        catch (...) {
          cout << "Error: Comma not followed by an integer." << endl;
        }
          
      }
      else if (numOfCommas < 1) {
        // no commas found
        cout << "Error: No comma in string." << endl;
      }
      else if (numOfCommas > 1) {
        // too many commas found
        cout << "Error: Too many commas in input." << endl;
      }
    }
  }
  cout << "Data string: " << dataStrings[dataStrings.size()-1] << endl;
  cout << "Data integer: " << to_string(dataIntegers[dataIntegers.size()-1]) << endl;
  return true;
  // now that
}

int main() {

  /* Overall flow of the program:
  Get some input for the title
  Get some input for column header #1
  Get some input for column header #2

  Until the user types "-1":
  Get input for a string
  Validate input
  If valid...
    Split
    Validate second half of input
    If also valid...
      Store separate pieces

  Print out data in table format

  Print out data in chart format
  */
  // WRITE YOUR CODE HERE
  
  // INITAL INPUTS

  // input for title
  cout << "Enter a title for the data:" << endl;
  string title;
  getline(cin, title);
  cout << "You entered: " << title << endl;

  // input for header 1
  cout << "Enter the column 1 header:" << endl;
  string header1;
  getline(cin, header1);
  cout << "You entered: " << header1 << endl;

  // input for header 2
  cout << "Enter the column 2 header:" << endl;
  string header2;
  getline(cin, header2);
  cout << "You entered: " << header2 << endl;
  
  // DATA POINTS

  // add data until "-1" is entered
  while (true) {
      if (!addDataPoint()) break;
  }

  if (dataStrings.size() > 0) {
    // print formatted table
    cout << endl << right << setw(33) << title << endl;
    cout << left << setw(20) << header1 << '|' << right << setw(23) << header2 << endl;
    for (int i = 0; i<=43; i++) cout << '-';
    cout << endl;
    for (int i = 0; i<dataStrings.size(); i++)
    {
        string datastr = dataStrings[i];
        string dataint = to_string(dataIntegers[i]);
        cout << left << setw(20) << datastr << '|' << right << setw(23) << dataint << endl;
    }
    // print formatted histogram
    cout << endl;
    for (int i = 0; i<dataStrings.size(); i++)
    {
        string datastr = dataStrings[i];
        string datapoints = "";
        for (int j = 1; j <=  dataIntegers[i]; j++) datapoints += '*';

        cout << right << setw(20) << datastr << ' ' << datapoints << endl;
    }
  }

}


