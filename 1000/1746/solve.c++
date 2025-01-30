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


void MT(vector<vector<ll>> &X, vector<vector<ll>> &Y, vector<vector<ll>> &out){
    int sz = X.size();
    for(int i=0; i<sz; i++){
        for(int j=0; j<sz; j++) out[i][j] = 0x3f3f3f3f3f3f;
    }

    // i->j to i->k->j
    for(int i=0; i<sz; i++){
        for(int j=0; j<sz; j++){
            for(int k=0; k<sz; k++){
                out[i][j] = min(out[i][j], X[i][k] + Y[k][j]);
            }
        }
    }

    
}

void poww(vector<vector<ll>> &A, ll n, vector<vector<ll>> &ans){
    int sz = A.size();
    for(int i=0; i<sz; i++){
        for(int j=0; j<sz; j++) {
            if(i == j) ans[i][j] = 0;
            else ans[i][j] = 0x3f3f3f3f3f3f;
        }
    }

    while(n){
        if(n&1){
            vector<vector<ll>> ans1(sz, vector<ll>(sz));
            MT(ans, A, ans1);
            ans = ans1;
        }
        n >>= 1;
        vector<vector<ll>> A1(sz, vector<ll>(sz));
        MT(A, A, A1);
        A = A1;
    }
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n, t, s, e; cin >> n >> t >> s >> e;

    vector<array<int,3>> edges(t);
    for(int i=0; i<t; i++) cin >> edges[i][0] >> edges[i][1] >> edges[i][2];

    vector<int> mp(1001, -999);
    int id = 0;
    for(int i=0; i<t; i++){
        if(mp[edges[i][1]] == -999){
            mp[edges[i][1]] = id;
            id++;
        }
        if(mp[edges[i][2]] == -999){
            mp[edges[i][2]] = id;
            id++;
        }
    }
    vector<vector<ll>> ans;
    vector<vector<ll>> A;

    ans = vector<vector<ll>>(id, vector<ll>(id, 0x3f3f3f3f3f3f));
    //ans[mp[s]][mp[s]] = 0;
    A = vector<vector<ll>>(id, vector<ll>(id, 0x3f3f3f3f3f3f));
    for(int i=0; i<t; i++){
        int i1 = mp[edges[i][1]];
        int i2 = mp[edges[i][2]];
        A[i1][i2] = edges[i][0];
        A[i2][i1] = edges[i][0];
    }

    poww(A, n, ans);

    cout << ans[mp[s]][mp[e]] << "\n";


    return 0;
}