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
        vector<ll> a;
        for(int i=0; i<n; i++){
            int b; cin >> b;
            if(b) a.push_back(b);
        }
        n = a.size();
        if(n == 0){
            cout << "NO\n"; continue;
        }
        int cnt = 0;
        ll sm = a[0];
        for(int i=1; i<n; i++){
            if(sm < 0){
                if(a[i] < 0) sm += a[i];
                else{
                    if(a[i] + sm > 0) sm += a[i];
                    else{
                        cnt -= 1;
                        sm = a[i];
                    }
                }
            }
            else{
                if(a[i] > 0){
                    cnt++;
                    sm = a[i];
                }
                else{
                    if(a[i] + sm > 0) sm += a[i];
                    else{
                        cnt++;
                        sm = a[i];
                    }
                }
            }
        }
        if(sm < 0) cnt--;
        else cnt++;
        if(cnt > 0) cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}