#include <iostream>
#include <ostream>
#include <vector>


using namespace std;



struct Data{
    static int b;
    static int max_key;
    int _key;
Data(){

    _key = 0;
}
Data(int key){

    this->_key = key;
}
void Execute(){
    cout << _key;
}
bool operator()(){
    this->Execute();
    return true;
}
bool operator ==(Data data){
    return this->_key == data._key;
    }
bool operator !=(Data data){
    return this->_key != data._key;
    }
bool operator >(Data data){
    return this->_key > data._key;
    }
bool operator <(Data data){
    return this->_key < data._key;
    }

friend ostream& operator <<(ostream &s, Data* data);

static void Exec(Data* data){
    if(Data::b < 0) {
        Data::b = 0;
        Data::max_key = data->_key;
    }else{
    if(data->_key < Data::max_key){
        Data::b++;
    }
    Data::max_key = data->_key;
    }
}


};
ostream& operator <<(ostream &s, Data* data){
    return  s << data->_key<< " ";
}


template<class T>
struct Node{
  T* _data;
  Node *_parent;
  Node *_left;
  Node *_right;
  Node(){
      _parent = _left = _right = NULL;
      _data = new T();
  }
  Node(T* data){
      _data = data;
      _parent = _left = _right = NULL;
  }
};

template<class T>
class myTree{
private:

public:
    typedef void (*funcData)(T* data);
    Node<T> *_root;
    myTree(){
        this->_root = NULL;
    }
    myTree(Node<T> *data){
        this->_root = data;
    }
    bool InOrder(funcData funcdata= NULL, Node<T> *node = NULL){
        Node<T> *data;
        if (node == NULL){
            data = _root;
        }else{
            data = node;
        }
        if(data == NULL) {return false;}
        if(data->_left != NULL){InOrder(funcdata, data->_left);}
        if(funcdata){
            funcdata(data->_data);
        }else{
            cout << data->_data;
        }
        if(data->_right != NULL){InOrder(funcdata, data->_right);}
        return true;
    }
    bool PreOrder(funcData funcdata = NULL,Node<T> *node = NULL){
        Node<T> *data;
        if (node == NULL){
            data = _root;
        }else{
            data = node;
        }
        if(data == NULL) {return false;}
        if(funcdata){
            funcdata(data->_data);
        }else{
            cout << data->_data;
        }
        if(data->_left != NULL){PreOrder(funcdata,data->_left);}
        if(data->_right != NULL){PreOrder(funcdata,data->_right);}

        return true;
    }
    bool PostOrder(funcData funcdata= NULL,Node<T> *node = NULL){
        Node<T> *data;
        if (node == NULL){
            data = _root;
        }else{
            data = node;
        }
        if(data == NULL) {return false;}
        if(data->_left != NULL){PostOrder(funcdata,data->_left);}
        if(data->_right != NULL){PostOrder(funcdata,data->_right);}
        if(funcdata){
            funcdata(data->_data);
        }else{
            cout << data->_data;
        }
        return true;
    }
    Node<T> *Root(){
        return _root;
    }
    Node<T> *FindNode(T *data,Node<T> *node  = NULL){
        Node<T> *n;
        if (node == NULL){
            n = _root;
        }else{
            n = node;
        }
        while(n != NULL && *n->_data != *data){
            if (*n->_data > *data){
                n = n->_left;
            }else{
                n = n->_right;
            }
        }
        return n;
    }
    Node<T> *AddNode(Node<T> *new_node){
        Node<T> *node;
        Node<T> *node_parent;
        if(_root== NULL){
            _root = new_node;
            return _root;
        }
        while(node != NULL ){
            if (node->_data > new_node->_data){
                node = node->_left;
            }else{
                node = node->_right;
            }
            node_parent = node;
        }
        new_node->_parent = node_parent;
        if(node_parent->_data > new_node->_data){
           node_parent->_left = new_node;
        }else{
           node_parent->_right = new_node;
        }
        return new_node;
    }


};
int Data::b = -1;
int Data::max_key=0;
vector<Data*> arr;

void ExecF(Data* data){
    if(Data::b < 0) {
        Data::b = 0;
        Data::max_key = data->_key;
    }else{
    if(data->_key < Data::max_key){
        Data::b++;
    }
    if(data->_key == Data::max_key){
        if (arr.size() !=0){
            Data* d = arr.back();
            if(d->_key != data->_key){
                arr.push_back(data);
            }
        }else{
            arr.push_back(data);
        }
    }
    Data::max_key = data->_key;
    }
}

bool IsCorrect(myTree<Data> *tree, Data *d, Node<Data> *n){
    if(d == NULL || n == NULL || tree == NULL){return true;}
    Node<Data> *node = tree->FindNode(d, n);
    if(node == NULL || node->_left == NULL){return true;}
    if(tree->FindNode(d, node->_left) != NULL){
        return false;
    }
    return IsCorrect(tree,d,node->_right);
}


int main()
{

    int m;
    cin >> m;
    if (m ==0){
        cout<< "CORRECT";
        return 0;
    }
    Node<Data> **arrNode = new Node<Data>*[m];
    int **arrint = new int*[m];
    for(int i=0;i<m;i++){
        arrNode[i]=NULL;
        arrint[i]=new int[3];
        cin >> arrint[i][0] >> arrint[i][1] >> arrint[i][2];
    }
    for(int i=0;i<m;i++){
        int n,l,r;
        n =arrint[i][0];
        l = arrint[i][1];
        r = arrint[i][2];
        if(arrNode[i]==NULL){
            arrNode[i]= new Node<Data>(new Data(n));
        }
        if(l != -1 && arrNode[l]==NULL){
            arrNode[l]= new Node<Data>(new Data(arrint[l][0]));
        }
        if(r !=-1 && arrNode[r]==NULL){
            arrNode[r]= new Node<Data>(new Data(arrint[r][0]));
        }
        if(l != -1){
            arrNode[i]->_left = arrNode[l];
        }
        if(r != -1){
            arrNode[i]->_right = arrNode[r];
        }
    }

    myTree<Data> *mytree = new myTree<Data>(arrNode[0]);


    mytree->InOrder(ExecF);

    if(Data::b<0){
        cout<< "ERROR";
        return 0;
    }
    if(Data::b > 0){
        cout<< "INCORRECT";
        return 0;
    }
    bool b = true;
    for (int i =0;i< arr.size();i++){
        b&=IsCorrect(mytree, arr[i], mytree->Root());
    }

    cout<< (b?"CORRECT":"INCORRECT");


return 0;
}
