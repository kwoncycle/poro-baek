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
vector<__int128> fb(2, 1);


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    
    for(int i=2; i<98; i++){
        __int128 o = fb[i-1] + fb[i-2];
        fb.push_back(o);
        //cout << (ll)(o/(1000000000000ll)) << (ll)(o%(1000000000000ll)) << "\n";
    }
    vector<vector<__int128>> DP(205, vector<__int128>(205, 0)); // DP[i][j]: i개 이하 사용, j lsb 미만 개수
    for(int i=0; i<105; i++) DP[1][i] = 1;
    for(int i=2; i<=105; i++){
        for(int j=1; j<=105; j++){
            DP[i][j]++;
            for(int k=1; k<=j-2; k++){
                DP[i][j] += DP[i-1][k];
            }
        }
    }

    ll k, n; cin >> k >> n;
    if(n == 1){
        cout << k << "\n"; return 0;
    }
    if(k == 1){
        if(n >= 87){
            cout << "NIE\n"; return 0;
        }
    }
    n += k-1;

    vector<vector<__int128>> smDP(205, vector<__int128>(205, 0));
    for(int i=0; i<105; i++){
        smDP[i][1] = DP[i][1];
        for(int j=2; j<=105; j++){
            smDP[i][j] = smDP[i][j-1] + DP[i][j];
        }
    }

    vector<ll> checked(205, 0);
    int ch = 0;
    for(int i=97; i>=0; i--){
        if(k == 0 or n == 1) break;
        if(!ch){
            if(smDP[k][i] < (__int128)n){
                checked[i+1] = 1;
                n -= smDP[k][i];
                k--;
                ch = 1;
            }
        }
        else{
            if(smDP[k][i] + 1 < (__int128)n){
            
            checked[i+1] = 1;
            n -= smDP[k][i] + 1;
            k--;
            ch = 1;
            }
        }
    }
    
    __int128 ans = 0;
    for(int i=1; i<=97; i++){
        ans += checked[i] * fb[i];
    }

    //for(int i=1; i<90; i++) cout << checked[i]; cout << "\n";

    if(ans > (__int128)1000000000000000000ll or n > 1) cout << "NIE\n";
    else cout << (ll)ans << "\n";

    return 0;
}