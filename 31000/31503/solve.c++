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
    int n, q; cin >> n >> q;
    vector<int> v(n);
    for(int i=0; i<n; i++) cin >> v[i];
    vector<int> DP(n), stk;
    vector<int> DP_inv(n), stk_inv;
    for(int i=0; i<n; i++){
        if(stk.empty()){
            stk.push_back(v[i]);
            DP[i] = 1;
        }
        else{
            if(stk.back() < v[i]) stk.push_back(v[i]), DP[i] = stk.size();
            else{
                int c = CNT_LOWER(stk, v[i]); DP[i] = c + 1;
                if(stk[c] > v[i]) stk[c] = v[i];
            }
        }
    }
    reverse(v.begin(), v.end());
    for(int i=0; i<n; i++) v[i] = -v[i];
    for(int i=0; i<n; i++){
        if(stk_inv.empty()){
            stk_inv.push_back(v[i]);
            DP_inv[i] = 1;
        }
        else{
            if(stk_inv.back() < v[i]) stk_inv.push_back(v[i]), DP_inv[i] = stk_inv.size();
            else{
                int c = CNT_LOWER(stk_inv, v[i]); DP_inv[i] = c + 1;
                if(stk_inv[c] > v[i]) stk_inv[c] = v[i];
            }
        }
    }

    while(q--) {
        int i; cin >> i; i--;
        cout << DP[i] + DP_inv[n-1-i] - 1 << "\n";
    }
    return 0;
}