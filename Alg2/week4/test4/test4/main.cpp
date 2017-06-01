#include <iostream>
#include <ostream>
#include <vector>


using namespace std;



struct Data{
    static int b;
    static long max_key;
    long _key;
    long sum;
Data(){

    _key = 0;
    sum = 0;
}
Data(int key){

    this->_key = key;
    sum = key;
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
  int getHeight(){
      if(this == NULL) return 0;
      return this->_height;
  }
  int getSizeLeft(){
      if(this->_left == NULL) return 0;
      return this->_left->_size;
  }
  int getSizeRight(){
      if(this->_right == NULL) return 0;
      return this->_right->_size;
  }
  int getSize(){
      if(this == NULL) return 0;
      return this->_size;
  }
  T* getDataLeft(){
      if(this->_left == NULL) return NULL;
      return this->_left->_data;
  }
  T* getDataRight(){
      if(this->_right == NULL) return NULL;
      return this->_right->_data;
  }
  T* getData(){
      if(this == NULL) return NULL;
      return this->_data;
  }

};



template<class T>
class myTree{
public:
    typedef void (*funcDataUpdate)(T* d_data, T* s1_data, T* s2_data);
private:
    bool updateHeight(Node<T> *node){
        if(node == NULL) return false;
        int max =0;
        if(node->_left !=NULL) {max = node->_left->_height;}
        if(node->_right != NULL && node->_right->_height > max) {max = node->_right->_height;}
        node->_height = ++max;

        if(this->f!=NULL){this->f(node->getData(),node->getDataLeft(),node->getDataRight());}

        node->_size = node->getSizeLeft() + node->getSizeRight() + 1;

        return true;
    }
    Node<T>* verifyBalans(Node<T> *node){
        if (node == NULL) return NULL;
        int delH = node->getHeightLeft() - node->getHeightRight();
        updateHeight(node);
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
                    return beta;
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
                    return gamma;
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
                    return beta;
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
                     return gamma;
                }
            }

        }
        return node;
    }
    void verifyTree(Node<T> *node){
            if (node == NULL) return;
            updateHeight(node);
            verifyBalans(node);
            if(node->_parent == NULL){
                _root = node;
            }else{
            verifyTree(node->_parent);
            }
    }
    Node<T>* MergeWithRoot(Node<T>* min_node,Node<T>* max_node, Node<T>* t_node){
        if(t_node == NULL) {return max_node;}
        t_node->_left = min_node;
        t_node->_right = max_node;
        if(min_node != NULL){t_node->_left->_parent = t_node;}
        if(max_node != NULL){t_node->_right->_parent = t_node;}
        updateHeight(t_node);
        return t_node;
    }
