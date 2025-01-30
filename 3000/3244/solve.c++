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

int na, nb;
string a, b;
vector<vector<int>> next_pos(2024, vector<int>(26, 0x3f3f3f));
vector<vector<int>> DP(2024, vector<int>(2024, -1)); // DP[i][j] : A_{0~i}에서 j개 쓸때 B의 몇번째 최대 index까지

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    cin >> a; cin >> b;
    na = a.size(); nb = b.size();

    for(int i=nb-1; i>=0; i--){
        for(int j=0; j<26; j++){
            next_pos[i][j] = next_pos[i+1][j];
        }
        next_pos[i][b[i]-'a'] = i;
    }

    if(next_pos[0][a[0]-'a'] == -1){
        cout << "1\n";
        cout << a[0] << "\n";
        return 0;
    }

    DP[0][1] = next_pos[0][a[0]-'a'];
    for(int i=1; i<na; i++){
        for(int j=1; j<=na; j++) DP[i][j] = DP[i-1][j];
        for(int j=i+1; j>=1; j--){
            int o = DP[i-1][j-1];
            if(o+1 < nb){
                DP[i][j] = max(DP[i][j], next_pos[o+1][a[i]-'a']);
            }
            else DP[i][j] = 0x3f3f3f;
        }
    }

    int mn = 1;
    string ans;
    while(DP[na-1][mn] != 0x3f3f3f) mn++;
    for(int i=na-1; i>=0; i--){
        if(i > 0){
            if(DP[i][mn] != DP[i-1][mn]){
                ans.push_back(a[i]);
                mn--;
            }
        }
        else{
            if(mn) ans.push_back(a[i]);
        }
    }

    reverse(ans.begin(), ans.end());
    cout << (int)ans.size() << "\n";
    cout << ans << "\n";
    return 0;
}