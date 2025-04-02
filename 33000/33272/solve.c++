#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n, m, k; cin >> n >> m >> k;
    set<int> used;
    for(int i=1; i<=m; i++){
        if(used.size() >= n) break;
        if(used.find(i^k) == used.end()){
            used.insert(i);
        }
    }

    if(used.size() < n) cout << "-1\n";
    else{
        for(int i:used) cout << i << " "; cout << "\n";
    }
    return 0;
}