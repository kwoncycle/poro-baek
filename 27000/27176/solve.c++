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

struct Segtree{
    int n;
    vector<int> tree;
    Segtree(int _n) : n(_n){
        tree.resize(4*n + 5);
    }
    void update(int i1, int val){ // tree[i]+=val;
        U(1, 0, n - 1, i1, val);
    }
    void U(int node, int s, int e, int i1, int val){
        if(i1 < s or e < i1) return;
        if(s == i1 and i1 == e){
            tree[node] += val;
            return;
        }
        int md = (s + e) / 2;
        U(node*2, s, md, i1, val);
        U(node*2 + 1, md + 1, e, i1, val);
        tree[node] = tree[node*2] + tree[node*2 + 1];
    }

    int query(int i1, int i2){
        return Q(1, 0, n-1, i1, i2);
    }
    int Q(int node, int s, int e, int i1, int i2){
        if(i2 < s or e < i1) return 0;
        if(i1 <= s and e <= i2) return tree[node];
        int md = (s + e)/2;
        return Q(node*2, s, md, i1, i2) + Q(node*2 + 1, md + 1, e, i1, i2);
    }

    int kth(int k){ // return i s.t query(0, i) == k
        return K(1, 0, n-1, k);
    }
    int K(int node, int s, int e, int k){
        if(tree[node] == k) return e;
        if(tree[node*2] >= k) return K(node*2, s, (s+e)/2, k);
        else return K(node*2 + 1, (s+e)/2 + 1, e, k - tree[node*2]);
    }
};

struct Segtree_min{
    int n;
    vector<int> tree;
    Segtree_min(int _n) : n(_n){
        tree.resize(4*n + 5, 0x3f3f3f3f);
    }
    void update(int i1, int val){ // tree[i]+=val;
        U(1, 0, n - 1, i1, val);
    }
    void U(int node, int s, int e, int i1, int val){
        if(i1 < s or e < i1) return;
        if(s == i1 and i1 == e){
            tree[node] = val;
            return;
        }
        int md = (s + e) / 2;
        U(node*2, s, md, i1, val);
        U(node*2 + 1, md + 1, e, i1, val);
        tree[node] = min(tree[node*2], tree[node*2 + 1]);
    }

    int query(int i1, int i2){
        return Q(1, 0, n-1, i1, i2);
    }
    int Q(int node, int s, int e, int i1, int i2){
        if(i2 < s or e < i1) return 0x3f3f3f3f;
        if(i1 <= s and e <= i2) return tree[node];
        int md = (s + e)/2;
        return min(Q(node*2, s, md, i1, i2), Q(node*2 + 1, md + 1, e, i1, i2));
    }
};

int n;
vector<int> v, vi;
Segtree T(500005);
Segtree_min T_min(500005);
vector<array<int, 4>> query;
vector<array<int, 2>> Q;

struct solve{
    solve(){
        cin >> n;
        v.resize(n+1), vi.resize(n+1);
        for(int i=1; i<=n; i++) {
            cin >> v[i];
            T_min.update(i, v[i]);
            vi[v[i]] = i;
        }
        int qq; cin >> qq;
        query.resize(qq); Q.resize(qq);
        for(auto &[i1,i2,i3,i4]:query){
            cin >> i1 >> i2 >> i3 >> i4;
        }
        vector<array<int, 3>> points;
        int id = 0;
        for(auto &[i1, i2, i3, i4]:query){
            points.push_back({i1,i2,id});
            points.push_back({i3,i4,id+1});
            id += 2;
        }
        sort(all(points));
        for(int i=0, j=0; i<=n; i++){
            if(i){
                T.update(vi[i], 1);
            }
            while(j < (int)points.size() and points[j][0] <= i){
                int o = find_nth(points[j]);
                id = points[j][2];
                Q[id/2][id%2] = o;
                j++;
            }
        }
        //for(auto [i,j]:Q) cout << i << " " << j << "\n";
        vector<pii> ans(qq);
        vector<array<int, 3>> task;
        for(int i=0; i<qq; i++){
            if(Q[i][0] == Q[i][1]){
                ans[i] = min(pii(query[i][0], query[i][1]), pii(query[i][2], query[i][3]));
            }
            else{
                int i0 = Q[i][0], i1 = Q[i][1];
                if(i0 > i1) swap(i0, i1);
                int l = T_min.query(i0+1, i1) - 1;
                l = min({l, query[i][0], query[i][2]});
                task.push_back({i0, l, i});
            }
        }
        sort(all(task));
        T.tree = vector<int>(T.n*4 + 5, 0);
        for(int i=0, j=0; i<=n; i++){
            if(i){
                T.update(v[i], 1);
            }
            while(j < (int)task.size() and task[j][0] <= i){
                int o = task[j][2];
                ans[o] = {task[j][1], task[j][1] - T.query(0, task[j][1])};
                j++;
            }
        }
        for(auto &[i,j]:ans){
            cout << i << " " << j << "\n";
        }
    }

    int find_nth(array<int, 3> p){ 
        p[1] = p[0] - p[1];
        if(p[1] == 0) return 0;
        return min(n, T.kth(p[1]));
    }
};  

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    solve S;
    return 0;
}