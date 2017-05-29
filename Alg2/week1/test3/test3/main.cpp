#include <iostream>


using namespace std;

struct Data{
    int arrival;
    int duration;
    Data(int arrival, int duration){
        this->arrival = arrival;
        this->duration = duration;
    }
};

template<class T>
struct Node{
    Node* next;
    Node* prev;
    T *data;
    Node(T *data){
        this->data = data;
        this->next = this->prev = NULL;
    }
    ~Node(){
        delete this->data;
    }
};

template<class T>
class  MyList{
private:
    Node<T> *root;
    Node<T> *tail;
    Node<T> *it;
public:
    bool Push(Node<T> *elem){
        if (elem == NULL) return false;
        if(this->root == NULL){
            this->root = elem;
            this->tail = elem;
        }else{
        this->PushBefor(elem, this->root);
        this->root=elem;
        }
        return true;
    }
    bool PushBack(Node<T> *elem){
        if (elem == NULL) return false;
        if(this->tail == NULL){
            this->root = elem;
            this->tail = elem;
        }else{
            this->PushAfter(elem, this->tail);
            this->tail=elem;
        }
        return true;
    }
    bool PushAfter(Node<T> *elem, Node<T>* dest){
        if(dest == NULL || elem == NULL) return false;
        elem->next = dest->next;
        if(dest->next!=NULL){dest->next->prev = elem;}
        elem->prev = dest;
        dest->next = elem;
        return true;
    }
    bool PushBefor(Node<T> *elem, Node<T>* dest){
        if(dest == NULL || elem ==NULL) return false;
        elem->prev = dest->prev;
        if(dest->prev == NULL){dest->prev->next = elem;}
        dest->prev = elem;
        elem->next = dest;
        return true;
    }

    Node<T> *Pop(){
        if(this->root == NULL) return NULL;
        Node<T> *elem = this->root;
        if (this->tail == this->root){this->tail=NULL;}
        this->root = this->root->next;
        return elem;
    }
    Node<T> *PopBack(){
        if(this->tail == NULL) return NULL;
        Node<T> *elem = this->tail;
        if (this->tail == this->root){this->root=NULL;}
        this->tail = this->tail->prev;
        return elem;
    }
    Node<T> *Top(){
        return this->root;
    }
    Node<T> *TopBack(){
        return this->tail;
    }
    Node<T> *Begin(){
        this->it = this->root;
        return this->it;
    }
    Node<T> *Next(){
        if(this->it == NULL) return NULL;
        this->it = this->it->next;
        return this->it;
    }

};

template<class T>
class MyQueue{
private:
    MyList<T> *list;
    int size;
    int max;
public:
    MyQueue(int size = 10){
        this->max = size;
        this->size=0;
        this->list = new MyList<T>();
    }
    bool AddElem(Node<T> *elem){
        if (this->size < this->max){
            this->list->PushBack(elem);
            size++;
            return true;
        }else{
            return false;
        }
    }
    Node<T> *getFirst(){
        if(size != 0){
            size--;
            return this->list->Pop();
        }else{
            return NULL;
        }
    }
    Node<T> *getTop(){
        if(size != 0){
            return this->list->Top();
        }else{
            return NULL;
        }
    }
    bool Empty(){
        return size==0?true:false;
    }
    ~MyQueue(){
        delete this->list;
    }
};


int main()
{

    int size_buf;
    cin >> size_buf;
    int count_p;
    cin >> count_p;
    if(count_p == 0) return 0;
    MyQueue<Data> *myqueue = new MyQueue<Data>(size_buf);
    int *res = new int[count_p];
    //int res[10];
    for(int i =0 ; i<count_p;i++){res[i]=-2;}
    int next_a;
    int next_d;
    int time = 0;
    cin >> next_a;
    cin >> next_d;
    int n=0;
    int m=0;


    while(true){
        Node<Data> *e;
        while(!myqueue->Empty() && res[m]+myqueue->getTop()->data->duration == time ){
                e = myqueue->getFirst();
                while(m < count_p && res[++m]!=-2){};
                if (m == count_p){
                    break;
                }else{
                    if(!myqueue->Empty()){res[m]=time;}
                }
            }
        while (next_a == time){
            if(myqueue->Empty()){
                res[n]=time;
            }
            if(!myqueue->AddElem(new Node<Data>(new Data(next_a,next_d)))){
                res[n]=-1;
            }
            e = myqueue->getTop();
            if (e!=NULL && res[m]+e->data->duration == time){
                myqueue->getFirst();
                while(m < count_p && res[++m]!=-2){};
                if (m == count_p){
                    break;
                }else{
                    if(!myqueue->Empty()){res[m]=time;}
                }
            }
            n++;
            if(n== count_p){break;}
            cin >> next_a;
            cin >> next_d;

        }
        e = myqueue->getTop();
        if (e!=NULL && res[m]+e->data->duration == time){
            myqueue->getFirst();
            while(m != count_p && res[++m]!=-2){};
            if (m == count_p){
                break;
            }else{
                if(!myqueue->Empty()){res[m]=time;}
            }
        }
        time++;
        if (m == count_p){
            break;
        }
    }
    for(int i = 0; i< count_p;i++ ){
        cout << res[i]<<endl;
    }

    return 0;
}

