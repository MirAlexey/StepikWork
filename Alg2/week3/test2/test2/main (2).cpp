#include <iostream>
#include <math.h>

using namespace std;
struct Node{
    string _str;
    Node* _next;
    Node(){
        _str="";
        _next = NULL;
    }
    Node(string str){
        _str = str;
        _next = NULL;
    }
};

class HashTable{
private:
    double _x;
    double _p;
    double  *_pow_x;
    Node **_table;
    int _m;

    int myHash(string str){
        double res=0;
        int p = 16<str.size()?16:str.size();
        for(int i=0; i<p; i++){
            res = fmod((res+fmod(((double)str[i]*_pow_x[i]),_p)),_p);
        }
        return (int)fmod(fmod(res,_p),_m);
    }

public:
    HashTable(int m, double x, double p, int len_s){
        _x = x;
        _p = p;
        _m = m;
        _pow_x = new double[len_s];
        _pow_x[0] = 1;
        for(int i = 1; i<len_s;i++){
            _pow_x[i]=fmod((_pow_x[i-1]*_x),_p);
        }
        _table = new Node*[m];
        for(int i=0; i<m; i++){_table[i]=NULL;}
    }
    bool Add(string str){
        if(Find(str)){return false;}
        Node *x = new Node(str);
        int i = myHash(str);
        x->_next = _table[i];
        _table[i] = x;
        return true;
    }
    bool Del(string str){
        int i = myHash(str);
        if (_table[i] == NULL){return true;}
        if (_table[i]->_str == str) {
            _table[i]= _table[i]->_next;
            return true;
        }
        Node *parent = _table[i];
        Node *next = _table[i]->_next;
        while(next->_str != str){
            parent = next;
            next = next->_next;
            if(next == NULL) return false;
        }
        parent->_next = next->_next;
        delete next;
        return true;

    }
    bool Find(string str){
        Node *next = _table[myHash(str)];
        while(next != NULL && next->_str !=str){
            next = next->_next;
        }
        return next != NULL;

    }
    string Check(int i){
        string res = "";
        if(i>=_m || i<0){return res;}
        Node *n = _table[i];
        while(n != NULL){
            res +=n->_str+' ';
            n = n->_next;
        }
        return res;
    }

};

int main()
{   long x = 263;
    long p = 1000000007;
    int len_s = 16;
    int m, n;
    cin >> m >> n;

    HashTable *table = new HashTable(m, x, p, len_s);
    for(int i=0;i<n;i++){
        string com, name;
        cin >> com;
        if(com == "add"){
            cin >> name;
            table->Add(name);
        }
        if(com == "del"){
            cin >> name;
            table->Del(name);
        }
        if(com == "find"){
            cin>>name;
            if(table->Find(name)){
               cout << "yes"<< endl;
            }else{
               cout << "no"<< endl;
            }
        }
        if(com == "check"){
            int num;
            cin >> num;
            cout << table->Check(num)<< endl;
        }
    }


    return 0;
}

