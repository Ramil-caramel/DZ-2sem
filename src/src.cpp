#include <Header.hpp>

bool BSTree::add_element(int v){
    Node* ptr_child = root;
    Node* ptr_parent = nullptr;

    if (root == nullptr){
        root = new Node(v);
        return 1;
    }else{
        while(ptr_child != nullptr) {

            if (ptr_child->value > v){
                ptr_parent = ptr_child;
                ptr_child = ptr_child->left_ptr;
            }

            else if(ptr_child->value < v){
                ptr_parent = ptr_child;
                ptr_child = ptr_child->right_ptr;
            }

            else{
                return 0;
            } 
        }

        if (ptr_parent->value > v){
            ptr_parent->left_ptr = new Node(v);
            return 1;
        }

        else if(ptr_parent->value < v){
            ptr_parent->right_ptr = new Node(v);
            return 1;
        }

        else{
            return 0;
        }
    }
}

BSTree::BSTree(std::initializer_list<int> list){
    for(std::initializer_list<int>::iterator itr = list.begin() ; itr != list.end() ;++itr){
        this->add_element(*itr);
    }
}

void BSTree::print(){
    print(root);
    std::cout << std::endl;
} 

void BSTree::print(const Node* root){
    if (root == nullptr){
        return;
    }
    print(root->left_ptr);
    std::cout << root->value << " ";
    print(root->right_ptr);
}

void BSTree::return_value(const Node* root, std::ofstream & outfile){
    if (root == nullptr){
        return;
    }

    outfile << root->value << " ";    
    return_value(root->left_ptr, outfile);
    return_value(root->right_ptr, outfile);
}

bool BSTree::save_to_file(const std::string& path){
    if (!path.empty() and path[path.size() - 1] != '/'){
        std::cout << "некоректный путь, либо добавьте в конце /, либо введите" << std::endl;
        return 0;
    }
    std::string file = path + "/" + "BSTree_output.txt";

    if (path.empty()) file = "BSTree_output.txt";
     
    std::ofstream outfile(file);

    if (!outfile.is_open()) {
        std::cout << "Не удалось открыть файл!" << std::endl;
        return 0;
    }

    return_value(root, outfile);
    outfile.close();
    return 1; 
}


bool BSTree::load_from_file(const std::string& path){
    std::ifstream fromfile(path);
    if (!fromfile.is_open()) {
        std::cout << "Не удалось открыть файл!" << std::endl;
        return 0;
    }
    std::string src,prom = "";
    std::getline(fromfile, src);

    for(int i{}; i < src.size(); ++i){
        if (src[i] != ' ') prom+=src[i];

        else if(src[i] == ' ' && !prom.empty()){
            this -> add_element(std::stoi(prom));
            prom = "";
            continue;
        }
    }
    if (!prom.empty())this -> add_element(std::stoi(prom));
    return 1;
}

bool BSTree::find_element(int value){
    Node* ptr = root;
    while (ptr != nullptr){
        if (ptr->value == value){
            return true;
        }

        else if (ptr->value > value){
            ptr = ptr->left_ptr;
        } 

        else if (ptr->value < value){
            ptr = ptr->right_ptr;
        }
    }
    return false;
}

Node* BSTree::find_element_ptr(int v){
    Node* ptr_child = root;

    while(ptr_child != nullptr) {

        if (ptr_child->value > v){
            ptr_child = ptr_child->left_ptr;
        }

        else if(ptr_child->value < v){
            ptr_child = ptr_child->right_ptr;
        }

        else{
                return ptr_child;
        } 
    }
    return nullptr;
}


bool BSTree::delete_element(int value){
    //1
    Node* ptr_f = find_element_ptr(value);
    if (!ptr_f) return false;
    //2
    if (!(ptr_f->left_ptr) && !(ptr_f->right_ptr)){
        delete ptr_f;
    }
}

BSTree::~BSTree(){
    if (root){
        delete root;
    }
}

/*
    }

    bool recur_add(Node* childe, Node* parent, int value){
        if (root == nullptr){
            root = new Node(value);
            return true;
        }
        if ( childe == nullptr){
            if(parent->left_ptr == childe){
                parent->left_ptr = new Node(value);
            }else{
                parent->right_ptr = new Node(value);
            }
            return true;
        }
        if(childe->value == value){
            return false;
        }
        if(childe->value > value){
            return recur_add(childe->left_ptr, childe, value);
        }
        if(childe->value < value){
            return recur_add(childe->right_ptr, childe, value);
        }
    }

    bool just_add(int vol){
        return recur_add(root, nullptr, vol);
    }
    */