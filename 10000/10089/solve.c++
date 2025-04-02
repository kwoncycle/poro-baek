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

struct SegTree{
    int n;
    vector<int> tree, lazy, who;
    SegTree(int _n) : n(_n){
        tree.resize(4*n + 5); lazy.resize(4*n + 5); who.resize(4*n + 5);
        init(1, 0, n-1);
    }

    void init(int node, int l, int r){
        who[node] = l;
        if(l != r){
            init(node*2, l, (l+r)/2);
            init(node*2 + 1, (l+r)/2 + 1, r);
        }
    }

    void update(int i1, int i2, ll T){ // add i1~i2, T
        U(1, 0, n-1, i1, i2, T);
    }

    void U(int node, int l, int r, int i1, int i2, ll T){
        flushlazy(node, l, r);
        if(i2 < l or r < i1) return;
        if(i1 <= l and r <= i2){
            lazy[node] = T; 
            flushlazy(node, l, r);
            return;
        }
        U(node*2, l, (l+r)/2, i1, i2, T);
        U(node*2 + 1, (l+r)/2 + 1, r, i1, i2, T);
        if(tree[node*2] < tree[node*2 + 1]) who[node] = who[node*2 + 1];
        else who[node] = who[node*2];
        tree[node] = max(tree[node*2], tree[node*2 + 1]);
    }

    pll query(int i1, int i2){
        return Q(1, 0, n-1, i1, i2);
    }

    pll Q(int node, int l, int r, int i1, int i2){
        flushlazy(node, l, r);
        if(i2 < l or r < i1) return {-0x3f3f3f3f, -1};
        if(i1 <= l and r <= i2) return {tree[node], who[node]};
        pll q1 = Q(node*2, l, (l+r)/2, i1, i2);
        pll q2 = Q(node*2 + 1, (l+r)/2 + 1, r, i1, i2);
        return max(q1, q2);
    }

    void flushlazy(int node, int l, int r){
        tree[node] += lazy[node];
        if(l != r){
            lazy[node*2] += lazy[node];
            lazy[node*2 + 1] += lazy[node];
        }
        lazy[node] = 0;
    }
};

#define MX 200005

int n;
vector<int> graph[MX];
int tp[MX];
int depth[MX];
int sparse[MX][20];
pii timeline[MX];
vector<int> ett(1, 0);
int ett_inv[MX];
vector<array<int, 3>> path_belong[MX];
SegTree SG(MX);

ll ans_real = 0;
pll path_real;
struct solve{
    int clk = 0;
    solve(){
        cin >> n;
        for(int i=0; i<n-1; i++){
            int a,b; cin >> a >> b;
            graph[a].push_back(b);
            graph[b].push_back(a);
        }
        depth[1] = 1;
        DFS(1, 0);
        for(int i=1; i<=n; i++) sparse[i][0] = tp[i];
        for(int d=1; d<20; d++){
            for(int i=1; i<=n; i++){
                sparse[i][d] = sparse[sparse[i][d-1]][d-1];
            }
        }
        int m; cin >> m;
        for(int i=0; i<m; i++){
            int i1, i2, val;
            cin >> i1 >> i2 >> val;
            assert(i1 != i2);
            path_belong[LCA(i1, i2)].push_back({i1, i2, val});
        }
        DFS1(1);
        if(ans_real == 0) cout << "1 2 ";
        else {
            assert(path_real.X and path_real.Y);
            cout << path_real.X << " " << path_real.Y << " ";
        }
        cout << ans_real << "\n";
    }

    void DFS(int node, int rt){
        clk++;
        timeline[node].X = clk; 
        ett_inv[node] = ett.size();
        ett.push_back(node);
        
        for(int i:graph[node]){
            if(i != rt){
                tp[i] = node;
                depth[i] = depth[node] + 1;
                DFS(i, node);
            }
        }
        
        timeline[node].Y = clk;
    }

    void DFS1(int node){
        for(int i:graph[node]){
            if(i != tp[node]) DFS1(i);
        }

        for(auto &[i1, i2, val]:path_belong[node]){
            if(i1 == node or i2 == node){
                int i = i1 + i2 - node;
                SG.update(timeline[ett_inv[i]].X, timeline[ett_inv[i]].Y, val);
            }
        }

        vector<pll> v;
        for(int i:graph[node]){
            if(i != tp[node]){
                v.push_back(SG.query(timeline[ett_inv[i]].X, timeline[ett_inv[i]].Y));
            }
        }
        sort(all(v), greater<pll>());
        ll mxans = 0;
        pll pathans;
        if(v.size() >= 1){
            mxans = v[0].X; pathans = {ett[v[0].Y], node};
        }
        if(v.size() >= 2){
            mxans = v[0].X + v[1].X; pathans = {ett[v[0].Y], ett[v[1].Y]};
        }
        for(auto &[i1, i2, val]:path_belong[node]){
            if(i1 != node and i2 != node){
                pll v1 = SG.query(timeline[ett_inv[i1]].X, timeline[ett_inv[i1]].Y);
                pll v2 = SG.query(timeline[ett_inv[i2]].X, timeline[ett_inv[i2]].Y);
                if(mxans < v1.X + v2.X + val){
                    mxans = v1.X + v2.X + val;
                    pathans = {ett[v1.Y], ett[v2.Y]};
                }
            }
        }
        if(ans_real < mxans){
            ans_real = mxans;
            path_real = pathans;
        }
    }

    int LCA(int l, int r){
        if(depth[l] < depth[r]) swap(l, r);
        if(depth[l] > depth[r]){
            for(int d=19; d>=0; d--){
                int o = sparse[l][d];
                if(depth[o] >= depth[r]) l = o;
            }
        }
        if(l == r) return l;
        for(int d=19; d>=0; d--){
            if(sparse[l][d] != sparse[r][d]){
                l = sparse[l][d];
                r = sparse[r][d];
            }
        }
        return tp[l];
    }
};




int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    solve s;
    return 0;
}