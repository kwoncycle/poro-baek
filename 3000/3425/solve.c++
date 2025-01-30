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

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    while(true){
        vector<pair<string, int>> vs;
        while(true){
            string s; cin >> s;
            int t = 0;
            if(s == "NUM") cin >> t;
            vs.push_back({s, t});
            if(s == "END") break;
            if(s == "QUIT"){
                return 0;
            }
        }
        int n; cin >> n;
        for(int i=0; i<n; i++){
            int x; cin >> x;
            stack<int> st; st.push(x);
            for(auto stt:vs){
                string s = stt.X;
                int t = stt.Y;
                if(s == "DUP"){
                    if(st.size() == 0){
                        goto err;
                    }
                    int x = st.top();
                    st.push(x);
                }

                if(s == "NUM"){
                    st.push(t);
                }

                if(s == "INV"){
                    if(st.size() == 0){
                        goto err;
                    }
                    int x = st.top();
                    st.pop();
                    st.push(-x);
                }

                if(s == "POP"){
                    if(st.size() == 0){
                        goto err;
                    }
                    st.pop();
                }

                if(s == "SWP"){
                    if(st.size() < 2){
                        goto err;
                    }
                    int x = st.top(); st.pop();
                    int y = st.top(); st.pop();
                    st.push(x);
                    st.push(y);
                }

                if(s == "ADD"){
                    if(st.size() < 2){
                        goto err;
                    }
                    int x = st.top(); st.pop();
                    int y = st.top(); st.pop();
                    ll u = (ll)x + (ll)y;
                    if(abs(u) > 1000000000) goto err;
                    st.push(u);
                }

                if(s == "SUB"){
                    if(st.size() < 2){
                        goto err;
                    }
                    int x = st.top(); st.pop();
                    int y = st.top(); st.pop();
                    ll u = (ll)y - (ll)x;
                    if(abs(u) > 1000000000) goto err;
                    st.push(u);
                }

                if(s == "MUL"){
                    if(st.size() < 2){
                        goto err;
                    }
                    int x = st.top(); st.pop();
                    int y = st.top(); st.pop();
                    ll u = (ll)y * (ll)x;
                    if(abs(u) > 1000000000) goto err;
                    st.push(u);
                }

                if(s == "DIV"){
                    if(st.size() < 2){
                        goto err;
                    }
                    int x = st.top(); st.pop();
                    int y = st.top(); st.pop();
                    if(x == 0) goto err;
                    ll u = (ll)abs(y) / (ll)abs(x);
                    if(abs(u) > 1000000000) goto err;
                    if((x<0) != (y<0)) u *= -1;
                    st.push(u);
                }

                if(s == "MOD"){
                    if(st.size() < 2){
                        goto err;
                    }
                    int x = st.top(); st.pop();
                    int y = st.top(); st.pop();
                    if(x == 0) goto err;
                    ll u = (ll)abs(y) % (ll)abs(x);
                    if(abs(u) > 1000000000) goto err;
                    if((y<0)) u *= -1;
                    st.push(u);
                }
            }

            if(st.size() != 1) goto err;
            cout << st.top() << "\n";

            continue;
            err:
            cout << "ERROR\n";
        }
        cout << "\n";
    }
    return 0;
}