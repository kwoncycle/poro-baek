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
map<ll, int> DP;

int findans(ll N){
    if(DP.find(N) != DP.end()) return DP[N];
    if(N % 4 != 0){
        int x = findans(N*4) + 1;
        if(DP.find(N) == DP.end()) DP[N] = x;
        return DP[N] = min(DP[N], x);
    }
    if(N % 16 == 0){
        int x = findans(N/4) + 1;
        if(DP.find(N) == DP.end()) DP[N] = x;
        return DP[N] = min(DP[N], x);
    } 
    ll i1 = (N%16)/4, i2 = 4 - i1;
    int a1 = findans(N - 4*i1) + i1;
    int a2 = findans(N + 4*i2) + i2;
    int x = min(a1, a2);
    if(DP.find(N) == DP.end()) DP[N] = x;
    return DP[N] = min(DP[N], x);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int tt; cin >> tt;
    
    DP[0] = 0;
    for(int i=0; i<(1<<16); i++){
        int start = 0, i1 = i;
        for(int j=0; j<8; j++){
            int k = i1&3;
            if(k == 0) start += 4;
            else if(k == 1) start -= 4;
            else if(k == 2) start *= 4;
            else{
                if(start % 4 == 0) start /= 4;
                else{
                    break;
                }
            }
            i1 /= 4;
            if(DP.find(start) == DP.end()) DP[start] = j+1;
            else DP[start] = min(DP[start], j+1);
            
        }
    }
    while(tt--){
        ll n; cin >> n;
        cout << findans(n) << "\n";
    }

    return 0;
}