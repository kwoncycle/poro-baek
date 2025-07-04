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

string s[4200];
int selecti[4200][4200];
vector<int> selected[4200];
int v[4200][4200][4];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    srand(time(0));
    int n, m, k;
    cin >> n >> m >> k;
    for(int i=0; i<n; i++) cin >> s[i];
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(s[i][j] == 'G') s[i][j] = 'B';
            else if(s[i][j] == 'T') s[i][j] = 'D';
        }
    }
    int mx = min(4200, 42000/n);
    for(int i=0; i<mx; i++){
        for(int j=0; j<n; j++){
            selecti[i][j] = rand() % 2;
            if(selecti[i][j]) selected[i].push_back(1);
        }
        for(int i1=0; i1<n; i1++){
            if(selecti[i][i1])
            for(int j=0; j<m; j++){
                v[i][j][s[i1][j]-'A']++;
            }
        }
    }
    vector<int> candidate;
    for(int i=0; i<n; i++){
        int truth = 1;
        for(int i1=0; i1<mx; i1++){
            int samesz = m * selected[i1].size();
            for(int j=0; j<m; j++){
                samesz -= v[i1][j][s[i][j]-'A'];
            }
            if(samesz != k * (selected[i1].size() - selecti[i1][i])){
                truth = 0; break;
            }
        }
        if(truth){
            candidate.push_back(i);
            //cout << i+1 << "\n"; return 0;
        }
    }
    for(int id:candidate){
        int truth = 1;
        for(int i=0; i<n; i++){
            if(id == i) continue;
            int cnt = 0;
            for(int j=0; j<m; j++){
                if(s[id][j] != s[i][j]) cnt++;
            }
            if(cnt != k){
                truth = 0; break;
            }
        }
        if(truth) {
            cout << id + 1 << "\n"; return 0;
        }
    }
    assert(false);
    return 0;
}