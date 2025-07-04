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

unordered_set<int> st[100004];
ll presm[100005];
ll DP[400][100005];
const int SZ = 300;
vector<pii> tasks_m[100005], tasks_p[100005];
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n, m, q; cin >> n >> m >> q;
    vector<array<int, 3>> query(q+1);
    for(int tm=1; tm<=q; tm++){
        auto &[i,j,k] = query[tm];
        cin >> i >> j;
        if(i != 3) cin >> k;
    }
    for(int tm=1; tm<=q; tm++){
        auto &[i,j,k] = query[tm];
        if(i == 1){
            if(st[j].find(k) == st[j].end()){
                st[j].insert(k);
                if(tm-1) tasks_p[tm-1].push_back({j, k});
            }
            else{
                st[j].erase(k);
                tasks_m[tm].push_back({-j, k});
            }
        }
        
        if(tm % SZ == 0){
            for(int id=1; id<=n; id++){
                for(int u:st[id]){
                    tasks_m[tm].push_back({-id, u});
                    tasks_p[tm].push_back({id, u});
                }
            }
        }
    }
    for(int id=1; id<=n; id++){
        st[id].clear();
    }
    //for(auto [i,j,k]:tasks) cout << i << " " << j << " " << k << " task\n";

    int id = 0, dpid = 1;
    for(int tm=1; tm<=q+1; tm++){
        if(tm != q+1){
            auto &[i,j,k] = query[tm];
            if(i == 2){
                presm[j] += k;
            }
        }
        for(auto &[i, j]:tasks_m[tm]){
            DP[dpid][j] += presm[-i];
            id++;
        }

        if(tm % SZ == 0){
            for(int u=1; u<=n; u++) DP[dpid+1][u] = DP[dpid][u];
            dpid++;
        }

        for(auto &[i, j]:tasks_p[tm]){
            DP[dpid][j] -= presm[i];
            id++;
        }
    }
    // fiil DP
    dpid = 0;
    for(int tm=1; tm<=q; tm+=SZ){
        vector<int> person;
        for(int i=0; i<SZ; i++){
            if(tm+i > q) continue;
            else if(query[tm+i][0] == 3){
                person.push_back(query[tm+i][1]);
            }
        }
        sort(all(person)); person.erase(unique(all(person)), person.end());
        for(int i1=0; i1<SZ; i1++){
            if(tm+i1 > q) continue;
            auto &[i,j,k] = query[tm + i1];
            if(i == 1){
                if(st[j].find(k) == st[j].end()){
                    st[j].insert(k);
                }
                else{
                    st[j].erase(k);
                }
            }
            else if(i == 2){
                for(int p:person){
                    if(st[j].find(p) != st[j].end()){
                        DP[dpid][p] += k;
                    }
                }
            }
            else if(i == 3){
                cout << DP[dpid][j] << "\n";
            }
        }
        dpid++;
    }

    return 0;
}