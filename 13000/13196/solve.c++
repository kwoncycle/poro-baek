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
    int n, m, p; cin >> n >> m >> p;

    vector<vector<int>> in(15), out(15);
    int id = 0;
    for(int i=1; i<=n; i++){
        if(in[id].size() >= 670) id++;
        in[id].push_back(i);
    }

    id = 0;
    for(int i=n+1; i<=2*n; i++){
        if(out[id].size() >= 670) id++;
        out[id].push_back(i);
    }

    id = 2*n+1;
    vector<pii> ans;
    for(int i=0; i<15; i++){
        for(int j=0; j<15; j++){
            for(int in_node:in[i]){
                ans.push_back({in_node, id});
            }
            for(int out_node:out[j]){                
                ans.push_back({id, out_node});
            }
            id++;
        }
    }

    cout << id-1 << " " << (int)ans.size() << "\n";

    for(auto [x,y]:ans){
        cout << x << " " << y << "\n";
    }

    return 0;
}