#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define pii pair<int,int>
#define pll pair<ll,ll>
#define pil pair<int,ll>
#define pli pair<ll,int>
#define X first
#define Y second
#define GETVECTOR(n) for(int i=0; i< (n); i++) scanf("%d ",&inp[i]);
#define CNT_LOWER(v,n) (int)(lower_bound((v).begin(),(v).end(),(n))-(v).begin())
#define CNT_UPPER(v,n) (int)(upper_bound((v).begin(),(v).end(),(n))-(v).begin())
 
// CNT_LOWER: number of element in v smaller than n
// CNT_UPPER: number of element in v smaller or same than n

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    __int128 n; ll n1; cin >> n1; n = n1;
    vector<__int128> v(n+1);
    for(int i=1; i<=n; i++){
		ll o; cin >> o; v[i] = o;
		//cin >> v[i];
	}
	__int128 sm = 0;
	for(int i=1; i<=n; i++){
		sm += v[i];
	}
	if(sm == 1){
		for(int i=1; i<=n; i++){
			if(v[i]) {
				if(i == 1) cout << 1 << "\n";
				else cout << i-1 << "\n";
			}
		}
		return 0;
	}


    __int128 mn = 1, mx = n + 55;
    while(mn+1<mx){
		__int128 md = (mn + mx)/2;
		vector<__int128> v1(md+1, 0);
		for(__int128 i=1; i<=min(n, md-1); i++){
			v1[i] = v[i];
		}
		for(__int128 i=min(n,md-1) + 1; i<=n; i++){
			v1[1] += v[i];
 		}

		v1[md] = -1;
		__int128 ttl = 0;
		for(__int128 i=md; i>=2; i--){
			if(v1[i] + ttl < 0){
				ttl += ttl + v1[i];
				v1[i] = 0;
			}
			else{
				v1[1] += ttl + v1[i];
				v1[i] = 0;
			}
			if(ttl < -(1ll<<60)) break;
		}
		if(ttl + v1[1] >= 0){
			mn = md;
		}
		else mx = md;
		//ll ttl = 0;
    }
	cout << (ll)mn-1 << "\n";
    return 0;
}