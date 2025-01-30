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

vector<vector<vector<vector<ll>>>> arr, segtree;

struct SegTree1{
    SegTree1(){
    }

    void update(array<int, 4> loc, array<int, 4> start, array<int, 4> end, ll val){ // + val
        vector<vector<int>> v_index(4);
        for(int i=0; i<4; i++){
            int s = start[i], e = end[i], nd = 1;
            while(s <= loc[i] and loc[i] <= e){
                v_index[i].push_back(nd);
                int mid = (s+e)/2;
                if(s == e) break;
                if(loc[i] <= mid){
                    e = mid;
                    nd *= 2;
                }
                else{
                    s = mid+1;
                    nd = nd*2 + 1;
                }
            }
        }

        for(int i0:v_index[0])for(int i1:v_index[1])for(int i2:v_index[2])for(int i3:v_index[3]) segtree[i0-1][i1-1][i2-1][i3-1] += val;
        return;
    }

    ll query(array<int, 4> start, array<int, 4> end, array<int, 4> l1, array<int, 4> l2){
        vector<vector<int>> v_index(4);
        for(int i=0; i<4; i++){
            find_index(start[i], end[i], l1[i], l2[i], 1, v_index[i]);
        }

        ll sm = 0;
        for(int i0:v_index[0])for(int i1:v_index[1])for(int i2:v_index[2])for(int i3:v_index[3]) sm += segtree[i0-1][i1-1][i2-1][i3-1];
        return sm;
    }

