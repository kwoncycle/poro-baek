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

pii operator + (pii l, pll r) { return pii(l.X+r.X, l.Y+r.Y); }
pii operator - (pii l, pll r) { return pii(l.X-r.X, l.Y-r.Y); }
ll operator / (pii l, pll r) { return (ll)l.X*r.Y - (ll)l.Y*r.X; }

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    pii p1, p2, p3;
    cin >> p1.X >> p1.Y;
    cin >> p2.X >> p2.Y;
    cin >> p3.X >> p3.Y;
    int ccw = (p2-p1)/(p3-p2);
    if(ccw > 0) cout << 1 << "\n";
    else if(ccw < 0) cout << -1 << "\n";
    else cout << 0 << "\n";
    return 0;
}