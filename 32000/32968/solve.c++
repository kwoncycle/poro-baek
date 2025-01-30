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

#define Z 88848

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int tt; cin >> tt;
    while(tt--){
        int n, l; cin >> n >> l;
        queue<int> v, v1, v2;
        for(int i=0; i<n; i++){
            int x; cin >> x;
            v.push(x);
        }
        int o = 1;
        while(o < n) o <<= 1;
        while(v.size() < o) v.push(Z);
        string cur = "A", end = "C";
        vector<string> ans;
        for(int u=1; u*2 <= o; u <<= 1){
            for(int i=0; i<n; i+=u*2){
                for(int t=0; t<u; t++){
                    int x = v.front();
                    v.pop();
                    v1.push(x);
                    if(x != Z) ans.push_back(cur + "B");
                }
                int id1 = 0, id2 = 0;
                while(id1 < u and id2 < u){
                    int x = v.front(), x1 = v1.front();
                    if(x < x1){
                        v.pop();
                        v2.push(x);
                        if(x != Z) ans.push_back(cur + end);
                        id1++;
                    }
                    else{
                        v1.pop();
                        v2.push(x1);
                        if(x1 != Z) ans.push_back("B" + end);
                        id2++;
                    }
                }
                while(id1 < u){
                    int x = v.front();
                    v.pop();
                    v2.push(x);
                    if(x != Z) ans.push_back(cur + end);
                    id1++;
                }
                while(id2 < u){
                    int x1 = v1.front();
                    v1.pop();
                    v2.push(x1);
                    if(x1 != Z) ans.push_back("B" + end);
                    id2++;
                }
            }
            for(int i=0; i<n; i++){
                v.push(v2.front()); v2.pop();
            }
            swap(cur, end);
        }
        cout << ans.size() << "\n";
        for(auto i:ans) cout << i << " "; cout << "\n";
    }
    return 0;
}