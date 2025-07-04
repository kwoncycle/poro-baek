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

int DP[300005];
vector<pii> G[300005];
ll dst[300005];

namespace Aho
{
    const int MAXN = 300000 + 4; // sum of the lengths
    const int MAXC = 26;
    int term[MAXN], len[MAXN], to[MAXN][MAXC], link[MAXN], sz = 1;
    void add(string s){
        int x = 0;
        for (auto &c : s){
            c -= 'a';
            if (!to[x][c]){
                to[x][c] = sz++;
                len[to[x][c]] = len[x] + 1;
            }
            x = to[x][c];
        }
        term[x] = x;
    }
    void push_links(){
        queue<int> q;
        q.push(0);
        while (!q.empty()){
            int x = q.front();
            q.pop();
            int y = link[x];
            if (!term[x]) term[x] = term[y];
            for (int c = 0; c < MAXC; c++){
                if (to[x][c]){
                    link[to[x][c]] = x ? to[y][c] : 0;
                    q.push(to[x][c]);
                }
                else to[x][c] = to[y][c];
            }
        }
    }
    bool get(string s){
        int x = 0;
        for (int i=0; i<(int)s.size(); i++){
            char c = s[i];
            x = to[x][c - 'a'];
            if (term[x]) {
                assert(i - len[term[x]] + 1 >= 0);
                G[i - len[term[x]] + 1].push_back({1, i+1});
                //DP[i - len[x] + 1] = max(DP[i - len[x] + 1], len[x]);
            }
        }
        return 0;
    }
};


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n; cin >> n;
    string s; cin >> s;

    int sm = 0;
    vector<string> txt(n);
    for(auto &i:txt) {
        cin >> i; sm += i.size();
        Aho::add(i);
    }
    Aho::push_links();
    Aho::get(s);

    
    for(int i=0; i<s.size(); i++){
        if(i) G[i].push_back({0, i-1});
        if(DP[i]){
            G[i].push_back({1, DP[i]+i});
        }
    }

    memset(dst, 0x3f, sizeof(dst));
    priority_queue<pll, vector<pll>, greater<pll>> pq;

    dst[0] = 0;
    pq.push({0, 0});
    while(!pq.empty()){
        auto [d, p] = pq.top(); pq.pop();
        if(d > dst[p]) continue;
        for(auto &[nd, np]:G[p]){
            if(d + nd < dst[np]){
                dst[np] = d + nd;
                pq.push({dst[np], np});
            }
        }
    }
    if(dst[s.size()] > 0x3f3f3f) cout << "-1\n";
    else cout << dst[s.size()] << "\n";

    return 0;
}