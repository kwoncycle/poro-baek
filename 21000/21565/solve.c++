#include <bits/stdc++.h>
using namespace std;

void query(int a, int b, int c){
    cout << a << " " << b << " " << c << "\n";
}

int main(){
    cout << "252\n";
    query(17, 1, 1);
    for(int j=15; j>=2; j--){
        for(int i=2; i<=j; i+=2){
            if(i+2 <= j+1){
                query(-1, -(i), -(i+1));
                query(i, i, i+1);
                query(i+1, 1, i+2);
                query(-(i+2), -1, -(i+2));
            }
            else{
                query(-1, -(i), -(i+1));
                query(i, i, i+1);
                query(i+1, 1, 1);
            }
        }
    }
    query(1, 17, 17);
    query(17, 16, 16);
    int j = 14;
    for(int i=1; i<=14; i+=2){
        if(i+2 <= j+1){
            query(-16, -(i), -(i+1));
            query(i, i, i+1);
            query(i+1, 16, i+2);
            query(-(i+2), -16, -(i+2));
        }
        else{
            query(-16, -(i), -(i+1));
            query(i, i, i+1);
            query(i+1, 16, 16);
        }
    }
    query(16, 17, 17);
    query(17, 15, 16);
    query(-16, -15, -16);
    query(15, 17, 17);
    return 0;
}