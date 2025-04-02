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

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n; cin >> n;
    vector<int> v(n);
    for(int i=0; i<n; i++) cin >> v[i];
    string s; cin >> s;

    int id = 0;
    int ans = 0;
    for(int i=0; i<n-1; i++){
        int i1 = i;
        while(i1 < n-1 and s[i] == s[i1]) i1++;
        int sz = i1 - i;
        if(s[i] == 'U'){
            vector<int> T;
            for(int j=id; j<n; j++){
                if(T.empty()) T.push_back(v[j]);
                else if(T[0] > v[j]) T[0] = v[j];
                else if(T.back() < v[j]) T.push_back(v[j]);
                else{
                    int o = CNT_LOWER(T, v[j]);
                    T[o] = v[j];
                }
                if(T.size() >= sz+1){
                    id = j;
                    break;
                }
            }
            if(T.size() == sz+1) ans += sz;
            else {
                ans += max(0, (int)T.size()-1); break;
            }
        }
        else{
            vector<int> T;
            for(int j=id; j<n; j++){
                if(T.empty()) T.push_back(v[j]);
                else if(T[0] < v[j]) T[0] = v[j];
                else if(T.back() > v[j]) T.push_back(v[j]);
                else{
                    int o = lower_bound(all(T), v[j], [&](int l, int r){
                        return l > r;
                    }) - T.begin();
                    T[o] = v[j];
                }
                if(T.size() >= sz+1){
                    id = j;
                    break;
                }
            }
            if(T.size() == sz+1) ans += sz;
            else {
                ans += max(0, (int)T.size()-1); break;
            }
        }
        i = i1-1;
    }

    cout << ans << "\n";

    return 0;
}