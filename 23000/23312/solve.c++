#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define pii pair<int,int>
#define pll pair<ll,ll>
#define X first
#define Y second
#define CNT_LOWER(v,n) (int)(lower_bound((v).begin(),(v).end(),(n))-(v).begin())
#define CNT_UPPER(v,n) (int)(upper_bound((v).begin(),(v).end(),(n))-(v).begin())

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n; cin >> n;
    vector<int> c(n), score(n);
    for(int i=0; i<n; i++){
        int v, e; cin >> v >> e;
        c[i] = v; score[i] = v - e;
        while(e--){
            int o, o1; cin >> o >> o1;
        }
    }
    for(int i=1; i<n; i++) c[i] = c[i-1] + c[i];
    int qq; cin >> qq;
    while(qq--){
        int q; cin >> q;
        if(q == 1){
            int k; cin >> k;
            cout << score[k-1] << "\n";
        }
        else if(q == 2){
            int u, v; cin >> u >> v;
            int k = CNT_LOWER(c, u);
            score[k]++;
        }
        else if(q == 3){
            int u, v; cin >> u >> v;
            int k = CNT_LOWER(c, u);
            score[k]--;
        }
    }
    return 0;
}