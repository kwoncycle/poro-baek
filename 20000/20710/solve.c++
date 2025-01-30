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

#define MX 200500

vector<int> par(MX);
vector<vector<int>> sparse(MX, vector<int>(20));
vector<int> val(MX);
vector<int> L(MX), R(MX);
vector<int> depth(MX);
vector<pii> rng(MX);
set<pii> s;

struct solve{
    int n;
    solve(){
        cin >> n;

        depth[1] = 1;
        for(int i=1; i<=n; i++){
            int l, r, k; cin >> l >> r >> k;
            par[l] = i;
            par[r] = i;
            L[i] = l; R[i] = r;
            val[i] = k;

            depth[l] = depth[i] + 1;
            depth[r] = depth[i] + 1;
            s.insert({val[i], i});
        }

        for(int i=n; i>=1; i--){
            rng[i] = {val[i], val[i]};
            if(L[i]){
                rng[i].X = min(rng[i].X, rng[L[i]].X);
                rng[i].Y = max(rng[i].Y, rng[L[i]].Y);
            }
            if(R[i]){
                rng[i].X = min(rng[i].X, rng[R[i]].X);
                rng[i].Y = max(rng[i].Y, rng[R[i]].Y);
            }
        }

        fill_sparse();
        int qq; cin >> qq;
        while(qq--){
            int l, r; cin >> l >> r;
            int x = query(l, r);
            cout << x << "\n";
        }
    }

    void fill_sparse(){
        for(int i=1; i<=n; i++){
            sparse[i][0] = par[i];
        }
        for(int d=1; d<20; d++){
            for(int i=1; i<=n; i++){
                if(sparse[i][d-1] >= 1) sparse[i][d] = sparse[sparse[i][d-1]][d-1];
                else sparse[i][d] = sparse[i][d-1];
            }
        }
    }

    int lca(int l, int r){
        if(depth[l] > depth[r]) swap(l, r);
        for(int d=19; d>=0; d--){
            if(depth[r] - (1<<d) < depth[l]) continue;
            r = sparse[r][d];
        }

        if(l == r) return l;
        for(int d=19; d>=0; d--){
            if(sparse[l][d] == sparse[r][d]) continue;
            l = sparse[l][d], r = sparse[r][d];
        }
        return par[l];
    }

    int query(int l, int r){
        l = max(l, rng[1].X); r = min(r, rng[1].Y);
        if(l>r) return 1;
        if(l == rng[1].X and r == rng[1].Y) return 1;
        auto [_1, l1] = *(s.lower_bound({l, -0x3f3f3f3f}));
        auto [_2, r1] = *(--s.lower_bound({r, 0x3f3f3f3f}));
        if(val[l1] > val[r1]){
            if(depth[l1] > depth[r1]) l1 = r1;
            else r1 = l1;
        }
        else{
            int d = 20;
            while(l <= rng[l1].X and rng[l1].Y <= r and d >= 1){
                d--;
                if(sparse[l1][d] == 0) continue;
                int i = sparse[l1][d];
                if(l <= rng[i].X and rng[i].Y <= r) l1 = i;
            }
            if(l <= rng[l1].X and rng[l1].Y <= r) l1 = par[l1];
            d = 20;
            while(l <= rng[r1].X and rng[r1].Y <= r and d >= 1){
                d--;
                if(sparse[r1][d] == 0) continue;
                int i = sparse[r1][d];
                if(l <= rng[i].X and rng[i].Y <= r) r1 = i;
            }
            if(l <= rng[r1].X and rng[r1].Y <= r) r1 = par[r1];
        }
        int tp = lca(l1, r1);
        int ans = 2*(depth[tp] - 1);
        if(l1 == r1){
            ans+=3; 
            return ans;
        }
        if(l1 != tp and r1 != tp){
            ans += 7;
            ans += 2*((depth[l1] - depth[tp] - 1) + (depth[r1] - depth[tp] - 1));
            return ans;
        }

        ans += (depth[l1] + depth[r1] - 2*depth[tp])*2 + 3;
        return ans;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    solve ss;
    return 0;
}