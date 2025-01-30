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
vector<ll> v, v_pre;

ll get_sm(int i, int j){
    if(i>j) return 0;
    return v_pre[j] - (i-1>=0 ? v_pre[i-1] : 0);
}

ll get_mn(int i, int j){
    if(i>j) return 0x3f3f3f3f3f3f3f3ll;
    int o = (i+j)>>1;
    return v[o]*(o-i+1) - get_sm(i, o) + get_sm(o+1, j) - (j-o)*v[o];
}

ll DP[103][103][103];

int main(){
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr); cout.tie(nullptr);

    ll n, p, l; cin >> n >> p >> l;
    v.resize(n); v_pre.resize(2*n);
    for(int i=0; i<n; i++) cin >> v[i];
    for(int i=0; i<n; i++) v.push_back(v[i] + l);
    v_pre[0] = v[0];
    for(int i=1; i<2*n; i++) v_pre[i] = v_pre[i-1] + v[i];
    
    for(int i=0; i<n; i++) for(int j=0; j<n; j++) for(int k=0; k<=p; k++) DP[i][j][k] = k ? 0x3f3f3f3f3f3f33fll : 0;
    // DP[i][j][k]: i~j 를 k개 최소값

    for(int i=0; i<n; i++){
        for(int j=i; j<n; j++){
            int o = (i+j)/2;
            DP[i][j][1] = get_mn(i, j);
        }
    }

    for(int c=2; c<=p; c++){
        for(int i=0; i<n; i++){
            for(int j=i; j<n; j++){
                for(int o=i; o<j; o++){
                    DP[i][j][c] = min(DP[i][j][c], DP[i][o][1] + DP[o+1][j][c-1]);
                }
            }
        }
    }

    ll ans = 0x3f3f3f3f3f3f3f3fll;
    ll mi, mj;
    if(p == 1){
        for(int i=0; i<n; i++){
            ll t = get_mn(i, i-1+n);
            if(ans > t){
                ans = t;
                mi = i;
            }
        }
        cout << ans << "\n";
        cout << v[((mi + mi-1 + n)/2) % n] << "\n";
        return 0;
    }

    for(int i=0; i<n; i++){
        for(int j=i; j<n; j++){
            if(j+1 > i-1+n) continue;
            ll t = DP[i][j][p-1] + get_mn(j+1, i-1+n);
            if(ans > t){
                ans = t;
                mi = i; mj = j;
            }
        }
    }

    vector<ll> anss;
    anss.push_back(v[((mj+1 + mi-1+n)/2) % n]);
    for(int c=p-1; c>=1; c--){
        if(c == 1){
            anss.push_back(v[(mi + mj)/2]);
        }
        else{
            int truth = 0;
            for(int i=mi; i<=mj; i++){
                if(DP[mi][i][1] + DP[i+1][mj][c-1] == DP[mi][mj][c]){
                    anss.push_back(v[(mi + i)/2]);
                    mi = i+1;
                    truth = 1;
                    break;
                }
            }
            assert(truth);
        }
    }


    cout << ans << "\n";
    sort(all(anss));
    for(auto i:anss) cout << i << " "; cout << "\n";
    return 0;
}