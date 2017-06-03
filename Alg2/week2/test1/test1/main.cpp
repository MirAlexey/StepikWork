#include <iostream>
#include <sstream>

using namespace std;

int main()
{
    int n;
    int count=0;
    int *x;
    cin >> n;
    x = new int[n];
    for(int i=0;i<n;i++){
        cin >> x[i];
    }
    stringstream ss;
    for(int i=(n-1)/2;i>=0;i--){
        int j = i;
        while(j<n){
            int min =j;
            if (2*j+1< n && x[min] > x[2*j+1]){min = 2*j+1;}
            if (2*j+2< n && x[min] > x[2*j+2]){min =2*j+2;}
            if (min != j){
                count++;
                int y = x[j];
                x[j] = x[min];
                x[min] = y;
                ss << j <<" "<< min << endl;
                j=min;
            }else{
                break;
            }
        }
    }
     cout <<count<< endl;
     string s;
     getline(ss,s);
     while(s!=""){
        cout << s <<  endl;
        getline(ss,s);
     }
}

