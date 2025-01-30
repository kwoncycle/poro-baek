#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n; cin >> n;
    vector<int> v(n);
    for(int i=0; i<n; i++) cin >> v[i];
    vector<vector<int>> U(25, vector<int>(n, 0));
    for(int i=0; i<25; i++){
        int u = (1<<(i+1))-1;
        for(int j=0; j<n; j++) U[i][j] = v[j]&u;
        sort(U[i].begin(), U[i].end());
    }
    int ans = 0;
    for(int i=0; i<n; i++){
        for(int j=0; j<25; j++){
            int u = (1<<(j+1))-1;
            int o = U[j][i];
            int r1 = 0, r2 = (1<<j)-1;
            if(r2 >= o){
                r1 += (1<<j) - o; r2 += (1<<j) - o;
                int t = i>0 ? (upper_bound(U[j].begin(), U[j].begin() + (i), r2) - lower_bound(U[j].begin(), U[j].begin() + (i), r1)) : 0;
                // t개가 1, (1<<j)
                if(t%2) ans ^= (1<<j);
            }
            else{
                r1 += (1<<(j+1)) - o; r2 += (1<<(j+1)) - o;
                int t = i>0 ? (upper_bound(U[j].begin(), U[j].begin() + (i), r2) - lower_bound(U[j].begin(), U[j].begin() + (i), r1)) : 0;
                // t개가 0, (1<<j)
                t = i-t;
                if(t%2) ans ^= (1<<j);
            }
        }
    }
    cout << ans << "\n";
    return 0;
}