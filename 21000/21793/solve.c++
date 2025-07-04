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

const int MX = 300000;
int n, k;
vector<pii> v;
int DP[300000]; // DP[i] : next one minimum
int sparse[20][300000];

struct solve{
    solve(){
        cin >> n >> k;
        v.resize(n);
        vector<int> jp;
        for(auto &[i,j]:v) {
            cin >> i >> j;
            jp.push_back(i); jp.push_back(j);
        }
        sort(all(jp));
        jp.erase(unique(all(jp)), jp.end());
        for(auto &[i, j]:v){
            i = CNT_UPPER(jp, i);
            j = CNT_UPPER(jp, j);
        }
        for(int i=0; i<MX; i++) DP[i] = MX - 1;
        for(auto &[i, j]:v){
            DP[i] = min(DP[i], j);
        }
        for(int i=MX-2; i>=0; i--){
            DP[i] = min(DP[i], DP[i+1]);
        }
        for(int i=0; i<MX; i++) sparse[0][i] = DP[i];
        for(int d=1; d<20; d++){
            for(int i=0; i<MX; i++){
                sparse[d][i] = sparse[d-1][sparse[d-1][i]];
            }
        }
        int cur = cnt(0, 200001);
        if(cur < k){
            cout << "-1\n"; return;
        }
        set<pii> st;
        st.insert({0,0});
        st.insert({250000,250000});
        
        vector<int> ans;
        for(int i=0; i<n; i++){
            auto p0 = st.lower_bound({v[i].X, MX}), p1 = p0;
            p0--;
            if((*p0).Y <= v[i].X and v[i].Y <= (*p1).X){
                int n0 = cnt((*p0).Y, (*p1).X);
                int n1 = cnt((*p0).Y, v[i].X), n2 = cnt(v[i].Y, (*p1).X);
                if(cur - n0 + n1 + n2 + 1 >= k){
                    ans.push_back(i);
                    st.insert(v[i]);
                    cur = cur - n0 + n1 + n2 + 1;
                }
            }
            if(ans.size() == k) break;
        }
        for(int i:ans) cout << i+1 << "\n";
    }

    int cnt(int l, int r){
        if(DP[l] > r) return 0;
        int ans = 0;
        for(int d=19; d>=0; d--){
            if(sparse[d][l] <= r){
                l = sparse[d][l];
                ans += (1<<d);
            }
        }
        return ans;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    solve S;
    return 0;
}