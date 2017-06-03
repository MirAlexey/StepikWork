#include <iostream>
#include <sstream>

using namespace std;

template <class T>
class Stack{
private:
    T *stack;
    T *stack_min;
    T *stack_max;
    int top;
    int max_num;
public:
    Stack(int stack_size=100){
       this->stack = new T[stack_size];
       this->stack_max = new T[stack_size];
       this->stack_min = new T[stack_size];
       this->max_num = stack_size-1;
       this->top=-1;
    }
    bool Push(T elem){
        if (this->top < this->max_num){

            if(this->Empty()){
               this->stack_max[top+1]=elem;
               this->stack_min[top+1]=elem;
            }else{
               if(this->stack_max[top]<elem){
                   this->stack_max[top+1]=elem;
               }else{
                   this->stack_max[top+1]=this->stack_max[top];
               }
               if(this->stack_min[top]>elem){
                   this->stack_min[top+1]=elem;
               }else{
                   this->stack_min[top+1]=this->stack_min[top];
               }
            }
            this->stack[++top]=elem;
            return true;
        }else{
            return false;
        }
    }
    T Pop(){

        return this->Empty()?0:this->stack[top--];
    }
    T Max(){
        return this->Empty()?0:this->stack_max[top];
    }
    T Min(){
        return this->Empty()?0:this->stack_min[top];
    }
    T Top(){
        return this->Empty()?0:this->stack[top];
    }
    int Size(){
    return this->top+1;
    }
    bool Empty(){
        return this->top==-1;
    }
    ~Stack(){
        delete[] this->stack;
        delete[] this->stack_max;
        delete[] this->stack_min;
    }
};

template <class T>
class MyQueueStackMinMax{
private:
    Stack<T> *in;
    Stack<T> *out;

    void Shift(){
        if(!this->out->Empty()) return;
        while(!this->in->Empty()){
            this->out->Push(this->in->Pop());
        }
    }

public:
    MyQueueStackMinMax(int n = 100){
        this->in = new Stack<T>(n);
        this->out = new Stack<T>(n);
    }
    bool AddElem(T elem){
       return this->in->Push(elem);
    }
    T PopElem(){
        if(this->Empty()) {return NULL;}
        if(this->out->Empty()) {this->Shift();}
        return out->Pop();
    }
    T TopElem(){
        if(this->Empty()) {return NULL;}
        if(this->out->Empty()) {this->Shift();}
        return out->Top();
    }
    bool Empty(){
       return this->in->Empty() && this->out->Empty();
    }
    T Max(){
        if(this->Empty()) {return NULL;}
        if(this->out->Empty()) {this->Shift();}
        if(this->in->Empty()) {return out->Max();}
        return in->Max()>out->Max()?in->Max():out->Max();
    }
    T Min(){
        if(this->Empty()) {return NULL;}
        if(this->out->Empty()) {this->Shift();}
        if(this->in->Empty()) {return out->Min();}
        return in->Min()>out->Min()?in->Min():out->Min();
    }
    ~MyQueueStackMinMax(){
        delete this->in;
        delete this->out;
    }
};



int main()
{   int n;
    int m;
    int x;
    string s;
    stringstream ss;
    getline(cin,s);
    stringstream(s) >> n;
    getline(cin,s);
    cin >> m;
    ss<<s;
    MyQueueStackMinMax<int> *myqueue = new MyQueueStackMinMax<int>(m);
    for(int i = 0;i<m;i++){
        ss>>x;
        myqueue->AddElem(x);
    }
    for(int i = m-1;i<n;i++){
        cout << myqueue->Max()<<' ';
        myqueue->PopElem();
        ss>>x;
        myqueue->AddElem(x);
    }
    return 0;
}

