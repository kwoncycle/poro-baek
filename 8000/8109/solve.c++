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

//bitset<10000> DP[41][41];
// DP[i][j][5000+o] = 1 -> i가 0칸 j가 o칸 밀린 상태에서 희망이 보임, o>0: j가 앞에


#define MOD 998244353ll

ll poww(ll a, ll e){
    ll ans = 1;
    while(e){
        if(e&1) ans = ans * a % MOD;
        e >>= 1;
        a = a * a % MOD;
    }
    return ans;
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int k; cin >> k;
    vector<string> v(k);
    string x, y;
    int o;
    cin >> o >> x;
    cin >> o >> y;
    for(int i=0; i<k; i++){
        cin >> o >> v[i];
    }

    if((int)x.size() > (int)y.size()){
        x.swap(y);
    }

    for(int i=0; i<(int)x.size(); i++){
        if(x[i] != y[i]){
            cout << "NIE\n"; return 0;
        }
    }

    x = y.substr((int)x.size(),(int)y.size());
    
    v.push_back(x);

    vector<vector<ll>> hshmap(k+1);
    for(int i=0; i<=k; i++){
        hshmap[i].resize(v[i].size() + 1, 0);
        ll u = 1;
        for(int j=0; j<(int)v[i].size(); j++){
            ll u1 = v[i][j];
            hshmap[i][j+1] = (hshmap[i][j] + u1 * u) % MOD;
            u = u * 15571557 % MOD;
        }
    }

    //if(hshmap[0][3] == hshmap[2][3]) cout << "YES\n";
    //return 0;

    vector<vector<vector<array<int,2>>>> graph(k+1);
    vector<vector<ll>> dst(k+1);
    for(int i=0; i<=k; i++){
        graph[i] = vector<vector<array<int,2>>>(v[i].size()+1);
        dst[i] = vector<ll>(v[i].size()+1, 0x3f3f3f3f3f3fll);
    }

    


    for(int i=0; i<=k; i++){
        for(int t=0; t<(int)v[i].size(); t++){
            for(int j=0; j<k; j++){
                if(t + (int)v[j].size() <= (int)v[i].size()){
                    if(hshmap[j][(int)v[j].size()] == (hshmap[i][t + v[j].size()] - hshmap[i][t] + MOD) * poww(449375313, t) % MOD){
                        graph[i][t].push_back({i, t+(int)v[j].size()});
                        //cout << i << " " << t << " " << i << " " << t+(int)v[j].size() << "\n";
                    }
                }
                else{
                    if(hshmap[j][v[i].size() - t] == (hshmap[i][v[i].size()] - hshmap[i][t] + MOD) * poww(449375313, t) % MOD){
                        graph[i][t].push_back({j, (int)v[i].size()-t});
                        //cout << i << " " << t << " " << j << " " << (int)v[i].size()-t << "\n";
                    }
                }
            }
        }
    }

    //dst[k][0] = 0;
    priority_queue<pair<ll, array<ll,2>>, vector<pair<ll, array<ll,2>>>, greater<pair<ll, array<ll,2>>>> pq;
    pq.push({0, {k, 0}});
    while(!pq.empty()){
        auto x = pq.top(); pq.pop();
        ll d = x.X;
        auto [i,j] = x.Y;
        if(dst[i][j] <= d) continue;
        dst[i][j] = d;
        for(auto [i1, j1]:graph[i][j]){
            if(dst[i][j] + 1 < dst[i1][j1]){
                pq.push({dst[i][j]+1, {i1, j1}});
            }
        }
    }

    ll mn = 0x3f3f3f3f3f3fll;
    for(int i=0; i<=k; i++){
        mn = min((ll)dst[i][v[i].size()], mn);
    }

    if(mn > 0x3f3f3f3f3f3fll - 123) cout << "NIE\n";
    else cout << mn << '\n';

    /*
    for(int i=0; i<k; i++){
        for(int j=i+1; j<k; j++){
            int truth = 1;
            int vis = v[i].size(), vjs = v[j].size();
            for(int i1 = 0; i1<min(vis, vjs); i1++){
                if(v[i][vis-i1-1] != v[j][vjs-i1-1]){
                    truth = 0; break;
                }
            }
            if(truth){
                DP[i][j][5000-v[i].size()+v[j].size()] = 1;
                //DP[j][i][5000-v[j].size()+v[i].size()] = 1;
            }
        }
    }
    */

    return 0;
}