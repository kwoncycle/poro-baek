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
    int n; cin >> n;
    vector<int> v(n);
    for(int i=0; i<n; i++) cin >> v[i];

    vector<vector<int>> DP(360, vector<int>(100001, 0));
    vector<vector<int>> DP1(360, vector<int>(360));
    vector<int> a2id(1000001);
    int id = 1;
    for(int i=0; i<n; i++){
        if(a2id[v[i]] == 0){
            a2id[v[i]] = id; id++;
        }
        v[i] = a2id[v[i]];
    }

    for(int i=0; i*300+299<n; i++){
        vector<int> cnt(100001, 0);
        int o = 0;
        for(int j=i*300; j<n; j++){
            if(j%300 == 0){
                DP1[i][j/300] = o;
            }
            cnt[v[j]]++;
            if(cnt[v[j]] == 1) o++;
        }
    }

    vector<int> cnt(100001, 0);
    for(int i=0; i<n; i+=300){
        if(i+299 < n){
            for(int j=0; j<300; j++){
                cnt[v[i+j]]++;
            }
            for(int j=0; j<100001; j++){
                DP[i/300][j] = cnt[j];
            }
        }
    }
    vector<int> mp(100001);
    int qq; cin >> qq;
    while(qq--){
        int a1, a2; cin >> a1 >> a2;
        a1--; a2--;
        int b1 = (a1/300)*300 + 300, b2 = (a2/300)*300;
        //map<int, int> mp;
        if(b1 >= b2){
            int o = 0;
            for(int i=a1; i<=a2; i++){
                mp[v[i]]++;
                if(mp[v[i]] == 1) o++;
            }
            int mx = 0;
            for(int i=a1; i<=a2; i++) mp[v[i]]--;
            cout << o << "\n";
            continue;
        }

        int o = 0;
        for(int i=a1; i<b1; i++){
            mp[v[i]]++;
            if(mp[v[i]] == 1 and DP[b2/300 - 1][v[i]] - (b1>0?DP[b1/300 - 1][v[i]]:0) == 0) o++;
        }
        for(int i=b2; i<=a2; i++){
            mp[v[i]]++;
            if(mp[v[i]] == 1 and DP[b2/300 - 1][v[i]] - (b1>0?DP[b1/300 - 1][v[i]]:0) == 0) o++;
        }
        o += DP1[b1/300][b2/300];
        for(int i=a1; i<b1; i++){
            mp[v[i]]--;
        }
        for(int i=b2; i<=a2; i++){
            mp[v[i]]--;
        }
        cout << o << "\n";
    }

    return 0;
}