#include <iostream>


using namespace std;


int main()
{   long x = 263;
    long p = 1000000007;
    long long pow_x=1;
    long long x_m;
    string text, pattern;
    cin >> pattern;
    cin >> text;
    int m = pattern.size();
    int n = text.size()-m;
    bool *res = new bool[n];
    long long hash_p = 0;
    long long hash=0;
    for (int i=0; i<m;i++, pow_x=(pow_x*x)%p){
        hash_p=(hash_p+((unsigned char)pattern[i]*pow_x)%p)%p;
        hash=(hash+((unsigned char)text[i+n]*pow_x)%p)%p;
        x_m = pow_x;
    }
    bool b;
    for(int i=n-1;i>=0;i--){
        b =false;
        if (hash == hash_p){
            b = true;
            for(int j = 0; j<m; j++){
                b &= text[i+1+j] == pattern[j];
            }
            res[i+1]=b;
        }else{
            res[i+1]=b;
            }
        hash = ((hash - ((unsigned char)text[i+m]* x_m)%p+p)%p * x + (unsigned char)text[i])%p;
    }
    b = false;
    if (hash == hash_p){
        b = true;
        for(int j = 0; j<m; j++){
            b &= text[j] == pattern[j];
        }
        res[0]=b;
    }else{
        res[0]=b;
        }

    for(int i=0; i<=n; i++){
        if(res[i]){cout << i << " ";}
    }


    return 0;
}
