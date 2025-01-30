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

ll area(pii p1, pii p2, pii p3){
    return abs(p1/p2 + p2/p3 + p3/p1);
}

struct Rotate{
    int n; vector<pii> v;
    vector<pii> dir;
    Rotate(int n, vector<pii> &v): n(n), v(v){}
    vector<int> idx, loc;
    void set_direction(){
        for(int i=0; i<n; i++){
            for(int j=i+1; j<n; j++){
                if(v[j] > v[i]) dir.push_back({j, i});
                else dir.push_back({i, j});
            }
        }
        sort(dir.begin(), dir.end(), [&](pii pl, pii pr){
            return (v[pl.Y] - v[pl.X])/(v[pr.Y] - v[pr.X])>0;
        });
    }
    void rotate(){
        idx.resize(n); loc.resize(n);
        for(int i=0; i<n; i++) idx[i] = i;
        sort(idx.begin(), idx.end(), [&](int l, int r){ return v[l]<v[r]; });
        for(int i=0; i<n; i++) loc[idx[i]] = i;

        ll mn = 0x3f3f3f3f3f3f3f3fll, mx = 0;
        for(int i=0; i<(int)dir.size(); i++){
            auto [i_cur, j_cur] = dir[i];
            int i1 = loc[i_cur], j1 = loc[j_cur];
            if(i1 > j1){
                swap(idx[i1], idx[j1]);
                swap(loc[i_cur], loc[j_cur]);
                swap(i1, j1);
            }
            // do some jobs here
            if(i1 > 0){
                mn = min(mn, area(v[idx[i1-1]], v[idx[i1]], v[idx[j1]]));
            }
            if(j1+1 < n){
                mn = min(mn, area(v[idx[j1+1]], v[idx[i1]], v[idx[j1]]));
            }
            mx = max(mx, area(v[idx[0]], v[idx[i1]], v[idx[j1]]));
            mx = max(mx, area(v[idx[n-1]], v[idx[i1]], v[idx[j1]]));
        }
        cout << fixed << setprecision(1) << (double)mn/2 << " " << (double)mx/2 << "\n";
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    while(true){
        int n; cin >> n;
        if(!n) break;
        vector<pii> v(n);
        for(int i=0; i<n; i++) cin >> v[i].X >> v[i].Y;
        Rotate rt(n, v);
        rt.set_direction();
        rt.rotate();
    }
    return 0;
}