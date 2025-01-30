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



int n;
vector<vector<int>> graph(501*501);
vector<pii> info(501*501);
vector<int> dist(501*501, 90000000);
int pii2int(pii xy){
    int x = xy.X, y = xy.Y;
    int o = (2*n-1)*((x-1)/2);
    o += y;
    if(x % 2 == 0) o += n;
    return o;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    cin >> n;
    for(int i=1; i<=n*n-n/2; i++){
        cin >> info[i].X >> info[i].Y;
    }

    for(int i=1; i<=n; i++){
        int o = n-1;
        if(i%2==1) o = n;
        for(int j=1; j<=o; j++){
            int now = pii2int({i, j});
            int u1 = pii2int({i, j+1});
            int u2 = pii2int({i+1, j+1-i%2});
            int u3 = pii2int({i-1, j+1-i%2});
            if(j < o)
            if(info[now].Y == info[u1].X){
                graph[now].push_back(u1);
                graph[u1].push_back(now);
            }

            if(i < n and (j+1-i%2) <= (n - 1 + (i+1)%2))
            if(info[now].Y == info[u2].X){
                graph[now].push_back(u2);
                graph[u2].push_back(now);
            }
            if(i > 1 and (j+1-i%2) <= (n - 1 + (i+1)%2)){
                if(info[now].Y == info[u3].X){
                    graph[now].push_back(u3);
                    graph[u3].push_back(now);
                }
            }
        }
    }

    //dist[1] = 0;
    queue<pii> q;
    q.push({1, 0});
    while(!q.empty()){
        pii x = q.front(); q.pop();
        if(dist[x.X] <= x.Y) continue;
        dist[x.X] = x.Y;
        for(int i:graph[x.X]){
            q.push({i, dist[x.X] + 1});
        }
    }

    int last;
    for(int i=n*n; i>=1; i--){
        if(dist[i] < 9000000){
            last = i; break;
        }
    }

    vector<int> ans;
    ans.push_back(last);
    while(dist[last] > 0){
        for(int i:graph[last]){
            if(dist[i] + 1 == dist[last]){
                last = i; break;
            }
        }
        ans.push_back(last);
    }
    vector<int> ans1;
    for(int i=(int)ans.size()-1; i>=0; i--) ans1.push_back(ans[i]);
    cout << ans.size() << "\n";
    for(int i:ans1) cout << i << " "; cout << "\n";
    return 0;
}