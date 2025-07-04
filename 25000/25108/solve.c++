#include <bits/stdc++.h>
using namespace std;

const int MX = 10000005, MOD = 1000003;
int p[MX], phi[MX], smphi[MX], DP0[MX], DP1[MX]; // 0[i]: i*i, 1[i] = i*(i-1)

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    p[1] = 1; phi[1] = 1; DP0[1] = 6; DP1[1] = 1;
    for(int i=2; i<=MX-2; i++){
        if(!p[i]){
            for(int j=i; j<=MX-2; j+=i){
                p[j] = i;
            }
        }
        if(p[i/p[i]] == p[i]) phi[i] = phi[i/p[i]] * p[i];
        else phi[i] = phi[i/p[i]] * (p[i] - 1);
    }
    for(int i=1; i<=MX-2; i++){
        smphi[i] = (phi[i] + smphi[i-1]) % MOD;
    }
    for(int i=2; i<=MX-2; i++){
        DP1[i] = (DP0[i-1]*2 - DP1[i-1] + 1ll*i*(phi[i] - (1-i%2)*phi[i/2])) % MOD;
        DP0[i] = (DP1[i]*2 - DP0[i-1] + 4*(smphi[i] - smphi[i/2])) % MOD;
    }
    int qq; cin >> qq;
    while(qq--){
        int n; cin >> n; n--;
        if(DP0[n] < 0) DP0[n] += MOD;
        cout << DP0[n] << "\n";
    }
    return 0;
}