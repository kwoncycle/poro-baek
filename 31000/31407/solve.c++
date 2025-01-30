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
    int n, l; cin >> n >> l;

    vector<pair<pii, int>> v(n);
    for(int i=0; i<n; i++){
        int a; char b; cin >> a >> b;
        v[i].X.X = a*4+1;
        v[i].X.Y = -1;
        v[i].Y = i+1;
        if(b == 'R') v[i].X.Y = 1;
    }

    vector<int> ans;

    int cnt = 0;
    for(int i=0; i<n; i++){
        if(v[i].X.Y == 1) cnt++;
    }

    int now = n;
    if(now - cnt < cnt){
        for(int i=0; i<n; i++){
            v[i].X.Y = -1 * v[i].X.Y;
        }
        ans.push_back(0);
    }

    int out1 = 0;
    while(now > 0){
        //for(int i=0; i<n; i++) cout << v[i].X.X << " "; cout << "\n";

        int truth = 0;
        int index = -1;
        for(int i=0; i<n; i++){
            v[i].X.X += v[i].X.Y;
            if(v[i].X.Y and (v[i].X.X <= 0 or v[i].X.X >= 4*l)){
                if(v[i].X.X <= 0) out1++;
                v[i].X.Y = 0;
                truth = 1;
                index = v[i].Y;
                now--;
            }
        }

        // direction change
        set<int> s, s1;
        for(int i=0; i<n; i++){
            if(s.find(v[i].X.X) != s.end()){
                s1.insert(v[i].X.X);
            }
            s.insert(v[i].X.X);
        }

        for(int i=0; i<n; i++){
            if(s1.find(v[i].X.X) != s1.end()){
                v[i].X.Y *= -1;
            }
        }

        if(truth){
            cnt = 0;
            for(int i=0; i<n; i++){
                if(v[i].X.Y == 1){
                    cnt++;
                }
            }
            if(now - cnt < cnt){
                for(int i=0; i<n; i++){
                    v[i].X.Y *= -1;
                }
                ans.push_back(index);
            }
        }
    }

    cout << out1 << "\n";
    cout << (int)ans.size() << "\n";
    for(int i:ans) cout << i << " ";
    cout << "\n";
    return 0;
}