#include <iostream>

using namespace std;


template<class T>
struct Element{
    T* data;
    int parent;
    int rang;
    Element(T* data){
        this->data = data;
    }
};
template<class T>
class Set {
private:
    int size;
    int max_size;
    Element<T> **arr_elems;
public:
    Set(int n = 10){
        arr_elems = new Element<T>*[n];
        max_size = n;
        size =-1;
    }
    int MakeSet(T *elem){
        arr_elems[++size] = new Element<T>(elem);
        arr_elems[size]->parent = size;
        arr_elems[size]->rang = 0;

        return size;
    }

    Element<T>* Find(Element<T> *elem){
        if (elem->parent != arr_elems[elem->parent]->parent){
            elem->parent = Find(arr_elems[elem->parent])->parent;
        }
        return arr_elems[elem->parent];
    }
    Element<T>* Union(Element<T> *x, Element<T> *y, bool with_rang = true){
        Element<T> *e_x = Find(x);
        Element<T> *e_y = Find(y);
        if(e_x->parent == e_y->parent) {return e_x;}
        if(with_rang){
            if(e_x->rang > e_y->rang){
                e_y->parent = e_x->parent;
                *e_x->data = *e_x->data + *e_y->data;
                return e_x;
            }else{
                e_x->parent = e_y->parent;
                *e_y->data = *e_y->data + *e_x->data;
                if(e_x->rang == e_y->rang){
                    e_y->rang++;
                }
                return e_y;
            }
        }else{
            e_y->parent = e_x->parent;
            if(e_x->rang<e_y->rang){
                if(e_x->rang==e_y->rang){
                    e_x->rang++;
                }else{
                    e_x->rang = e_y->rang;
                }
            }
            *e_x->data = *e_x->data + *e_y->data;
            return e_x;
        }
    }
    Element<T>* GetElement(int i){
       return arr_elems[i];
    }
    bool Empty(){
        return size == -1;
    }

};
int main()
{
       int n,e,d;

       cin >> n;
       Set<int>* set = new Set<int>(n);
       int *data = new int[n];
       cin >> e >> d;
       for(int i=0;i<n;i++){
           data[i]=i;
            set->MakeSet(&data[i]);
       }
       for(int i=0;i<e;i++){
            int x,y;
            cin >> x >> y;
            set->Union(set->GetElement(--x),set->GetElement(--y));
       }
       bool pass= true;
       for(int i=0;i<d;i++){
           int x,y;
           cin >> x >> y;
           pass &= set->Find(set->GetElement(--x))->parent != set->Find(set->GetElement(--y))->parent;

       }
       if(pass){
           cout << '1';
       }else{
           cout << '0';
       }


    return 0;
}

