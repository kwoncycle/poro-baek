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

void mul(vector<ll> &v1, ll n, ll modx){ // v1 = v1 * (1 + x^n) % (x^modx-1)
    n %= modx;
    vector<ll> t1 = v1;
    rotate(t1.begin(), t1.begin() + n, t1.end());
    for(int i=0; i<modx; i++) v1[i] = (v1[i] + t1[i]) % 3;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int tt; cin >> tt;
    for(int tc=1; tc<=tt; tc++){
        string s; cin >> s;
        ll t; cin >> t;
        int n = s.size();
        vector<int> v(n);
        for(int i=0; i<n; i++){
            if(s[i] == 'R') v[i] = 1;
            else if(s[i] == 'G') v[i] = 2;
            else v[i] = 0;
        }

        ll o = 1;
        while(o*3 <= 1000000000000000000ll){
            o *= 3;
        }
        while(o){
            if(t >= o){
                t -= o;
                vector<int> v1(n);
                for(int i=0; i<n; i++) v1[i] = v[(i+o)%n];
                for(int i=0; i<n; i++) v[i] = (v[i] + v1[i]) % 3;
            }
            if(t >= o){
                t -= o;
                vector<int> v1(n);
                for(int i=0; i<n; i++) v1[i] = v[(i+o)%n];
                for(int i=0; i<n; i++) v[i] = (v[i] + v1[i]) % 3;
            }
            o /= 3;
        }
        vector<int> ans(3, 0);
        for(auto i:v) ans[i]++;
        cout << "Case #" << tc << ": ";
        for(auto i:ans) cout << i << " "; cout << "\n";
    }
    return 0;
}