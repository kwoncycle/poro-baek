#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
const ll MOD = 761369052314887ll, A = 15571557, Ai = 693898941392298ll;

ll pA[250000], pAi[250000];
ll sm[250000];

string s;
int d, n;

ll getH(int i, int j){
    return (__int128)(MOD - (i-1>=0 ? sm[i-1] : 0) + sm[j]) * pAi[i] % MOD;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    pA[0] = 1; pAi[0] = 1;
    for(int i=1; i<250000; i++){
        pA[i] = (__int128)pA[i-1] * A % MOD;
        pAi[i] = (__int128)pAi[i-1] * Ai % MOD;
    }

    cin >> s >> d;
    n = s.size();
    for(int i=0; i<n; i++){
        sm[i] = ((i-1>=0 ? sm[i-1] : 0) + (__int128)pA[i]*s[i]) % MOD;
    }
    int id = 0, ans = 0;
    while(id < n){
        int mx = 0;
        for(int i=1; i<=d; i++){
            if(id + i >= n){
                mx = i; break;
            }
            if(s[id+i] != s[id]){
                mx = max(mx, i);
                continue;
            }
            int st = 1, ed = n-id-i + 1;
            while(st + 1 < ed){
                int md = (st + ed) / 2;
                if(getH(id, id+md-1) == getH(id+i, id+i+md-1)) st = md;
                else ed = md;
            }
            mx = max(mx, i + st);
        }
        ans++;
        id += mx;
    }
    cout << ans << "\n";
    return 0;
}