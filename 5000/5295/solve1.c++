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
    for(int i=0; i<n; i++) cin >> v[i];
    sort(v.begin(), v.end());
    vector<pii> ansp;
    for(int i=0; i<n; i++){
        for(int j=i+1; j<n; j++){
            for(int k=j+1; k<n; k++){
                if(v[i] != v[j] and v[j]*2==v[i]+v[k]){
                    ansp.push_back({v[i],v[j]});
                }
            }
        }
    }

    if(ansp.empty())
        cout << "Sequence is 3-free.\n";
    else{
        sort(ansp.begin(), ansp.end());
        cout << "Sequence is not 3-free. Witness: " << ansp[0].X << "," << ansp[0].Y << "," << ansp[0].Y*2-ansp[0].X << ".\n";
    }
    return 0;
}