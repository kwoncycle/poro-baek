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

const int MX = 200005;
const ll MOD = 998244353, A = 15571557, Ai = 449375313;

int n;
char C[MX];
vector<int> graph[MX];
int sparse_tree[19][MX], par[MX], depth[MX];
ll sparse_hash0[19][MX], sparse_hash1[19][MX];
ll pow_A[MX*5], pow_Ai[MX*5];


struct solve{
    solve(){
        cin >> n;
        for(int i=1; i<=n; i++){
            cin >> C[i];
        }
        for(int i=0; i<n-1; i++){
            int a,b; cin >> a >> b;
            graph[a].push_back(b);
            graph[b].push_back(a);
        }
        depth[1] = 1;
        DFS(1, 0);
        for(int i=1; i<=n; i++) sparse_tree[0][i] = par[i];
        for(int d=1; d<19; d++){
            for(int i=1; i<=n; i++){
                sparse_tree[d][i] = sparse_tree[d-1][sparse_tree[d-1][i]];
            }
        }

        for(int i=1; i<=n; i++){
            sparse_hash0[0][i] = C[i];
            sparse_hash1[0][i] = C[i];
        }

        for(int d=1; d<19; d++){
            for(int i=1; i<=n; i++){
                sparse_hash0[d][i] = (sparse_hash0[d-1][i] + sparse_hash0[d-1][sparse_tree[d-1][i]]*pow_A[1<<(d-1)]) % MOD;
                sparse_hash1[d][i] = (sparse_hash1[d-1][i] + sparse_hash1[d-1][sparse_tree[d-1][i]]*pow_Ai[1<<(d-1)]) % MOD;
            }
        }

        //cout << hashpath(4, 5, 1, 3) << "\n";
        //cout << hashpath(5, 4, 1, 3) << "\n";
        int mm; cin >> mm;
        while(mm--){
            int a0, b0, a1, b1;
            cin >> a0 >> b0 >> a1 >> b1;
            int l0 = lca(a0, b0), l1 = lca(a1, b1);
            int d = min(depth[a0] + depth[b0] - 2*depth[l0], depth[a1] + depth[b1] - 2*depth[l1]);
            if(hashpath(a0, b0, l0, d) == hashpath(a1, b1, l1, d)){
                cout << d+1 << "\n"; continue;
            }
            if(C[a0] != C[a1]){
                cout << "0\n"; continue;
            }
            int st = 0, ed = d; // st yes, ed no
            while(st + 1 < ed){
                int md = (st + ed) / 2;
                if(hashpath(a0, b0, l0, md) == hashpath(a1, b1, l1, md)) st = md;
                else ed = md;
            }
            cout << st+1 << '\n';
        }
    }

    void DFS(int node, int rt){
        for(int i:graph[node]){
            if(i == rt) continue;
            par[i] = node;
            depth[i] = depth[node] + 1;
            DFS(i, node);
        }
    }

    int lca(int l, int r){
        if(depth[l] < depth[r]) swap(l, r);
        int o = depth[l] - depth[r];
        for(int d=18; d>=0; d--){
            if(o & (1<<d)) l = sparse_tree[d][l];
        }
        if(l == r) return l;
        for(int d=18; d>=0; d--){
            if(sparse_tree[d][l] != sparse_tree[d][r]){
                l = sparse_tree[d][l];
                r = sparse_tree[d][r];
            }
        }
        return par[l];
    }

    int up(int l, int o){
        for(int d=18; d>=0; d--){
            if(o & (1<<d)) l = sparse_tree[d][l];
        }
        return l;
    }

    ll hash0(int l, int sz){
        if(sz == 0) return C[l];
        ll ans = 0, cur = 0;
        for(int d=18; d>=0 and sz; d--){
            if(sz & (1<<d)){
                sz ^= (1<<d);
                ans = (ans + sparse_hash0[d][l] * pow_A[cur]) % MOD;
                cur ^= (1<<d);
                l = sparse_tree[d][l];
            }
        }
        ans = (ans + C[l] * pow_A[cur]) % MOD;
        return ans;
    }

    ll hash1(int l, int sz){
        if(sz == 0) return C[l];
        ll ans = 0, cur = 0;
        for(int d=18; d>=0 and sz; d--){
            if(sz & (1<<d)){
                sz ^= (1<<d);
                ans = (ans + sparse_hash1[d][l] * pow_Ai[cur]) % MOD;
                cur ^= (1<<d);
                l = sparse_tree[d][l];
            }
        }
        ans = (ans + C[l] * pow_Ai[cur]) % MOD;
        return ans;
    }

    ll hashpath(int l, int r, int LC, int d){ //assert(lca(l,r) == LC);
        if(depth[l] - d >= depth[LC]){
            return hash0(l, d);
        }
        ll ans = hash0(l, depth[l] - depth[LC]);
        d -= depth[l] - depth[LC];
        int d1 = depth[r] - depth[LC] - d;
        r = up(r, d1);
        ans = (ans + hash1(r, d-1) * pow_A[depth[l] - depth[LC] + d]) % MOD;
        return ans;
    }


};


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    pow_A[0] = 1; pow_Ai[0] = 1;
    for(int i=1; i<MX*5; i++){
        pow_A[i] = pow_A[i-1] * A % MOD;
        pow_Ai[i] = pow_Ai[i-1] * Ai % MOD;
    }

    solve S;
    return 0;
}