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

struct SegTree{
    int n;
    vector<set<int>> seg;
    SegTree(int x, int y){
        seg.resize(4*x+7);
        for(int i=1; i<4*x+7; i++){
            seg[i].insert(0); seg[i].insert(y);
        }
    }

    void update(int node, int start, int end, int l, int r, int y){
        if(r < start or end < l) return;
        if(l <= start and end <= r){
            seg[node].insert(y);
            return;
        }
        int mid = (start + end) / 2;
        update(node*2, start, mid, l, r, y);
        update(node*2 + 1, mid + 1, end, l, r, y);
    }

    pii query(int node, int start, int end, int target, int y){
        if(target < start or end < target) return {-1, 0x3f3f3f3f};
        int mn = -1, mx = 0x3f3f3f3f;
        if(start <= target and target <= end){
            auto i = seg[node].lower_bound(y);
            i--;
            mn = *i;
            i++;
            mx = *i;
        }
        if(start == end) return {mn, mx};

        int mid = (start + end) / 2;
        pii q1 = query(node*2, start, mid, target, y);
        pii q2 = query(node*2 + 1, mid + 1, end, target, y);
        return pii(max(mn, max(q1.X, q2.X)), min(mx, min(q1.Y, q2.Y)));
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int a, b; cin >> a >> b;
    SegTree tree1(a, b), tree2(b, a);
    int n; cin >> n;
    for(int i=0; i<n; i++){
        int x, y, d; cin >> x >> y >> d;
        pii rangex = tree2.query(1, 0, b-1, y, x);
        pii rangey = tree1.query(1, 0, a-1, x, y);
        if(d == 1){
            tree1.update(1, 0, a-1, rangex.X, rangex.Y, y);
            ll o1 = (ll)(rangex.Y-rangex.X) * (y-rangey.X);
            ll o2 = (ll)(rangex.Y-rangex.X) * (rangey.Y-y);
            cout << min(o1,o2) << " " << max(o1,o2) << "\n";
        }
        else{
            tree2.update(1, 0, b-1, rangey.X, rangey.Y, x);
            ll o1 = (ll)(rangey.Y-rangey.X) * (x-rangex.X);
            ll o2 = (ll)(rangey.Y-rangey.X) * (rangex.Y-x);
            cout << min(o1,o2) << " " << max(o1,o2) << "\n";
        }
    }
    return 0;
}