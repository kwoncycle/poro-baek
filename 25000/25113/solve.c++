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

int n1;
pii v[1004];
int lca[1004][1004];
double DP0[1004][1004], DP1[1004][1004], dst[1004][1004];
double ans = 0x3f3f3f3f3f3fll;
int st, ed;


void divide(vector<int> idx, int depth){
    if(idx.size() <= 1) {
        if(!idx.empty()) {
            lca[idx[0]][idx[0]] = depth;
            DP0[idx[0]][idx[0]] = 0;
        }
        return;
    }
    if(depth%2 == 0){
        sort(all(idx), [&](int l, int r){
            return v[l].X < v[r].X;
        });
    }
    else{
        sort(all(idx), [&](int l, int r){
            return v[l].Y < v[r].Y;
        });
    }
    int n = idx.size();
    for(int i=0; i<n/2; i++){
        for(int j=n/2; j<n; j++){
            lca[idx[i]][idx[j]] = depth;
            lca[idx[j]][idx[i]] = depth;
        }
    }
    vector<int> v1;
    for(int j=n/2; j<n; j++){
        v1.push_back(idx.back()); idx.pop_back();
    }
    divide(idx, depth+1); divide(v1, depth+1);

    for(int i:idx){
        for(int j:v1){
            for(int i1:idx){
                if(lca[i][i1] != depth+1) continue;
                DP1[i][j] = min(DP1[i][j], DP0[i][i1] + dst[j][i1]);
            }
            for(int j1:v1){
                if(lca[j][j1] != depth+1) continue;
                DP1[j][i] = min(DP1[j][i], DP0[j][j1] + dst[i][j1]);
            }
        }
    }
    
    for(int i:idx){
        for(int j:v1){
            for(int j1:v1){
                if(lca[j][j1] != depth+1) continue;
                DP0[i][j] = min(DP0[i][j], DP1[i][j1] + DP0[j][j1]);
            }
            DP0[j][i] = DP0[i][j];
        }
    }

    if(depth == 0){
        for(int i:idx){
            for(int j:v1){
                if(ans > DP0[i][j]){
                    ans = DP0[i][j];
                    st = i, ed = j;
                }
            }
        }
    }
}

vector<int> path;
void pathfind(vector<int> idx, int depth, int s, int e){
    if(idx.size() <= 1) {
        return;
    }
    if(depth%2 == 0){
        sort(all(idx), [&](int l, int r){
            return v[l].X < v[r].X;
        });
    }
    else{
        sort(all(idx), [&](int l, int r){
            return v[l].Y < v[r].Y;
        });
    }
    int n = idx.size();
    vector<int> v1;
    for(int j=n/2; j<n; j++){
        v1.push_back(idx.back()); idx.pop_back();
    }
    int truth = 0;
    for(int i:idx){
        if(i == s) truth = 1;
    }
    if(!truth) v1.swap(idx);
    int i1 = -1, j1 = -1;
    for(int i:idx){
        for(int j:v1){
            if(lca[i][s] != depth+1 or lca[j][e] != depth+1) continue;
            
            if(abs(DP0[s][i] + dst[i][j] + DP0[j][e] - DP0[s][e]) < 0.000001){
                i1 = i; j1 = j; goto outt;
            }
        }
    }
    outt:
    pathfind(idx, depth+1, s, i1); 
    path.push_back(j1);
    pathfind(v1, depth+1, j1, e);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    cin >> n1;
    for(int i=1; i<=n1; i++){
        cin >> v[i].X >> v[i].Y;
    }
    for(int i=1; i<=n1; i++){
        for(int j=1; j<=n1; j++){
            pii p = v[i]-v[j];
            dst[i][j] = sqrt(p*p);
            DP0[i][j] = 0x3f3f3f3f3f3fll;
            DP1[i][j] = DP0[i][j];
        }
    }

    vector<int> T;
    for(int i=1; i<=n1; i++) T.push_back(i);
    divide(T, 0);
    cout << fixed << setprecision(15) << ans << "\n";
    pathfind(T, 0, st, ed);
    cout << st << " ";
    for(int i:path) cout << i << " "; cout << "\n";
    return 0;
}