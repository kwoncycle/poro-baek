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
    ll r, c, n; cin >> r >> c >> n;
    vector<pii> tremp(n);
    for(int i=0; i<n; i++){
        cin >> tremp[i].X >> tremp[i].Y;
    }

    sort(tremp.begin(), tremp.end());
    
    vector<vector<int>> lca(n, vector<int>(30, -1));
    for(int i=0; i<n; i++){
        pii target = {tremp[i].X+1, tremp[i].Y};
        int o = CNT_LOWER(tremp, target);
        if(o < n and tremp[o].X == tremp[i].X+1){
            lca[i][0] = o;
        }
        else lca[i][0] = -1;
    }
    for(int j=1; j<25; j++){
        for(int i=0; i<n; i++){
            if(lca[i][j-1] == -1) lca[i][j] = -1;
            else lca[i][j] = lca[lca[i][j-1]][j-1];
            
        }
    }


    int tt; cin >> tt;
    while(tt--){
        int x_start, y_start, x_stop, y_stop;
        cin >> x_start >> y_start >> x_stop >> y_stop;
        pii st = {x_start, y_start};
        pii ed = {x_stop, y_stop};
        if(x_start == x_stop and y_start <= y_stop){
            cout << "Yes\n"; continue;
        }
        if(st > ed){
            cout << "No\n"; continue;
        }
        int o = CNT_LOWER(tremp, st);
        if(!(o<n and tremp[o].X == x_start)){
            cout << "No\n"; continue;
        }
        while(tremp[o] <= ed){
            //cout << (tremp[lca[o][0]] <= ed) << "\n";
            if(lca[o][0] == -1) break;
            if(tremp[lca[o][0]] > ed) break;
            for(int i=25; i>=0; i--){
                if(lca[o][i] >= 0){
                    if(tremp[lca[o][i]] <= ed){
                        o = lca[o][i]; break;
                    }
                }
            }
        }
        if(tremp[o].X + 1 >= ed.X and tremp[o].Y <= ed.Y) cout << "Yes\n";
        else cout << "No\n";
    }
    return 0;
}