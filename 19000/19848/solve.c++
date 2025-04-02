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

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    string s; cin >> s;
    vector<array<int, 3>> v;
    int n = s.size();
    for(int i=0; i<n; i++){
        int i1 = i;
        while(i1 < n and s[i1] == s[i]) i1++;
        v.push_back({s[i], i, i1-1});
        i = i1 - 1;
    }

    vector<pii> ans;

    while(!v.empty()){
        if(v.size() == 2){
            ans.push_back({v[0][1], v[1][2]}); v.pop_back(); v.pop_back();
            break;
        }

        int sz = v.size();
        auto t1 = v[sz-3];
        auto t2 = v[sz-2];
        auto t3 = v[sz-1];
        for(int i=0;i<3;i++) v.pop_back();
        //  ... 1 2 3
        int sz1 = t1[2] - t1[1] + 1, sz2 = t2[2] - t2[1] + 1, sz3 = t3[2] - t3[1] + 1;

        if(sz1 == sz2){
            ans.push_back({t1[1], t2[2]});
            t3[1] -= sz1*2; t3[2] -= sz1*2;
            v.push_back(t3);
            continue;
        }

        if(sz1 > sz2){
            ans.push_back({t2[2]-sz2*2+1, t2[2]});
            t1[2] = t1[2] - sz2 + sz3;
            v.push_back(t1);
            continue;
        }

        if(sz1 < sz2){
            ans.push_back({t1[1], t1[1] + sz1*2 - 1});
            t2[1] += sz1;
            t2[1] -= sz1*2; t2[2] -= sz1*2; t3[1] -= sz1*2; t3[2] -= sz1*2;
            if(!v.empty()){
                v.back()[2] = t2[2];
            }
            else v.push_back(t2);
            v.push_back(t3);
            continue;
        }




        // if(t1[2] - t1[1] == t2[2] - t2[1]){
        //     ans.push_back({t2[1], t1[2]});
        // }
        // else if(t2[2]-t2[1] > t1[2]-t1[1]){
        //     array<int, 3> t3 = {t2[0], t2[1], t2[1] + sz2-sz1 - 1};
        //     ans.push_back({t3[2]+1, t1[2]});
        //     if(v.back()[0] == t3[0]) {v.back()[2] = t3[2]; assert(false);}
        //     else v.push_back(t3);
        // }
        // else{
        //     array<int, 3> t3 = {t1[0], t2[1], t2[1] + sz1-sz2 - 1};
        //     ans.push_back({t2[1], t2[1] + sz2*2 - 1});
        //     if(v.back()[0] == t3[0]) v.back()[2] = t3[2];
        //     else {v.push_back(t3); assert(false);}
        // }
    }

    cout << ans.size() << "\n";
    for(auto [i,j]:ans) cout << i+1 << " " << j+1 << "\n";


    return 0;
}