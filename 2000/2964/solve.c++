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

struct S{
    int n;
    vector<pii> v;
    string s;
    vector<int> order;
    int left_id1, left_id2;
    vector<pii> LL;
    int li, ri, di, ui;

    S(){
        cin >> n;
        v.resize(n); LL.resize(n);
        for(int i=0; i<n; i++) cin >> v[i].X >> v[i].Y;
        cin >> s;
        del_order();
        solve();
    }

    void del_order(){
        vector<int> idx_x(n), idx_y(n), check(n, 0);
        for(int i=0; i<n; i++) idx_x[i] = i, idx_y[i] = i;
        sort(idx_x.begin(), idx_x.end(), [&](int l, int r){
            return v[l].X < v[r].X;
        });
        sort(idx_y.begin(), idx_y.end(), [&](int l, int r){
            return v[l].Y < v[r].Y;
        });
        int il = 0, ir = n-1, id = 0, iu = n-1;
        for(char c:s){
            if(c == 'L'){
                while(check[idx_x[il]]) il++;
                order.push_back(idx_x[il]);
                check[idx_x[il]] = 1;
            }
            else if(c == 'R'){
                while(check[idx_x[ir]]) ir--;
                order.push_back(idx_x[ir]);
                check[idx_x[ir]] = 1;
            }
            else if(c == 'D'){
                while(check[idx_y[id]]) id++;
                order.push_back(idx_y[id]);
                check[idx_y[id]] = 1;
            }
            else if(c == 'U'){
                while(check[idx_y[iu]]) iu--;
                order.push_back(idx_y[iu]);
                check[idx_y[iu]] = 1;
            }
        }
        left_id1 = 0, left_id2 = n-1;
        while(check[left_id1]) left_id1++;
        while(check[left_id2]) left_id2--;
        LL[left_id1].X = left_id2; LL[left_id1].Y = left_id2; LL[left_id2].X = left_id1; LL[left_id2].Y = left_id1;

        li = v[left_id1].X < v[left_id2].X ? left_id1 : left_id2;
        ri = v[left_id1].X > v[left_id2].X ? left_id1 : left_id2;
        di = v[left_id1].Y < v[left_id2].Y ? left_id1 : left_id2;
        ui = v[left_id1].Y > v[left_id2].Y ? left_id1 : left_id2;
    }

    ll add(int id, char c){
        int i0;
        if(c == 'L') i0 = li;
        if(c == 'R') i0 = ri;
        if(c == 'D') i0 = di;
        if(c == 'U') i0 = ui;
        int i1 = i0;
        ll A = 0;
        while(true){
            int r = LL[i1].Y;
            if((v[i1]-v[r])/(v[id]-v[i1]) <= 0){
                A += abs((v[i1]-v[r])/(v[id]-v[r]));
                i1 = r;
            }
            else break;
        }

        int i2 = i0;
        while(true){
            int l = LL[i2].X;
            if((v[i2]-v[l])/(v[id]-v[i2]) >= 0){
                A += abs((v[i2]-v[l])/(v[id]-v[l]));
                i2 = l;
            }
            else break;
        }
        LL[i1].X = id;
        LL[i2].Y = id;
        LL[id].X = i2;
        LL[id].Y = i1;

        li = v[id].X < v[li].X ? id : li;
        ri = v[id].X > v[ri].X ? id : ri;
        di = v[id].Y < v[di].Y ? id : di;
        ui = v[id].Y > v[ui].Y ? id : ui;
        return A;
    }

    void solve(){
        vector<ll> ans(n-1);
        for(int i=n-3; i>=0; i--){
            ans[i] = ans[i+1] + add(order[i], s[i]);
        }
        for(int i=0; i<n-2; i++){
            cout << ans[i]/2 << "." << (ans[i]%2*5) << '\n';
        }
    }

};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    S s;
    return 0;
}