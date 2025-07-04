#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

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

int n, q;
vector<pii> tree[400005];
int andtree[400005];
int v[100004];
void init(int node, int st, int ed){
    if(st == ed){
        tree[node].push_back({0, v[st]});
        tree[node].push_back({v[st], 0x7fffffff});
        andtree[node] = v[st];
        return;
    }
    init(node*2, st, (st+ed)/2);
    init(node*2+1, (st+ed)/2+1, ed);
    for(auto &[o1, a1]:tree[node*2]){
        for(auto &[o2, a2]:tree[node*2 + 1]){
            if((o1|o2) <= (a1&a2)) tree[node].push_back({o1|o2, a1&a2});
        }
    }
    sort(all(tree[node]));
    tree[node].erase(unique(all(tree[node])), tree[node].end());
    andtree[node] = andtree[node*2] & andtree[node*2+1];
}

vector<pii> query(int node, int st, int ed, int l, int r){
    if(ed < l or r < st) return vector<pii>(1, {0,0x7fffffff});
    if(l <= st and ed <= r) return tree[node];
    vector<pii> v1 = query(node*2, st, (st+ed)/2, l, r);
    vector<pii> v2 = query(node*2+1, (st+ed)/2+1, ed, l, r);
    vector<pii> ans;
    for(auto &[o1, a1]:v1){
        for(auto &[o2, a2]:v2){
            if((o1|o2) <= (a1&a2)) ans.push_back({o1|o2, a1&a2});
        }
    }
    sort(all(ans));
    ans.erase(unique(all(ans)), ans.end());
    return ans;
}

int queryand(int node, int st, int ed, int l, int r){
    if(ed < l or r < st) return 0x7fffffff;
    if(l <= st and ed <= r) return andtree[node];
    return queryand(node*2, st, (st+ed)/2, l, r) & queryand(node*2+1, (st+ed)/2+1, ed, l, r);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    cin >> n >> q;
    for(int i=0; i<n; i++) cin >> v[i];
    set<int> zero;
    for(int i=0; i<n; i++){
        if(!v[i]) zero.insert(i);
    }
    zero.insert(-10); zero.insert(0x3f3f3f3f);
    init(1, 0, n-1);
    while(q--){
        int l, r; cin >> l >> r;
        l--; r--;
        if(l == r){
            cout << "NO\n"; continue;
        }

        int l1 = *zero.lower_bound(l);
        int l2 = *(--(zero.lower_bound(r+1)));
        if(l1 == l2){
            int u = (l <= l1-1 ? queryand(1, 0, n-1, l, l1-1) : 0x7fffffff) & (l1+1 <= r ? queryand(1, 0, n-1, l1+1, r) : 0x7fffffff);
            if(u == 0){
                cout << "YES\n"; continue;
            }
        }
        else if(l1 < l2){
            cout << "YES\n";
            continue;
        }

        vector<pii> ans = query(1, 0, n-1, l, r);
        int truth = 0;
        for(auto &[i,j]:ans){
            if(i and i==j){
                truth = 1; //break;
            }
        }
        if(truth) cout << "YES\n";
        else cout << "NO\n";
    }
    
    return 0;
}