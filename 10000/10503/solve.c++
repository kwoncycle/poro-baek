#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define pii pair<ll,ll>
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


struct Convex_hull{
    int n;
    vector<pii> v, ch;
    int mx = 0;
    Convex_hull(vector<pii> &_v): v(_v){
        n = v.size();
        make_CH();
        reverse(all(ch));
        rotate(ch.begin(), min_element(all(ch)), ch.end());
        ch.erase(max_element(all(ch)) + 1, ch.end());
        n = ch.size();
    }
    void make_CH(){
        pii p = *min_element(v.begin(), v.end(), [&](pii l, pii r){
            return l.Y == r.Y ? l.X < r.X : l.Y < r.Y;
        });
        sort(v.begin(), v.end(), [&](pii l, pii r){
            return (l-p)/(r-p) == 0 ? (l-p)*(l-p) < (r-p)*(r-p) : (l-p)/(r-p) > 0;
        });
        for(int i=0; i<(int)v.size(); i++){
            while((int)ch.size() >= 2 and (ch.back() - ch[ch.size()-2]) / (v[i] - ch.back()) <= 0) ch.pop_back();
            ch.push_back(v[i]);
        }
    }
};

int lr(pii p, vector<pii> &v){
    ll nv = v.size(), i1 = 0;
    pii ans;
    if((v[i1]-p)/(v[(i1+1)%nv]-v[i1]) == 0) i1 = (i1+1) % nv;
    if((v[i1]-p)/(v[(i1+1)%nv]-v[i1]) > 0){
        for(ll T = (1<<20); T >= 1; T >>= 1){
            if(T >= nv) continue;
            ll id = (i1 + T) % nv;
            if((v[id]-p)/(v[(id+1)%nv]-v[id])>=0 and (v[i1]-p)/(v[id]-p)>=0) i1 = id;
        }
        i1 = (i1 + 1) % nv;
        return i1;
        // ans.X = i1;
        // if((v[i1]-p)/(v[(i1+1)%nv]-v[i1]) == 0) i1 = (i1+1) % nv;
        // for(ll T = (1<<16); T >= 1; T >>= 1){
        //     if(T >= nv) continue;
        //     ll id = (i1 + T) % nv;
        //     if((v[id]-p)/(v[(id+1)%nv]-v[id])<0 and (v[i1]-p)/(v[id]-p)<0) i1 = id;
        // }
        // i1 = (i1 + 1) % nv;
        // ans.Y = i1;
        // return ans;
    }
    else{
        for(ll T = (1<<20); T >= 1; T >>= 1){
            if(T >= nv) continue;
            ll id = (i1 + T) % nv;
            if((v[id]-p)/(v[(id+1)%nv]-v[id]) < 0 and (v[i1]-p)/(v[id]-p)<0) i1 = id;
        }
        i1 = (i1 + 1) % nv;
        ans.Y = i1;
        if((v[i1]-p)/(v[(i1+1)%nv]-v[i1]) == 0) i1 = (i1+1) % nv;
        for(ll T = (1<<16); T >= 1; T >>= 1){
            if(T >= nv) continue;
            ll id = (i1 + T) % nv;
            if((v[id]-p)/(v[(id+1)%nv]-v[id])>=0 and (v[i1]-p)/(v[id]-p)>=0) i1 = id;
        }
        i1 = (i1 + 1) % nv;
        ans.X = i1;
        return i1;
        //return ans;
    }
}


bool isright(pii p1, pii p2, vector<pii> &v){ //strictly...oh fuck TC doesn't want that
    int n = v.size();
    if(n <= 2){
        for(int i=0; i<n; i++){
            if((p2-p1) / (v[i]-p2) > 0) return false;
        }
        return true;
    }
    int l = lr(p1, v);
    pii p = v[l];
    return (p2-p1) / (p-p1) <= 0;
}

struct CHtree{
    vector<vector<pii>> tree;
    vector<pii> point;
    vector<int> ans;
    int n;
    CHtree(vector<pii> &P) : point(P){
        n = point.size();
        tree.resize(n*4 + 4);
        init(1, 0, n-1);
    }

    void init(int node, int st, int ed){
        if(st == ed){
            tree[node].push_back(point[st]);
            return;
        }
        init(node*2, st, (st+ed)/2);
        init(node*2 + 1, (st+ed)/2 + 1, ed);
        tree[node] = tree[node*2];
        for(auto &p:tree[node*2 + 1]) tree[node].push_back(p);
        tree[node] = Convex_hull(tree[node]).ch;
    }

    void query(int l, int r){
        ans.clear();
        Q(1, 0, n-1, l, r);
    }

    void Q(int node, int st, int ed, int l, int r){
        if(l <= st and ed <= r){
            ans.push_back(node);
            return;
        }
        if(ed < l or r < st) return;
        Q(node*2, st, (st+ed)/2, l, r);
        Q(node*2 + 1, (st+ed)/2 + 1, ed, l, r);
    }
};

struct solve{
    int n;
    vector<pii> v;
    solve(){
        cin >> n;
        v.resize(n);
        for(auto &[i,j] : v) cin >> i >> j;
        CHtree C(v);
        for(int i=0; i<n-2; i++){
            int st = i+2, ed = n-1;
            if((v[i+1]-v[i]) / (v[st]-v[i+1]) > 0){
                cout << st << " "; continue;
            }
            C.query(st, ed);
            bool isR = 1;
            for(auto j:C.ans){
                if(!isright(v[i], v[i+1], C.tree[j])){
                    isR = 0; break;
                }
            }
            if(isR){
                cout << "0 "; continue;
            }
            // st..st : isR, st..ed : !isR
            while(st + 1 < ed){
                int md = (st + ed) / 2;
                C.query(st, md);
                isR = 1;
                for(auto j:C.ans){
                    if(!isright(v[i], v[i+1], C.tree[j])){
                        isR = 0; break;
                    }
                }
                if(isR) st = md;
                else ed = md;
            }
            cout << ed << " ";
        }
        // last 0
        cout << "0\n";
    }
};


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int tt; cin >> tt;
    while(tt--){
        solve S;
    }
    return 0;
}