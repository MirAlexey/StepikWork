#include <iostream>


using namespace std;
struct Element{
  char symbol;
  int pos;
};

template <class T>
class Stack{
private:
    T *stack;
    int top;
    int max_num;
public:
    Stack(int stack_size=100){
       this->stack = new T[stack_size];
       this->max_num = stack_size-1;
       this->top=-1;
    }
    bool Push(T elem){
        if (this->top < this->max_num){
            this->stack[++top]=elem;
            return true;
        }else{
            return false;
        }
    }
    T Pop(){
        return this->stack[top--];
    }
    T Top(){
        return this->stack[top];
    }
    int Size(){
    return this->top+1;
    }
    bool Empty(){
        return this->top==-1;
    }
    ~Stack(){
        delete[] this->stack;
    }
};

int main()
{
    bool fail = false;
    string input_str;
    cin >> input_str;
    int i;
    Stack<Element> *myStack = new Stack<Element>(input_str.size());
    for(i = 0;i<input_str.size(); i++ ){
        char c = input_str[i];
        if(c=='(' || c=='{' || c=='['){
            Element e;
            e.symbol=c;
            e.pos=i;
            myStack->Push(e);
        }
        if(c==')' || c=='}' || c==']'){
            char c2;
            switch (c) {
            case ')':c2='(';break;
            case '}':c2='{';break;
            case ']':c2='[';break;
            }
            if(!myStack->Empty()){
               if (myStack->Top().symbol==c2) {
                   myStack->Pop();
               }else{
                   fail = true;
               }
            }else{
                fail = true;
            }
            if(fail){
                Element e;
                e.symbol=c;
                e.pos=i;
                myStack->Push(e);
            }
        }
        if(fail){
            break;
        }
    }
    if(!fail && myStack->Empty()){
        cout << "Success";
    }else{
        cout << myStack->Top().pos+1;
    }


return 0;
}

