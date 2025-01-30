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

    int n, m, s; cin >> n >> m >> s;
    vector<vector<pii>> group_log(n+1);
    vector<vector<pair<pii, int>>> student_log(m+1);
    vector<int> cnt(m+1, 0);
    for(int tm=0; tm<s; tm++){
        int t, x, y; cin >> t >> x >> y;
        if(t == 3){
            group_log[y].push_back({tm, x});
            cnt[x]--;
        }
        else{
            student_log[x].push_back({{y,tm}, t});
        }
    }

    for(int i=1; i<=m; i++){
        for(auto yt:student_log[i]){
            int y = yt.X.X, tm = yt.X.Y, t = yt.Y;
            pii p = {tm, 0};
            int u = (int)group_log[y].size() - CNT_LOWER(group_log[y], p);
            if(t == 1) cnt[i] += u;
            else cnt[i] -= u;
        }
        cout << cnt[i] << "\n";
    }
    return 0;
}