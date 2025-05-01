#include <iostream>
#include "Header.hpp"

int main() {
    
    BSTree tree = {10, 5, 15, 4, 7, 14, 20, 21, 13};
    tree.print();

    std::cout << tree.delete_element(10) << std::endl;
    tree.print();


    std::cout << std::endl;




/*
    BSTree t;
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
*/
    return 0;
}


