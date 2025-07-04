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
    for(auto &i:v) cin >> i;

    vector<vector<int>> G(26);

    int truth = 1;

    for(int i=0; i<n-1; i++){
        for(int j=0; j<min((int)v[i].size(), (int)v[i+1].size()); j++){
            if(v[i][j] == v[i+1][j]) {
                if(j == min((int)v[i].size(), (int)v[i+1].size()) - 1){
                    if(v[i].size() > v[i+1].size()) truth = 0;
                }
                continue;
            }
            else{
                G[v[i][j]-'a'].push_back(v[i+1][j]-'a');
                break;
            }
        }
    }

    vector<int> deg(26);
    for(int i=0; i<26; i++){
        sort(all(G[i]));
        G[i].erase(unique(all(G[i])), G[i].end());
        for(int j:G[i]) deg[j]++;
    }

    queue<int> Q;
    for(int i=0; i<26; i++){
        if(!deg[i]) Q.push(i);
    }

    string ans;
    while(!Q.empty()){
        int o = Q.front(); Q.pop();
        ans.push_back(o + 'a');
        for(int j:G[o]){
            deg[j]--;
            if(!deg[j]) Q.push(j);
        }
    }

    if(ans.size() == 26 and truth) cout << ans << "\n";
    else cout << "impossible\n";


    return 0;
}