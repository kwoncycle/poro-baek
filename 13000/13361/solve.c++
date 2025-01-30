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

struct DJS{
    int n;
    vector<int> par;
    DJS(int n){
        par.resize(n);
        for(int i=0; i<n; i++) par[i] = i;
    }

    int find(int x){
        if(par[x] == x) return x;
        return par[x] = find(par[x]);
    }

    bool Union(int x, int y){
        x = find(x);
        y = find(y);
        if(x == y) return false;
        par[x] = y;
        return true;
    }
};


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n; cin >> n;
    vector<pii> v(n);
    map<int, int> mp;
    vector<int> mpi;
    int id = 0;
    for(int i=0; i<n; i++){
        cin >> v[i].X >> v[i].Y;
        if(mp.find(v[i].X) == mp.end()) mp[v[i].X] = id++, mpi.push_back(v[i].X);
        if(mp.find(v[i].Y) == mp.end()) mp[v[i].Y] = id++, mpi.push_back(v[i].Y);
    }
    DJS djs(2*n+2);
    vector<int> cnt1(2*n+2);
    vector<ll> ttl(2*n+2);
    vector<set<int>> idx(2*n+2);
    for(int i=0; i<n; i++){
        int i1 = mp[v[i].X], i2 = mp[v[i].Y];
        djs.Union(i1, i2);
    }

    for(int i=0; i<n; i++){
        int i1 = mp[v[i].X], i2 = mp[v[i].Y];
        int id = djs.find(i1);

        cnt1[id]++;
        idx[id].insert(mpi[i1]);
        idx[id].insert(mpi[i2]);
        ttl[id] += mpi[i1];
        ttl[id] += mpi[i2];
    }

    ll ans = 0;

    for(int i=0; i<=2*n; i++){
        if(cnt1[i]){
            if(cnt1[i] == (int)idx[i].size()){
                ll sm = 0;
                for(int j:idx[i]) sm += j;
                ans += ttl[i] - sm;
            }
            else if(cnt1[i] + 1 == (int)idx[i].size()){
                ll sm = 0;
                for(int j:idx[i]) sm += j;
                sm -= *idx[i].rbegin();
                ans += ttl[i] - sm;
            }
            else assert(0);
        }
    }

    cout << ans << "\n";



    return 0;
}