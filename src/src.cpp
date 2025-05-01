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
    root = nullptr;
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
    Node* ptr_parent = nullptr;

    
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
            return ptr_parent;
        } 
    }
    return nullptr;
}


bool BSTree::delete_element(int value){
    Node* ptr_f = find_element_ptr(value);

    //1 нет такого узла
    if (!ptr_f && root->value != value){
        std::cout << "нет такого узла" << std::endl;
        return false;
    } 

    if (root ->value != value){    
    if (ptr_f->value > value){
        Node* ptr_f_left = ptr_f->left_ptr;
        //2 у узла нет детей
        if (!(ptr_f_left->left_ptr) && !(ptr_f_left->right_ptr)){
            delete ptr_f_left;
            ptr_f->left_ptr = nullptr;
            return true;
        }
        //3 у узла только один ребенок
        if(!(ptr_f_left->left_ptr) || !(ptr_f_left->right_ptr)){
            if(!(ptr_f_left->left_ptr)){
                ptr_f->left_ptr = ptr_f_left->right_ptr;
                ptr_f_left->right_ptr = nullptr;
                delete ptr_f_left;
                return true;
            }
            if(!(ptr_f_left->right_ptr)){
                ptr_f->left_ptr = ptr_f_left->left_ptr;
                ptr_f_left->left_ptr = nullptr;
                delete ptr_f_left;
                return true;
            }
        }
    }
    if (ptr_f->value < value){
        Node* ptr_f_right = ptr_f->right_ptr;
        //2 у узла нет детей
        if (!(ptr_f_right->left_ptr) && !(ptr_f_right->right_ptr)){
            delete ptr_f_right;
            ptr_f->right_ptr = nullptr;
            return true;
        }
        //3 у узла только один ребенок
        if(!(ptr_f_right->left_ptr) || !(ptr_f_right->right_ptr)){
            if(!(ptr_f_right->left_ptr)){
                ptr_f->right_ptr = ptr_f_right->right_ptr;
                ptr_f_right->right_ptr = nullptr;
                delete ptr_f_right;
                return true;
            }
            if(!(ptr_f_right->right_ptr)){
                ptr_f->right_ptr = ptr_f_right->left_ptr;
                ptr_f_right->left_ptr = nullptr;
                delete ptr_f_right;
                return true;
            }
        }
    }
}
    // 4
    //ptr_f - родитель ноды которую нужно удалить
    //ptr_f_child - сама эта нода
    //ptr_zamena - родитель для замены
    
    Node *ptr_f_child, *ptr_zamena;
    ptr_f_child = root;
    if(root->value != value){
        if (ptr_f->value > value) ptr_f_child = ptr_f->left_ptr;
        else  ptr_f_child = ptr_f->right_ptr;
    }
    ptr_zamena = ptr_f_child -> right_ptr;
    
    Node* ptr_zamena_child = ptr_zamena;
    while( ptr_zamena_child->left_ptr != nullptr) {
        ptr_zamena = ptr_zamena_child;
        ptr_zamena_child = ptr_zamena_child -> left_ptr;
        
    }

    int a = ptr_zamena_child->value;
    
    this -> delete_element(ptr_zamena_child->value);
    if(root->value != value){
        ptr_f_child -> value = a; 
    }    
    else{
        root->value = a;
    }
    return true;

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