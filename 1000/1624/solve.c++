#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define pii pair<int,int>
#define pll pair<ll,ll>
#define pil pair<int,ll>
#define pli pair<ll,int>
#define X first
#define Y second
#define CNT_LOWER(v,n) (int)(lower_bound((v).begin(),(v).end(),(n))-(v).begin())
#define CNT_UPPER(v,n) (int)(upper_bound((v).begin(),(v).end(),(n))-(v).begin())
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n; cin >> n;
    vector<int> v(n);
    vector<vector<int>> index(3000);
    for(int i=0; i<n; i++){
        cin >> v[i];
        index[v[i]+1001].push_back(i);
    }
    sort(v.begin(), v.end());
    int cnt = 1;
    int UD = 0; // 0 down 1 up
    int before = 999999999;
    for(int i=0; i<n; i++){
        if(UD == 0){
            if(before > index[v[i]+1001].back()){
                before = index[v[i]+1001].back();
                index[v[i]+1001].pop_back();
            }
            else{
                UD = 1; before = -999999999; i--;
            }
        }
        else{
            if(before < index[v[i]+1001][0]){
                before = index[v[i]+1001][0];
                for(int j=0; j<(int)index[v[i]+1001].size() - 1; j++){
                    index[v[i]+1001][j] = index[v[i]+1001][j+1];
                }
                index[v[i]+1001].pop_back();
            }
            else{
                UD = 0; before = 999999999; i--; cnt++;
            }
        }
    }
    cout << cnt << "\n";
    return 0;
}