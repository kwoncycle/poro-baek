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

#define MOD 998244353
#define A 1557881
#define Ai 893614843

ll Apow[500005], Aipow[500005];

ll hashsm[500005];

string s;
int n;
int arr[500005];

ll gethash(int i, int j){
    ll o = (hashsm[j] - (i-1>=0 ? hashsm[i-1] : 0)) * Aipow[i] % MOD;
    if(o < 0) o += MOD;
    return o;
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    Apow[0] = 1;
    Aipow[0] = 1;
    for(int i=1; i<=500003; i++){
        Apow[i] = Apow[i-1] * A % MOD;
        Aipow[i] = Aipow[i-1] * Ai % MOD;
    }


    cin >> s;
    cin >> n;
    for(int i=0; i<n; i++) cin >> arr[i];

    for(int i=0; i<s.size(); i++){
        hashsm[i] = ((i-1>=0 ? hashsm[i-1] : 0) + Apow[i] * s[i]) % MOD;
    }
    map<ll, ll> mp;
    map<ll, ll> idx;
    for(int i=0; i<n; i++){
        if(mp.find(arr[i]) == mp.end()) mp[arr[i]] = 0;
        mp[arr[i]] = (mp[arr[i]] + Apow[i]) % MOD;
        idx[arr[i]] = i;
    }

    if(mp.size() > 26){
        cout << "0\n"; return 0;
    }

    ll ans = 0;
    for(int i=0; i+n-1<(int)s.size(); i++){
        ll cnt1 = 0;
        set<char> s1;
        for(auto &[o1, _]:mp){
            cnt1 = (cnt1 + (s[i + idx[o1]] * mp[o1] % MOD)) % MOD;
            s1.insert(s[i + idx[o1]]);
        }
        if(cnt1 == gethash(i, i+n-1) and s1.size() == mp.size()) {
            ans++;
        }
    }
    cout << ans << "\n";
    return 0;
}