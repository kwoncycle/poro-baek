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

priority_queue<int, vector<int>, greater<int>> pq;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n, k; cin >> n >> k;
    vector<int> v(n);
    for(auto &i:v) cin >> i;

    int id = 0;
    for(int i=0; i<min(n, k); i++) pq.push(v[i]);
    id = min(n, k);

    int T = 0;
    int mx = 0;
    while(!pq.empty()){
        int nT = pq.top(); pq.pop();
        mx = max(mx, nT - T);
        T = nT;
        if(id < n) {
            pq.push(v[id++] + T);
        }
    }
    cout << mx << "\n";


    return 0;
}