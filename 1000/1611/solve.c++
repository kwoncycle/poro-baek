#include <bits/stdc++.h>
using namespace std;
int main(){
    int k; cin >> k;
    for(int i=0; i<k/2; i++){
        cout << i+1 << " ";
        int st = i;
        for(int j=1; j<=k-2; j++){
            if(j%2) st = (st + j) % (k-1);
            else st = (st - j + k-1) % (k-1);
            cout << st+1 << " ";
        }
        cout << k << "\n";
    }
    return 0;
}