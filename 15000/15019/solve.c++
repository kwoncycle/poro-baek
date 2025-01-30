#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define pii pair<int,int>
#define pll pair<ll,ll>
#define X first
#define Y second
#define CNT_LOWER(v,n) (int)(lower_bound((v).begin(),(v).end(),(n))-(v).begin())
#define CNT_UPPER(v,n) (int)(upper_bound((v).begin(),(v).end(),(n))-(v).begin())
 
// CNT_LOWER: number of element in v smaller than n
// CNT_UPPER: number of element in v smaller or same than n

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n, k; cin >> n >> k;
    vector<vector<int>> graph(1<<k);
    vector<int> dst(1<<k, -999999);
    queue<int> q;
    for(int i=0; i<n; i++){
        string s; cin >> s;
        int o = 0;
        for(int j:s){
            o *= 2;
            o += j - '0';
        }
        if(dst[o] == 0) continue;
        dst[o] = 0;
        q.push(o);
    }

    for(int i=0; i<(1<<k); i++){
        for(int j=0; j<k; j++){
            graph[i].push_back(i^(1<<j));
        }
    }

    while(!q.empty()){
        int x = q.front(); q.pop();
        for(int j:graph[x]){
            if(dst[j] < 0){
                dst[j] = dst[x] + 1;
                q.push(j);
            }
        }
    }

    int mx = -9999999, idx = 0;
    for(int i=0; i<(1<<k); i++){
        if(dst[i] > mx){
            mx = dst[i];
            idx = i;
        }
    }

    vector<int> ans(k, 0);
    for(int i=k-1; i>=0; i--){
        ans[i] = idx & 1;
        idx >>= 1;
    }

    for(int i:ans) cout << i; cout << "\n";
    return 0;
}