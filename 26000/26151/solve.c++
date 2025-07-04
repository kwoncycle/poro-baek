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

__int128 DP[26][60];
string nato[26] = {
    "ALFA",
    "BRAVO",
    "CHARLIE",
    "DELTA",
    "ECHO",
    "FOXTROT",
    "GOLF",
    "HOTEL",
    "INDIA",
    "JULIETT",
    "KILO",
    "LIMA",
    "MIKE",
    "NOVEMBER",
    "OSCAR",
    "PAPA",
    "QUEBEC",
    "ROMEO",
    "SIERRA",
    "TANGO",
    "UNIFORM",
    "VICTOR",
    "WHISKEY",
    "XRAY",
    "YANKEE",
    "ZULU"
};

const ll MX = 1100'000'000'000'000'000ll;
vector<ll> presm[40];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    for(int i=0; i<26; i++){
        DP[i][0] = 1;
    }
    for(int j=1; j<40; j++){
        for(int i=0; i<26; i++){
            for(char c:nato[i]){
                DP[i][j] += DP[c-'A'][j-1];
            }
            if(DP[i][j] >= (__int128)MX) DP[i][j] = MX;
        }
    }
    string s;
    int qq;
    cin >> s >> qq;
    for(int i=0; i<40; i++){
        presm[i].resize(s.size()+1);
        for(int j=0; j<(int)s.size(); j++){
            presm[i][j+1] = presm[i][j] + DP[s[j]-'A'][i];
            if(presm[i][j+1] > MX) presm[i][j+1] = MX;
        }
    }
    ll sm = 0;
    while(qq--){
        ll q, x; cin >> q >> x;
        if(q == 1) sm += x;
        else{
            if(sm >= 32) sm = 32 - 1;
            ll cur = sm;
            ll id = 0;
            if(cur == 0){
                cout << s[x-1]; continue;
            }
            id = CNT_LOWER(presm[cur], x);
            id--;
            x -= presm[cur][id];
            int target = s[id]-'A';
            id = 0;
            while(cur){
                if(x > DP[nato[target][id]-'A'][cur-1]){
                    x -= DP[nato[target][id]-'A'][cur-1]; id++;
                }
                else{
                    cur--;
                    target = nato[target][id]-'A';
                    id = 0;
                }
            }
            
            cout << nato[target][id];
        }
    }
    return 0;
}