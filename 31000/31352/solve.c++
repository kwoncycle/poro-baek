#include <bits/stdc++.h>
using namespace std;
 
#define ll __int128
#define pii pair<int,int>
#define pll pair<ll,ll>
#define X first
#define Y second
#define CNT_LOWER(v,n) (int)(lower_bound((v).begin(),(v).end(),(n))-(v).begin())
#define CNT_UPPER(v,n) (int)(upper_bound((v).begin(),(v).end(),(n))-(v).begin())
 
// CNT_LOWER: number of element in v smaller than n
// CNT_UPPER: number of element in v smaller or same than n

pll operator + (pll l, pll r){
    ll o1 = l.X*r.Y + r.X*l.Y, o2 = l.Y*r.Y;
    return pll(o1/__gcd(o1,o2), o2/__gcd(o1,o2));
}
pll operator - (pll l, pll r){
    ll o1 = l.X*r.Y - r.X*l.Y, o2 = l.Y*r.Y;
    return pll(o1/__gcd(o1,o2), o2/__gcd(o1,o2));
}
pll operator * (pll l, pll r){
    ll o1 = l.X*r.X, o2 = l.Y*r.Y;
    return pll(o1/__gcd(o1,o2), o2/__gcd(o1,o2));
}
pll operator / (pll l, pll r){
    ll o1 = l.X*r.Y, o2 = l.Y*r.X;
    return pll(o1/__gcd(o1,o2), o2/__gcd(o1,o2));
}

int n, m;
vector<vector<int>> edges(10, vector<int>(10, 0));
vector<int> sv(10);
vector<int> state2idx(1<<24), idx2state(5000);
int stid = 0;
void under_state(vector<int> &v){
    vector<int> mp(n+1, 0);
    int id = 0;
    for(int i=0; i<n; i++){
        if(mp[v[i]] == 0){
            mp[v[i]] = ++id;
        }
        v[i] = mp[v[i]];
    }
}

void search(int x){
    if(x == n){
        vector<int> tmp(n);
        for(int i=0; i<n; i++) tmp[i] = sv[i];
        under_state(tmp);
        int a = 0;
        for(int i=0; i<n; i++){
            a *= n;
            a += tmp[i]-1;
        }

        if(state2idx[a] == 0) {
            state2idx[a] = ++stid;
            idx2state[stid] = a;
        }
        return;
    }

    int mx = 0;
    for(int i=0; i<x; i++) mx = max(sv[i], mx);
    for(int i=1; i<=mx+1; i++){
        sv[x] = i;
        search(x+1);
        sv[x] = 0;
    }
}

vector<vector<pll>> DP(5000, vector<pll>(100, {0, 1})), prob(5000, vector<pll>(100, {0, 1}));
vector<pii> edges1;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    cin >> n >> m;
    for(int i=0; i<m; i++){
        int a, b; cin >> a >> b;
        a--; b--;
        edges[a][b] = 1;
        edges[b][a] = 1;
        edges1.push_back({a,b});
    }
    search(0);

    vector<int> initial_state(n);
    for(int i=0; i<n; i++) initial_state[i] = i+1;
    ll initid = 0;
    for(auto &si:initial_state){
        initid *= n;
        initid += si-1;
    }
    prob[state2idx[initid]][0] = {1,1};

    for(int i=0; i<m; i++){
        for(int j=1; j<=stid; j++){
            if(prob[j][i].X == 0) continue;
            int stateid = idx2state[j];
            vector<int> state(n);
            for(int ji=n-1; ji>=0; ji--) state[ji] = stateid % n, stateid /= n;
            int cnt = 0;
            for(auto &[a,b]:edges1){
                if(state[a] == state[b]) {
                    cnt++;
                }
            }
            for(auto &[a,b]:edges1){
                if(state[a] == state[b]) {
                    DP[j][i+1] = DP[j][i+1] + ((prob[j][i] * pll(1, m-i) * pll(cnt-i, cnt)) * (DP[j][i]/prob[j][i]));
                    prob[j][i+1] = prob[j][i+1] + prob[j][i] * pll(1, m-i) * pll(cnt-i, cnt);
                }
                else{
                    vector<int> newstate(n);
                    for(int si=0; si<n; si++) newstate[si] = state[si];
                    int o = newstate[b];
                    for(auto &si:newstate) if(si == o) si = newstate[a];
                    under_state(newstate);
                    stateid = 0;
                    for(auto &si:newstate){
                        stateid *= n;
                        stateid += si-1;
                    }
                    DP[state2idx[stateid]][i+1] = DP[state2idx[stateid]][i+1] + ((prob[j][i] * pll(1, m-i)) * ((pll(i+1, m+1)) + DP[j][i]/prob[j][i]));
                    prob[state2idx[stateid]][i+1] = prob[state2idx[stateid]][i+1] + prob[j][i] * pll(1, m-i);
                }
            }
        }
    }

    vector<int> state(n, 1);
    int stateid = 0;
    for(auto &si:state){
        stateid *= n;
        stateid += si-1;
    }

    cout << (long long)DP[state2idx[stateid]][m].X << "/" << (long long)DP[state2idx[stateid]][m].Y << "\n";

    return 0;
}