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

#define LINE array<pii, 2>
// LINE: l[0] + kl[1]

pii operator + (pii l, pii r){return {l.X+r.X, l.Y+r.Y};};
pii operator - (pii l, pii r){return {l.X-r.X, l.Y-r.Y};};
ll operator * (pii l, pii r){return (ll)l.X*r.X + (ll)l.Y*r.Y;};
ll operator / (pii l, pii r){return (ll)l.X*r.Y - (ll)l.Y*r.X;};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n; cin >> n;
    vector<int> v(n);
    vector<int> next_same(n, -1), next_diff(n, -1);
    vector<vector<int>> loc(n+5);
    vector<int> idx(n);
    map<int, int> mp; int id = 1;
    vector<int> tmp;
    for(int i=0; i<n; i++) {
        cin >> v[i];
        tmp.push_back(v[i]);
    }

    sort(tmp.begin(), tmp.end());
    for(int i=0; i<n; i++){
        if(mp.find(tmp[i]) == mp.end()){
            mp[tmp[i]] = id++;
        }
    }

    

    for(int i=0; i<n; i++) {
        v[i] = mp[v[i]];
        
        for(int j=(int)loc[v[i]].size()-1; j>=0; j--){
            int i1 = loc[v[i]][j];
            if(next_same[i1] >= 0) break;
            next_same[i1] = i;
        }

        for(int j=(int)loc[v[i]-1].size()-1; j>=0; j--){
            int i1 = loc[v[i]-1][j];
            if(next_diff[i1] >= 0) break;
            next_diff[i1] = i;
        }
        
        loc[v[i]].push_back(i);
        idx[i] = loc[v[i]].size() - 1;
    }

    //for(int i=0; i<n; i++) cout << next_same[i] << " "; cout << "\n";
    //for(int i=0; i<n; i++) cout << next_diff[i] << " "; cout << "\n";

    vector<int> DP(n, 1), DP2(n);
    for(int i=id+1; i>=0; i--){
        if(loc[i].empty()) continue;
        for(int j=(int)loc[i].size()-1; j>=0; j--){
            int i1 = loc[i][j];
            if(next_same[i1] >= 0){
                DP[i1] = max(DP[i1], DP[next_same[i1]] + 1);
            }
            if(next_diff[i1] >= 0){
                int i2 = next_diff[i1];
                if(loc[v[i2]][0] != i2){
                    DP[i1] = max(DP[i1], 1 + (int)loc[v[i2]].size() - idx[i2]);
                }
                else{
                    DP[i1] = max(DP[i1], 1 + DP2[i2]);
                }
            }
        }
        if(true){
            int i1 = loc[i][0], i2 = loc[i].back();
            DP2[i1] = loc[i].size() + DP[i2] - 1;
        }
    }

    
    int mx = 0;
    for(int i=0; i<n; i++) mx = max(mx, DP[i]);
    cout << n - mx << "\n";

    
    return 0;
}