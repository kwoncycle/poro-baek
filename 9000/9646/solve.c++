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

    vector<vector<int>> v(8);
    for(int i=0; i<(1<<7); i++){
        int j = i;
        int cnt = 0;
        while(j){
            cnt += j&1; j >>= 1;
        }
        v[cnt].push_back(i);
    }
    int n;
    while(cin >> n){
        vector<int> l1(n);
        for(int i=0; i<n; i++) cin >> l1[i];
        vector<int> l(l1[0]);
        for(int i:l1){
            for(int j=0; j<i; j++) l[j]++;
        }
        n = l.size();
        int t; cin >> t;
        vector<vector<ll>> DP(n, vector<ll>(64));
        for(int i=n-1; i>=0; i--){
            for(int j=0; j<(int)v[l[i]].size(); j++){
                vector<int> v1;
                int i1 = v[l[i]][j];
                for(int it=0; it<t; it++){
                    if(i1&1) {v1.push_back(it);}
                    i1 >>= 1;
                }
                if(v1.size() != l[i]) continue;
                if(i==n-1) DP[i][j] = 1;
                else{
                    for(int k=0; k<(int)v[l[i+1]].size(); k++){
                        int i2 = v[l[i+1]][k];
                        vector<int> v2;
                        
                        for(int it=0; it<t; it++){
                            if(i2&1) v2.push_back(it);
                            i2 >>= 1;
                        }

                        if(v2.size() != l[i+1]) continue;
                        
                        int truth = 1;
                        for(int j1=0; j1<(int)v2.size(); j1++){
                            if(v1[j1] > v2[j1]) truth = 0;
                        }
                        if(truth){
                            DP[i][j] += DP[i+1][k];
                        }
                    }
                }
            }
        }
        ll ans = 0;
        for(int i=0; i<64; i++) ans += DP[0][i];
        cout << ans << "\n";
    }
    return 0;
}