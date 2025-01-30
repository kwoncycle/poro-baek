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

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int k, n;
    cin >> k >> n;

    vector<vector<array<int,2>>> graph(k+1);
    vector<array<int, 3>> p(n);
    for(int i=0; i<n; i++){
        cin >> p[i][0] >> p[i][1] >> p[i][2];
    }

    for(int i=0; i<n; i++){
        graph[p[i][0]-1].push_back({p[i][1], p[i][2]});
        graph[p[i][1]].push_back({p[i][0]-1, -p[i][2]});
    }

    for(int i=0; i<k; i++){
        graph[i].push_back({i+1, 1});
        graph[i+1].push_back({i, 0});
    }

    vector<int> dst(k+1, 0x3f3f3f3f);
    dst[0] = 0;
    for(int i=0; i<=k; i++){
        for(int j=0; j<=k; j++){
            for(auto &[i1, i2]:graph[j]){
                dst[i1] = min(dst[i1], dst[j] + i2);
            }
        }
    }

    for(int i=0; i<=k; i++){
        for(auto &[i1,i2]: graph[i]){
            if(dst[i1] > dst[i] + i2){
                cout << "NONE\n"; return 0;
            }
        }
    }

    for(int i=1; i<=k; i++){
        if(dst[i] == dst[i-1]) cout << "-";
        else cout << "#";
    }

    cout << "\n";


    return 0;
}