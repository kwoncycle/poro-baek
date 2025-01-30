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
    set<int> s;
    vector<pii> ansp;
    for(int i=0; i<n; i++){
        if(s.find(v[i]) != s.end()){
            for(int i1=0; i1<i; i1++){
                for(int i2=i1+1; i2<i; i2++){
                    if(v[i2]-v[i1] == v[i] - v[i2] and v[i] > v[i1]){
                        ansp.push_back({v[i1], v[i2]});
                    }
                }
            }
        }
        for(int i1=0; i1<i; i1++){
            if(v[i1] != v[i]){
                s.insert(v[i]+v[i]-v[i1]);
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