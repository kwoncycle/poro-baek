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
    vector<ll> v(n);
    for(int i=0; i<n; i++) cin >> v[i];
    vector<ll> sm(n-1);
    for(int i=0; i<n-1; i++){
        sm[i] -= v[i];
        v[i+1] -= v[i]; v[i] -= v[i];
    }
    if(n%2 == 1){
        for(int i=0; i<n-1; i+=2){
            sm[i] += v[n-1];
            v[i] += v[n-1]; v[i+1] += v[n-1];
        }
        cout << "0\n";
        cout << n-1 << "\n";
        for(int i=0; i<n-1; i++) cout << i+1 << " " << sm[i] << "\n"; 
        return 0;
    }

    else{
        if(n==2){
            cout << abs(v[1]) << "\n";
            cout << "0\n";
            return 0;
        }
        int fliped = 1;
        if(v[n-1] < 0){
            fliped = -1; v[n-1] = -v[n-1];
        }
        ll A = n/2, B = n-1-A;
        //A B A B A
        //-3A + 2B >= 0
        ll o = (__int128)v[n-1]*B/A; //  7 7 7 7 -5 -5 -6 -6 -6
        ll cnt = (__int128)v[n-1]*B%A;
        for(int i=0; i<n-2; i++){
            if(i%2 == 0){
                ll u = o - v[i];
                if(cnt) u++, cnt--;
                v[i] += u;
                v[i+1] += u;
                sm[i] += u*fliped;
            }
            else{
                ll u = v[n-1] - v[i];
                v[i] += u;
                v[i+1] += u;
                sm[i] += u*fliped;
            }
        }
        cout << v[n-1] - o << "\n";
        cout << n-1 << "\n";
        for(int i=0; i<n-1; i++) cout << i+1 << " " << sm[i] << "\n"; 
        return 0;
    }
    return 0;
}