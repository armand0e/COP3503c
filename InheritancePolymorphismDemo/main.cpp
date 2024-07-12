#include <iostream>
#include <string>
using namespace std;

// Declare an Animal class (base class)
class Animal {
protected: 
  string name;

public:
    // Create a constructor for the Animal class that passes a string variable
    Animal(string s) {
        name = s;
    }
    
    // Create a void function: Eat()
    void Eat() {
        cout << "// \"\"--.._\n||  (_)  _ \"-._\n||    _ (_)    '-.\n||   (_)   __..-'\n \\__..--\"\"" << endl;
        cout << "nom nom nom... *burp*" << endl; 
    }

    //(7) Create a void function: Sleep()
    void Sleep() {
        cout << "ZZZZZZZZZZzzzzzzzzz........" << endl;
        cout << "      _____|~~\\_____      _____________\n  _-~               \\    |    \\\n  _-    | )     \\    |__/   \\   \\\n  _-         )   |   |  |     \\  \\\n  _-    | )     /    |--|      |  |\n __-_______________ /__/_______|  |_________\n(                |----         |  |\n `---------------'--\\\\\\\\      .`--'\n                              `||||" << endl; 
    }

};
// Declare a derived Dog class (child class) 
class Dog :: virtual public Animal {

    // Create a Dog constructor that inherits the Animal constructor
    Dog(string s):Animal(s) {
        
    }
    //(11) Create a void function: Bark()
    void Bark() {
        //(12) Create a print statement
        cout << "woof" << endl;
    }
        //(13) Override the Eat() function, this is Polymorphism
    //(14) Create a print statement 
};

//(15) Declare a derived Cat class (child class)
class Cat :: virtual public Animal {
    //(16) Create a Dog constructor that inherits the Animal constructor

    //(17) Create a void function: Bark()
 
        //(18) Create a print statement
};

//(19) Declare a derived CatDog class that inherits Cat and Dog (child class)
class CatDog :: public Cat, public Dog
    //(20) Create a CatDog constructor that inherits the Animal constructor
    //(21) Notice the error. This is the "diamond problem" go back to steps 9 and 15 add the virtual keyword

    //(22) Create a void function: Bark()

        //(23) Create a print statement


int main() {
  
    Animal someAnimal("Animal");
    someAnimal.Sleep();
   /*  Dog myDog;
    Cat myCat;
    CatDog myCatDog;

    someAnimal.Eat();
    someAnimal.Sleep();

    cout << endl;

    myDog.Eat(); 
    myDog.Sleep();
    myDog.Bark();

    cout << endl;

    myCat.Eat();
    myCat.Sleep();
    myCat.Meow();

    cout << endl;

    myCatDog.Eat();
    myCatDog.Sleep();
    myCatDog.Bark();
    myCatDog.Meow();
    myCatDog.Meork(); */
   
    return 0;
}