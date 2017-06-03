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

enum Direction {Straight,Simm,Reverse};
enum updateDirection {up,down};

std::map<char,string> myCode;

class Tree{
private:

public:
    Node *root;
    Tree(){
    root = new Node();
    }
    Tree(Node *node){
        root=node;
    }
    bool applyFunc(bool (*Func)(Node *node) , Node *node, Direction direction = Straight){
        if(node == NULL) return false;
        if(direction == Straight){
            Func(node);
            applyFunc(Func, node->left, direction);
            applyFunc(Func, node->right, direction);
        }
        if(direction == Simm){
            applyFunc(Func, node->left, direction);
            Func(node);
            applyFunc(Func, node->right, direction);
        }
        if(direction == Reverse){
            applyFunc(Func, node->left, direction);
            applyFunc(Func, node->right, direction);
            Func(node);
        }
        return true;
    }
    ~Tree(){

    }
};

bool myFunc(Node *node){
    if (node->list==false) return false;
    string code="";
    char letter= node->data->letter[0];
    if(node->parent == NULL){code = node->data->code;}
    while(node->parent != NULL){
        code=node->data->code + code;
        node = node->parent;
    }
    //code=node->data->code + code;
    myCode[letter]=code;
    return true;
}

class QueuePriority{
private:
    std::vector<Node*> heapNodes;
    void update(updateDirection dir = up){
     if(dir==down){
         int i = 1;
         while(i< heapNodes.size()){
             int j;
            if(2*i >= heapNodes.size()) break;
            if(2*i+1 >= heapNodes.size()){
                j = 2*i;
            }else{
            j =  heapNodes[2*i]->data->frequency < heapNodes[2*i+1]->data->frequency?2*i:2*i+1;
            }
            if(heapNodes[i]->data->frequency > heapNodes[j]->data->frequency){
                Node *p = heapNodes[i];
                heapNodes[i] = heapNodes[j];
                heapNodes[j] = p;
                i=j;
            }else{
                break;
            }
         }
    }else{
         int i = heapNodes.size()-1;
         while(i>1){
            if(heapNodes[i]->data->frequency < heapNodes[i/2]->data->frequency){
                Node *p = heapNodes[i];
                heapNodes[i] = heapNodes[i/2];
                heapNodes[i/2] = p;
                i/=2;
            }else{
                break;
            }
         }

     }
    }
public:
    QueuePriority(){
       heapNodes.push_back(new Node());
    }
    bool insertElem(Node *node){
        heapNodes.push_back(node);
        update();
        return true;
    }
    Node *getFirstElem(){
        if(heapNodes.size()<2) return NULL;
        Node *node = heapNodes[1];
        heapNodes[1] = heapNodes.back();
        heapNodes.pop_back();
        update(down);
        return node;
    }
    int size(){
        return heapNodes.size();
    }
};




int main()
{
    std::map<char, int> myMap;

    QueuePriority * myQueue = new QueuePriority();
    Tree *mytree;
    string str;
    //cin >> str;
    str = "aaaaaaaassddddddffffggggghhhhhhjjjjjjjkkkkk";
    //str = "abacabad";
    //str="a";
    for(int i = 0 ; i<str.size();i++){
        myMap[str[i]]++;
    }
    for (std::map<char,int>::iterator it=myMap.begin(); it!=myMap.end(); ++it){
       Node *node = new Node();
       node->data->letter = (*it).first;
       node->data->frequency =  (*it).second;
       node->list = true;
       myQueue->insertElem(node);
    }
    while(myQueue->size()>1){
        Node *left = myQueue->getFirstElem();
        Node *right = myQueue->getFirstElem();
        if (left != NULL ){
            left->data->code="0";
        }
        if (right != NULL ){
            right->data->code="1";
            Node *par = new Node();
            par->left = left;
            par->right = right;
            par->data->frequency = left->data->frequency + right->data->frequency;
            left->parent = right->parent = par;
            myQueue->insertElem(par);
        }else{
            mytree = new Tree(left);
        }
    }

    mytree->applyFunc(myFunc, mytree->root);
    string result ="";
    for(int i = 0; i< str.size(); i++){
        result=result+myCode[str[i]];
    }
    cout<< myCode.size() <<" "<< result.size()<< std::endl;
    for(std::map<char,string>::iterator it=myCode.begin(); it!=myCode.end(); ++it){
        cout<< (*it).first << ": " << (*it).second << std::endl;
    }
    cout<< result<< std::endl;


}

