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

const double eps = 0.00000001;


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int tt; cin >> tt;
    for(int tc=1; tc<=tt; tc++){
        int n; cin >> n;
        vector<vector<double>> v(n, vector<double>(4));
        for(int i=0; i<n; i++){
            for(int j=0; j<4; j++) cin >> v[i][j];
        }

        double st = 0, ed = 10000005; // ed able st boom
        while(st + 0.0000001 < ed){
            double md = (st + ed) / 2.0;
            vector<double> range(8, 0x3f3f3f3f3f3f3f3fll);
            for(int i=0; i<n; i++){
                double u = md*v[i][3];
                for(int j=0; j<8; j++){
                    int j1 = j, id = 0;
                    double val = u;
                    for(; id<3; j1 /= 2, id++){
                        int o = 2*(j1&1)-1; // 1 + 0 -
                        val += (double)o*v[i][id];
                    }
                    range[j] = min(range[j], val);
                }
            }
            swap(range[3], range[4]);
            //cout << md << "\n";
            //for(int i=0; i<8; i++) cout << range[i] << "ramge\n";
            int truth = 1;
            for(int i=0; i<4; i++){
                if(-range[i] > eps + range[7-i]){
                    truth = 0; break;
                }
            }

            if(truth){
                double r2 = range[6]+range[5]+range[4], r1 = -(range[1]+range[2]+range[3]);
                double r3 = -range[0], r4 = range[7];
                if(r4 + eps < r1 or r2 + eps < r3) truth = 0;
            }
            //cout << truth << "\n";
            if(truth) ed = md;
            else st = md;
        }
        cout << "Case #" << tc << ": ";
        cout << fixed << setprecision(12) << ed << "\n";
    }
    return 0;
}