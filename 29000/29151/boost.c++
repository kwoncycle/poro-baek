#include <boost/progress.hpp>
#include <boost/timer.hpp>
#include <iostream>
int main(){
    std::cout << "HI\n";
    int ii = 1000000;
    boost::progress_display loading_bar(100000);
    for(int i=0; i<=1000000; i++){
        ++loading_bar;
        for(int j=0; j<100000; j++){
            int asdf = 1;
            asdf = asdf + asdf;
            asdf += j;
        }
    }
}