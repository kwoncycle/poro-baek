#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;

vector<pll> graph[200003];
ll n, m, M;
ll x[1000003];
pll a[200003];
ll ans[200003];
ll u, v, w;

pll X;

ll dfs(ll cur, ll pre=-1){
    ll tmp = x[cur];
    for (pll p : graph[cur]){
        //if (p.first == pre) continue;

        pll newval;
        newval.first = (M - a[cur].first) % M;
        newval.second = (p.second + M - a[cur].second) % M;
        if (newval.first == 0) newval.first = M;
        if (newval.second == 0) newval.second = M;

        if (a[p.first].first != -1){
            ll o = a[p.first].first + a[cur].first;
            if(o % M == 0){
                if((a[p.first].second + a[cur].second)%M != (p.second%M)){
                    cout << "-1\n"; exit(0);
                }
            }
            else{
                if(o%M == 2){
                    ll X1 = (p.second - a[p.first].second + M + M - a[cur].second) % M;
                    assert(X1 >= 0);
                    if(X.first == -1) X.first = X1;
                    else{
                        if(X1%M != X.first%M) {
                            cout << "-1\n"; exit(0);
                        }
                        else continue;
                    }
                }
                else{
                    assert(o%M == M-2);
                    ll X1 = (-p.second + a[p.first].second + M + M + a[cur].second) % M;
                    assert(X1 >= 0);
                    if(X.first == -1) X.first = X1;
                    else{
                        if(X1%M != X.first%M) {
                            cout << "-1\n"; exit(0);
                        }
                        else continue;
                    }
                }
            }
            continue;
        }

        a[p.first] = newval;
        tmp = min(tmp, dfs(p.first, cur));
    }

    return tmp;
}

void dfs2(ll cur){
    ans[cur] = (a[cur].first * X.first + a[cur].second) % M;
    if (ans[cur] == 0) ans[cur] = M;

    for (pll p : graph[cur]){
        if (ans[p.first] == -1) dfs2(p.first);
    }
}

int main(){
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m >> M;
    for (ll i = 1; i <= n; i++){
        cin >> x[i];
        a[i] = {-1, -1};
        ans[i] = -1;
    }
    while (m--){
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }

    ll res = 0;
    for (ll i = 1; i <= n; i++){
        if (a[i].first == -1){
            a[i] = {1, 0};
            X = {-1, -1};
            ll o = dfs(i);
            if (X.first == -1) {
                X = {1, 0}; res += o;
            }
            else{
                ll tt = X.first%M;
                if(X.first % 2 !=0 and (X.first + M) % 2 != 0){
                    cout << "-1\n"; return 0;
                }
                if(X.first % 2 == 0 and (X.first + M) % 2 == 0){
                    res += o;
                }
                if(X.first % 2 == 0) X.first = X.first / 2;
                else if((X.first + M) % 2 == 0) X.first = (X.first + M) / 2;
                assert(X.first*2%M == tt);
            }
            dfs2(i);

            // cout << i << ' ' << X << endl;
        }
    }

    for(ll i=1; i<=n; i++){
        for(auto [j,t]:graph[i]){
            assert((ans[i]+ans[j])%M == t);
        }
    }

    cout << res << '\n';
    for (ll i = 1; i <= n; i++){
        cout << ans[i] << ' ';
        //assert(ans[i] > 0);
    }
    cout << '\n';

}