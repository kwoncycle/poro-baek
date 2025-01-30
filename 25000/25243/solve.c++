#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define pii pair<int,int>
#define pll pair<ll,ll>
#define X first
#define Y second
#define CNT_LOWER(v,n) (int)(lower_bound((v).begin(),(v).end(),(n))-(v).begin())
#define CNT_UPPER(v,n) (int)(upper_bound((v).begin(),(v).end(),(n))-(v).begin())
#define all(x) (x).begin(), (x).end()

// CNT_LOWER: number of element in v smaller than n
// CNT_UPPER: number of element in v smaller or same than n

#define LINE array<pii, 2>
// LINE: l[0] + kl[1]

pii operator + (pii l, pii r){return {l.X+r.X, l.Y+r.Y};};
pii operator - (pii l, pii r){return {l.X-r.X, l.Y-r.Y};};
ll operator * (pii l, pii r){return (ll)l.X*r.X + (ll)l.Y*r.Y;};
ll operator / (pii l, pii r){return (ll)l.X*r.Y - (ll)l.Y*r.X;};

int s2time(string s){
    for(auto &i:s) i -= '0';
    return (s[0]*10 + s[1]) * 60 + s[3]*10 + s[4];
}

struct Event{
    pii n;
    int q;
    Event(pii _n, int _q) : n(_n), q(_q) {}
};

string int2time(int i){
    int x = i/60, y = i%60;
    x %= 24;
    string s;
    s.push_back('0' + y%10);
    y /= 10;
    s.push_back('0' + y%10);
    y /= 10;
    s.push_back(':');
    s.push_back('0' + x%10);
    x /= 10;
    s.push_back('0' + x%10);
    x /= 10;
    reverse(all(s));
    return s;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n1, n2;
    cin >> n1 >> n2;

    vector<vector<Event>> E(500000);

    priority_queue<pii, vector<pii>, greater<pii>> a[4];//, b[5];
    for(int i=0; i<n1; i++){
        int num;
        string s;
        cin >> num >> s;
        E[s2time(s)].push_back(Event({s2time(s), num}, 0));
    }

    for(int i=0; i<n2; i++){
        int num;
        string s;
        cin >> num >> s;
        E[s2time(s)].push_back(Event({s2time(s), num}, 3));
    }

    vector<int> isin(4, 0);
    vector<int> remain = {7, 7, 8, 10};
    vector<pii> ans;
    for(int i=0; i<500000; i++){
        for(auto [n, t]: E[i]){
            a[t].push(n);
        }

        for(int j=0; j<4; j++){
            if(isin[j] == 0) continue;
            isin[j]--;
        }

        for(int j=0; j<4; j++){
            if(isin[j] == 0 and !a[j].empty()){
                isin[j] = remain[j];
                pii train = a[j].top(); a[j].pop();
                if(train.Y % 2 == 1){
                    if(j+1 < 4){
                        E[i + remain[j] + 1].push_back({train, j+1});
                    }
                    else ans.push_back({train.Y, i + remain[j]});
                }
                else{
                    if(j-1 >= 0){
                        E[i + remain[j] + 1].push_back({train, j-1});
                    }
                    else ans.push_back({train.Y, i + remain[j]});
                }
            }
        }
    }
    sort(all(ans));
    for(auto [i,j]:ans) cout << int2time(j) << "\n";
    return 0;
}