#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define pii pair<ll,ll>
#define pll pair<ll,ll>
#define X first
#define Y second
#define CNT_LOWER(v,n) (ll)(lower_bound((v).begin(),(v).end(),(n))-(v).begin())
#define CNT_UPPER(v,n) (ll)(upper_bound((v).begin(),(v).end(),(n))-(v).begin())
 
// CNT_LOWER: number of element in v smaller than n
// CNT_UPPER: number of element in v smaller or same than n

#define LINE array<pii, 2>
// LINE: l[0] + kl[1]

pii operator + (pii l, pii r){return {l.X+r.X, l.Y+r.Y};};
pii operator - (pii l, pii r){return {l.X-r.X, l.Y-r.Y};};
ll operator * (pii l, pii r){return (ll)l.X*r.X + (ll)l.Y*r.Y;};
ll operator / (pii l, pii r){return (ll)l.X*r.Y - (ll)l.Y*r.X;};

void solve1(){
    ll tt; cin >> tt;
    while(tt--){
        ll n; cin >> n;
        string s; cin >> s;
        vector<ll> v1, v2;
        vector<ll> floc(3*n), eloc(3*n);
        for(ll i=0; i<3*n; i++){
            if(s[i] == '(') v1.push_back(i);
            else if(s[i] == '|'){
                ll i1 = v1.back();
                floc[i] = i1;
                v1.pop_back();
                v2.push_back(i);
            }
            else{
                ll i2 = v2.back();
                eloc[i2] = i;
                v2.pop_back();
            }
        }
        vector<pii> graph(3*n, {-1, -1});
        vector<ll> roots;
        for(ll i=0; i<3*n; i++){
            if(s[i] == '|'){
                ll i1 = floc[i], i2 = eloc[i];
                if(i1-1 >= 0 and s[i1-1] == '|'){
                    graph[i1-1].Y = i;
                }
                else if(i2+1 < 3*n and s[i2+1] == '|'){
                    graph[i2+1].X = i;
                }
                else{
                    roots.push_back(i);
                }
            }
        }
        vector<ll> visitorder;
        for(ll i:roots){
            queue<ll> q;
            q.push(i);
            while(!q.empty()){
                ll o = q.front(); q.pop();
                visitorder.push_back(o);
                if(graph[o].X >= 0) q.push(graph[o].X);
                if(graph[o].Y >= 0) q.push(graph[o].Y);
            }
            ll o = visitorder.back();
            assert(graph[o].X == -1 and graph[o].Y == -1);
            graph[o] = {-100, -100};
        }
        vector<ll> ans(n);
        for(ll i=0; i<n; i++){
            ll o = 0;
            if(graph[visitorder[i]].X == -100) o = 4;
            else{
                if(graph[visitorder[i]].X >= 0) o += 1;
                if(graph[visitorder[i]].Y >= 0) o += 2;
            }
            ans[i] = o;
            //cout << ans[i] << " ";
        }
        ll u = 0;
        for(ll i=0; i<n; i++){
            u *= 5;
            u += ans[i];
        }
        assert(0 <= u and u <= 2000000000000000000ll);
        cout << u << "\n";
    }
}


void solve2(){
    ll tt; cin >> tt;
    while(tt--){
        ll n; cin >> n;
        ll s; cin >> s;
        vector<ll> a(n);
        for(ll i=n-1; i>=0; i--){
            a[i] = s % 5; s /= 5;
        }

        vector<pii> graph(n, {-1, -1});
        queue<pii> bk;
        vector<ll> roots(1, 0);
        for(ll i=0; i<n-1; i++){
            if(a[i] == 4) roots.push_back(i+1);
        }
        for(ll i=0; i<n; i++){
            if(!bk.empty()){
                pii o = bk.front(); bk.pop();
                if(o.Y == 0) graph[o.X].X = i;
                else graph[o.X].Y = i;
            }
            if(a[i] != 4 and (a[i]&1)){
                bk.push({i, 0});
            }
            if(a[i] != 4 and (a[i]&2)){
                bk.push({i, 1});
            }
        }
        vector<string> ans(n);
        for(ll i=n-1; i>=0; i--){
            if(graph[i].X == -1 and graph[i].Y == -1){
                ans[i] = "(|)"; continue;
            }
            ll i1 = graph[i].X, i2 = graph[i].Y;
            string now = "(";
            if(i1 >= 0) now += ans[i1];
            now += "|";
            if(i2 >= 0) now += ans[i2];
            now += ")";
            ans[i] = now;
        }
        string total;
        for(ll i:roots) total += ans[i];
        cout << total << "\n";
        //for(ll i=0; i<n; i++) cout << graph[i].X << " " << graph[i].Y << " " << i << "\n";
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    string task; cin >> task;
    if(task == "encode"){
        solve1();
    }
    else{
        solve2();
    }
    return 0;
}