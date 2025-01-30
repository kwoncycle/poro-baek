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
    ll n, m; cin >> n >> m;
    vector<vector<ll>> v(n, vector<ll>(m, 0));
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++) cin >> v[i][j];
    }

    map<int, int> mp;
    int index = 0;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(mp.find(v[i][j]) == mp.end()){
                mp[v[i][j]] = index; index++;
            }
            v[i][j] = mp[v[i][j]];
        }
    }

    vector<vector<ll>> go_up(n, vector<ll>(m, 0));
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(i == 0) go_up[i][j] = 1;
            else{
                if(v[i][j] == v[i-1][j]) go_up[i][j] = go_up[i-1][j] + 1;
                else go_up[i][j] = 1;
            }
        }
    }
    ll ans = 0;
    vector<vector<ll>> DP(n, vector<ll>(m, 0));
    vector<pair<ll, ll>> stck(index+5);
    ll stcksz = 0;
    for(ll i=0; i<n; i++){
        for(ll j=0; j<m; j++){
            if(j != 0){
                if(v[i][j] != v[i][j-1]){
                    stck.clear(); stcksz = 0;
                }
            }
            if(stck.empty()){
                stck.push_back({go_up[i][j], j});
                ans += go_up[i][j];
                stcksz++;
                DP[i][j] = go_up[i][j];
            }
            else{
                ll o = 0;
                o += go_up[i][j];
                if(go_up[i][j] <= stck[0].X) o += stcksz * go_up[i][j];
                else if(go_up[i][j] >= stck.back().X) {
                    ll j1 = stck.back().Y;
                    o += DP[i][j1];
                }

                else{
                    pll target = {go_up[i][j], j};;
                    ll u = CNT_LOWER(stck, target);
                    u--;
                    o += DP[i][stck[u].Y];
                    o += (ll)(j-1 - stck[u].Y)*go_up[i][j];
                }

                while(!stck.empty() and stck.back().X >= go_up[i][j]) stck.pop_back();
                stck.push_back({go_up[i][j], j});
                stcksz++;
                ans += o;
                DP[i][j] = o;
            }
        }
        stck.clear();
        stcksz = 0;
    }

    ll sm = 0;

    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++) sm += DP[i][j];//cout << DP[i][j] << " ";
        //cout << "\n";
    }

    cout << sm << "\n";
    return 0;
}