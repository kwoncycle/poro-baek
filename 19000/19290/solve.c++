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

void change(int a, int b, vector<pii> &edge){
    for(auto &[i,j] : edge){
        if(i == a) i = b;
        if(j == a) j = b;
    }
}

void printans(vector<pii> &edge){
    cout << edge.size() + 1 << "\n";
    for(auto [i,j]:edge) cout << i << " " << j << "\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n; cin >> n;
    vector<int> v(n+1);
    for(int i=1; i<=n; i++) cin >> v[i];
    vector<int> deg(n+1);
    vector<pii> edge(n-1);
    ll ttl = n;
    for(auto &[i, j]:edge){
        cin >> i >> j;
        deg[i]++; deg[j]++;
        ttl ^= i; ttl ^= j;
    }

    if(ttl == 0){
        printans(edge);
        return 0;
    }

    vector<int> ch0, ch1;
    for(int i=1; i<=n; i++){
        if(v[i]){
            if(deg[i] % 2 == 0) ch0.push_back(i);
            else ch1.push_back(i);
        }
    }

    if(ch1.size() >= 3){
        int a = ch1[0], b = ch1[1], c = ch1[2];
        if((a^ttl) == b){
            change(a, a^ttl^(1<<24), edge);
            change(c, c^(1<<24), edge);
        }
        else{
            change(a, a^ttl^(1<<24), edge);
            change(b, b^(1<<24), edge);
        }
        printans(edge); return 0;
    }

    else if(ch1.size() == 2){
        int a = ch1[0], b = ch1[1];
        if((a^ttl) == b){
            cout << "-1\n";
        }
        else{
            change(a, a^ttl^(1<<24), edge);
            change(b, b^(1<<24), edge);
            printans(edge);
        }
        return 0;
    }

    else if(ch1.size() == 1){
        int a = ch1[0];
        if(n < (a^ttl)){
            change(a, a^ttl, edge);
            printans(edge);
        }
        else if((a^ttl) == 0){
            cout << "-1\n";
        }
        else{
            if(v[a^ttl] == 1){
                assert(deg[a^ttl] % 2 == 0);
                change(a^ttl, a^ttl^(1<<24), edge);
                change(a, a^ttl, edge);
                printans(edge);
            }
            else{
                cout << "-1\n";
            }
        }
    }

    else if(ch1.empty()){
        cout << "-1\n";
    }

    return 0;
}