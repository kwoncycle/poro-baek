#include <bits/stdc++.h>
using namespace std;
int main(){
    int n; cin >> n;
    vector<int> v(n), v1;
    set<int> s;
    for(int i=0; i<n; i++){
        cin >> v[i];
        s.insert(v[i]);
    }
    for(int i:s) v1.push_back(i);
    int n1 = v1.size();
    int start = 0;
    int cnt = 0;
    while(start < n1){
        int i1 = start, i2 = n1-1;
        deque<int> dq;
        cnt++;
        int truth = 1;
        for(int i=0; i<n; i++){
            if(v[i] >= v1[start]){
                if(dq.empty()) dq.push_back(v[i]);
                else{
                    if(v[i] >= dq.back()) dq.push_back(v[i]);
                    else if(v[i] <= dq.front()) dq.push_front(v[i]);
                    else{
                        truth = 0; break;
                    }
                }
            }
        }
        if(truth) break;
        while(i1 + 1 < i2){
            int i3 = (i1 + i2)/2;
            truth = 1;
            dq.clear();
            for(int i=0; i<n; i++){
                if(v[i] >= v1[start] and v[i] <= v1[i3]){
                    if(dq.empty()) dq.push_back(v[i]);
                    else{
                        if(v[i] >= dq.back()) dq.push_back(v[i]);
                        else if(v[i] <= dq.front()) dq.push_front(v[i]);
                        else{
                            truth = 0; break;
                        }
                    }
                }
            }
            if(truth) i1 = i3;
            else i2 = i3;
        }
        start = i1 + 1;
    }
    cout << cnt << "\n";
}