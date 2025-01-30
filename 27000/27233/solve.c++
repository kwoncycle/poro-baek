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


vector<int> v1(10000);

void swap3(int a, int b, vector<int> &v){
    int n = v.size() - 1;
    int idx = 1;
    for(int i=b+1; i<=n; i++) {
        v1[idx] = v[i];
        idx++;
    }

    for(int i=a+1; i<=b; i++){
        v1[idx] = v[i];
        idx++;
    }

    for(int i=1; i<=a; i++){
        v1[idx] = v[i];
        idx++;
    }

    for(int i=1; i<=n; i++){
        v[i] = v1[i];
    }
}

void swap2(int a, vector<int> &v){
    int n = v.size() - 1;
    int idx = 1;

    for(int i=a+1; i<=n; i++){
        v1[idx] = v[i];
        idx++;
    }

    for(int i=1; i<=a; i++){
        v1[idx] = v[i];
        idx++;
    }

    for(int i=1; i<=n; i++){
        v[i] = v1[i];
    }
    v1.clear();
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n; cin >> n;
    vector<int> v(n+1);
    for(int i=1; i<=n; i++) cin >> v[i];

    vector<array<int, 3>> ans;
    int dff = n - v[n];
    for(int i=1; i<=n; i++){
        v[i] += dff;
        while(v[i] > n) v[i] -= n;
    }

    int id;
    int f1 = n-1, f2 = 1;

    for(int i=1; i<=n-2; i++){
        if(i % 2 == 1){
            id = 1;
            while(v[id] != f2) id++;
            if(id == 1){
                ans.push_back({2, n-i, 0});
                swap2(n-i, v);
            }

            else{
                ans.push_back({3, id-1, n-i});
                swap3(id-1, n-i, v);
            }
            f2++;
        }
        else{
            id = 1;

            while(v[id] != f1) id++;
            if(id == n){
                ans.push_back({2, i, 0});
                swap2(i, v);
            }
            else{
                ans.push_back({3, i, id});
                swap3(i, id, v);
            }
            f1--;
        }   
    }
    for(int i=1; i<=n; i++){
        v[i] -= dff;
        while(v[i] <= 0) v[i] += n;
    }


    id = 1;
    while(v[id] != 1) id++;
    if(id != 1){
        ans.push_back({2, id-1, 0});
        swap2(id - 1, v);
    }


    cout << (int)ans.size() << "\n";
    for(int i=(int)ans.size()-1; i>=0; i--){
        auto [x,y,z] = ans[i];
        if(x == 2) cout << x << " " << n - y << "\n";
        else cout << x << " " << n-z << " " << n-y << "\n";
    }
    return 0;
}