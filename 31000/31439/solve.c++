#include <bits/stdc++.h>
using namespace std;
#define all(x) (x).begin(), (x).end()

int prime[1010];
bool isans(vector<int> ans){
    set<int> st;
    int n = ans.size();
    int truth = 1;
    for(int i=0; i<n; i++){
        st.insert(ans[i]);
        assert(1 <= ans[i] and ans[i] <= n);
        for(int j=i+1; j<n; j++){
            int mn = ans[i], mx = ans[i];
            for(int t=i; t<=j; t++){
                mn = min(mn, ans[t]);
                mx = max(mx, ans[t]);
            }
            if(!prime[mx-mn]){
                truth = 0; break;
            }
        }
    }
    if(st.size() != n) truth = 0;
    return truth;
}



int main(){
    for(int i=2; i<=1000; i++){
        if(prime[i] == 0){
            for(int j=i+i; j<=1000; j+=i){
                prime[j] = 1;
            }
        }
    }
    prime[1] = 1;
    
    int n; cin >> n;
    assert(n >= 2 and n <= 1000);
    if(n == 13){
        vector<int> ans = {12, 3, 9, 5, 13, 7, 1, 11, 2, 6, 10, 4, 8};
        cout << "YES\n";
        for(int i:ans) cout << i << " "; cout << "\n";
        assert(isans(ans));
        return 0;
    }
    if(n == 15){
        vector<int> ans = {4, 8, 2, 10, 1, 13, 5, 9, 3, 7, 11, 15, 14, 6, 12};
        cout << "YES\n";
        for(int i:ans) cout << i << " "; cout << "\n";
        assert(isans(ans));
        return 0;
    }
    if(n <= 10){
        vector<int> ans(n);
        for(int i=0; i<n; i++) ans[i] = i+1;
        do{
            int truth = 1;
            for(int i=0; i<n-1; i++){
                if(!prime[abs(ans[i]-ans[i+1])]){
                    truth = 0; break;
                }
            }
            if(truth)
            for(int i=0; i<n; i++){
                for(int j=i+1; j<n; j++){
                    int mn = ans[i], mx = ans[i];
                    for(int t=i; t<=j; t++){
                        mn = min(mn, ans[t]);
                        mx = max(mx, ans[t]);
                    }
                    if(!prime[mx-mn]){
                        truth = 0; break;
                    }
                }
            }
            if(truth){
                cout << "YES\n";
                for(int i:ans) cout << i << " "; cout << "\n";
                assert(isans(ans));
                return 0;
            }
        }while(next_permutation(all(ans)));

        cout << "NO\n";
        return 0;
    }

    if(!prime[n-1]){
        cout << "NO\n"; return 0;
    }

    if(n%2 == 0){
        vector<int> ans(n);
        int id, cur = n;
        for( id = n/2-1; id>=0, cur > 0; id--, cur -= 4){
            ans[id] = cur;
        }

        cur = n-2;
        for( ; id >=0; id--, cur -= 4){
            ans[id] = cur;
        }

        for(id=n/2; id<n; id++){
            ans[id] = n+1 - ans[n-1-id];
        }
        cout << "YES\n";
        for(int i:ans) cout << i << " "; cout << "\n";
        assert(isans(ans));
        return 0;
    }

    else{
        if(!prime[n-2]){
            if(!prime[n-4]){
                vector<int> ans(n);
                ans[0] = 4; ans[1] = 8; ans[2] = 2; ans[3] = 10;
                ans[4] = 1; ans[5] = n-2;
                int id = 6, cur = 5;
                for(; cur < n-2; cur += 4, id++) ans[id] = cur;
                cur = 3;
                for(; cur < n-2; cur += 4, id++) ans[id] = cur;
                ans[id] = n;
                ans[id+1] = 6;
                cur = 14;
                id+=2;
                for(; cur <= n; cur += 4, id++) ans[id] = cur;
                cur = 12;
                for(; cur <= n; cur += 4, id++) ans[id] = cur;
                cout << "YES\n";
                for(int i:ans) cout << i << " "; cout << "\n";
                assert(isans(ans));
                return 0;
            }
            else{
                vector<int> ans(n);
                ans[0] = n-1;
                ans[1] = 3;
                ans[n/2 - 1] = n;
                ans[n/2] = 1;
                ans[n/2 + 1] = n-2;
                int id = 2, cur = 7;
                for(; cur < n-2; cur += 4, id++){
                    ans[id] = cur;
                }
                cur = 5;
                for(; cur < n-2; cur += 4, id++){
                    ans[id] = cur;
                }

                id = n/2 + 2; cur = 2;
                for(; cur < n-1; cur += 4, id++){
                    ans[id] = cur;
                }
                cur = 4;
                for(; cur < n-1; cur += 4, id++){
                    ans[id] = cur;
                }
                cout << "YES\n";
                for(int i:ans) cout << i << " "; cout << "\n";
                assert(isans(ans));
                return 0;
            }
        }
        vector<int> ans(n);

        ans[n/2] = 1;
        int id = n/2-1, cur = n;
        for( ; id>=0, cur > 1; id--, cur -= 4){
            ans[id] = cur;
        }

        cur = n-2;
        for( ; id >=0, cur > 1; id--, cur -= 4){
            ans[id] = cur;
        }

        id = n/2 + 1, cur = n-1;
        for( ; cur > 0; cur -= 4, id++){
            ans[id] = cur;
        }
        cur = n-3;
        for( ; cur > 0; cur -= 4, id++){
            ans[id] = cur;
        }
        cout << "YES\n";
        for(int i:ans) cout << i << " "; cout << "\n";
        assert(isans(ans));
        return 0;
    }

    return 0;
}