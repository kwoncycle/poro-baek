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


#define MOD 963758792369677ll
#define A 1557
#define A_i 240784951979322ll

string v[1001];
ll hash_pre[1001][2002];
ll Ai_arr[3000];
ll pow2[1000100];
ll sparse[1001][1001][15]; // [i][j][k] : (i,j) start, 2^k 줄

struct solve{
    int n, m;
    solve(){
        before();

        cin >> n >> m;
        for(int i=0; i<n; i++){
            cin >> v[i];
            v[i] = v[i] + v[i];
        }
        for(int i=0; i<n; i++){
            ll o = 1;
            for(int j=0; j<m*2; j++){
                hash_pre[i][j] = ((j-1>=0 ? hash_pre[i][j-1] : 0) + o*v[i][j]) % MOD;
                o = o * A % MOD;
            }
        }

        fill_sparse();
        pii cur = {0, 0};
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                if(cmp(cur.X, cur.Y, i, j)) cur = {i, j};
            }
        }
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                cout << v[(i+cur.X)%n][(j+cur.Y)%m];
            }
            cout << "\n";
        }
        //cout << cur.X << " " << cur.Y << "\n";
    }

    void before(){
        Ai_arr[0] = 1;
        for(int i=1; i<3000; i++){
            Ai_arr[i] = (__int128)Ai_arr[i-1] * A_i % MOD;
        }
        pow2[0] = 1;
        for(int i=1; i<=1000000; i++){
            pow2[i] = (pow2[i-1] + pow2[i-1]);
            if(pow2[i] >= MOD) pow2[i] -= MOD;
        }
    }

    ll hashval(int i, int j, int sz){
        ll o = (__int128)(hash_pre[i][j+sz-1] - (j-1>=0 ? hash_pre[i][j-1] : 0)) * Ai_arr[j] % MOD;
        if(o < 0) o += MOD;
        return o;
    }

    void fill_sparse(){
        for(int j=0; j<m; j++){
            for(int i=0; i<n; i++){
                sparse[i][j][0] = hashval(i, j, m);
            }
            for(int d=1, d2=2; d2 <= n; d++, d2 *= 2){
                for(int i=0; i<n; i++){
                    sparse[i][j][d] = ((__int128)sparse[i][j][d-1] + (__int128)sparse[(i+d2/2)%n][j][d-1] * pow2[d2*m/2])%MOD;
                }
            }
        }
    }

    bool cmp(int i1, int j1, int i2, int j2){ // p1 better than p2 = true
        //cout << i1 << " " << j1 << " " << i2 << " " << j2 << "\n";
        int d = 0, d2 = 1;
        for( ; d2 <= n; d++, d2 *= 2) ;
        int sm = 0;
        for( ; d >= 0; d--, d2 /= 2){
            if(sm + d2 > n) continue;
            if(sparse[i1][j1][d] == sparse[i2][j2][d]){
                i1 = (i1 + d2) % n; i2 = (i2 + d2) % n; sm += d2;
            }
        }
        if(sm == n) return false;
        //cout << hashval(i1, j1, 1) << " " << hashval(i2, j2, 1) << "\n";
        int st = 0, ed = m; // st same ed diff
        while(st + 1 < ed){
            int md = (st + ed) / 2;
            if(hashval(i1, j1, md) == hashval(i2, j2, md)) st = md;
            else ed = md;
        }
        j1 = (j1 + ed - 1) % m;
        j2 = (j2 + ed - 1) % m;
        //cout << sm << "\n";
        assert(v[i1][j1] != v[i2][j2]);
        assert(ed > 0);
        //cout << "-> " << i1 << " " << j1 << " " << i2 << " " << j2 << "\n";
        if(v[i1][j1] == '*') return false;
        else return true;
    }
};



int main(){
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr); cout.tie(nullptr);
    solve();
    return 0;
}