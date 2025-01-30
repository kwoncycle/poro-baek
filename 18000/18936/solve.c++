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

#define MOD 1000000007ll

ll poww(ll a,ll x,ll m){
	if(x==1) return a%m;
	if(x==0) return 1;
    a %= m;
	ll v = 1;
	while(x){
        if(x&1) v = v*a%m;
        x /= 2;
        a = a*a%m;
    }
	return v;
}
// a^x (mod m)
 
ll modInverse(ll A, ll M){
    ll m0 = M;
    ll y = 0, x = 1;
    if (M == 1)
        return 0;
    while (A > 1) {
        ll q = A / M;
        ll t = M;
        M = A % M, A = t;
        t = y;
        y = x - q * y;
        x = t;
    }
    if (x < 0)
        x += m0;
    return x;
}

void multiply(vector<vector<ll>> &A, vector<vector<ll>> &B, vector<vector<ll>> &ans){
    ll ans1[2][2];
    for(int i=0; i<2; i++){
        for(int j=0; j<2; j++){
            ans1[i][j] = 0;
            for(int k=0; k<2; k++){
                ans1[i][j] += A[i][k]*B[k][j];
            }
            ans1[i][j] %= MOD;
        }
    }
    ans[0][0] = ans1[0][0];
    ans[0][1] = ans1[0][1];
    ans[1][0] = ans1[1][0];
    ans[1][1] = ans1[1][1];
}

vector<vector<ll>> matrixpow(vector<vector<ll>> &M, ll e){
    vector<vector<ll>> A(2, vector<ll>(2, 0)), P(2, vector<ll>(2, 0));
    A[0][0] = 1;
    A[1][1] = 1;
    for(int i=0; i<2; i++)for(int j=0; j<2; j++) P[i][j] = M[i][j];
    while(e){
        if(e&1){
            multiply(A, P, A);
        }
        e /= 2;
        multiply(P, P, P);
    }
    return A;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    ll qqq; cin >> qqq;

    ll mod2inv = modInverse(2, MOD);
    while(qqq--){
        ll n, m; cin >> n >> m;
        ll u = (4*n*n-2)%MOD;
        vector<vector<ll>> M(2, vector<ll>(2, 0));
        M[0][0] = u;
        M[0][1] = -1;
        M[1][0] = 1;
        vector<vector<ll>> M1 = matrixpow(M, m);
        ll t = M1[1][0]; ll t1 = t;
        ll A = ((2*t*n%MOD)*n+1)%MOD;
        ll B = (n*n%MOD)*(t*(t+1)%MOD)%MOD; 
        ll pw = poww((A*A-4*B)%MOD, (MOD+1)/4, MOD);
        ll u1 = (A + pw) * mod2inv % MOD, u2 = ((A - pw)) * mod2inv % MOD;
        if(u1 < 0) u1 += MOD;
        if(u2 < 0) u2 += MOD;
        multiply(M1, M, M1);
        t = M1[1][0];
        A = ((2*t*n%MOD)*n+1)%MOD;
        B = (n*n%MOD)*(t*(t+1)%MOD)%MOD;
        pw = poww((A*A-4*B)%MOD, (MOD+1)/4, MOD);
        ll u3 = (A + pw) * mod2inv % MOD, u4 = ((A - pw)) * mod2inv % MOD;
        if(u3 < 0) u3 += MOD;
        if(u4 < 0) u4 += MOD;
        ll ans_A = u2;
        if(u1 == u3 or u1 == u4) ans_A = u1;
        ll ans_B = (MOD + (ans_A - t1) % MOD) % MOD;
        cout << ans_A << " " << ans_B << "\n";
    }
    return 0;
}