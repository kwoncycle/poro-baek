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
    int n, k; cin >> n >> k;
    vector<int> v(n);
    for(int i=0; i<n; i++){
        cin >> v[i]; v[i]--;
    }

    int st = -1, ed = k; // ed able
    while(st + 1 < ed){
        int md = (st + ed) / 2;
        int sz = k-md;
        vector<int> cnt(n, 0);
        set<int> s;
        int nm2 = 0;
        for(int i=0; i<sz; i++){
            cnt[v[i]]++;
            s.insert(v[i]);
            if(cnt[v[i]] == 2) nm2++;
        }
        int able = 0;
        for(int i=0; i<n; i++){
            if(*s.rbegin() - *s.begin() <= k-1 and nm2 == 0){
                able = 1; break;
            }
            cnt[v[i]]--;
            if(cnt[v[i]] == 1) nm2--;
            else if(cnt[v[i]] == 0) s.erase(v[i]);

            cnt[v[(i+sz)%n]]++;
            if(cnt[v[(i+sz)%n]] == 2) nm2++;
            else if(cnt[v[(i+sz)%n]] == 1) s.insert(v[(i+sz)%n]);
        }
        if(able) ed = md;
        else st = md;
    }

    cout << ed << "\n";
    return 0;
}