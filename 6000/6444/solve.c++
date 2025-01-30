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

ll MX = 1ll<<40;

int s2i(string s){
    int i = 0;
    for(auto c:s){
        i *= 10;
        i += c - '0';
    }
    return i;
}

void parse(string &s, vector<pii> &v){
    int i1 = 1, i2 = 1, i3 = 1;
    int n = s.size();
    for(; i1<n; ){
        i2 = i1;
        i3 = i1;
        while(i2+1 < n and s[i2+1] != '+') i2++;
        while(i3+1 < n and 'A' <= s[i3+1] and s[i3+1] <= 'Z') i3++;
        int o = 0, u = 0;
        int t[3] = {0, 26, 26+26*26};
        for(int j=i1; j<=i3; j++){
            o *= 26;
            o += s[j] - 'A';
        }
        o += t[i3-i1];
        u = s2i(s.substr(i3+1, i2-i3));
        u--;
        v.push_back({u, o});
        i1 = i2 + 2;
    }
}

struct solve{
    int n, m;
    vector<vector<string>> v;
    vector<vector<ll>> ans;
    vector<vector<vector<pii>>> express;
    solve(){
        cin >> m >> n;
        v = vector<vector<string>>(n, vector<string>(m));
        ans = vector<vector<ll>>(n, vector<ll>(m, MX));
        express = vector<vector<vector<pii>>>(n, vector<vector<pii>>(m));
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                cin >> v[i][j];
                if(v[i][j][0] != '='){
                    ans[i][j] = s2i(v[i][j]);
                }
                else{
                    parse(v[i][j], express[i][j]);
                }
            }
        }
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                ans[i][j] = getV(i, j);
            }
        }

        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++) cout << ans[i][j] << " ";
            cout << "\n";
        }
    }

    ll getV(int i, int j){
        if(ans[i][j] != MX) return ans[i][j];
        ll sm = 0;
        for(auto [x,y]:express[i][j]){
            sm += getV(x, y);
        }
        ans[i][j] = sm;
        return ans[i][j];
    }
};


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int tt; cin >> tt;
    while(tt--){
        solve s;
    }
    return 0;
}