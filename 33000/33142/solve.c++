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

const ll MOD = 1000000007, SZ = 8005;
int n, m;
ll val[SZ][SZ], B[SZ], T[SZ], chk[SZ];
vector<int> G[SZ];
int order[SZ];

int clk = 1;
void DFS(int node){
    T[node] = B[node]; val[node][node] = 1;
    for(int i:G[node]){
        if(!chk[i]){
            chk[i] = 1;
            DFS(i);
        }
        for(int j=1; j<=n; j++){
            val[node][j] = (val[node][j] + val[i][j]) % MOD;
        }
        T[node] = (T[node] + T[i]) % MOD;
    }
    order[clk] = node; clk++;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    cin >> n;
    for(int i=1; i<=n; i++) cin >> B[i];
    cin >> m;
    for(int i=0; i<m; i++){
        int a,b; cin >> a >> b;
        G[a].push_back(b);
    }
    for(int i=1; i<=n; i++){
        if(!chk[i]){
            chk[i] = 1;
            DFS(i);
        }
    }
    assert(clk == n+1);

    int qq; cin >> qq;
    int cur = 0;
    vector<pii> change;
    ll k = 1;
    ll ttl = 0;
    while(qq--){
        if(cur % 90 == 0){
            for(int i=1; i<=n; i++){
                int i1 = order[i];
                T[i1] = B[i1];
                for(int j:G[i1]){
                    T[i1] = (T[i1] + T[j]) % MOD;
                }
            }
            change.clear();
        }
        char q; cin >> q;
        if(q == 'Q'){
            int id; cin >> id;
            ll ans = T[id];
            for(auto &[i, x]:change){
                ans = (ans + val[id][i]*x) % MOD;
            }
            ttl = (ttl + ans*k) % MOD;
            k++;
        }
        else{
            ll id, x; cin >> id >> x;
            change.push_back({id, x - B[id]});
            B[id] = x;
        }

        cur++;
    }
    ttl %= MOD; if(ttl < 0) ttl += MOD;
    cout << ttl << "\n";

    return 0;
}