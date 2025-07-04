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

int main(){
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr); cout.tie(nullptr);
    int n, tt; cin >> n >> tt;
    vector<array<int,2>> ptime(n);
    vector<double> prob(n);
    for(int i=0; i<n; i++){
        cin >> ptime[i][0] >> ptime[i][1] >> prob[i];
    }


    vector<vector<double>> DP(tt*3+10, vector<double>(1<<n));
    vector<vector<double>> solved(tt*3+10, vector<double>(n));
    DP[0][0] = 1;
    
    for(int t=0; t<=tt; t++){
        if(t){
            for(int i=0; i<n; i++){
                solved[t][i] += solved[t-1][i];
            }
        }
        for(int i=0; i<(1<<n); i++){
            if(DP[t][i] > 0){
                double ttl = 0, cnt = 0;
                for(int j=0; j<n; j++){
                    if(0 == ((i>>j)&1)){
                        ttl += solved[t][j]; cnt++;
                    }
                }
                for(int j=0; j<n; j++){
                    if(0 == ((i>>j)&1)){
                        double p;
                        if(ttl <= 0.0000000001){
                            p = (double)1/cnt;
                        }
                        else{
                            p = solved[t][j]/ttl;
                        }
                        solved[t+ptime[j][0]+ptime[j][1]][j] += p*DP[t][i]*prob[j];
                        int nj = i ^ (1<<j);
                        DP[t+ptime[j][0]][nj] += p*DP[t][i]*(1.0-prob[j]);
                        DP[t+ptime[j][0]+ptime[j][1]][nj] += p*DP[t][i]*prob[j];
                    }
                }
            }
        }
    }

    for(int i=0; i<n; i++){
        cout << fixed << setprecision(15) << solved[tt][i] << "\n";
    }
    // for(int i=0; i<1<<n; i++){
    //     cout << fixed << setprecision(15) << DP[20][i] << "\n";
    // }

    return 0;
}