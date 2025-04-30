#include <iostream>
#include "Header.hpp"

int main() {
    BSTree t;
    BSTree tree{10, 4, 20, 1, 5};
    tree.print();
    std::cout << std::endl;
    t.load_from_file("./BSTree_output.txt");
    t.print();
    std::cout << std::endl;
    t.add_element(20);
    t.add_element(30);
    t.add_element(10);
    t.add_element(5);
    t.add_element(25);
    t.add_element(27);
    t.add_element(7);
    t.print();
    t.save_to_file("");

    return 0;
}


