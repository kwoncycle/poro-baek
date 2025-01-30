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

bool cmp(string s1, string s2){
    ll u1 = 0, uN1 = 0, u2 = 0, uN2 = 0;
    for(char c:s1){
        u1 *= 10; u1 += c-'0';
        uN1 *= 10; uN1 += 9;
    }
    for(char c:s2){
        u2 *= 10; u2 += c-'0';
        uN2 *= 10; uN2 += 9;
    }
    u1 = u1 * 100000000000ll / uN1;
    u2 = u2 * 100000000000ll / uN2;
    return u1 < u2;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n; cin >> n;
    vector<string> v(n);
    for(int i=0; i<n; i++) cin >> v[i];
    sort(v.begin(), v.end(), cmp);
    int index = 0;
    while(index < n and v[index][0] == '0') index++;
    if(index == n) cout << "INVALID\n";
    else{
        vector<string> ans;
        for(int i=0; i<n; i++){
            if(v[i][0] == '0') continue;
            string s;
            s = v[i];
            for(int j=0; j<n; j++){
                if(i != j) s += v[j];
            }
            ans.push_back(s);
        }
        sort(ans.begin(), ans.end());
        cout << ans[0] << "\n";
    }
    return 0;
}