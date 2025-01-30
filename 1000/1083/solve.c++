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
    vector<int> v(n);
    vector<pii> vp(n);
    for(int i=0; i<n; i++) {
        cin >> v[i];
        vp[i] = {v[i], i};
    }

    sort(vp.begin(), vp.end(), greater<pii>());
    int s; cin >> s;
    int i0 = 0;
    while(i0 < n){
        for(int i=0; i<n; i++){
            if(vp[i].Y >= i0 and vp[i].Y - i0 <= s){
                for(int j=vp[i].Y; j>i0; j--){
                    swap(v[j], v[j-1]);
                    s--;
                }
                for(int j=0; j<n; j++) {
                    vp[j] = {v[j], j};
                }
                sort(vp.begin(), vp.end(), greater<pii>());
                break;
            }
        }
        i0++;
    }

    for(int i:v) cout << i << " "; cout << "\n";
    return 0;
}