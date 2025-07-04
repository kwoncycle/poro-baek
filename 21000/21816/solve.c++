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

int id[50*50*50];
array<int, 3> p[50*50*50];
vector<pii> v;

bool isin(array<int,3> l, int r){
    for(int i=0; i<3; i++){
        if(l[i] == r) return true;
    }
    vector<int> chk(3);
    for(int i=0; i<3; i++){
        chk[i] = ((v[l[i]] - v[r]) / (v[l[(i+1)%3]] - v[r])) > 0;
    }
    return chk[0] == chk[1] and chk[1] == chk[2];
}

#define MOD 1000000007

vector<int> whoisin[50*50*50];
ll DP[42][50*50*50];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n; cin >> n;
    v.resize(n);
    for(auto &[i,j]:v) cin >> i >> j;
    int idval = 0;
    for(int i=0; i<n; i++){
        for(int j=i+1; j<n; j++){
            for(int k=j+1; k<n; k++){
                id[i*2500 + j*50 + k] = idval; // we only need this
                id[i*2500 + k*50 + j] = idval;
                id[j*2500 + i*50 + k] = idval;
                id[j*2500 + k*50 + i] = idval;
                id[k*2500 + i*50 + j] = idval;
                id[k*2500 + j*50 + i] = idval;
                p[idval] = {i, j, k};
                idval++;
            }
        }
    }

    for(int i=0; i<n; i++){
        for(int j=i+1; j<n; j++){
            for(int k=j+1; k<n; k++){
                DP[3][id[i*2500 + j*50 + k]] = 6;
                for(int t=0; t<n; t++){
                    if(isin({i,j,k}, t)){
                        whoisin[id[i*2500 + j*50 + k]].push_back(t);
                    }
                }
            }
        }
    }

    for(int ord=4; ord<=n; ord++){
        for(int i=0; i<n; i++){
            for(int j=i+1; j<n; j++){
                for(int k=j+1; k<n; k++){
                    int idcur = id[i*2500 + j*50 + k];
                    if(ord > (int)whoisin[idcur].size()) continue;
                    for(int t:whoisin[idcur]){
                        if(t == i or t == j or t == k) continue;
                        DP[ord][idcur] = (DP[ord][idcur] + DP[ord-1][id[i*2500 + j*50 + t]]) % MOD;
                        DP[ord][idcur] = (DP[ord][idcur] + DP[ord-1][id[i*2500 + t*50 + k]]) % MOD;
                        DP[ord][idcur] = (DP[ord][idcur] + DP[ord-1][id[t*2500 + j*50 + k]]) % MOD;
                    }
                    DP[ord][idcur] = (DP[ord][idcur] + (DP[ord-1][idcur] * ((ll)whoisin[idcur].size()-(ord-1)))) % MOD;
                }
            }
        }
    }
    ll ans = 0;
    for(int i=0; i<50*50*50; i++) ans = (ans + DP[n][i]) % MOD;
    cout << ans << "\n";


    return 0;
}