public:
    typedef void (*funcData)(T* data);
    Node<T> *_root;
    funcDataUpdate f;
    myTree(){
        this->_root = NULL;
        this->f = NULL;
    }
    myTree(Node<T> *data = NULL, funcDataUpdate f = NULL){
        this->_root = data;
        this->f = f;
    }
    bool InOrder(Node<T> *node, funcData funcdata= NULL){
        if (node == NULL){
            return false;
        }
        Node<T> *data;
        data = node;
        if(data->_left != NULL){InOrder(data->_left, funcdata );}
        if(funcdata){
            funcdata(data->_data);
        }else{
            cout << data->_data;
        }
        if(data->_right != NULL){InOrder(data->_right, funcdata );}
        return true;
    }
    bool InOrder(funcData funcdata = NULL){
        return InOrder(_root,funcdata);
    }
    bool PreOrder(Node<T> *node,funcData funcdata = NULL){
        if (node == NULL){
            return false;
        }
        Node<T> *data;
        data = node;
        if(funcdata){
            funcdata(data->_data);
        }else{
            cout << data->_data;
        }
        if(data->_left != NULL){PreOrder(data->_left, funcdata);}
        if(data->_right != NULL){PreOrder(data->_right, funcdata);}
        return true;
    }
    bool PreOrder(funcData funcdata = NULL){
        return PreOrder(_root,funcdata);
    }
    bool PostOrder(Node<T> *node,funcData funcdata= NULL){
        if (node == NULL){
            return false;
        }
        Node<T> *data;
        data = node;
        if(data->_left != NULL){PostOrder(data->_left,funcdata);}
        if(data->_right != NULL){PostOrder(data->_right,funcdata);}
        if(funcdata){
            funcdata(data->_data);
        }else{
            cout << data->_data;
        }
        return true;
    }
    bool PostOrder(funcData funcdata= NULL){
        return PostOrder(_root,funcdata);
    }
    Node<T>* Root(){
        return _root;
    }
    Node<T>* FindNode(T *data,Node<T> *node){
        if (node == NULL){
            return NULL;
        }
        Node<T> *n;
        n = node;
        while(n != NULL && *n->_data != *data){
            if (*n->_data > *data){
                n = n->_left;
            }else{
                n = n->_right;
            }
        }
        return n;
    }
    Node<T>* FindNode(T *data){
        return FindNode(data, _root);
    }
    Node<T>* AddNode(Node<T> *new_node){
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
    Node<T>* DelNode(Node<T> *node, bool free_mem = true){
        if(node == NULL) return NULL;
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
            if(free_mem) {
                delete node;
                return NULL;
            }
            node->_left = node->_right = node->_parent = NULL;
            return node;
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
            if(free_mem) {
                delete node;
                return NULL;
            }
            node->_left = node->_right = node->_parent = NULL;
            return node;
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
            if(free_mem) {
                delete node;
                return NULL;
            }
            node->_left = node->_right = node->_parent = NULL;
            return node;
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
        if(free_mem) {
            delete node;
            return NULL;
        }
        node->_left = node->_right = node->_parent = NULL;
        return node;
    }
    Node<T>* Max(Node<T> *elem){
        if (elem == NULL){
            return NULL;
        }
        Node<T> *node;
        node = elem;
        while(node->_right != NULL){
            node = node->_right;
        }
        return node;
    }
    Node<T>* Max(){
        return Max(_root);
    }
    Node<T>* Min(Node<T> *elem){
        if (elem == NULL){
            return NULL;
        }
        Node<T> *node;
        node = elem;
        while(node->_left != NULL){
            node = node->_left;
        }
        return node;
    }
    Node<T>* Min(){
        return Min(_root);
    }
    Node<T>* Next(Node<T> *elem){
        if (elem == NULL){
           return NULL;
        }
        Node<T> *node;
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
    Node<T>* Next(){
        return Next(_root);
    }
    Node<T>* Prev(Node<T> *elem){
        if (elem == NULL){
           return NULL;
        }
        Node<T> *node;
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
    Node<T>* Prev(){
        return Prev(_root);
    }
    Node<T>* OrderStatistics(int k,Node<T> *node){
        if(node == NULL) return NULL;
        int leftsize = node->getSizeLeft();
        if(k==leftsize+1){return node;}
        if(k<leftsize+1){
            return OrderStatistics(k,node->_left);
        }else{
            return OrderStatistics(k-leftsize-1,node->_right);
        }
    }
    Node<T>* AVLMergeWithRoot(Node<T>* min_node,Node<T>* max_node, Node<T>* t_node){
        if(min_node == NULL && max_node == NULL){
            if(t_node == NULL) return NULL;
            t_node->_left= t_node->_right = NULL;
            t_node->_height=1;
            return t_node;
        }
        int d = min_node->getHeight() - max_node->getHeight();
        d=d<0?-d:d;
        if(d<=1){
            return MergeWithRoot(min_node,max_node,t_node);
        }else{
            if(min_node->getHeight() > max_node->getHeight()){
                Node<T> *t = AVLMergeWithRoot(min_node->_right,max_node,t_node);
                min_node->_right = t;
                if(t != NULL) {t->_parent = min_node;}
                return verifyBalans(min_node);
            }else{
                Node<T> *t = AVLMergeWithRoot(min_node,max_node->_left,t_node);
                max_node->_left= t;
                if(t != NULL) {t->_parent = max_node;}
                return verifyBalans(max_node);
            }
        }
    }
    bool Split( T *key, Node<T>* &source_node, Node<T>* &dest_min_node, Node<T>* &dest_max_node){
        if(source_node == NULL){
            dest_min_node = NULL;
            dest_max_node = NULL;
            return true;
        }
        Node<T> *source_left = source_node->_left;
        Node<T> *source_right = source_node->_right;
        if(source_left != NULL) {source_left->_parent = NULL;}
        if(source_right != NULL) {source_right->_parent = NULL;}
        source_node->_left = NULL;
        source_node->_right = NULL;
        updateHeight(source_node);
        if(*key < *source_node->_data){
            Node<T> *node_min = NULL;
            Node<T> *node_max = NULL;
            Split(key, source_left,node_min,node_max);
            dest_max_node = AVLMergeWithRoot(node_max,source_right,source_node);
            dest_max_node->_parent =NULL;
            dest_min_node = verifyBalans(node_min);
            if(dest_min_node != NULL){dest_min_node->_parent =NULL;}
            return true;
        }else{
            Node<T> *node_min = NULL;
            Node<T> *node_max = NULL;
            Split(key, source_right,node_min,node_max);
            dest_min_node = AVLMergeWithRoot(source_left,node_min,source_node);
            dest_min_node->_parent =NULL;
            dest_max_node = verifyBalans(node_max);
            if(dest_max_node != NULL){dest_max_node->_parent =NULL;}
            return true;
        }
    }
    Node<T>& operator[](int k){
        return OrderStatistics(k, _root);
    }
};
int Data::b = -1;
long Data::max_key=0;
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

void UpdateSum(Data* d_data, Data *s1_data, Data *s2_data){
    if (d_data == NULL) return;
    int sum = d_data->_key;
    if (s1_data != NULL){sum += s1_data->sum;}
    if (s2_data != NULL){sum += s2_data->sum;}
    d_data->sum = sum;
}

int foo(int s, int x){
    return (x+s)%1000000001;
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
   /* Node<Data> **arrNode = new Node<Data>*[10];
    for(int i=0;i<10;i++){
        arrNode[i]=NULL;
    }
    myTree<Data> *mytree = new myTree<Data>(NULL, UpdateSum);
    int m[]={4,2,6,1,3,5,7,7,6,4,3};
    for(int i = 0; i< 7; i++){
        arrNode[i] =new Node<Data>(new Data(m[i]));
        mytree->AddNode(arrNode[i]);
    }
    Node<Data> *min_node = NULL;
    Node<Data> *max_node = NULL;
    Node<Data> *source = mytree->Root();
    mytree->Split(new Data(4),source,min_node,max_node);
    Node<Data> *min_node2 = NULL;
    Node<Data> *max_node2 = NULL;
    delete mytree;
    mytree = new myTree<Data>(min_node,UpdateSum);
    source = mytree->Root();
    mytree->Split(new Data(1),source,min_node2,max_node2);*/

    long n, x, y;
    long s=0;
    cin >> n;
    string str;

    myTree<Data> *mytree = new myTree<Data>(NULL, UpdateSum);

    for(int i=0;i<n;i++){
        cin >> str;
        cin >> x;
        if(str == "+"){
            if(mytree->FindNode(new Data(foo(s,x))) == NULL){mytree->AddNode(new Node<Data>(new Data(foo(s,x))));}
        }else if(str == "-"){
            mytree->DelNode(mytree->FindNode(new Data(foo(s,x))));
        }else if(str == "?"){
            if(mytree->FindNode(new Data(foo(s,x))) == NULL){cout << "Not found"<<endl;}
            else{cout << "Found"<<endl;}
        }else if(str == "s"){
            cin >> y;
            Node<Data> *left_t = NULL;
            Node<Data> *right_t = NULL;
            Node<Data> *center_right_t = NULL;
            Node<Data> *center_t= NULL;
            Node<Data> *source = mytree->Root();
            mytree->Split(new Data(foo(s,x)-1),source,left_t,center_right_t);
           /* delete mytree;
            mytree = new myTree<Data>(center_right_t, UpdateSum);*/
            mytree->_root = center_right_t;
            mytree->Split(new Data(foo(s,y)),center_right_t,center_t,right_t);

            if(center_t==NULL){
                s = 0;
            }else{
                s = center_t->_data->sum;
            }
            cout<< s << endl;
            mytree->_root = left_t;
            Node<Data> *t_key = mytree->DelNode(mytree->Max(left_t),false);
            Node<Data> *acum = mytree->AVLMergeWithRoot(mytree->_root,center_t, t_key);
            mytree->_root = acum;
            t_key = mytree->DelNode(mytree->Max(acum),false);
            acum = mytree->AVLMergeWithRoot(mytree->_root,right_t,t_key);
            mytree->_root = acum;
        }


    }




return 0;
}

