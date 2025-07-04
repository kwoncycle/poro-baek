#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    string s; cin >> s;
    int n = s.size();
    vector<int> v(26);
    for(int i=n-1; i>=0; i--){
        if(v[s[i]-'A']){
            cout << i+1 << "\n"; return 0;
        }
        v[s[i]-'A'] = 1;
    }
    return 0;
}