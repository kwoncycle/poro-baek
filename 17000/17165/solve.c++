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
    vector<string> v(n);
    for(int i=0; i<n; i++) cin >> v[i];
    
    vector<int> cnt(n, 0);
    vector<vector<int>> dst(n, vector<int>(n, 9000));
    for(int i=0; i<n; i++) dst[i][i] = 0;
    vector<queue<int>> vq(n);
    for(int i=0; i<n; i++) vq[i].push(i);


    for(int d=0; d<=30; d++){
        for(int i=0; i<n; i++){
            while(!vq[i].empty()){
                int j = vq[i].front();
                if(dst[i][j] > d) break;
                vq[i].pop();
                for(int k=0; k<n; k++){
                    if(v[j][k] == 'L' and dst[i][k] > d + 1){
                        dst[i][k] = d+1;
                        cnt[k]++;
                        vq[i].push(k);
                    }
                }
            }
        }
        for(int i=0; i<n; i++){
            if(cnt[i] == n-1){
                cout << d+1 << " " << i+1 << "\n";
                return 0;
            }
        }
    }

    return 0;
}