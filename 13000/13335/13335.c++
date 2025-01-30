#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <stack>
#include <string.h>
#include <queue>
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
typedef struct p3{
	int a; int b; int c;
}p3;

char a[1000005];
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n, w, l; cin >> n >> w >> l; vector<int> a(n); for(int i=0; i<n; i++) cin >> a[i]; a.push_back(10000000);
    int t = 0;
    queue<int> bridge; for(int i=0; i<w; i++) bridge.push(0);
    int ind = 0, sm = 0;
    while(ind < n or sm > 0){
        t++;
        int r = bridge.front();
        sm -= r; bridge.pop();
        if(sm + a[ind] > l) bridge.push(0);
        else{
            sm += a[ind];
            bridge.push(a[ind]);
            ind++;
        }
    }
    cout << t << "\n";
    return 0;
}