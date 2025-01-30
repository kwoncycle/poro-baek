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

vector<int> v;

vector<int> able(int t){
    int n = v.size();
    vector<int> check(n, 0);
    int prev = v[0];
    vector<int> path;
    for(int i=0; i<n-1; i++){
        int j = i;
        while(j < n and v[j] - prev <= t) j++;
        j--;
        prev = v[j];
        check[j] = 1;
        path.push_back(v[j]);
        if(j == i) return vector<int>(0);
        i = j - 1;
    }
    vector<int> v1;
    v1.push_back(-v[0]);
    for(int i=1; i<n-1; i++){
        if(!check[i]) v1.push_back(-v[i]);
    }
    v1.push_back(-v[n-1]);
    sort(v1.begin(), v1.end());
    n = v1.size();
    prev = v1[0];
    for(int i=0; i<n-1; i++){
        int j = i;
        while(j < n and v1[j] - prev <= t) j++;
        j--;
        prev = v1[j];
        if(j == i) return vector<int>(0);
        i = j - 1;
    }
    for(int i=0; i<n; i++) v1[i] = -v1[i];
    for(int i:path) v1.push_back(i);
    v1.pop_back();
    return v1;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n; cin >> n;
    v.resize(n);
    for(int i=0; i<n; i++) cin >> v[i];
    sort(v.begin(), v.end());
    int start = -1, end = 3000;
    vector<int> ans;
    while(start + 1 < end){
        int mid = (start + end)/2;
        ans = able(mid);
        if(ans.size() == 0){
            start = mid;
        }
        else{
            end = mid;
        }
    }

    vector<int> check(n, 0);
    int prev = v[0];
    vector<int> path;
    for(int i=0; i<n-1; i++){
        int j = i;
        while(j < n and v[j] - prev <= end) j++;
        j--;
        prev = v[j];
        if(j < n-1) check[j] = 1;
        if(j < n-1) path.push_back(v[j]);
        i = j - 1;
    }
    ans = vector<int>(0);
    for(int i=0; i<n; i++){
        if(!check[i]) ans.push_back(v[i]);
    }
    for(int i=(int)path.size()-1; i>=0; i--) ans.push_back(path[i]);
    for(int i:ans) cout << i << " "; cout << "\n";
    return 0;
}