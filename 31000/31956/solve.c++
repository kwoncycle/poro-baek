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

ll q, w;
set<pll> st;
vector<ll> vals, diff;
struct Segtree01{
    int n = 802020;
    int tree[4000000];
    ll len[4000000];
    void update(int node, int st, int ed, int l, int r, int v){
        if(ed < l or r < st) return;
        if(l <= st and ed <= r) tree[node] += v;
        else{
            update(node*2, st, (st+ed)/2, l, r, v);
            update(node*2 + 1, (st+ed)/2+1, ed, l, r, v);
        }
        if(tree[node] > 0) len[node] = vals[ed] - vals[st-1];
        else if(st == ed) len[node] = 0;
        else len[node] = len[node*2] + len[node*2 + 1];
    }
    void update(int l, int r, int v){
        update(1, 0, n-1, l + 1, r, v);
    }
    ll query(){
        return len[1];
    }
} S;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    cin >> q >> w;
    vector<pll> v(q);
    
    for(auto &[i,j]:v) {
        cin >> i >> j;
        vals.push_back(i-j); vals.push_back(i-j-1);
        vals.push_back(i+j); vals.push_back(i+j+1);
    }
    vals.push_back(-0x3f3f3f3fll*2); vals.push_back(-0x3f3f3f3fll*2 - 1); 
    vals.push_back(0); vals.push_back(1);
    vals.push_back(w); vals.push_back(w - 1); 
    vals.push_back(0x3f3f3f3fll*2 + w); vals.push_back(0x3f3f3f3fll*2 + w + 1);
    

    sort(all(vals)); 
    vals.erase(unique(all(vals)), vals.end());
    for(int i=0; i<(int)vals.size()-1; i++){
        diff.push_back(vals[i+1]-vals[i]);
    }


    S.update(CNT_LOWER(vals, -0x3f3f3f3fll*2), CNT_LOWER(vals, 0), 1);
    S.update(CNT_LOWER(vals, w), CNT_LOWER(vals, 0x3f3f3f3fll*2 + w), 1);

    for(auto &[l, r]:v){
        if(st.find({l,r}) == st.end()){
            st.insert({l, r});
            S.update(CNT_LOWER(vals, l-r), CNT_LOWER(vals, l+r), 1);
            ll U = S.query() - 0x3f3f3f3fll*4;
            cout << fixed << setprecision(12) << (double)U * sqrt(2) << "\n";
        }
        else{
            st.erase({l, r});
            S.update(CNT_LOWER(vals, l-r), CNT_LOWER(vals, l+r), -1);
            ll U = S.query() - 0x3f3f3f3fll*4;
            cout << fixed << setprecision(12) << (double)U * sqrt(2) << "\n";
        }
    }

    return 0;
}