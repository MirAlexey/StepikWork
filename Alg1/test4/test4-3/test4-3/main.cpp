#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

class Data{
public:
    string code;
    string letter;
    int frequency;
    Data(){
        letter = "";
        code ="";
        frequency = 0;
    }
    bool operator < (Data* data){
        return this->frequency < data->frequency;
    }
    bool operator < (Data data){
        return this->frequency < data.frequency;
    }
    bool operator > (Data* data){
        return this->frequency > data->frequency;
    }
    bool operator > (Data data){
        return this->frequency > data.frequency;
    }
};

class Node{
public:
    Data *data;
    Node *left;
    Node *right;
    Node *parent;
    bool list;
    Node(){
        left = right = parent = NULL;
        list= false;
        data = new Data();
    }
    bool operator < (Node* node){
        return this->data < node->data ;
    }
    bool operator < (Node node){
        return this->data < node.data;
    }
    bool operator > (Node* node){
        return this->data > node->data;
    }
    bool operator > (Node node){
        return this->data > node.data;
    }
};

int main(){




}
