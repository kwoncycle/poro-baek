#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int,int>
#define pll pair<ll,ll>
#define pil pair<int,ll>
#define pli pair<ll,int>
#define X first
#define Y second
#define GETVECTOR(n) for(int i=0; i< (n); i++) scanf("%d ",&inp[i]);
#define CNT_LOWER(v,n) (int)(lower_bound((v).begin(),(v).end(),(n))-(v).begin())
#define CNT_UPPER(v,n) (int)(upper_bound((v).begin(),(v).end(),(n))-(v).begin())
 

// THIS IS LAZY
struct SegTree{
    int n;
    vector<ll> tree, lazy;
    SegTree(int _n):n(_n){
        lazy.resize(4*n+5, 0);
        tree.resize(4*n+5, 0);
    }
    /*
    void init(int node, int s, int e){
        if(s == e){
            segtree[node] = arr[s];
            return;
        }
        init(node * 2, s, (s + e)/2);
        init(node * 2 + 1, (s + e)/2 + 1, e);
        segtree[node] = segtree[node * 2] + segtree[node * 2 + 1];
        return;
    }*/
    
    // add s~e += target
    void update(int i1, int i2, ll target){
        U(1, 0, n-1, i1, i2, target);
    }

    void U(int node, int s, int e, int i1, int i2, ll target){
        lazyU(node, s, e);
        if(e < i1 or i2 < s) return;
        if(i1 <= s and e <= i2){
            lazy[node] += target;
            lazyU(node, s, e);
            return;
        }
        U(node*2, s, (s + e)/2, i1, i2, target);
        U(node*2 + 1, (s + e)/2 + 1, e, i1, i2, target);
        tree[node] = tree[node * 2] + tree[node * 2 + 1];
    }

    ll query(int i1, int i2){
        return Q(1, 0, n-1, i1, i2);
    }

    ll Q(int node, int s, int e, int i1, int i2){
        lazyU(node, s, e);
        if(e < i1 or i2 < s) return 0;
        if(i1 <= s and e <= i2){
            return tree[node];
        }
        ll q1 = Q(node*2, s, (s+e)/2, i1, i2);
        ll q2 = Q(node*2 + 1, (s+e)/2 + 1, e, i1, i2);
        return q1 + q2;
    }

    void lazyU(int node, int s, int e){
        tree[node] += lazy[node] * (e - s + 1);
        if(e != s){
            lazy[node * 2] += lazy[node];
            lazy[node * 2 + 1] += lazy[node];
        }
        lazy[node] = 0;
    }
};

int main(){
    return 0;
}