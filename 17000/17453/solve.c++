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

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n, m; cin >> n >> m;
    string s1; cin >> s1;
    bitset<100> s, start;
    for(int i=0; i<n; i++){
        if(s1[i] == '1') s[i] = 1;
    }
    bitset<100> v[m];
    for(int i=0; i<m; i++){
        cin >> s1;
        for(int j=0; j<n; j++){
            if(s1[j] == '1') v[i][j] = 1;
        }
    }
    vector<int> arr(300, -1); // arr[i] = i-n th
    for(int i=0; i<(1<<m); i++){
        int i1 = i;
        start = s;
        for(int j=0; j<m; j++, i1 >>= 1){
            if(i1&1) start ^= v[j];
        }
        int cnt1 = start.count();
        int cnt0 = n - cnt1;
        arr[cnt1 - cnt0 + n] = i;
    }
    for(int i=-n; i<=n; i++){
        if(arr[i + n] == -1) cout << "-1\n";
        else{
            int i1 = arr[i + n];
            vector<int> ans;
            for(int j=1; j<=m; j++, i1 >>= 1){
                if(i1&1) ans.push_back(j);
            }
            cout << ans.size() << " ";
            for(int j:ans) cout << j << " ";
            cout << "\n";
        }
    }
    return 0;
}