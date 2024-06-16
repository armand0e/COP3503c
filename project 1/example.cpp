#include "LinkedList.h"
#include <iostream>

int main() {
    LinkedList<int> list;
    list.append(1);
    list.append(2);
    list.append(3);
    list.printList();

    try {
        std::cout << "Data at node 1: " << list.getNode(1)->data << std::endl;
        std::cout << "Data at node 3: " << list.getNode(3)->data << std::endl; // This will throw an exception
    } catch (const std::out_of_range& e) {
        std::cerr << e.what() << std::endl;
    }

    LinkedList<std::string> strList;
    strList.append("Hello");
    strList.append("World");
    strList.printList();

    try {
        std::cout << "Data at node 0: " << strList.getNode(1)->data << std::endl;
        std::cout << "Data at node 2: " << strList.getNode(2)->data << std::endl; // This will throw an exception
    } catch (const std::out_of_range& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
