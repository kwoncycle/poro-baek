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


struct solve{
    int n, m;
    vector<int> v;
    solve(){
        cin >> n >> m;
        v.resize(m);
        for(int i=0; i<m; i++) cin >> v[i];
        int d = -1;
        for(int i=v[0]; i>=1; i--){
            v[0] -= i;
            if(rmv(v, -1, 0)){
                d = i;
            }
            v[0] += i;
            if(d >= 0) break;
        }
        if(d < 0){
            cout << "NO\n"; return;
        }

        vector<int> order(n, -1);
        for(int i=0; i<d; i++) order[n-1-i] = 0;
        v[0] -= d;
        int cur = -1, cnt = 0;
        for(int i=0; i<n-d; i++){
            for(int j=0; j<m; j++){
                if(v[j] == 0) continue;
                v[j]--;
                int ncur = cur, ncnt = cnt;
                if(ncur == -1 or ncnt == 0){
                    ncur = j; ncnt = 1; 
                }
                else if(ncur == j){
                    ncnt++;
                }
                else{
                    if(ncnt > 0) ncnt--;
                }
                if(rmv(v, ncur, ncnt)){
                    cur = ncur; cnt = ncnt;
                    order[i] = j; break;
                }
                v[j]++;
            }
        }
        cout << "YES\n";
        cout << d << "\n";
        for(int i=0; i<n; i++) cout << order[i]+1 << "\n";
    }
    bool rmv(vector<int> &cur, int now, int cnt){
        if(now == -1){
            int mx = *max_element(cur.begin(), cur.end());
            int sm = 0;
            for(int i=0; i<m; i++) sm += cur[i];
            if(sm % 2 or mx*2 > sm) return 0;
            return 1;
        }
        else{
            cur[now]+=cnt;
            int mx = *max_element(cur.begin(), cur.end());
            int sm = 0;
            for(int i=0; i<m; i++) sm += cur[i];
            cur[now]-=cnt;
            if(sm % 2 or mx*2 > sm) return 0;
            return 1;
        }
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    solve ss;
    return 0;
}