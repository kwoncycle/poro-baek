#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int tt; cin >> tt;
    while(tt--){
        int n; cin >> n;
        int o;
        vector<int> v(4);
        for(int i=0; i<n; i++){
            cin >> o;
            v[i%4] += o;
        }
        int i1 = 0;
        for(int i=0; i<4; i++){
            if(v[i] < v[i1]) i1 = i;
        }
        int ed = n/4*4+i1+4;
        while(ed >= n) ed -= 4;
        cout << "YES\n";
        for(int i=0; i<n; i++){
            if(i==0 or i%4 == i1) cout << "0";
            else{
                if(i<i1) cout << i1-1;
                else if(ed < i) cout << n-1-ed;
                else cout << 3;
            }
        }
        cout << "\n";
    }
    return 0;
}