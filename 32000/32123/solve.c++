#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define pii pair<int,int>
#define pll pair<ll,ll>
#define X first
#define Y second

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    vector<int> v(n*2+1);
    vector<ll> cnt(n+2), cntm(n+2);
    for(int i=0; i<2*n; i++){
        if(s[i] == '0') v[i+1] = v[i] + 1;
        else v[i+1] = v[i] - 1;
        if(v[i+1] >= 0) cnt[v[i+1]]++;
        else cntm[-v[i+1]]++;
    } 
    for(int i=n; i>=2; i--){
        cnt[i-2] += cnt[i];
        cntm[i-2] += cntm[i];
    }

    for(int i=n-1; i>=1; i--){
        cnt[i] = cnt[i] + cnt[i+1];
        cntm[i] = cntm[i] + cntm[i+1];
    }

    ll ans = 0x3f3f3f3f3f3f3fll;
    for(int i=n; i>=0; i--){
        int i1 = i, i2 = -(i-k);
        if(i2 < 0) continue;
        ans = min(ans, cnt[i1+1] + cntm[i2+1]);
    }
    cout << ans << "\n";
    return 0;
}