    void find_index(int s, int e, int i1, int i2, int nd, vector<int> &v){
        if(e<i1 or i2 < s) return;
        if(i1 <= s and e <= i2){
            v.push_back(nd); return;
        }
        int md = (s+e)/2;
        find_index(s, md, i1, i2, nd*2, v);
        find_index(md+1, e, i1, i2, nd*2+1, v);
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    ll n, k, q; cin >> n >> k >> q;
    if(k == 1){
        arr = vector<vector<vector<vector<ll>>>>(1, vector<vector<vector<ll>>>(1, vector<vector<ll>>(1, vector<ll>(500005, 0))));
        segtree = vector<vector<vector<vector<ll>>>>(1, vector<vector<vector<ll>>>(1, vector<vector<ll>>(1, vector<ll>(2000005, 0))));
        SegTree1 sgtree;
        array<int, 4> end = {0,0,0,499999};
        for(int i1=0; i1<1; i1++){
        for(int i2=0; i2<1; i2++){
        for(int i3=0; i3<1; i3++){
        for(int i4=0; i4<n; i4++){
            cin >> arr[i1][i2][i3][i4];
            sgtree.update({i1,i2,i3,i4}, {0,0,0,0}, end, arr[i1][i2][i3][i4]);
        }    
        }    
        }    
        }
        while(q--){
            ll q1; cin >> q1;
            if(q1 == 1){
                array<int, 4> i1, i2;
                for(int i=4-k; i<4; i++) {
                    cin >> i1[i] >> i2[i];
                    i1[i]--; i2[i]--;
                }
                for(int i=0; i<4-k; i++){
                    i1[i]=0; i2[i]=0;
                }
                ll o = 0;
                o = sgtree.query({0,0,0,0}, end, i1, i2);
                cout << o << "\n";
            }
            else{
                array<int, 4> b;
                for(int i=4-k; i<4; i++) {
                    cin >> b[i];
                    b[i]--;
                }
                for(int i=0; i<4-k; i++){
                    b[i] = 0;
                }
                ll x; cin >> x;
                sgtree.update(b, {0,0,0,0}, end, x - arr[b[0]][b[1]][b[2]][b[3]]);
                arr[b[0]][b[1]][b[2]][b[3]] = x;
            }
        }
    }
    if(k == 2){
        arr = vector<vector<vector<vector<ll>>>>(1, vector<vector<vector<ll>>>(1, vector<vector<ll>>(800, vector<ll>(800, 0))));
        segtree = vector<vector<vector<vector<ll>>>>(1, vector<vector<vector<ll>>>(1, vector<vector<ll>>(3200, vector<ll>(3200, 0))));
        SegTree1 sgtree;
        array<int, 4> end = {0,0,799,799};
        for(int i1=0; i1<1; i1++){
        for(int i2=0; i2<1; i2++){
        for(int i3=0; i3<n; i3++){
        for(int i4=0; i4<n; i4++){
            cin >> arr[i1][i2][i3][i4];
            sgtree.update({i1,i2,i3,i4}, {0,0,0,0}, end, arr[i1][i2][i3][i4]);
        }    
        }    
        }    
        }
        while(q--){
            ll q1; cin >> q1;
            if(q1 == 1){
                array<int, 4> i1, i2;
                for(int i=4-k; i<4; i++) {
                    cin >> i1[i] >> i2[i];
                    i1[i]--; i2[i]--;
                }
                for(int i=0; i<4-k; i++){
                    i1[i]=0; i2[i]=0;
                }
                ll o = 0;
                o = sgtree.query({0,0,0,0}, end, i1, i2);
                cout << o << "\n";
            }
            else{
                array<int, 4> b;
                for(int i=4-k; i<4; i++) {
                    cin >> b[i];
                    b[i]--;
                }
                for(int i=0; i<4-k; i++){
                    b[i] = 0;
                }
                ll x; cin >> x;
                sgtree.update(b, {0,0,0,0}, end, x - arr[b[0]][b[1]][b[2]][b[3]]);
                arr[b[0]][b[1]][b[2]][b[3]] = x;
            }
        }
    }
    if(k == 3){
        arr = vector<vector<vector<vector<ll>>>>(1, vector<vector<vector<ll>>>(128, vector<vector<ll>>(128, vector<ll>(128, 0))));
        segtree = vector<vector<vector<vector<ll>>>>(1, vector<vector<vector<ll>>>(256, vector<vector<ll>>(256, vector<ll>(256, 0))));
        SegTree1 sgtree;
        array<int, 4> end = {0,79,79,79};
        for(int i1=0; i1<1; i1++){
        for(int i2=0; i2<n; i2++){
        for(int i3=0; i3<n; i3++){
        for(int i4=0; i4<n; i4++){
            cin >> arr[i1][i2][i3][i4];
            sgtree.update({i1,i2,i3,i4}, {0,0,0,0}, end, arr[i1][i2][i3][i4]);
        }    
        }    
        }    
        }
        while(q--){
            ll q1; cin >> q1;
            if(q1 == 1){
                array<int, 4> i1, i2;
                for(int i=4-k; i<4; i++) {
                    cin >> i1[i] >> i2[i];
                    i1[i]--; i2[i]--;
                }
                for(int i=0; i<4-k; i++){
                    i1[i]=0; i2[i]=0;
                }
                ll o = 0;
                o = sgtree.query({0,0,0,0}, end, i1, i2);
                cout << o << "\n";
            }
            else{
                array<int, 4> b;
                for(int i=4-k; i<4; i++) {
                    cin >> b[i];
                    b[i]--;
                }
                for(int i=0; i<4-k; i++){
                    b[i] = 0;
                }
                ll x; cin >> x;
                sgtree.update(b, {0,0,0,0}, end, x - arr[b[0]][b[1]][b[2]][b[3]]);
                arr[b[0]][b[1]][b[2]][b[3]] = x;
            }
        }
    }
    if(k == 4){
        arr = vector<vector<vector<vector<ll>>>>(32, vector<vector<vector<ll>>>(32, vector<vector<ll>>(32, vector<ll>(32, 0))));
        segtree = vector<vector<vector<vector<ll>>>>(64, vector<vector<vector<ll>>>(64, vector<vector<ll>>(64, vector<ll>(64, 0))));
        SegTree1 sgtree;
        array<int, 4> end = {26,26,26,26};
        for(int i1=0; i1<n; i1++){
        for(int i2=0; i2<n; i2++){
        for(int i3=0; i3<n; i3++){
        for(int i4=0; i4<n; i4++){
            cin >> arr[i1][i2][i3][i4];
            sgtree.update({i1,i2,i3,i4}, {0,0,0,0}, end, arr[i1][i2][i3][i4]);
        }    
        }    
        }    
        }
        while(q--){
            ll q1; cin >> q1;
            if(q1 == 1){
                array<int, 4> i1, i2;
                for(int i=4-k; i<4; i++) {
                    cin >> i1[i] >> i2[i];
                    i1[i]--; i2[i]--;
                }
                for(int i=0; i<4-k; i++){
                    i1[i]=0; i2[i]=0;
                }
                ll o = 0;
                o = sgtree.query({0,0,0,0}, end, i1, i2);
                cout << o << "\n";
            }
            else{
                array<int, 4> b;
                for(int i=4-k; i<4; i++) {
                    cin >> b[i];
                    b[i]--;
                }
                for(int i=0; i<4-k; i++){
                    b[i] = 0;
                }
                ll x; cin >> x;
                sgtree.update(b, {0,0,0,0}, end, x - arr[b[0]][b[1]][b[2]][b[3]]);
                arr[b[0]][b[1]][b[2]][b[3]] = x;
            }
        }
    }
    return 0;
}