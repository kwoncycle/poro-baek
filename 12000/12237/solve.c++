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
    for(int ti = 1; ti <= tt; ti++){
        int n; cin >> n;
        cout << "Case #" << ti << ": ";
        vector<int> v(n);
        for(int i=0; i<n; i++) cin >> v[i];
        int i0 = 0, i1 = n-1;
        int cnt = 0;
        while(i0 < i1){
            int idx = i0;
            for(int i=i0; i<=i1; i++){
                if(v[idx] > v[i]) idx = i;
            }
            if(i1 - idx > idx - i0){
                cnt += idx-i0;
                int x = v[idx];
                for(int i=idx-1; i>=i0; i--){
                    v[i+1] = v[i];
                }
                v[i0] = x;
                i0++;
            }
            else{
                cnt += i1 - idx;
                int x = v[idx];
                for(int i=idx+1; i<=i1; i++){
                    v[i-1] = v[i];
                }
                v[i1] = x;
                i1--;
            }
        }
        cout << cnt << "\n";
    }
    return 0;
}