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

ll ccw(pll &p1, pll &p2, pll &p3){
    ll o = (p2.X - p1.X) * (p3.Y - p2.Y) - (p2.Y - p1.Y) * (p3.X - p2.X);
    if(o > 0) return -1;
    if(o < 0) return 1;
    return 0;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    ll n; cin >> n;
    vector<pll> v(n);

    for(ll i=0; i<n; i++) cin >> v[i].X >> v[i].Y;
    ll ttl = 0;
    for(ll i=0; i<n; i++){
        vector<ll> idx;
        for(ll j=0; j<n; j++){
            if(i-j) idx.push_back(j);
        }
        sort(idx.begin(), idx.end(), [&](ll x, ll y){
            if(v[x].X == v[i].X and v[x].Y > v[i].Y) return 1;
            if(v[y].X == v[i].X and v[y].Y > v[i].Y) return 0;
            if(v[x].X == v[i].X){
                if(v[y].X > v[i].X) return 0;
                else return 1;
            }
            if(v[y].X == v[i].X){
                if(v[x].X > v[i].X) return 1;
                else return 0;
            }
            if(v[x].X - v[i].X > 0 and v[y].X - v[i].X <= 0){
                return 1;
            }

            if(v[x].X - v[i].X <= 0 and v[y].X - v[i].X > 0){
                return 0;
            }

            if ((v[x].Y - v[i].Y)*(v[y].X - v[i].X) > (v[y].Y - v[i].Y)*(v[x].X - v[i].X)) return 1;
            else return 0;
        });
        /*
        for(ll j:idx){
            cout << v[j].X - v[i].X << " " << v[j].Y - v[i].Y << "\n";
        }
        cout << "\n";*/
        ll u = 0;
        ll i1 = 0;
        for(ll j=0; j<n-1; j++){
            while(ccw(v[idx[j]], v[i], v[idx[i1]]) <= 0) {
                i1++;
                if(i1 >= n-1) i1 -= n-1;
                if(i1 == j) {
                    break;
                }
            }
            i1--;
            if(i1 < 0) i1 += n-1;
            //cout << j << " " << i1 << "ED\n";
            ll left = ((i1-j+2*n-2)%(n-1)), right = ((2*n-2 - (i1-j+1))%(n-1));
            if(i1 == j){
                if(ccw(v[idx[j]], v[i], v[idx[(j+1)%(n-1)]]) < 0){
                    left = n-2; right = 0;
                }
                else{
                    left = 0; right = n-2;
                }
            }
            //cout << left << " " << right << "\n";
            if(right >= 2){
                u -= (right)*(right-1)/2;
            }

            if(i1 == j) {
                i1++; if(i1 >= n-1) i1 -= n-1;
                continue;
            }
            //cout << u << " ";
            //cout << "ADDED " << oo;
            u += left * right;
            //cout << " and " << u << "\n";
        }


        //cout << u << " final\n";
        u /= 3;
        ttl += u;
        //cout << u << "\n";
        /*
        for(ll j:idx){
            cout << v[j].X << " " << v[j].Y << "\n";
        }
        break;*/
    }

    cout << (n*(n-1)*(n-2)*(n-3)/24 - ttl)*2 << "\n";

    //cout << ccw({0,0}, {0,1}, {-1,1}) << "\n";
    return 0;
}