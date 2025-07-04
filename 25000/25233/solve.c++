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

__int128 n, c;
vector<array<ll,2>> task;
vector<array<ll,3>> order0, order1;

int chk[200005];

bool isable(__int128 md){
    memset(chk, 0, sizeof(chk));
    __int128 ttl = 0;
    __int128 left = md * c;
    for(auto &[val, sz, i]:order0){
        if(sz > min(left, md)){
            ttl += (__int128)val * (sz - min(left, md) - 1);
            ttl++;
            left -= min(left, md);
        }
        else{
            if(sz < md) chk[i/2] = 1;
            else chk[i/2] = 2;
            left -= sz;
        }
    }
    for(auto &[val, sz, i]:order1){
        if(chk[i/2] == 1 and left){
            left--;
        }
        else if(chk[i/2]){
            ttl++;
        }
        else{
            ttl += val;
        }
    }
    return ttl <= c;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    ll n1, c1;
    cin >> n1 >> c1;
    n = n1; c = c1;
    task.resize(n);
    int id = 0;
    for(auto &[t,d]:task) {
        cin >> t >> d;
        if(t%d == 0){
            order0.push_back({d, t/d - 1, 2*id});
            order1.push_back({d, 1, 2*id + 1});
        }
        else{
            order0.push_back({d, t/d, 2*id});
            order1.push_back({t%d, 1, 2*id+1});
        }
        id++;
    }
    sort(all(order0)); reverse(all(order0));
    sort(all(order1)); reverse(all(order1));
    
    if(n <= c){
        ll st = -1, ed = 0x3f3f3f3f;
        while(st + 1 < ed){
            ll md = (st + ed) / 2;
            ll sm = 0;
            for(auto &[i,j]:task){
                if(i - j*md > 0) sm += max(0ll, i - j*md - j) + 1;
            }
            if(sm <= c) ed = md;
            else st = md;
        }
        cout << ed << "\n";
        return 0;
    }

    ll st = -1, ed = 0x3f3f3f3f3f3f3f3fll; // ed able
    while(st + 1 < ed){
        ll md = (st + ed) / 2;
        if(isable(md)) ed = md;
        else st = md;
    }
    cout << ed << "\n";

    return 0;
}