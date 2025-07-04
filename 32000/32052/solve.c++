#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

#define X first
#define Y second
#define CNT_LOWER(v,n) (int)(lower_bound((v).begin(),(v).end(),(n))-(v).begin())
#define CNT_UPPER(v,n) (int)(upper_bound((v).begin(),(v).end(),(n))-(v).begin())
#define all(x) (x).begin(), (x).end()

// CNT_LOWER: number of element in v smaller than n
// CNT_UPPER: number of element in v smaller or same than n

#define LINE array<pii, 2>
// LINE: l[0] + kl[1]

pii operator + (pii l, pii r){return {l.X+r.X, l.Y+r.Y};};
pii operator - (pii l, pii r){return {l.X-r.X, l.Y-r.Y};};
ll operator * (pii l, pii r){return (ll)l.X*r.X + (ll)l.Y*r.Y;};
ll operator / (pii l, pii r){return (ll)l.X*r.Y - (ll)l.Y*r.X;};


bitset<500> DP[72][36];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    while(true){
        int n; cin >> n;
        if(!n) break;
        vector<int> v(n);
        for(auto &i:v) cin >> i;
        int sm = 0;
        for(auto &i:v) sm += i;
        if(sm % 2 != 0){
            cout << "No\n"; continue;
        }
        vector<int> id;
        int truth = 0;
        if(n%2 == 1){
            for(int i=0; i<n; i++) id.push_back(i);
            truth = 1;
        }
        else{
            int i = 0;
            while(i < n and v[i] % 2 != 0) i++;
            if(i != n){
                for(int j=0; j<i; j++) id.push_back(j);
                for(int j=i+1; j<n; j++) id.push_back(j);
                truth = 1;
            }
        }
        if(truth){
            vector<pii> ans(n, {-500, -500});
            ans[id[0]] = {0, v[id[0]]};
            for(int i=1; i<(int)id.size(); i++){
                ans[id[i]].X = ans[id[i-1]].Y;
                ans[id[i]].Y = v[id[i]] - ans[id[i]].X;
            }
            int delta = ans[id.back()].Y/2;
            for(int i=0; i<(int)id.size(); i++){
                if(i%2 == 0){
                    ans[id[i]].X += delta;
                    ans[id[i]].Y -= delta;
                }
                else{
                    ans[id[i]].X -= delta;
                    ans[id[i]].Y += delta;
                }
            }
            for(int i=0; i<n; i++){
                if(ans[i].X + ans[i].Y != v[i]){
                    ans[i].X = v[i]/2; ans[i].Y = v[i]/2;
                }
            }
            cout << "Yes\n";
            for(int i=0; i<n; i++) cout << ans[i].X << " "; cout << "\n";
            for(int i=0; i<n; i++) cout << ans[i].Y << " "; cout << "\n";
            continue;
        }

        sm = 0;
        for(int i=0; i<n; i++) {
            v[i] += 150; // set ans -= 75
            sm += v[i];
        }

        for(int i=0; i<72; i++){
            for(int j=0; j<36; j++) DP[i][j].reset();
        }


        DP[0][0][0] = 1;
        int target = sm / 2;
        for(int i=0; i<n; i++){
            for(int j=0; j<=35; j++){
                DP[i+1][j] |= DP[i][j];
            }
            for(int j=0; j<35; j++){
                DP[i+1][j+1] |= (DP[i][j] << v[i]);
            }
        }

        if(DP[n][n/2][target] == 0){
            cout << "No\n";
            continue;
        }

        int cnt = n/2;

        vector<int> S0, S1;
        for(int i=n-1; i>=0; i--){
            if(target-v[i] >= 0 and cnt-1 >= 0 and DP[i][cnt-1][target-v[i]] == 1){
                S0.push_back(i);
                target -= v[i];
                cnt--;
            }
            else S1.push_back(i);
        }

        id.clear();
        for(int i=0; i<S0.size(); i++){
            id.push_back(S0[i]); id.push_back(S1[i]);
        }

        vector<pii> ans(n, {-500, -500});
        ans[id[0]] = {0, v[id[0]]};
        for(int i=1; i<(int)id.size(); i++){
            ans[id[i]].X = ans[id[i-1]].Y;
            ans[id[i]].Y = v[id[i]] - ans[id[i]].X;
        }

        cout << "Yes\n";
        for(int i=0; i<n; i++) cout << ans[i].X - 75 << " "; cout << "\n";
        for(int i=0; i<n; i++) cout << ans[i].Y - 75 << " "; cout << "\n";
    }
    return 0;
}