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
#define DEBUG 0
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int r, c, k; cin >> r >> c >> k;
    vector<vector<int>> v(101, vector<int>(101, 0));
    int n_r = 3, n_c = 3;
    for(int i=1; i<=3; i++){
        for(int j=1; j<=3; j++) cin >> v[i][j];
    }

    int ans = -1;
    if(v[r][c] == k){
        cout << "0\n"; return 0;
    }
    for(int t=1; t<=100; t++){
        if(n_r >= n_c){
            vector<vector<int>> v1(101, vector<int>(101, 0));
            int mx = 0;
            for(int i=1; i<=n_r; i++){
                vector<int> cnt(101, 0);
                for(int j=1; j<=n_c; j++){
                    cnt[v[i][j]]++;
                }
                vector<pii> vp;
                for(int j=1; j<=100; j++){
                    if(cnt[j] != 0){
                        vp.push_back({cnt[j], j});
                    }
                }
                sort(vp.begin(), vp.end());
                mx = max(mx, (int)vp.size()*2);
                for(int j=0; j<(int)vp.size(); j++){
                    v1[i][j*2+1] = vp[j].Y;
                    v1[i][j*2+2] = vp[j].X;
                }
            }
            n_c = mx;
            v = v1;
        }

        else{
            vector<vector<int>> v1(101, vector<int>(101, 0));
            int mx = 0;
            for(int j=1; j<=n_c; j++){
                vector<int> cnt(101, 0);
                for(int i=1; i<=n_r; i++){
                    cnt[v[i][j]]++;
                }
                vector<pii> vp;
                for(int i=1; i<=100; i++){
                    if(cnt[i] != 0){
                        vp.push_back({cnt[i], i});
                    }
                }
                sort(vp.begin(), vp.end());
                mx = max(mx, (int)vp.size()*2);
                for(int i=0; i<(int)vp.size(); i++){
                    v1[i*2+1][j] = vp[i].Y;
                    v1[i*2+2][j] = vp[i].X;
                }
            }
            n_r = mx;
            v = v1;
        }
        if(DEBUG){
            for(int i=1; i<=n_r; i++){
                for(int j=1; j<=n_c; j++){
                    cout << v[i][j] << " ";
                }
                cout << "\n";
            }
        }

        if(v[r][c] == k){
            ans = t; break;
        }
    }
    cout << ans << "\n";
    return 0;
}