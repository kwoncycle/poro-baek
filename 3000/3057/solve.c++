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

#define MOD 998244353
#define A 1557
#define Ainv 106428107


int n, m;
string v[305];
int inv[100005], poww[100005];
int hash_sm[305][305];
vector<vector<vector<int>>> hash_sparse(301); // [i][j][k] : [i...j]

int hash_sm_1[305][305];
vector<vector<vector<int>>> hash_sparse_1(301); // [i][j][k] : [i...j]

ll get_hash(int i, int j, int k){ // hsh[i][j...k]
    ll o = hash_sm[i][k] - (j-1 >= 0 ? hash_sm[i][j-1] : 0);
    o = (ll)o * inv[j] % MOD;
    if(o < 0) o += MOD;
    return o;
}

ll get_hash_1(int i, int j, int k){ // hsh[i][j...k]
    ll o = hash_sm_1[i][k] - (j-1 >= 0 ? hash_sm_1[i][j-1] : 0);
    o = (ll)o * inv[j] % MOD;
    if(o < 0) o += MOD;
    return o;
}

int main(){
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr); cout.tie(nullptr);
    inv[0] = 1;
    poww[0] = 1;
    for(int i=1; i<=100000; i++){
        inv[i] = (ll)inv[i-1] * Ainv % MOD;
        poww[i] = (ll)poww[i-1] * A % MOD;
    }
    cin >> n >> m;
    for(int i=0; i<n; i++) cin >> v[i];
    for(int i=0; i<n; i++){
        ll o = 1;
        for(int j=0; j<m; j++){
            hash_sm[i][j] = ((j-1 >= 0 ? hash_sm[i][j-1] : 0) + o*v[i][j]) % MOD;
            o = o * A % MOD;
        }
    }

    for(int i=0; i<m; i++){
        hash_sparse[i].resize(m-i);
        for(int j=0; j<m-i; j++){
            hash_sparse[i][j].resize(301);
            int j1 = j+i;
            for(int k=0; k<n; k++){
                hash_sparse[i][j][k] = (ll)get_hash(k, i, j1) * poww[k*(j+1)] % MOD;
                hash_sparse[i][j][k] = ((k-1 >= 0 ? hash_sparse[i][j][k-1] : 0) + hash_sparse[i][j][k]) % MOD;
            }
        }
    }

    for(int i=0; i<n-i-1; i++){
        swap(v[i], v[n-1-i]);
    }
    for(int i=0; i<n; i++) reverse(v[i].begin(), v[i].end());

    for(int i=0; i<n; i++){
        ll o = 1;
        for(int j=0; j<m; j++){
            hash_sm_1[i][j] = ((j-1 >= 0 ? hash_sm_1[i][j-1] : 0) + o*v[i][j]) % MOD;
            o = o * A % MOD;
        }
    }

    for(int i=0; i<m; i++){
        hash_sparse_1[i].resize(m-i);
        for(int j=0; j<m-i; j++){
            hash_sparse_1[i][j].resize(301);
            int j1 = j+i;
            for(int k=0; k<n; k++){
                hash_sparse_1[i][j][k] = (ll)get_hash_1(k, i, j1) * poww[k*(j+1)] % MOD;
                hash_sparse_1[i][j][k] = ((k-1 >= 0 ? hash_sparse_1[i][j][k-1] : 0) + hash_sparse_1[i][j][k]) % MOD;
            }
        }
    }
    int mx = 0;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            for(int d=1; i+d-1<n and j+d-1<m; d++){
                
                ll o = (hash_sparse[j][d-1][i+d-1] - (i-1>=0 ? hash_sparse[j][d-1][i-1] : 0));
                o = o * inv[d*i] % MOD;
                if(o < 0) o += MOD;
                int i1 = n-1-(i+d-1), j1 = m-1-(j+d-1);
                ll o1 = (hash_sparse_1[j1][d-1][i1+d-1] - (i1-1>=0 ? hash_sparse_1[j1][d-1][i1-1] : 0));
                o1 = o1 * inv[d*i1] % MOD;
                if(o1 < 0) o1 += MOD;
                if(o1 == o) mx = max(mx, d);
                //if(i == 1 and j == 0) cout << o << " " << o1 << "\n";
            }
        }
    }
    
    if(mx == 1) mx = -1;
    cout << mx << "\n";



    //cout << hash_sparse[1][2][2] << "\n";
    //cout << hash_sparse[3][2][2] << "\n";




    return 0;
}