#include <iostream>
#include <string>
#include <sstream>

using namespace std;
struct Node{
    Node *parent;
    int level;
    Node(){
        this->parent = NULL;
        this->level = 0;
    }
};

int main()
{   int n;
    cin >> n;
    Node *root;
    Node* tree[n];

    int parent[n];
    for(int i = 0; i<n; i++){
        cin >> parent[i];
        tree[i]=NULL;
    }
    string str;
   // stringstream ss;
    for(int  i=0; i< n;i++){
        if(tree[i] == NULL){
           int lvl = 1;
            Node *e = new Node();
            Node *p;
            e->level = lvl;
            tree[i]=e;
            if(parent[i] == -1){
                root = e;
                continue;
            }
            int x = parent[i];
            while(true){
                lvl++;
                if(tree[x]==NULL){
                    p = new Node();
                    p->level = lvl;
                    e->parent=p;
                    tree[x]=p;
                    e=p;
                    if(parent[x] == -1){
                        root = p;
                    }
                }else{
                    tree[x]->level=tree[x]->level>lvl?tree[x]->level:lvl;
                }
                if(parent[x] == -1){
                    break;
                }else{
                    x = parent[x];
                }
            }
        }
     }

cout << root->level;


    return 0;
}

