#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define pii pair<int,int>
#define pll pair<ll,ll>
#define pil pair<int,ll>
#define pli pair<ll,int>
#define X first
#define Y second
#define GETVECTOR(n) for(int i=0; i< (n); i++) scanf("%d ",&inp[i]);
#define CNT_LOWER(v,n) (int)(lower_bound((v).begin(),(v).end(),(n))-(v).begin())
#define CNT_UPPER(v,n) (int)(upper_bound((v).begin(),(v).end(),(n))-(v).begin())
 
// CNT_LOWER: number of element in v smaller than n
// CNT_UPPER: number of element in v smaller or same than n
#define ld double
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    ll n, d, r;
    cin >> n >> d >> r;
    vector<vector<ld>> C(1005, vector<ld>(1005, 0));
    for(int i=0; i<=1001; i++) {
        C[i][0] = 1;
        C[i][i] = 1;
    }
    for(int i=1; i<=1001; i++){
        for(int j=1; j<i; j++) C[i][j] = C[i-1][j-1] + C[i-1][j];
    }

    vector<vector<vector<ld>>> DP(n+1, vector<vector<ld>>(d+1, vector<ld>(n+1, 0)));
    for(int j=0; j<=d; j++){
        for(int k=0; k<=r; k++){
            if(r-j>k) continue;
            if(j!=0 and r-1<k) continue;
            DP[r][j][k] = j+r;
        }
    }

    for(int i=r+1; i<=n; i++){
        for(int j=0; j<=d; j++){
            for(int k=0; k<=i; k++){
                if(i-j>k) continue;
                if(j != 0 and i-1<k) continue;
                if(k > 0){
                    if(i-r<=k){
                        DP[i][j][k] = (ld)(j+r);
                    }
                    else{
                        DP[i][j][k] = DP[i-k][j][0];
                    }
                }
                else{
                    if(i == j) DP[i][j][k] = (ld)(2*r);
                    else{
                        DP[i][j][k] = (ld)r;
                        for(int i1=0; i1<i; i1++){
                            if(2*i-j > i1) continue;
                            ld p1 = ((C[i][i1] * C[j-i-1][i-i1-1])/C[j-1][i-1]);
                            if(p1 < 0.00000000001L) continue;
                            DP[i][j][k] += p1*DP[i][j-i][i1];
                        }
                    }
                }
            }
        }
    }

    ld ans = 0;
    for(int i=0; i<n; i++){
        ans += ((C[n][i] * C[d-1][n-i-1])/C[n+d-1][n-1]) * DP[n][d][i];
    }
    cout << fixed << setprecision(9) << ans << "\n";
    return 0;
}