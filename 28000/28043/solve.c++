#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n, h, w;
    cin >> n >> h >> w;
    for(int i=0; i<n; i++){
        char c0, c1; cin >> c0 >> c1;
        if(c0 == 'Y'){
            cout << "Y ";
            h--; w++;
        }
        else{
            if(w == 0){
                cout << "Y ";
                h--; w++;
            }
            else cout << "N ";
        }

        if(c1 == 'Y'){
            cout << "Y\n";
            h++; w--;
        }
        else{
            if(h == 0){
                cout << "Y\n";
                h++; w--;
            }
            else cout << "N\n";
        }
    }
    return 0;
}