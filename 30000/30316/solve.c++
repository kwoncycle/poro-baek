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

int par[1000005], deg[1000005], depth[1000005];

int main(){
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr); cout.tie(nullptr);
    int n, k; cin >> n >> k;
    depth[1] = 0;
    for(int i=2; i<=n; i++) {
        cin >> par[i]; par[i]++;
        depth[i] = depth[par[i]] + 1;
        deg[par[i]]++;
    }
    par[0] = -1;

    set<array<int,3>> st;
    for(int i=1; i<=n; i++){
        if(deg[i] == 0){
            int i1 = i;
            i1 = par[i1];
            while(i1 != 0 and deg[i1] == 1) {
                i1 = par[i1];
            }
            if(i1 == 0){
                cout << "1\n"; return 0;
            }
            st.insert({depth[i]-depth[i1], i, i1});
        }
    }

    //for(auto [i,j,k]:st) cout << i << " " << j << " " << k << "\n";

    while(k){
        while(true){
            auto U = st.begin();
            if(deg[(*U)[2]] == 1){
                int i1 = (*U)[2];
                while(i1 != 0 and deg[i1] == 1) i1 = par[i1];
                if(i1 == 0){
                    cout << "1\n"; return 0;
                }
                int i = (*U)[1];
                array<int,3> nw = {depth[i]-depth[i1], i, i1};
                st.erase(U);
                st.insert(nw);
            }
            else break;
        }
        auto U = st.begin();
        int i = (*U)[1], i1 = (*U)[2];
        while(i != i1 and k){
            k--;
            deg[par[i]]--;
            i = par[i];
        }
        if(i == i1) st.erase(U);
        else break;
    }

    cout << st.size() << "\n";




    return 0;
}