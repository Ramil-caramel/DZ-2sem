#include <initializer_list>
#include <iostream>
#include <fstream>
#include <string>

struct Node
{
    int value;
    Node* left_ptr;
    Node* right_ptr;

    Node(int value){
        this->value = value;
        left_ptr = nullptr;
        right_ptr = nullptr; 
    }
    ~Node(){
        if (left_ptr){
            delete left_ptr;
        }
        if (right_ptr){
            delete right_ptr;
        }
    }

};


class BSTree {
private:
    Node* root;
    void print(const Node* root);
    void return_value(const Node*, std::ofstream & outfile);
    Node* find_element_ptr(int v);

public:
    BSTree() : root{nullptr} {};
    BSTree(std::initializer_list<int> list);

    bool add_element(int v);
    void print(); 

    bool save_to_file(const std::string& path);
    bool load_from_file(const std::string& path);
    bool find_element(int value);
    bool delete_element(int value);

    ~BSTree();
};
