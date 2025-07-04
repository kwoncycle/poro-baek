#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define pii pair<int,int>
#define pll pair<ll,ll>
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

const ll MX = 100005, M1 = 0x3f3f3f3f3f3f3fll;
int n;

ll v[MX];
pll p[MX];

struct solve{
    solve(){
        cin >> n;
        for(int i=1; i<=n; i++){
            cin >> v[i];
        }
        for(int i=1; i<=n; i++){
            cin >> p[i].X >> p[i].Y;
        }
        ll st = 0, ed = 0x3f3f3f3fll; // ed ddait
        while(st + 1 < ed){
            ll md = (st + ed) / 2;
            if(able(md)) st = md;
            else ed = md;
        }
        cout << st << "\n";
    }

    bool able(ll vol){
        vector<array<ll,2>> task;
        for(int i=1; i<=n; i++){
            task.push_back({p[i].X - p[i].Y - v[i]*vol, +i});
            task.push_back({p[i].X - p[i].Y + v[i]*vol, -i});
        }
        sort(all(task));
        set<pll> st;
        st.insert({-M1, -M1}); st.insert({M1, M1});
        for(auto [_, i]:task){
            if(i > 0){
                pll target = {p[i].X + p[i].Y - v[i]*vol, p[i].X + p[i].Y + v[i]*vol};
                auto t1 = st.lower_bound(target), t0 = t1;
                t0--;
                if((*t0).Y <= target.X and target.Y <= (*t1).X){
                    st.insert(target);
                }
                else{
                    return false;
                }
            }
            else{
                i = -i;
                pll target = {p[i].X + p[i].Y - v[i]*vol, p[i].X + p[i].Y + v[i]*vol};
                st.erase(target);
            }
        }
        return true;
    }
};




int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    solve S;
    return 0;
}