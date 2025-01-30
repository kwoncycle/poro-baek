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

vector<ll> v;

ll JG(int left, int right){
    if(right == left) return v[left];
    if(left + 1 == right){
        return max(v[left], max(v[right], __gcd(v[left], v[right]) * 2));
    }
    int mid = (left + right) / 2;
    ll o1 = JG(left, mid);
    ll o2 = JG(mid + 1, right);
    vector<ll> v1(right - left + 1);
    v1[mid - left] = v[mid];
    for(int i=mid-1; i>=left; i--){
        v1[i - left] = __gcd(v1[i - left + 1], v[i]);
    }
    v1[mid+1 - left] = v[mid+1];
    for(int i=mid+2; i<=right; i++){
        v1[i - left] = __gcd(v1[i - left - 1], v[i]);
    }

    vector<pll> vp1, vp2;
    for(int i=0; i<=mid - left; i++){
        vp1.push_back({v1[i], i});
        int j = i;
        while(j <= mid-left and v1[i] == v1[j]) j++;
        j--;
        i = j;
    }

    for(int i=right-left; i>=mid+1-left; i--){
        vp2.push_back({v1[i], i});
        int j = i;
        while(j >= mid+1-left and v1[i] == v1[j]) j--;
        j++;
        i = j;
    }
    ll mx = 0;
    for(pll i1: vp1){
        for(pll i2:vp2){
            mx = max(mx, __gcd(i1.X, i2.X) * (i2.Y - i1.Y + 1));
        }
    }
    return max(mx, max(o1, o2));
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int tt; cin >> tt;
    while(tt--){
        int n; cin >> n;
        v = vector<ll>(n);
        for(int i=0; i<n; i++) cin >> v[i];
        cout << JG(0, n-1) << "\n";
    }
    return 0;
}