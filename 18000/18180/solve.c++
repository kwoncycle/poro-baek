#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

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

const int SQ = 300;

int chk[100005];

struct DJS{
    int par[100005];
    DJS(){
        for(int i=0; i<100005; i++) par[i] = i;
    }
    int find(int x){
        if(x == par[x]) return x;
        return par[x] = find(par[x]);
    }
    bool Union(int l, int r){
        l = find(l); r = find(r);
        if(l == r) return false;
        par[l] = r;
        return true;
    }
} D;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n, e, p; cin >> n >> e >> p;
    unordered_set<ll> st;
    vector<pii> edge;
    for(int i=0; i<e; i++){
        ll a,b; cin >> a >> b;
        st.insert((a<<32) ^ b);
        st.insert((b<<32) ^ a);
        edge.push_back({a, b});
    }
    while(p--){
        int m; cin >> m;
        vector<ll> v(m);
        for(auto &i:v){
            cin >> i; 
            chk[i] = 1;
        }

        if(m < SQ){
            for(int i=0; i<m; i++){
                for(int j=i+1; j<m; j++){
                    if(st.find((v[i]<<32)^v[j]) != st.end()){
                        D.Union(v[i], v[j]);
                    }
                }
            }
            int cnt = 0;
            for(ll i:v){
                if(D.find(i) == i) cnt++;
            }
            cout << cnt << "\n";
        }

        else{
            for(auto &[i, j]:edge){
                if(chk[i] and chk[j]) D.Union(i, j);
            }
            int cnt = 0;
            for(ll i:v){
                if(D.find(i) == i) cnt++;
            }
            cout << cnt << "\n";
        }

        for(auto &i:v){
            chk[i] = 0; D.par[i] = i;
        }
    }
    return 0;
}