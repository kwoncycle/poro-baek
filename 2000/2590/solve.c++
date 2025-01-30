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

#define DEBUG 0
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    vector<int> v(7);
    for(int i=1; i<=6; i++) cin >> v[i];

    int cnt = 0;
    cnt += v[6];

    if(DEBUG){
        cout << "6: " << cnt << '\n';
    }

    cnt += v[5];

    if(DEBUG){
        cout << "5: " << cnt << '\n';
    }

    if(v[1] > 0) v[1] -= v[5] * 11;
    cnt += v[4];
    int o = 5 * v[4];
    int x = min(v[2], o);
    o -= x; v[2] -= x;

    if(DEBUG){
        cout << "4: " << cnt << '\n';
    }

    if(v[1] > 0) v[1] -= o*4;
    o = 0;
    cnt += v[3]/4;
    v[3] %= 4;
    if(v[3]) {
        cnt++;
        int ttl = 36 - 9*v[3];
        if(v[3] == 1){
            o = 5;
        }
        if(v[3] == 2){
            o = 3;
        }
        if(v[3] == 3){
            o = 1;
        }
        ttl -= 4*o;
        x = min(v[2], o);
        o -= x; v[2] -= x;
        ttl += 4*o;
        if(v[1] > 0) v[1] -= ttl;
    }

    if(DEBUG){
        cout << "3: " << cnt << '\n';
        cout << v[3] << " " << v[2] << " " << v[1] << "\n";
    }

    cnt += v[2]/9;
    v[2] %= 9;
    if(v[2]){
        cnt++;
        int ttl = 36 - 4 * v[2];
        if(v[1] > 0) v[1] -= ttl;
    }

    if(DEBUG){
        cout << "2: " << cnt << '\n';
        cout << v[1] << "\n";
    }
    if(v[1] > 0){
        cnt += v[1]/36;
        v[1] %= 36;
        if(v[1]) cnt++;
    }
    
    if(DEBUG){
        cout << "1: " << cnt << '\n';
    }
    cout << cnt << "\n";


    return 0;
}