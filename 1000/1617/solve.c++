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

#define LINE array<pii, 2>
// LINE: l[0] + kl[1]

pii operator + (pii l, pii r){return {l.X+r.X, l.Y+r.Y};};
pii operator - (pii l, pii r){return {l.X-r.X, l.Y-r.Y};};
ll operator * (pii l, pii r){return (ll)l.X*r.X + (ll)l.Y*r.Y;};
ll operator / (pii l, pii r){return (ll)l.X*r.Y - (ll)l.Y*r.X;};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n; cin >> n;
    vector<array<int, 5>> v(n);
    vector<int> x;
    for(int i=0; i<n; i++){
        for(int j=0; j<5; j++) cin >> v[i][j];
        v[i][2]--; v[i][3]--;
        x.push_back(v[i][0]);
        x.push_back(v[i][2]);
        x.push_back(v[i][2]+1);
    }
    sort(x.begin(), x.end());
    x.erase(unique(x.begin(), x.end()), x.end());
    map<int, int> mp;
    int sz_x = x.size();
    ll ans = 0;
    for(int i=0; i<sz_x; i++) mp[x[i]] = i;
    for(int i=0; i<=40000; i++){
        vector<int> x1(sz_x+1), x2(sz_x+1), x3(sz_x+1), x4(sz_x+1);
        for(int j=0; j<n; j++){
            if(v[j][1] <= i and i <= v[j][3]){
                if(v[j][4] == 1){
                    x1[mp[v[j][0]]]++;
                    x1[mp[v[j][2]+1]]--;
                }
                else if(v[j][4] == 2){
                    if((i-v[j][1])%2 != 0){
                        x1[mp[v[j][0]]]++;
                        x1[mp[v[j][2]+1]]--;
                    }
                }
                else if(v[j][4] == 3){
                    if(v[j][0]%2 == 0){
                        x2[mp[v[j][0]]]++;
                        x2[mp[v[j][2]+1]]--;
                    }
                    else{
                        x3[mp[v[j][0]]]++;
                        x3[mp[v[j][2]+1]]--;
                    }
                }
                else if(v[j][4] == 4){
                    if(((i-v[j][1])%2 != 0) == (v[j][0]%2 == 0)){
                        x2[mp[v[j][0]]]++;
                        x2[mp[v[j][2]+1]]--;
                    }
                    else{
                        x3[mp[v[j][0]]]++;
                        x3[mp[v[j][2]+1]]--;
                    }
                }
            }
        }
        for(int j=1; j<=sz_x; j++){
            x1[j] = x1[j-1] + x1[j];
            x2[j] = x2[j-1] + x2[j];
            x3[j] = x3[j-1] + x3[j];   
        }
        for(int j=0; j<sz_x-1; j++){
            if(x1[j] > 0 or (x2[j] > 0 and x3[j] > 0)){
                ans += x[j+1]-x[j];
            }
            else{
                if(x2[j] > 0){
                    // 짝 흰 홀 검
                    int o2 = x[j+1]-1, o1 = x[j];
                    if(o2%2 == 1) o2++;
                    if(o1%2 == 0) o1++;
                    o2 -= o1;
                    ans += max(0, (o2+1)/2);
                    // 2 1 3 1
                    //ans += sz/2;
                }
                else if(x3[j] > 0){
                    int o2 = x[j+1]-1, o1 = x[j];
                    if(o2%2 == 0) o2++;
                    if(o1%2 == 1) o1++;
                    o2 -= o1;
                    ans += max(0, (o2+1)/2);
                }
            }
        }
    }
    cout << ans << "\n";
    return 0;
}