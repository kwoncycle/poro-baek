#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

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
    vector<string> v(n);
    for(auto &s:v){
        cin >> s;
    }

    string T; cin >> T;
    string ans;
    while(!v.empty() and !T.empty()){
        char c = T.back();
        for(int i=v.size()-1; i>=0; i--){
            while(!v[i].empty() and v[i].back() != c){
                ans.push_back(v[i].back());
                v[i].pop_back();
            }
            if(v[i].empty()){
                v[i].swap(v[v.size()-1]);
                v.pop_back();
            }
            else{
                v[i].pop_back();
            }
        }
        if(v.empty()) break;
        ans.push_back(c);
        T.pop_back();
    }
    if(!v.empty()){
        cout << "NO\n";
    }
    else{
        cout << "YES\n";
        reverse(all(ans));
        cout << ans << "\n";
    }
    return 0;
}