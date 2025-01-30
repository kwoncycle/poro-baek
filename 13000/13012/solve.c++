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
    string s; cin >> s;
    int n = s.size();
    vector<int> v(n);
    for(int i=0; i<n; i++) v[i] = i;
    vector<string> lcp;
    for(int i=0; i<n; i++){
        lcp.push_back(s.substr(i, n-i));
    }

    sort(v.begin(), v.end(), [&](int l, int r){
        return lcp[l] < lcp[r];
    });

    for(int i=0; i<n; i++){
        if(s[i] > 'a'){
            s[i]--;
            lcp.clear();
            vector<int> v1(n);
            for(int i1=0; i1<n; i1++) v1[i1] = i1;
            for(int i1=0; i1<n; i1++){
                lcp.push_back(s.substr(i1, n-i1));
            }
            sort(v1.begin(), v1.end(), [&](int l, int r){
                return lcp[l] < lcp[r];
            });

            //cout << s << "\n";
            //for(int j:v1) cout << j << " "; cout << "\n";
            s[i]++;

            int truth = 1;
            for(int i1=0; i1<n; i1++){
                if(v[i1] != v1[i1]) truth = 0;
            }
            if(truth){
                cout << "1\n"; return 0;
            }
        }
    }

    cout << "0\n";


    return 0;
}