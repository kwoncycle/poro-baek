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

__int128 DP[100][100005];

const ll MX = 2000'000'000'000'000'000ll;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    ll n, k; cin >> n >> k;
    
    for(int j=0; j<=100000; j++){
        DP[0][j] = 1;
    }

    for(int i=1; i<100; i++){
        DP[i][i] = DP[i-1][i];
        for(int j=i+1; j<=100000; j++){
            DP[i][j] = DP[i-1][j] + DP[i][j-1];
            if(DP[i][j] > MX) DP[i][j] = MX; 
        }
    }

    string ans;
    ll a = n/2, d = n/2;
    ans.push_back('A');
    a--; d--;
    while(a >= 100){
        ans.push_back('A'); a--;
    }
    while(a and d){
        if(DP[a-1][d] < (__int128)k and a < d){
            k -= DP[a-1][d];
            ans.push_back('D'); d--;
        }
        else{
            ans.push_back('A'); a--;
        }
    }
    while(d) {
        ans.push_back('D'); d--;
    }
    ans.push_back('D');
    if(k > 1 or a) cout << "-1\n";
    else cout << ans << "\n";


    return 0;
}