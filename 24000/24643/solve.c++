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

// we need A[n][m][t] : person n solve prob m at time t, and B = A_prefixsum(time)

#define MOD 998244353

ll poww(ll a, ll e){
    a %= MOD;
    ll ans = 1;
    while(e){
        if(e&1) ans = ans * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return ans;
}

ll fct[200001], fcti[200001];
void fillfct(){
    fct[0] = 1;
    for(int i=1; i<=200000; i++) fct[i] = fct[i-1] * i % MOD;
    fcti[200000] = poww(fct[200000], MOD - 2);
    for(int i=200000; i>=1; i--) fcti[i-1] = fcti[i] * i % MOD;
}


ll n, m, k;

ll V[505][30];
ll A[505][30][305], B[505][30][305], Pmul[30][305], PmulZero[30][305]; // Pmul: no one solve prob m at time t

ll knap[30][305]; // m문제를 다 푼 시간

void fillA(int node){
    memset(knap, 0, sizeof(knap));
    knap[0][0] = 1;
    for(int i=0; i<m; i++){
        for(int j=i; j>=0; j--){
            for(int t=V[node][i]; t<=k; t++){
                knap[j+1][t] += knap[j][t - V[node][i]];
                if(knap[j+1][t] >= MOD) knap[j+1][t] -= MOD;
            }
        }
    }

    for(int i=0; i<m; i++){
        for(int j=0; j<m; j++){
            for(int t=0; t + V[node][i] <= k; t++){
                knap[j+1][t + V[node][i]] -= knap[j][t];
                if(knap[j+1][t + V[node][i]] < 0) knap[j+1][t + V[node][i]] += MOD;
            }
        }

        for(int j=0; j<m; j++){
            for(int t=0; t + V[node][i] <= k; t++){
                A[node][i][t + V[node][i]] += knap[j][t] * fct[m - 1 - j] % MOD * fct[j] % MOD;
                if(A[node][i][t + V[node][i]] >= MOD) A[node][i][t + V[node][i]] -= MOD;
            }
        }

        for(int t=0; t<=k; t++){
            if(V[node][i] == 0) A[node][i][t] = 0;
            else A[node][i][t] = A[node][i][t] * fcti[m] % MOD;
        }

        for(int j=m-1; j>=0; j--){
            for(int t=V[node][i]; t<=k; t++){
                knap[j+1][t] += knap[j][t - V[node][i]];
                if(knap[j+1][t] >= MOD) knap[j+1][t] -= MOD;
            }
        }
    }
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    fillfct();
    cin >> n >> m >> k;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++) cin >> V[i][j];
    }

    for(int i=0; i<n; i++) fillA(i);

    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            for(int t=0; t<=k; t++){
                B[i][j][t] = (t > 0 ? B[i][j][t-1] : 0) + A[i][j][t];
                if(B[i][j][t] >= MOD) B[i][j][t] -= MOD;
            }
        }
    }

    for(int j=0; j<m; j++){
        for(int t=0; t<=k; t++){
            Pmul[j][t] = 1;
            for(int i=0; i<n; i++){
                if((1 - B[i][j][t]) % MOD) Pmul[j][t] = Pmul[j][t] * (1 - B[i][j][t]) % MOD;
                else PmulZero[j][t]++;
            }
        }
    }

    for(int i=0; i<n; i++){
        ll ans = 0;
        for(int j=0; j<m; j++){
            if(V[i][j]){
                for(int t=0; t<=k; t++){
                    if(A[i][j][t]){
                        ll sm = 1;
                        if(t > 0){
                            if(PmulZero[j][t-1] >= 2 or (PmulZero[j][t-1] == 1 and (1 - B[i][j][t-1]) % MOD)) sm = 0;
                            else{
                                if(PmulZero[j][t-1]) sm = Pmul[j][t-1];
                                else{
                                    sm = Pmul[j][t-1] * poww(MOD + 1 - B[i][j][t-1], MOD - 2) % MOD;
                                }
                            }
                        }
                        /*for(int i1=0; i1<n; i1++){
                            if(i1 != i) sm = sm * (1 - (t-1>=0 ? B[i1][j][t-1] : 0)) % MOD;
                        }*/
                        ans = (ans + A[i][j][t] * sm) % MOD;
                    }
                    //A[i][j][t] * pi_i=0~n (1 - B[i][j][t])
                }
            }
        }
        if(ans < 0) ans += MOD;
        cout << ans << "\n";
    }


    return 0;
}