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

int n;
int v[3004];
int minDP[3004][3004]; // minDP[i][j] : id of minimum in [i, j]
ll DP[3004][3004]; // DP[i][j] : [0..i], end with j
ll DPsm[3004][3004];
#define MOD 1000000007
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    cin >> n;
    for(int i=0; i<n; i++) {
        cin >> v[i];
    }

    for(int i=0; i<n; i++) minDP[i][i] = i;
    for(int d=2; d<=n; d++){
        for(int i=0; i+d-1<n; i++){
            int i1 = minDP[i][i+d-2], i2 = minDP[i+d-1][i+d-1];
            minDP[i][i+d-1] = (v[i1] < v[i2]) ? i1 : i2;
        }
    }

    for(int j=0; j<n; j++){
        if(minDP[0][j] == j){
            DP[0][j] = 1; 
        }
        DPsm[0][j] = (j-1 >= 0 ? DPsm[0][j-1] : 0) + DP[0][j];
    }

    for(int i=1; i<n; i++){
        for(int j=0; j<n; j++){
            if((j<=i and minDP[j][i] == j) or (i<j and minDP[i][j] == j)){
                DP[i][j] = DPsm[i-1][j];
            }
            DPsm[i][j] = ((j-1 >= 0 ? DPsm[i][j-1] : 0) + DP[i][j]) % MOD;
        }
    }

    cout << DPsm[n-1][n-1] << "\n";

    return 0;
}