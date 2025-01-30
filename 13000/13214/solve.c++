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
    vector<int> A(n+1), B(n+1), per(n+1);
    for(int i=1; i<=n; i++) cin >> A[i];
    for(int i=1; i<=n; i++) cin >> B[i];
    for(int i=1; i<=n; i++){
        per[A[i]] = i;
    }
    for(int i=1; i<=n; i++) B[i] = per[B[i]];
    fill(A.begin(), A.end(), 0);

    int cnt = 0;
    for(int i=1; i<=n; i++){
        if(A[i] == 0){
            int i1 = i, u = 0;
            A[i1] = 1; u++;
            while(B[i1] != i){
                i1 = B[i1];
                A[i1] = 1; u++;
            }
            cnt += u-1;
        }
    }
    cout << cnt << "\n";
    return 0;
}