#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define pii pair<int,int>
#define pll pair<ll,ll>
#define X first
#define Y second
#define CNT_LOWER(v,n) (int)(lower_bound((v).begin(),(v).end(),(n))-(v).begin())
#define CNT_UPPER(v,n) (int)(upper_bound((v).begin(),(v).end(),(n))-(v).begin())
 
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
    vector<pii> v(n);
    vector<vector<int>> sort_idx(n);
    for(int i=0; i<n; i++){
        cin >> v[i].X >> v[i].Y;
    }
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(i-j) sort_idx[i].push_back(j);
        }
        sort(sort_idx[i].begin(), sort_idx[i].end(), [&](int l, int r){
            return (v[l]>v[i]) == (v[r]>v[i]) ? ((v[l]-v[i])/(v[r]-v[i])>0) : v[l]<v[r];
        });
    }


    int cnt = 0;
    for(int i=0; i<n; i++){
        for(int j=i+1; j<n; j++){
            int DEBUG = 0;
            //if(i == 0 and j == 2) DEBUG = 1;
            //line i-j
            int loc = 0;
            while(sort_idx[j][loc] != i) loc++;
            int l1 = (loc+1) % (n-1);
            while((v[i]-v[j])/(v[sort_idx[j][l1]]-v[j]) > 0){
                l1 = (l1 + 1); if(l1 >= n-1) l1 -= n-1;
            }
            if((loc+1)%(n-1) != l1){
                loc = (loc + 1) % (n-1);
                pii mx = v[sort_idx[j][loc]]; cnt++;
                while((loc + 1) % (n-1) != l1){
                    loc = (loc + 1) % (n-1);
                    int id = sort_idx[j][loc];
                    if((v[id]-v[i])/(mx-v[i]) > 0) continue;
                    mx = v[id];
                    cnt++;
                    // makr1[id] = i1, mark2[id] = ?
                }
            }

            loc = 0;
            while(sort_idx[i][loc] != j) loc++;
            l1 = (loc+1) % (n-1);
            while((v[j]-v[i])/(v[sort_idx[i][l1]]-v[i]) > 0){
                l1 = (l1 + 1); if(l1 >= n-1) l1 -= n-1;
            }
            if((loc+1)%(n-1) != l1){
                loc = (loc + 1) % (n-1);
                pii mx = v[sort_idx[i][loc]]; cnt++;
                while((loc + 1) % (n-1) != l1){
                    loc = (loc + 1) % (n-1);
                    int id = sort_idx[i][loc];
                    if((v[id]-v[j])/(mx-v[j]) > 0) continue;
                    mx = v[id];
                    cnt++;
                    // makr1[id] = i1, mark2[id] = ?
                }
            }
        }
    }

    cout << n*(n-1)*(n-2)/6 - cnt/3 << "\n";
    return 0;
}