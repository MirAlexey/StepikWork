#include <iostream>

using namespace std;

int main()
{
    bool *arr_num =     new bool[10000000];
    string *arr_str = new string[10000000];
    int n;
    cin >> n;
    for(int i=0;i<n;i++){
        string com, name;
        int num;
        cin >> com;
        if(com == "add"){
            cin >> num;
            cin >> name;
            arr_str[num]=name;
            arr_num[num]=true;
        }
        if(com == "del"){
            cin >> num;
            arr_num[num]=false;
        }
        if(com == "find"){
            cin>>num;
            if (arr_num[num]){
                cout << arr_str[num] << endl;
            }else{
                cout << "not found" << endl;
            }
        }
    }
    return 0;
}

