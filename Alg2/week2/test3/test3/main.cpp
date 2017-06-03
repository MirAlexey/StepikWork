#include <iostream>

using namespace std;
struct Data{
    int count;
    Data(int data){
        count=data;
    }
    int operator +(Data data){
        return count+data.count;
    }
    int operator =(int n){
        count = n;
        return n;
    }
    bool operator >(Data data){
        return this->count > data.count;
    }
    bool operator <(Data data){
        return this->count < data.count;
    }
    int Get(){
        return count;
    }
};

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
    T* max_data;
    Element<T> **arr_elems;
public:
    Set(int n = 10){
        arr_elems = new Element<T>*[n];
        max_size = n;
        size =-1;
    }
    int MakeSet(T *elem){
        if(size == -1){
            max_data = elem;
        }else{
            if( *max_data < *elem){
                max_data = elem;
            }
        }
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
                if( *max_data < *e_x->data){
                    max_data = e_x->data;
                }
                return e_x;
            }else{
                e_x->parent = e_y->parent;
                *e_y->data = *e_y->data + *e_x->data;
                if(e_x->rang == e_y->rang){
                    e_y->rang++;
                }
                if( *max_data < *e_y->data){
                    max_data = e_y->data;
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
            if( *max_data < *e_x->data){
                max_data = e_x->data;
            }
            return e_x;
        }
    }
    Element<T>* GetElement(int i){
       return arr_elems[i];
    }
    bool Empty(){
        return size == -1;
    }
    T* GetMax(){
        return max_data;
    }
};



int main()
{   int n,m;
    cin >> n;
    Set<Data>* set = new Set<Data>(n);
    cin >> m;
    for(int i=0;i<n;i++){
        int r;
        cin >>r;
        set->MakeSet(new Data(r));
    }
    int x = 0;
    for(int i=0;i<m;i++){
        int x,y;
        cin >> x >> y;
        set->Union(set->GetElement(x-1), set->GetElement(y-1), false);
        cout<< set->GetMax()->Get()<< endl;
    }
    x = 0;


    return 0;
}

