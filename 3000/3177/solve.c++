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

// CNT_LOWER: number of element in v smaller than n
// CNT_UPPER: number of element in v smaller or same than n

#define LINE array<pii, 2>
// LINE: l[0] + kl[1]

pii operator + (pii l, pii r){return {l.X+r.X, l.Y+r.Y};};
pii operator - (pii l, pii r){return {l.X-r.X, l.Y-r.Y};};
ll operator * (pii l, pii r){return (ll)l.X*r.X + (ll)l.Y*r.Y;};
ll operator / (pii l, pii r){return (ll)l.X*r.Y - (ll)l.Y*r.X;};
ll poww(ll a, ll e){
    ll ans = 1;
    while(e){
        if(e&1) ans = ans * a;
        a = a * a;
        e >>= 1;
    }
    return ans;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    char c; ll n; 
    cin >> c >> n;
    c = c - 'A' + 'a';
    string v = "ajdtapasoddjdtapasod";
    vector<pll> array[126];

    for(int i=1; i<20; i++){
        array[v[i]].push_back({i,i});
    }
    for(int d=2; d<=9; d++){
        array[v[d]].push_back({d*10, d*10+9});
    }

    array['s'].push_back({100, 199});
    for(int d=2; d<=9; d++){
        array[v[d]].push_back({d*100, d*100+99});
    }

    string u = "aastdsmdsmds";
    for(ll d=3; d<=12; d+=3){
        array[u[d]].push_back({poww(10, d), poww(10, d)*2 - 1}); // 1000 ~ 1999
        // 2000 ~ 9999
        for(int t=2; t<=9; t++){
            array[v[t]].push_back({poww(10, d)*t, poww(10, d)*(t+1) - 1});
        }

        // 10000 ~ 10999
        array[u[d+1]].push_back({poww(10, d)*10, poww(10, d)*11 - 1});

        // 11000 ~ 19999
        for(int t=11; t<=19; t++){
            array[v[t]].push_back({poww(10, d)*t, poww(10, d)*(t+1)-1});
        }
        // 20000 ~ 99999
        for(int t=2; t<=9; t++){
            array[v[t]].push_back({poww(10, d+1)*t, poww(10, d+1)*(t+1)-1});
        }
        // 100 000 ~ 199999
        array[u[d+2]].push_back({poww(10, d+2), poww(10, d+2) * 2 - 1});
        // 200000 ~ 999999
        for(int t=2; t<=9; t++){
            array[v[t]].push_back({poww(10, d+2)*t, poww(10, d+2)*(t+1) - 1});
        }
    }

    //for(auto [i, j]:array['p']) cout << i << "~" << j << " ";
    int id = 0;
    for(int i=0; ; i++){
        if(array[c][i].X + n - 1 <= array[c][i].Y){
            cout << array[c][i].X + n - 1 << "\n"; return 0;
        }
        else{
            n -= array[c][i].Y - array[c][i].X + 1;
        }
    }

    // 1000-1
    return 0;
}