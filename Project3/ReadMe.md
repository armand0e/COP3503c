# For Apple Silicon Mac Users using CLion:
1. Open your terminal and type:
```
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install.sh)"
```
2. Once that is complete, type:
```
brew install sfml
```

3. Once that is complete, in your Minesweeper project, copy and paste this into your CMakeLists.txt file:
```
cmake_minimum_required(VERSION 3.14)
project(<your project name here>)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)

add_executable(<your project name here> ${SOURCE_FILES})

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
target_link_libraries(<your project name here> sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
Be sure to replace <your project name here> with the name of the project you make in CLion. 
```
4. Lastly, copy and paste the code in your main.cpp file
```
#include <iostream>
#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML Works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Red);

    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
            window.close();
            }
        }

    window.clear();
    window.draw(shape);
    window.display();
    }
    return 0;
}
```

# For Windows Users using CLion:
1. Open your Command Prompt and type:
```
systeminfo
```
Look for the System Type and check to see if your type is 32-bit or 64-bit. In the figure below this is what you should see for 64-bit machines:

image.png

2. Go to https://www.sfml-dev.org/download/sfml/2.5.1/Links to an external site. and download the SFML package library that corresponds to your system. For example, a 64-bit machine running MinGW, you will download the package here:
image.png

3. Once the download is complete, locate it and extract the zip file somewhere on your computer. It shouldn't matter where you have it, but you must keep it there while you work on the project.

4. In the SFML-2.5.1 folder you extracted, go to the folder named bin. Inside this folder you should see the following:
image.png

Copy all files and paste them into your cmake-build-debug folder in your CLion project. It should look like this in your CLion:


image.png

4. Once that is complete, in your Minesweeper project, copy and paste this into your CMakeLists.txt file:
```
cmake_minimum_required(VERSION 3.2)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(<your project name here>)

## If you want to link SFML statically
# set(SFML_STATIC_LIBRARIES TRUE)

## In most cases better set in the CMake cache
set(SFML_DIR "<sfml root prefix>/lib/cmake/SFML")

find_package(SFML 2.5.1 COMPONENTS system window graphics audio REQUIRED)
add_executable(<Project Name> main.cpp)
target_link_libraries(<Project Name> sfml-system sfml-window sfml-graphics sfml-audio)
Be sure to replace <your project name here> with the name of the project you make in CLion. 
```
5. Now we need to get the <sfml root prefix>. Open the SFML-2.5.1 file you downloaded earlier and copy the path to that folder. This can be done by clicking on the path bar near the top of your File Explorer window:
image.png

6. Copy that path and paste it into the CMakeLists.txt file in your CLion Project and be sure to replace all back-slashes ( \ ) with forward-slashes ( / ).

7. After this step, in some instances your IDE may not automatically reset the cache and reload the project. In order to do so manually, go to: Tools > CMake > Reset Cache and Reload Project
image.png


8. Lastly, copy and paste the code in your main.cpp file
```
#include <iostream>
#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML Works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Red);

    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
            window.close();
            }
        }

    window.clear();
    window.draw(shape);
    window.display();
    }
    return 0;
}
```
