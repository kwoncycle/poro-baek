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
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr); cout.tie(nullptr);
    int n; cin >> n;
    vector<pii> v(n);
    for(int i=0; i<n; i++) cin >> v[i].X >> v[i].Y;

    vector<vector<int>> sort_idx(n);
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(i-j) sort_idx[i].push_back(j);
        }
        sort(sort_idx[i].begin(), sort_idx[i].end(), [&](int l, int r){
            return (v[l] > v[i]) == (v[r] > v[i]) ? (v[l]-v[i])/(v[r]-v[i]) > 0 : v[l] < v[r];
        });
    }
    ll cnt1 = 0, cnt2 = 0;
    for(int i=0; i<n; i++){
        for(int j=i+1; j<n; j++){
            
            vector<int> left, right;
            int id = 0;
            while(sort_idx[i][id] != j) id++;
            int loc = (id+1) % (n-1);
            while((v[j] - v[i]) / (v[ sort_idx[i][loc] ] - v[i]) > 0){
                loc = (loc + 1) % (n-1);   
            }
            {   
                int pv = -1;
                for(int i1 = (id+1)%(n-1); i1 != loc; i1 = (i1+1)%(n-1)){
                    int id = sort_idx[i][i1];
                    if(pv == -1) pv = id;
                    if((v[pv] - v[j])/(v[id] - v[j]) >= 0){
                        left.push_back(id);
                        pv = id;
                    }
                }
            }

            id = 0;
            while(sort_idx[j][id] != i) id++;
            loc = (id+1) % (n-1);
            while((v[i] - v[j]) / (v[ sort_idx[j][loc] ] - v[j]) > 0){
                loc = (loc + 1) % (n-1);   
            }
            {   
                int pv = -1;
                for(int i1 = (id+1)%(n-1); i1 != loc; i1 = (i1+1)%(n-1)){
                    int id = sort_idx[j][i1];
                    if(pv == -1) pv = id;
                    if((v[pv] - v[i])/(v[id] - v[i]) >= 0){
                        right.push_back(id);
                        pv = id;
                    }
                }
            }
            
            int nl = left.size(), nr = right.size();
            int c1 = 0;
            if(nl == 0 or nr == 0) continue;
            for(int i1=0, i2 = -1, i3 = -1; i1 < nl; i1++){
                while(i3+1 < nr and (v[left[i1]] - v[j]) / (v[right[i3+1]] - v[j]) > 0) i3++;
                while(i2+1 < nr and (v[left[i1]] - v[i]) / (v[right[i2+1]] - v[i]) > 0) i2++;
                c1 += max(0, i3-i2);
            }
            
            int c2 = nl*nr - c1;
            //cout << v[i].X << "," << v[i].Y << " " << v[j].X << "," << v[j].Y << " " << ":\n";
            //cout << "LEFT: "; for(int k:left) cout << v[k].X << "," << v[k].Y << " "; cout << "\n";
            //cout << "RIGHT: "; for(int k:right) cout << v[k].X << "," << v[k].Y << " "; cout << "\n";
            //cout << c1 << " " << c2 << "\n";
            cnt1 += c1; cnt2 += c2;
        }
    }

    //cout << cnt1 << " " << cnt2 << "\n";
    cout << cnt1/2 + cnt2 << "\n";
    return 0;
}