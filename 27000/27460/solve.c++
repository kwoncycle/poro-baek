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
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr); //cout.tie(nullptr);
    int n; cin >> n;
    vector<int> deg(n+1);
    for(int i=0; i<n-1; i++){
        int a, b; cin >> a >> b;
        deg[a]++; deg[b]++;
    }
    vector<int> v(n);
    for(int i=0; i<n; i++) v[i] = i+1;
    sort(all(v), [&](int l, int r){
        return deg[l] < deg[r];
    });
    int i1 = 0;
    while(deg[v[i1]] == 1) i1++;
    int st = 0, ed = n;
    while(st + 1 < ed){
        int md = (st + ed + 1) / 2;
        vector<int> out;
        if(md <= i1){ // all leaf
            for(int i=0; i<md; i++) out.push_back(v[i]);
            for(int i=ed; i<i1; i++) out.push_back(v[i]);
            //if(out.size() == 1) out.push_back(v.back());
            //assert(out.size() > 1); 이게 씨발 왜 걸림?
        }
        else{
            if(i1 <= st){ // all not leaf
                for(int i=0; i<i1; i++) out.push_back(v[i]);
                for(int i=st; i<md; i++) out.push_back(v[i]);
            }
            else{
                for(int i=0; i<md; i++) out.push_back(v[i]);
            }
        }
        assert(out.size() > 1);
        cout << "? " << out.size() << " ";
        for(int i:out) cout << i << " ";
        cout << endl;
        string ans; cin >> ans;
        if(ans == "YES") ed = md;
        else st = md; 
    }
    cout << "! " << v[st] << endl;
    return 0;
}