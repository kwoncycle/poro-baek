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
 
double poww(double a,ll x){
	if(x==1) return a;
	if(x==0) return 1;
	double v = poww(a, x/2);
	v = v*v;
	if(x%2) v = v*a;
	return v;
}
// a^x (mod m)

int main(){
    int n, pi, k; cin >> n >> pi >> k; 
    double a = 0;
    for(int i=1; i<=n; i++){
        double x1 = poww((double)i/(double)n, k), x2 = poww((double)(i-1)/(double)n, k);
        x1 -= x2;
        if(i < pi) a += x1 * (double)pi;
        else a += x1 * (double)(i+1) / (double)2;
    }
    cout << fixed << setprecision(12) << a << "\n";
    return 0;
}