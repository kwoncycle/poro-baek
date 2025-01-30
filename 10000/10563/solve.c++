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
    int tt; cin >> tt;
    while(tt--){
        int n; cin >> n;
        vector<int> v(n);
        for(int i=0; i<n; i++) cin >> v[i];
        vector<vector<int>> DP(n, vector<int>(n, 0));
        vector<vector<int>> DP1(n, vector<int>(n, 0));
        int id = 0;
        while(v[id] != 1) id++;
        DP[id][id] = 1; // could you win with even
        DP1[id][id] = 1; // win with odd extra
        // 1: Alice, 0 : Bob

        for(int sz = 2; sz <= n; sz++){
            for(int i=0; i<n; i++){
                if(i <= id and i+sz-1 >= id and i+sz-1 < n){
                    // DP[i][i+sz-1]
                    for(int j=i; j<=id-1; j++){
                        int truth = 1;
                        if(!(j == i or v[j] > v[j-1])) truth = 0;
                        if(!(v[j] > v[j+1])) truth = 0;
                        if(j == id-1 and i+sz-1 == id) truth = 0;
                        if(truth){
                            if((j-1-i+1) % 2 == 0){
                                if(DP[j+1][i+sz-1] == 0){
                                    DP[i][i+sz-1] = 1;
                                }
                                if(DP1[j+1][i+sz-1] == 0){
                                    DP1[i][i+sz-1] = 1;
                                }
                            }
                            else{
                                if(DP1[j+1][i+sz-1] == 0){
                                    DP[i][i+sz-1] = 1;
                                }
                                if(DP[j+1][i+sz-1] == 0){
                                    DP1[i][i+sz-1] = 1;
                                }
                            }


                        }
                    }

                    for(int j=id+1; j<=i+sz-1; j++){
                        int truth = 1;
                        if(!(j == i+sz-1 or v[j] > v[j+1])) truth = 0;
                        if(!(v[j] > v[j-1])) truth = 0;
                        if(j == id+1 and i == id) truth = 0;
                        if(truth){
                            if((i+sz-1 - j-1 + 1) % 2 == 0){
                                if(DP[i][j-1] == 0) DP[i][i+sz-1] = 1;
                                if(DP1[i][j-1] == 0) DP1[i][i+sz-1] = 1;
                            }
                            else{
                                if(DP[i][j-1] == 0) DP1[i][i+sz-1] = 1;
                                if(DP1[i][j-1] == 0) DP[i][i+sz-1] = 1;
                            }
                        }
                    }
                    
                    if(DP[i][i+sz-1] == 0) DP1[i][i+sz-1] = 1;
                }

                
            }
        }
        /*
        for(int i=0; i<=id; i++){
            for(int j=id; j<n; j++){
                cout << i << " " << j << " " << DP[i][j] << "\n";
            }
        }*/
        if(DP[0][n-1]) cout << "Alice\n";
        else cout << "Bob\n";
    }
    return 0;
}