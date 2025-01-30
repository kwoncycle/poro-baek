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
    vector<int> v(n);
    for(int i=0; i<n; i++) {
        cin >> v[i];
        v[i]--;
    }

    if(k <= 17){
        vector<bitset<(1<<17)>> DP(n);
        DP[0][(1<<v[0])] = 1;
        for(int i=1; i<n; i++){
            int o = 1<<v[i];
            for(int j=0; j<(1<<k); j++){
                if(DP[i-1][j]) DP[i][j] = 1;
                else{
                    
                }

                DP[i+1][j] = DP[i+1][j] | DP[i][j];
                DP[i+1][j|o] = DP[i+1][j|o] | DP[i][j];
            }
        }
    }

    if(k >= 25){
        int id = 0;
        vector<int> checked(k+1, 0);
        vector<int> ans;
        for(int i=k; i>=1; i--){
            set<int> st;
            for(int j=1; j<=k; j++){
                if(!checked[j]) st.insert(j);
            }

            while(id < n){
                if(st.find(v[id]) != st.end()) st.erase(v[id]);
                if(st.empty()){
                    checked[v[i]] = 0;
                    ans.push_back(v[i]);
                    break;
                }
                id++;
            }
        }
    }
    return 0;
}