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

array<int, 3> cross(array<int, 3> A, array<int, 3> B){
    // x >= A[0], B[0]
    int ox = max(A[0], B[0]), oy = max(A[1], B[1]), oxy = min(A[0]+A[1]+A[2], B[0]+B[1]+B[2]);
    return {ox, oy, max(0, oxy-ox-oy)};
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n; cin >> n;
    vector<array<int, 3>> V(n);
    for(auto &[i,j,k]:V) cin >> i >> j >> k;

    ll ans = 0; // *= 2
    for(int i=1; i<(1<<n); i++){
        array<int, 3> C = {0, 0, 0x1f3f3f3f};
        int add = 0;
        for(int j=0; j<n; j++){
            if(i & (1<<j)){
                C = cross(C, V[j]);
                add++;
            }
        }
        if(add&1) ans += (ll)C[2]*C[2]*(1ll<<(add-1));
        else ans -= (ll)C[2]*C[2]*(1ll<<(add-1));
    }

    cout << ans/2 << "." << (ans%2)*5 << "\n";

    return 0;
}