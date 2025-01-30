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

struct Node{
    ll left_max;
    ll right_max;
    ll sum_max;
    ll sum_all;
public:
    Node(ll lm, ll rm, ll sm, ll sa){
        left_max = lm;
        right_max = rm;
        sum_max = sm;
        sum_all = sa;
    }

    Node operator+(const Node &N1) const{
        ll new_lm = max(left_max, sum_all + N1.left_max);
        ll new_rm = max(N1.right_max, right_max + N1.sum_all);
        ll new_sm = max(right_max + N1.left_max, max(sum_max, N1.sum_max));
        ll new_sa = sum_all + N1.sum_all;

        return Node(new_lm, new_rm, new_sm, new_sa);
    }
};

struct SegTree{
    ll n;
    vector<Node> segtree;
    vector<ll> arr;
    SegTree(ll ni, vector<ll> &arri){
        n = ni;
        segtree = vector<Node>(4*n+5, Node(0,0,0,0));
        arr = arri;
        init(1, 0, n-1);
    }

    void init(int node, int start, int end){
        if(start == end){
            segtree[node] = Node(arr[start], arr[start], arr[start], arr[start]);
            return;
        }
        int mid = (start + end)/2;
        init(node * 2, start, mid);
        init(node * 2 + 1, mid+1, end);
        segtree[node] = segtree[node*2] + segtree[node*2+1];
    }

    Node query(int node, int start, int end, int i1, int i2){
        //return segtree[node].sum_max;
        
        if(i2 < start or end < i1){
            return Node(-999999999999999999ll, -999999999999999999ll, -999999999999999999ll, 0);
        }
        if(i1 <= start and end <= i2){
            return segtree[node];
        }
        int mid = (start + end)/2;
        Node q1 = query(node*2, start, mid, i1, i2);
        Node q2 = query(node*2+1, mid+1, end, i1, i2);
        return q1 + q2;
        
    }

    void update(int node, int start, int end, int i1, ll target){
        if(i1 < start or end < i1) return;
        if(start == end){
            segtree[node] = Node(target, target, target, target);
            return;
        }
        int mid = (start + end)/2;
        update(node * 2, start, mid, i1, target);
        update(node * 2 + 1, mid+1, end, i1, target);
        segtree[node] = segtree[node*2] + segtree[node*2+1];
    }
};


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n; cin >> n;
    vector<ll> v(n);
    for(int i=0; i<n; i++) cin >> v[i];
    SegTree sgtree(n, v);
    int m; cin >> m;
    while(m--){
        int i, j; cin >> i >> j;
        i--; j--;
        cout << (sgtree.query(1,0,n-1,i,j)).sum_max << "\n";
    }
    return 0;
}