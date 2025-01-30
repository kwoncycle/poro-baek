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

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    vector<vector<int>> v(100002);
    vector<int> prime(100002, 0);
    vector<int> ohi(100002, 0);
    for(int i=2; i<=100000; i++){
        if(!prime[i]){
            for(int j=i; j<=100000; j+=i){
                prime[j] = i;
            }
        }
    }

    for(int i=2; i<=100000; i++){
        int i1 = i;
        int ans = 1;
        while(i1 > 1){
            int p = prime[i1];
            ans *= p-1;
            i1 /= p;
            while(i1 % p == 0){
                i1 /= p; ans *= p;
            }
        }
        ohi[i] = ans;
    }

    for(int i=1; i<=100000; i++){
        for(int j=i+i; j<=100000; j+=i) v[j].push_back(i);
    }


    int tt; cin >> tt; tt++;
    set<int> s; 
    while(tt--){
        int r; cin >> r; s.insert(r);
    }
    s.insert(1);
    vector<int> chk(100001, 0);
    ll ans = 0;
    for(int i:s){
        int t = i-1;
        for(int j:v[i]){
            if(chk[j]) t -= ohi[j];
            chk[j] = 1;
        }
        chk[i] = 1;
        //cout << t << "\n";
        ans += t;
    }

    cout << ans << "\n";


    return 0;
}