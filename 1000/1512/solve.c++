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

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int m; cin >> m;
    string s; cin >> s;
    int n = s.size();
    int mn = n;
    for(int i=1; i<=m; i++){
        vector<vector<int>> v(i, vector<int>(26, 0));
        for(int j=0; j<n; j++){
            v[j%i][s[j]-'A']++;
        }
        int ans = 0;
        for(int j=0; j<i; j++){
            int sm = 0;
            int mx = 0;
            for(int k=0; k<26; k++){
                mx = max(mx, v[j][k]);
                sm += v[j][k];
            }
            ans += sm - mx;
        }
        mn = min(mn, ans);
    }
    cout << mn << "\n";
    return 0;
}