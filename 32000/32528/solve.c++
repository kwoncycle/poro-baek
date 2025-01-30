#include <bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n; cin >> n;
    int a, b; cin >> a >> b;
    vector<int> v(n+1);
    for(int i=1; i<=n; i++) cin >> v[i];
    for(int i=0; i<888484; i++){
        int cnt = n-2; 
        if(a == b) cnt = n-1;
        if(cnt%2 == 1){
            cout << "first\n"; return 0;
        }
        a = v[a];

        cnt = n-2; 
        if(a == b) cnt = n-1;
        if(cnt%2 == 1){
            cout << "second\n"; return 0;
        }
        b = v[b];
    }
    cout << "draw\n";
    return 0;
}