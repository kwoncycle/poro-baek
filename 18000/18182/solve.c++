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

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n; cin >> n;
    vector<int> v(n), v1;
    for(auto &i:v){
        cin >> i; v1.push_back(i);
    }

    sort(all(v1));
    v1.erase(unique(all(v1)), v1.end());

    for(auto &i:v){
        i = CNT_LOWER(v1, i);
    }

    vector<vector<int>> idx(n+3);
    for(int i=0; i<n; i++){
        idx[v[i]].push_back(i);
    }

    vector<int> cnt0(n+3), cnt1(n+3);
    set<int> st0, st1;
    for(int i=0; i<n; i++){
        st1.insert(v[i]);
        cnt1[v[i]]++;
    }

    vector<string> ans;

    for(int i=0; i<n; i++){
        cnt1[v[i]]--;
        if(!cnt1[v[i]]) st1.erase(v[i]);

        if(!st0.empty() and !st1.empty()){
            int b0 = *st0.begin(), e0 = *st0.rbegin();
            int b1 = *st1.begin(), e1 = *st1.rbegin();
            // mid = 1
            if(v[i] < e0 and v[i] < e1){
                if(*st0.upper_bound(v[i]) < e1){
                    ans.push_back("213");
                }
                if(e0 > *st1.upper_bound(v[i])){
                    ans.push_back("312");
                }
            }
            // mid 2
            if(b0 < v[i] and v[i] < e1) ans.push_back("123");
            if(e0 > v[i] and v[i] > b1) ans.push_back("321");

            //mid 3
            if(b0 < v[i] and b1 < v[i]){
                auto t0 = st0.lower_bound(v[i]); t0--;
                auto t1 = st1.lower_bound(v[i]); t1--;
                if(*t0 > b1) ans.push_back("231");
                if(b0 < *t1) ans.push_back("132");
            }
        }

        if(!cnt0[v[i]]) st0.insert(v[i]);
        cnt0[v[i]]++;
    }
    st0.clear(); st1.clear();
    for(int i=0; i<n; i++) st1.insert(i);
    st1.insert(-0x3f3f3f3f); st1.insert(0x3f3f3f3f);
    st0.insert(-0x3f3f3f3f); st0.insert(0x3f3f3f3f);

    for(int i=0; i<=n; i++){
        if(idx[i].size() >= 3) ans.push_back("111");
        for(int j:idx[i]){
            st1.erase(j);
        }

        if(idx[i].size() >= 2){
            // 1
            auto t = st1.begin(); t++; 
            int b1 = *t;
            auto t1 = st1.rbegin(); t1++;
            int e1 = *t1;
            if(idx[i][1] < e1) ans.push_back("112");
            if(b1 < idx[i][idx[i].size()-2]) ans.push_back("211");
            if(*st1.upper_bound(idx[i][0]) < idx[i].back()) ans.push_back("121");
        
            // 2
            t = st0.begin(); t++; 
            int b0 = *t;
            t1 = st0.rbegin(); t1++;
            int e0 = *t1;
            if(idx[i][1] < e0) ans.push_back("221");
            if(b0 < idx[i][idx[i].size()-2]) ans.push_back("122");
            if(*st0.upper_bound(idx[i][0]) < idx[i].back()) ans.push_back("212");
        }

        for(int j:idx[i]){
            st0.insert(j);
        }
    }

    sort(all(ans));
    ans.erase(unique(all(ans)), ans.end());
    for(auto &s:ans) cout << s << "\n";


    return 0;
}