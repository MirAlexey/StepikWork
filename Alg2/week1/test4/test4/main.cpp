#include <iostream>
#include <sstream>
#include <string>

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

int main()
{
    int n;
    int x;
    string s;
    cin >> n;
    Stack<int> *stack = new Stack<int>(n);
    /*for(int i = 0; i < n; i++){
        string c;
        string c2;
        cin >> c;
        if(c=="push"){cin>>c2;}
        s=s+' '+c+' '+c2;
    }
    stringstream ss;
    ss <<s;*/
    for(int i = 0; i < n; i++){

        string s;
        cin >> s;
        if (s == "push"){
            cin >> x;
            stack->Push(x);
        }
        if(s == "pop"){
            stack->Pop();
        }
        if(s=="max"){
            if (!stack->Empty()){
                cout << stack->Max() << endl;
            }
        }
    }
return 0;
}

