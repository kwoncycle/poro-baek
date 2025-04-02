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

int mp1[300][300], mp2[300][300];

void rotate(){
    int mp[300][300];
    for(int i=0; i<300; i++) for(int j=0; j<300; j++) mp[i][j] = 0;
    for(int i=100; i<=150; i++){
        for(int j=100; j<=150; j++){
            mp[i][j] = mp2[j][250-i];
        }
    }
    for(int i=0; i<300; i++){
        for(int j=0; j<300; j++){
            mp2[i][j] = mp[i][j];
        }
    }
}

ll able(int dx, int dy){
    ll mnx = 0x3f3f3f, mxx = -0x3f3f3f, mny = 0x3f3f3f, mxy = -0x3f3f3f;
    for(ll i=90; i<=210; i++){
        for(ll j=90; j<=210; j++){
            if(mp2[i][j] and mp1[i+dx][j+dy]) return 0x3f3f3f3fefefefll;
            if(mp2[i][j]){
                mnx = min(mnx, i+dx);
                mxx = max(mxx, i+dx);
                mny = min(mny, j+dy);
                mxy = max(mxy, j+dy);
            }
            if(mp1[i][j]){
                mnx = min(mnx, i);
                mxx = max(mxx, i);
                mny = min(mny, j);
                mxy = max(mxy, j);
            }
        }
    }
    return (mxx-mnx+1) * (mxy-mny+1);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n1, m1; cin >> n1 >> m1;
    for(int i=0; i<n1; i++){
        string s; cin >> s;
        for(int j=0; j<m1; j++){
            mp1[100+i][100+j] = s[j]-'0';
        }
    }

    int n2, m2; cin >> n2 >> m2;
    for(int i=0; i<n2; i++){
        string s; cin >> s;
        for(int j=0; j<m2; j++){
            mp2[100+i][100+j] = s[j]-'0';
        }
    }
    ll ans = 0x3f3f3f3f3f3f3fll;
    for(int dx=-60; dx<=60; dx++){
        for(int dy=-60; dy<=60; dy++){
            ans = min(able(dx, dy), ans);
        }
    }
    rotate();
    for(int dx=-60; dx<=60; dx++){
        for(int dy=-60; dy<=60; dy++){
            ans = min(able(dx, dy), ans);
        }
    }
    rotate();
    for(int dx=-60; dx<=60; dx++){
        for(int dy=-60; dy<=60; dy++){
            ans = min(able(dx, dy), ans);
        }
    }
    rotate();
    for(int dx=-60; dx<=60; dx++){
        for(int dy=-60; dy<=60; dy++){
            ans = min(able(dx, dy), ans);
        }
    }
    rotate();
    assert(ans < 100000000);
    cout << ans << "\n";




    return 0;
}