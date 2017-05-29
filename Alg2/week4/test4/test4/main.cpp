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
  int _height;
  int _size;
  Node(){
      _parent = _left = _right = NULL;
      _data = new T();
      _height = 1;
      _size = 1;
  }
  Node(T* data){
      _data = data;
      _parent = _left = _right = NULL;
      _height = 1;
      _size = 1;
  }
  int getHeightLeft(){
      if(this->_left == NULL) return 0;
      return this->_left->_height;
  }
  int getHeightRight(){
      if(this->_right == NULL) return 0;
      return this->_right->_height;
  }
  int getSizeLeft(){
      if(this->_left == NULL) return 0;
      return this->_left->_size;
  }
  int getSizeRight(){
      if(this->_right == NULL) return 0;
      return this->_right->_size;
  }

};

template<class T>
class myTree{
private:
    bool updateHeight(Node<T> *node){
       if(node == NULL) return false;
       int max =0;

       int size = node->getSizeLeft() + node->getSizeRight() + 1;

       if(node->_left !=NULL) {max = node->_left->_height;}
       if(node->_right != NULL && node->_right->_height > max) {max = node->_right->_height;}
       //if (node->_height != ++max) {
           node->_height = ++max;
       //    b=true;
       //}
       //if(node->_size != size){
          node->_size = size;
       //   b=true;
       //}
       return true;
    }

    bool verifyBalans(Node<T> *node){
        if (node == NULL) return false;
        int delH = node->getHeightLeft() - node->getHeightRight();
        if((delH<0?-delH:delH)>1){
            if(delH<0){
                Node<T> *alpha = node;
                Node<T> *beta = node->_right;
                Node<T> *B;
                Node<T> *C;
                Node<T> *gamma;
                if (beta->getHeightLeft() <= beta->getHeightRight()){
                    B = beta->_left;
                    beta->_parent = alpha->_parent;
                    alpha->_parent = beta;
                    alpha->_right = B;
                    beta->_left = alpha;
                    if(B!= NULL){B->_parent=alpha;}
                    if(beta->_parent != NULL){
                        if(beta->_parent->_left == alpha){
                            beta->_parent->_left = beta;
                        }else{
                            beta->_parent->_right = beta;
                        }
                    }
                    updateHeight(alpha);
                    updateHeight(beta);
                    updateHeight(beta->_parent);
                }else{
                    gamma = beta->_left;
                    B = gamma->_left;
                    C = gamma->_right;
                    gamma->_parent = alpha->_parent;
                    alpha->_parent = gamma;
                    beta->_parent = gamma;
                    alpha->_right = B;
                    beta->_left = C;
                    if(B!= NULL){B->_parent = alpha;}
                    if(C!= NULL){C->_parent = beta;}
                    gamma->_left = alpha;
                    gamma->_right = beta;
                    if(gamma->_parent != NULL){
                        if(gamma->_parent->_left == alpha){
                            gamma->_parent->_left = gamma;
                        }else{
                            gamma->_parent->_right = gamma;
                        }
                    }
                    updateHeight(alpha);
                    updateHeight(beta);
                    updateHeight(gamma);
                    updateHeight(gamma->_parent);
                }
            }else{
                Node<T> *alpha = node;
                Node<T> *beta = node->_left;
                Node<T> *B;
                Node<T> *C;
                Node<T> *gamma;
                if (beta->getHeightLeft() >= beta->getHeightRight()){
                    B = beta->_right;
                    beta->_parent = alpha->_parent;
                    alpha->_parent = beta;
                    alpha->_left = B;
                    beta->_right = alpha;
                    if(B!= NULL){B->_parent=alpha;}
                    if(beta->_parent != NULL){
                        if(beta->_parent->_left == alpha){
                            beta->_parent->_left = beta;
                        }else{
                            beta->_parent->_right = beta;
                        }
                    }
                    updateHeight(alpha);
                    updateHeight(beta);
                    updateHeight(beta->_parent);
                }else{
                    gamma = beta->_right;
                    B = gamma->_left;
                    C = gamma->_right;
                    gamma->_parent = alpha->_parent;
                    alpha->_parent = gamma;
                    beta->_parent = gamma;
                    alpha->_left = C;
                    beta->_right =B;
                    if(B!= NULL){B->_parent = beta;}
                    if(B!= NULL){C->_parent = alpha;}
                    gamma->_left = beta;
                    gamma->_right = alpha;
                    if(gamma->_parent != NULL){
                        if(gamma->_parent->_left == alpha){
                            gamma->_parent->_left = gamma;
                        }else{
                            gamma->_parent->_right = gamma;
                        }
                    }
                    updateHeight(alpha);
                    updateHeight(beta);
                    updateHeight(gamma);
                    updateHeight(gamma->_parent);
                }
            }
            return true;
        }
        return false;
    }

