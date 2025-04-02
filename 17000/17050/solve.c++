#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define pii pair<int,int>
#define pll pair<ll,ll>
#define X first
#define Y second
#define CNT_LOWER(v,n) (int)(lower_bound((v).begin(),(v).end(),(n))-(v).begin())
#define CNT_UPPER(v,n) (int)(upper_bound((v).begin(),(v).end(),(n))-(v).begin())
#define all(x) (x).begin(), (x).end()

// CNT_LOWER: number of element in v smaller than n
// CNT_UPPER: number of element in v smaller or same than n

#define LINE array<pii, 2>
// LINE: l[0] + kl[1]

pii operator + (pii l, pii r){return {l.X+r.X, l.Y+r.Y};};
pii operator - (pii l, pii r){return {l.X-r.X, l.Y-r.Y};};
ll operator * (pii l, pii r){return (ll)l.X*r.X + (ll)l.Y*r.Y;};
ll operator / (pii l, pii r){return (ll)l.X*r.Y - (ll)l.Y*r.X;};

map<string, int> mp;
vector<string> D[64];
int cnt[64];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<string> v(n);
    for(int i=0; i<n; i++) cin >> v[i];

    for(int i=0; i<n; i++){
        int o = 0;
        for(int j=0; j<m; j++){
            if(v[i][j] != '?') o += 1<<j;
        }
        D[o].push_back(v[i]);
        if(mp.find(v[i]) == mp.end()) mp[v[i]] = 0;
        mp[v[i]]++;
    }

    ll ans = 0;
    for(int i=0; i<(1<<m); i++){
        for(int j=i+1; j<(1<<m); j++){
            int t = i&j;
            if(t == 0) {
                ans += (ll)D[i].size() * (ll)D[j].size();
                continue;
            }
            map<string, int> m1;
            for(auto &s1: D[i]){
                string s;
                for(int o=0; o<m; o++){
                    if(t & (1<<o)) s.push_back(s1[o]);
                }
                if(m1.find(s) == m1.end()) m1[s] = 0;
                m1[s]++;
            }
            for(auto &s1: D[j]){
                string s;
                for(int o=0; o<m; o++){
                    if(t & (1<<o)) s.push_back(s1[o]);
                }
                if(m1.find(s) != m1.end()) ans += m1[s];
            }
        }
    }

    for(auto [s, r]:mp){
        ans += (ll)r*(r-1)/2;
    }

    cout << ans << "\n";
    return 0;
}