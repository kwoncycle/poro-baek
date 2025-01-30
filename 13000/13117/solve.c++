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

int bitcnt(int i){
    int cnt = 0;
    while(i){
        cnt += i&1; i >>= 1;
    }
    return cnt;
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n, k; cin >> n >> k;
    vector<vector<double>> v(n, vector<double>(3));
    for(int i=0; i<n; i++){
        for(int j=0; j<3; j++) cin >> v[i][j];
    }

    vector<vector<double>> DP(1<<n, vector<double>(n+1, 0));
    DP[1][1] = 1;
    for(int i=3; i<(1<<n); i+=2){
        double sm = 0;
        for(int j=1; j<(1<<n); j+=2){
            if((i&j) == j){
                int G1 = j, G2 = i^j; // G1 : 1 포함.
                assert((G1&G2) == 0);
                if(G2 == 0) continue;
                // G1 0 G2 1
                {
                    double p = 1;
                    int n1 = 0, n2 = 1;
                    for(int t=0, t1=1; t<n; t++, t1<<=1){
                        if(t1&G1) p *= v[t][n1];
                        else if(t1&G2) p *= v[t][n2];
                    }
                    sm += p;
                }

                {
                    double p = 1;
                    int n1 = 1, n2 = 2;
                    for(int t=0, t1=1; t<n; t++, t1<<=1){
                        if(t1&G1) p *= v[t][n1];
                        else if(t1&G2) p *= v[t][n2];
                    }
                    sm += p;
                }

                {
                    double p = 1;
                    int n1 = 2, n2 = 0;
                    for(int t=0, t1=1; t<n; t++, t1<<=1){
                        if(t1&G1) p *= v[t][n1];
                        else if(t1&G2) p *= v[t][n2];
                    }
                    sm += p;
                }

                {
                    double p = 1;
                    int n1 = 1, n2 = 0;
                    for(int t=0, t1=1; t<n; t++, t1<<=1){
                        if(t1&G1) p *= v[t][n1];
                        else if(t1&G2) p *= v[t][n2];
                    }
                    sm += p;
                }

                {
                    double p = 1;
                    int n1 = 2, n2 = 1;
                    for(int t=0, t1=1; t<n; t++, t1<<=1){
                        if(t1&G1) p *= v[t][n1];
                        else if(t1&G2) p *= v[t][n2];
                    }
                    sm += p;
                }

                {
                    double p = 1;
                    int n1 = 0, n2 = 2;
                    for(int t=0, t1=1; t<n; t++, t1<<=1){
                        if(t1&G1) p *= v[t][n1];
                        else if(t1&G2) p *= v[t][n2];
                    }
                    sm += p;
                }
            }
        }
        assert(sm > 0);
        for(int j=1; j<(1<<n); j+=2){
            if((i&j) == j){
                int G1 = j, G2 = i^j; // G1 : 1 포함.
                int c1 = bitcnt(G1), c2 = bitcnt(G2);
                if(G2 == 0) continue;
                // G1 0 G2 1
                {
                    double p = 1;
                    int n1 = 0, n2 = 1;
                    for(int t=0, t1=1; t<n; t++, t1<<=1){
                        if(t1&G1) p *= v[t][n1];
                        else if(t1&G2) p *= v[t][n2];
                    }
                    p /= sm;
                    for(int t=1; t<=c1; t++){
                        DP[i][t+c2] += DP[G1][t] * p;
                    }
                }

                {
                    double p = 1;
                    int n1 = 1, n2 = 2;
                    for(int t=0, t1=1; t<n; t++, t1<<=1){
                        if(t1&G1) p *= v[t][n1];
                        else if(t1&G2) p *= v[t][n2];
                    }
                    p /= sm;
                    for(int t=1; t<=c1; t++){
                        DP[i][t+c2] += DP[G1][t] * p;
                    }
                }

                {
                    double p = 1;
                    int n1 = 2, n2 = 0;
                    for(int t=0, t1=1; t<n; t++, t1<<=1){
                        if(t1&G1) p *= v[t][n1];
                        else if(t1&G2) p *= v[t][n2];
                    }
                    p /= sm;
                    for(int t=1; t<=c1; t++){
                        DP[i][t+c2] += DP[G1][t] * p;
                    }
                }

                {
                    double p = 1;
                    int n1 = 1, n2 = 0;
                    for(int t=0, t1=1; t<n; t++, t1<<=1){
                        if(t1&G1) p *= v[t][n1];
                        else if(t1&G2) p *= v[t][n2];
                    }
                    p /= sm;
                    for(int t=1; t<=c1; t++){
                        DP[i][t] += DP[G1][t] * p;
                    }
                }

                {
                    double p = 1;
                    int n1 = 2, n2 = 1;
                    for(int t=0, t1=1; t<n; t++, t1<<=1){
                        if(t1&G1) p *= v[t][n1];
                        else if(t1&G2) p *= v[t][n2];
                    }
                    p /= sm;
                    for(int t=1; t<=c1; t++){
                        DP[i][t] += DP[G1][t] * p;
                    }
                }

                {
                    double p = 1;
                    int n1 = 0, n2 = 2;
                    for(int t=0, t1=1; t<n; t++, t1<<=1){
                        if(t1&G1) p *= v[t][n1];
                        else if(t1&G2) p *= v[t][n2];
                    }
                    p /= sm;
                    for(int t=1; t<=c1; t++){
                        DP[i][t] += DP[G1][t] * p;
                    }
                }
            }
        }
    }
    //for(int i=1; i<(1<<n); i++){
        //for(int j=1; j<=n; j++) cout << DP[i][j] << " "; cout << "\n";
    //}

    cout << fixed << setprecision(12) << DP[(1<<n)-1][k] << "\n";
    return 0;
}