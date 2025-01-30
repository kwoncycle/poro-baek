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
    int n, k; cin >> n >> k;
    vector<vector<int>> v1(n), v2(n);
    for(int i=0; i<n; i++){
        int t; cin >> t;
        while(t--){
            int j; cin >> j; j--;
            v1[i].push_back(j);
            v2[j].push_back(i);
        }
    }

    for(int i=0; i<n; i++){
        vector<int> visited(n, 0);
        visited[i] = 1;
        queue<int> q;
        q.push(i);
        while(!q.empty()){
            int r = q.front(); q.pop();
            for(int j:v2[r]){
                if(!visited[j]){
                    visited[j] = 1;
                    q.push(j);
                }
            }
        }
        int cnt = 0;
        for(int j=0; j<n; j++) cnt += visited[j];
        if(cnt > k) cout << "1\n";
        else cout << "0\n";
    }
    return 0;
}