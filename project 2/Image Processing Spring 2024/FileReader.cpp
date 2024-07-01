#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

string binaryRead(string path) {
    fstream someFile(path, ios_base::in | ios_base::binary);
    unsigned int size = 0;
    if(someFile.is_open()) {
        someFile.read(reinterpret_cast<char *>(&size), sizeof(size));
        string buffer;
        buffer.resize(size);
        someFile.read(&buffer[0], buffer.size());
        return buffer;
    }
    return "null";
}

void binaryAppend(string path, string data) {
    fstream someFile(path, ios_base::out | ios_base::binary | ios_base::app);
    if (someFile.is_open()) {
        unsigned int size = data.size();
        someFile.write(reinterpret_cast<char *>(&size), sizeof(size));
    }
}

void binaryWrite(string path, string data) {
    fstream someFile(path, ios_base::out | ios_base::binary);
    if (someFile.is_open()) {
        unsigned int size = data.size();
        someFile.write((char *) &size, sizeof(size));
    }
}


void createHeader();

template <typename T>
void toBinary(T data) {

}
int main() {
    binaryWrite("output/hello.tga", "Hello World!");
    cout << endl;
    cout << binaryRead("output/hello.tga") << endl;
    return 0;
}