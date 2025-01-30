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
ll n, k;

#define MOD 1000000007

vector<vector<ll>> M, tmp, M1;

void mul(vector<vector<ll>> &M1, vector<vector<ll>> &M2, vector<vector<ll>> &out){
    for(int i=0; i<3*k; i++){
        for(int j=0; j<3*k; j++) out[i][j] = 0;
    }

    for(int i=0; i<3*k; i++){
        for(int j=0; j<3*k; j++){
            for(int t=0; t<3*k; t++){
                out[i][j] = (out[i][j] + M1[i][t] * M2[t][j]) % MOD;
            }
        }
    }
}

void poww(vector<vector<ll>> &M1, ll e, vector<vector<ll>> &out){
    vector<vector<ll>> v(3*k, vector<ll>(3*k)), ans(3*k, vector<ll>(3*k)),  v2 = M1;
    for(int i=0; i<3*k; i++) ans[i][i] = 1;
    while(e){
        if(e&1){
            mul(ans, v2, v);
            ans = v;
        }
        mul(v2, v2, v);
        v2 = v;
        e >>= 1;
    }
    for(int i=0; i<3*k; i++){
        for(int j=0; j<3*k; j++) out[i][j] = ans[i][j];
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    cin >> n >> k;

    M = vector<vector<ll>>(3*k, vector<ll>(3*k, 0));
    tmp = vector<vector<ll>>(3*k, vector<ll>(3*k, 0));
    M1 = vector<vector<ll>>(3*k, vector<ll>(3*k, 0));
    if(k == 0){
        k=1;
        M = vector<vector<ll>>(3*k, vector<ll>(3*k, 0));
        tmp = vector<vector<ll>>(3*k, vector<ll>(3*k, 0));
        M1 = vector<vector<ll>>(3*k, vector<ll>(3*k, 0));
        for(int i=0; i<k; i++){
            // A: A,i-1 B,i-1 C,i-1
            // B: A,i C,i
            // C: A,i B,i C,i
            
            M[i+k][(i) + k + k] = 1;

            M[i+k+k][(i) + k] = 1;
            M[i+k+k][(i) + k + k] = 1;
        }
        poww(M, n, tmp);

        ll ans = 0;
        for(int i=0; i<3*k; i+=k) ans += tmp[i][2*k], ans %= MOD;
        cout << ans << "\n";
        return 0;
    }
    // 0~k-1 = A, i // k~2k-1 = B, i // 2k~3k-1 = C
    for(int i=0; i<k; i++){
        // A: A,i-1 B,i-1 C,i-1
        // B: A,i C,i
        // C: A,i B,i C,i
        M[i][(i-1+k)%k] = 1;
        M[i][(i-1+k)%k + k] = 1;
        M[i][(i-1+k)%k + k + k] = 1;
        
        M[i+k][(i)] = 1;
        M[i+k][(i) + k + k] = 1;

        M[i+k+k][(i)] = 1;
        M[i+k+k][(i) + k] = 1;
        M[i+k+k][(i) + k + k] = 1;
    }

    for(int i=0; i<k; i++){
        // A: A,i-1 B,i-1 C,i-1
        // B: A,i C,i
        // C: A,i B,i C,i
        M1[i][(i-1+k)%k] = 1;
        M1[i][(i-1+k)%k + k] = 1;
        
        M1[i+k][(i)] = 1;
    }

    poww(M, n, tmp);

    ll ans = 0;
    for(int i=0; i<3*k; i+=k) ans += tmp[i][0], ans %= MOD;

    poww(M1, n, tmp);

    for(int i=0; i<3*k; i+=k) ans -= tmp[i][0], ans %= MOD;
    ans %= MOD;
    if(ans < 0) ans += MOD;
    cout << ans << "\n";
    // DP[n][A][i] = DP[n-1][A][i-1] + DP[n-1][B][i-1] + DP[n-1][C][i-1]
    return 0;
}