#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define pii pair<ll,ll>
#define pll pair<ll,ll>
#define X first
#define Y second
#define CNT_LOWER(v,n) (ll)(lower_bound((v).begin(),(v).end(),(n))-(v).begin())
#define CNT_UPPER(v,n) (ll)(upper_bound((v).begin(),(v).end(),(n))-(v).begin())
 
// CNT_LOWER: number of element in v smaller than n
// CNT_UPPER: number of element in v smaller or same than n


ll ccw(pair<ll, ll>p1, pair<ll, ll>p2, pair<ll, ll>p3) {
    ll s = p1.first * p2.second + p2.first * p3.second + p3.first * p1.second;
    s -= (p1.second * p2.first + p2.second * p3.first + p3.second * p1.first);

    if (s > 0) return 1;
    else if (s == 0) return 0;
    else return -1; 
}

bool isIntersect(pair<pii, pii> l1, pair<pii, pii> l2) {

    pii p1 = l1.first;
    pii p2 = l1.second;
    pii p3 = l2.first;
    pii p4 = l2.second;

    ll p1p2 = ccw(p1, p2, p3) * ccw(p1, p2, p4); // l1 기준
    ll p3p4 = ccw(p3, p4, p1) * ccw(p3, p4, p2); // l2 기준

    // 두 직선이 일직선 상에 존재
    if (p1p2 == 0 && p3p4 == 0) {
    	// 비교를 일반화하기 위한 점 위치 변경
        if (p1 > p2) swap(p2, p1);
        if (p3 > p4) swap(p3, p4);
        
        return p3 <= p2 && p1 <= p4; // 두 선분이 포개어져 있는지 확인
    }
    
    return p1p2 <= 0 && p3p4 <= 0;
    
}

// killerwhale0917.tistory.com/6


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    ll tcn = 1;
    while(true){
        ll r, c, o, d; cin >> r >> c >> o >> d;
        if(r+c+o+d == 0) break;
        cout << "Case " << tcn << ": ";
        vector<pll> po(o), pd(d);
        for(ll i=0; i<o; i++){
            cin >> po[i].X >> po[i].Y;
            po[i].X *= 2;
            po[i].Y *= 2;
        }
        for(ll i=0; i<d; i++){
            cin >> pd[i].X >> pd[i].Y;
            pd[i].X *= 2;
            pd[i].Y *= 2;
        }

        vector<ll> ans;
        for(ll i=1; i<o; i++){
            ll A = po[i].Y - po[0].Y;
            ll B = po[0].X - po[i].X;
            ll C = -(A*po[0].X + B*po[0].Y);

            ll truth = 1;
            for(ll j=0; j<d; j++){
                vector<pll> o = {{-3, -3}, {-3, 3}, {3, 3}, {3, -3}, {-3, -3}};
                for(int oi = 0; oi<4; oi++){
                    pair<pll, pll> p;
                    pll p1, p2;
                    p1.X = pd[j].X + o[oi].X;
                    p1.Y = pd[j].Y + o[oi].Y;
                    p2.X = pd[j].X + o[oi+1].X;
                    p2.Y = pd[j].Y + o[oi+1].Y;
                    p = {p1, p2};
                    if(isIntersect({po[i], po[0]}, p)) truth = 0;
                }
                if(abs(po[i].X - pd[j].X) <= 3 and abs(po[i].Y - pd[j].Y) <= 3) truth = 0;
                if(abs(po[0].X - pd[j].X) <= 3 and abs(po[0].Y - pd[j].Y) <= 3) truth = 0;
            }
            if(truth) ans.push_back(i + 1);
        }
        for(int i:ans) cout << i << " ";
        cout << "\n";
        tcn++;
    }
    return 0;
}