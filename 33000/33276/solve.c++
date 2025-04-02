#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n; cin >> n;
    ll ans;

    // first
    for(int i=1; i<=n-1; i++){
        cout << "A " << i << " " << i << endl;
        cout << "A " << i << " " << i+1 << endl;
    }

    cout << "Q " << n-1 << " ";
    for(int i=1; i<=n-1; i++) cout << i << " ";
    cout << endl;

    cin >> ans;
    cout << "! " << ans << endl;

    // second
    for(int i=1; i<=n; i++){
        cout << "A " << i << " " << i << endl;
    }

    for(int i=1; i<=n; i++){
        cout << "C " << i << " " << (1<<29) << endl;
    }
    cout << "C " << n+1 << " " << (3<<29) << endl;

    cout << "Q " << n+1 << " ";
    for(int i=1; i<=n+1; i++) cout << i << " ";
    cout << endl;

    cin >> ans;
    cout << "! " << (ans ^ (3<<29)) << endl;

    return 0;
}