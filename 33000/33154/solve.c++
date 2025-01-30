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

ll m;
vector<ll> fibo(62);
vector<ll> fibocrs(62);
unordered_map<ll, vector<int>> mp[2];

vector<int> v[2];
void JG1(int depth, int num, ll sm){
    if(depth == 9 or depth == 10){
        if(mp[num].find(sm) == mp[num].end()){
            mp[num][sm] = v[num];
        }
    }
    if(depth == 10){
        return;
    }

    if(num == 0){
        int u = 0;
        if(!v[num].empty()) u = v[num].back() + 2;
        for(int i=u; i<=28; i++){
            v[num].push_back(i);
            JG1(depth + 1, num, (sm + fibocrs[i])%m);
            v[num].pop_back();
        }
    }

    else{
        int u = 30;
        if(!v[num].empty()) u = v[num].back() + 2;
        for(int i=u; i<=59; i++){
            v[num].push_back(i);
            JG1(depth + 1, num, (sm + fibocrs[i])%m);
            v[num].pop_back();
        }
    }
}


int main(){
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr); cout.tie(nullptr);

    cin >> m;
    //cout << m << "\n";
    fibo[0] = 1; fibo[1] = 1;
    for(ll i=2; i<=60; i++) fibo[i] = (fibo[i-1] + fibo[i-2]) % m;
    for(ll i=0; i<=59; i++) fibocrs[i] = (__int128)fibo[i]*fibo[59-i]%m;
    mp[0].clear(); mp[1].clear();
    v[0].push_back(0);
    JG1(1, 0, fibocrs[0]);
    JG1(0, 1, 0);
    

    int truth = 0;
    for(auto &[i, vi]:mp[0]){
        for(ll t=0; t<=5; t++){
            ll o = (- i - t*fibo[59])%m;
            if(o < 0) o += m;
            if(mp[1].find(o) != mp[1].end()){
                vector<int> bridge;
                for(int t:mp[0][i]) bridge.push_back(t);
                for(int t:mp[1][o]) bridge.push_back(t);
                
                string ans[60];
                for(int j=0; j<60; j++) {
                    ans[j] = ".#.";
                    for(int u=0; u<57; u++) ans[j] += '#';
                }
                
                for(int t:bridge) ans[t][1] = '.';
                for(int j=3; j<60; j++) ans[59][j] = '.';

                for(int j=0; j<60; j++) ans[0][j] = '.';
                for(int j=0; j<t; j++){
                    for(int k=0; k<60; k++) ans[k][4+2*j] = '.';
                }

                cout << "60\n";
                for(int j=0; j<60; j++) cout << ans[j] << "\n";
                return 0;
            }
        }
    }

    assert(false);

    return 0;
}