    void verifyTree(Node<T> *node){
            updateHeight(node);
            verifyBalans(node);
            if(node->_parent == NULL){
                _root = node;
            }else{
            verifyTree(node->_parent);
            }

    }

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
        node = _root;
        while(node != NULL ){
            node_parent = node;
            if (*node->_data > *new_node->_data){
                node = node->_left;
            }else{
                node = node->_right;
            }

        }
        new_node->_parent = node_parent;
        if(*node_parent->_data > *new_node->_data){
           node_parent->_left = new_node;
        }else{
           node_parent->_right = new_node;
        }
        verifyTree(new_node->_parent);
        return new_node;
    }
    bool DelNode(Node<T> *node){
        if(node == NULL) return true;
        if(node->_left == NULL && node->_right == NULL){
            if(node->_parent == NULL){
                _root= NULL;
            }else{
                if(node->_parent->_left == node){
                    node->_parent->_left = NULL;
                }else{
                    node->_parent->_right = NULL;
                }
            }
            verifyTree(node->_parent);
            delete node;
            return true;
        }
        if(node->_left != NULL && node->_right != NULL){
            Node<T> *prev = Prev(node);
            Node<T> *prev_l = prev->_left;
            Node<T> *prev_p = prev->_parent;
            prev->_parent = node->_parent;
            prev->_left = node->_left;
            prev->_right = node->_right;
            node->_left->_parent = prev;
            node->_right->_parent = prev;
            if(prev->_parent == NULL){
                _root = prev;
            }else{
                if(prev->_parent->_left == node){
                   prev->_parent->_left = prev;
                }else{
                   prev->_parent->_right = prev;
                }
            }
            prev_p->_right =  prev_l;
            if(prev_l != NULL){prev_l->_parent = prev_p;}
            verifyTree(prev_p);
            delete node;
            return true;
        }
        if(node->_left == NULL){
            if(node->_parent == NULL){
                _root = node->_right;
                node->_right->_parent = NULL;
            }else{
                if(node->_parent->_left == node){
                   node->_parent->_left = node->_right;
                }else{
                   node->_parent->_right = node->_right;
                }
                node->_right->_parent = node->_parent;
            }
            verifyTree(node->_parent);
            delete node;
            return true;
        }
        if(node->_parent == NULL){
            _root = node->_left;
            node->_left->_parent = NULL;
        }else{
            if(node->_parent->_left == node){
               node->_parent->_left = node->_left;
            }else{
               node->_parent->_right = node->_left;
            }
            node->_left->_parent = node->_parent;
        }
        verifyTree(node->_parent);
        delete node;
        return true;
    }
    Node<T>* Max(Node<T> *elem = NULL){
        Node<T> *node;
        if (elem == NULL){
            node = _root;
        }
        node = elem;
        while(node->_right != NULL){
            node = node->_right;
        }
        return node;

    }
    Node<T>* Min(Node<T> *elem = NULL){
        Node<T> *node;
        if (elem == NULL){
            node = _root;
        }
        node = elem;
        while(node->_left != NULL){
            node = node->_left;
        }
        return node;

    }
    Node<T>* Next(Node<T> *elem = NULL){
        Node<T> *node;
        if (elem == NULL){
            node = _root;
        }
        node = elem;
        if(node->_right == NULL){
            while (node->_parent != NULL && node->_parent->_right == node) {
                node = node->_parent;
            }
            return node->_parent;
        }else{
            return Min(node->_right);
        }

    }
    Node<T>* Prev(Node<T> *elem = NULL){
        Node<T> *node;
        if (elem == NULL){
            node = _root;
        }
        node = elem;
        if(node->_left == NULL){
            while (node->_parent != NULL && node->_parent->_left == node) {
                node = node->_parent;
            }
            return node->_parent;
        }else{
            return Max(node->_left);
        }
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

    /*int m;
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

    cout<< (b?"CORRECT":"INCORRECT");*/
    //--------------------------    ----------------------
    Node<Data> **arrNode = new Node<Data>*[10];
    for(int i=0;i<10;i++){
        arrNode[i]=NULL;
    }
    myTree<Data> *mytree = new myTree<Data>();
    int m[]={5,1,10,9,11,8,12,7,6,4,3};
    for(int i = 0; i< 11; i++){
        arrNode[i] =new Node<Data>(new Data(m[i]));
        mytree->AddNode(arrNode[i]);
    }
    mytree->DelNode(mytree->FindNode(new Data(12)));
    mytree->DelNode(mytree->FindNode(new Data(11)));
    mytree->DelNode(mytree->FindNode(new Data(9)));

return 0;
}

