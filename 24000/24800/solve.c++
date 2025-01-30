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
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr); cout.tie(nullptr);
    int s, n;
    cin >> s >> n;
    vector<int> v(2*n, 0);
    for(int i=0; i<n; i++) v[i*2] = 1;
    int start = 0;
    // 1: fist 2: hand-up 3:hand-down
    while(true){
        int ppl = 0;
        for(int i=0; i<n; i++){
            if(v[i*2] or v[i*2+1]) ppl++;
        }
        if(ppl <= 1) break;
        int cnt = 0;
        while(cnt < s){
            if(v[start] != 0){
                cnt++;
            }
            if(cnt >= s) break;
            start = (start + 1) % (2*n);
        }
        if(v[start] == 1){
            v[start] = 2;
            v[start + 1] = 2;
        }
        else if(v[start] == 2){
            v[start] = 3;
            start = (start + 1) % (2*n);
        }
        else if(v[start] == 3){
            v[start] = 0;
            start = (start + 1) % (2*n);
        }
    }
    int ans = 0;
    for(int i=0; i<n; i++){
        if(v[2*i] or v[2*i+1]){
            ans = i;
        }
    }
    cout << ans+1 << "\n";
    return 0;
}