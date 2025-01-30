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

#define SZ 200005

int n;
vector<pii> v(SZ);
vector<int> deg(SZ);
vector<ll> money(SZ);
queue<int> q;

ll ans = 0;

void kill_cycle(vector<int> &cycle){
    for(int cur:cycle){
        int next = v[cur].X;
        ll o = max(0ll, v[next].Y - (money[next] + v[cur].Y));
        ans += o;
        money[next] += o;
    }
    ll trigger = 0x3f3f3f3f3f3fll;
    for(int cur:cycle){
        ll need = max(0ll, v[cur].Y - money[cur]);
        trigger = min(trigger, need);
    }
    ans += trigger;
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    
    cin >> n;
    for(int i=1; i<=n; i++){
        cin >> v[i].X >> v[i].Y;
    }

    for(int i=1; i<=n; i++){
        deg[v[i].X]++;
    }

    for(int i=1; i<=n; i++){
        if(!deg[i]) {
            q.push(i);
        }
    }

    while(!q.empty()){
        int cur = q.front(); q.pop();
        int next = v[cur].X;
        ans += max(0ll, v[cur].Y - money[cur]);
        money[next] += v[cur].Y;
        deg[next]--;
        if(!deg[next]) q.push(next);
    }

    for(int i=1; i<=n; i++){
        if(deg[i] == 1){
            int i1 = i;
            vector<int> cycle;
            for( ; deg[v[i1].X]; i1 = v[i1].X, deg[i1]--){
                cycle.push_back(v[i1].X);
            }
            kill_cycle(cycle);
        }
    }

    cout << ans << "\n";

    return 0;
}