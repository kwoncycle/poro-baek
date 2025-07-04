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

#define A3 array<int, 3>

A3 operator + (A3 l, A3 r){ return {l[0]+r[0], l[1]+r[1], l[2]+r[2]}; }
A3 operator * (A3 l, int r){ return {l[r%3], l[(r+1)%3], l[(r+2)%3]}; }

struct SegTree{
    int n;
    vector<A3> tree;
    vector<int> lazy;
    SegTree(int _n) : n(_n){
        tree.resize(4*n + 5);
        lazy.resize(4*n + 5);
        init(1, 0, n-1);
    }

    void init(int node, int st, int ed){
        if(st == ed){
            tree[node] = {1, 0, 0}; return;
        }
        init(node*2, st, (st + ed)/2);
        init(node*2 + 1, (st + ed)/2 + 1, ed);
        tree[node] = tree[node*2] + tree[node*2 + 1];
    }

    void U(int node, int st, int ed, int l, int r, int val){
        F(node, st, ed);
        if(l <= st and ed <= r){
            lazy[node] += val;
            F(node, st, ed);
            return;
        }
        if(r < st or ed < l) return;
        U(node*2, st, (st+ed)/2, l, r, val);
        U(node*2 + 1, (st+ed)/2 + 1, ed, l, r, val);
        tree[node] = tree[node*2] + tree[node*2 + 1];
    }

    A3 Q(int node, int st, int ed, int l, int r){
        F(node, st, ed);
        if(l <= st and ed <= r) return tree[node];
        if(r < st or ed < l) return A3{0,0,0};
        return Q(node*2, st, (st+ed)/2, l, r) + Q(node*2 + 1, (st+ed)/2 + 1, ed, l, r);
    }

    void F(int node, int st, int ed){
        tree[node] = tree[node] * lazy[node];
        if(st != ed){
            lazy[node*2] = (lazy[node*2] + lazy[node]) % 3;
            lazy[node*2 + 1] = (lazy[node*2 + 1] + lazy[node]) % 3;
        }
        lazy[node] = 0;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n, m;
    while(cin >> n >> m){
        SegTree S(n + 5);
        for(int i=0; i<m; i++){
            char c; int l, r;
            cin >> c >> l >> r;
            if(c == 'C'){
                A3 A = S.Q(1, 0, n+4, l, r);
                cout << A[0] << " " << A[1] << " " << A[2] << "\n";
            }
            else{
                S.U(1, 0, n+4, l, r, 2);
            }
        }
        cout << "\n";
    }
    return 0;
}