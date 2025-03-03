#include <iostream>
#include <vector>
#include <map>

std::vector <int> v = {53,100,81,99,46,103,108,101,74,111,119,95,115,55,48,69,119,116,66,101,111,101,90,99,113,103,48,76,84,107,75,111,46,101,83,49,115,107,100,49,116,100,47,298,121,47,48,117,68,65,98,98,97,100,109,100,69,69,100,82,108,111,104,116,109,116,111,105,79,111,76,99,106,66,110,10,52,50,32,51,333,52,334,55,334,51,32,50,54,32,54,341,55,49,345,345,333,50,48,32,53,32,55,341,49,354,54,344,52,341,53,356,50,349,50,337,52,57,355,344,50,333,55,363,349,52,339,54,354,52,371,354,53,349,49,373,49,337,53,365,373,54,337,49,356,53,352,382,349,51,337,51,56,32,49,344,339,55,333,53,398,408,341,54,417,356,52,375,408,53,408,49,341,51,404,344,373,50,356,55,356,49,333,51,373,269,32,52,408,50,440,337,54,339,49,339,51,354,369,365,339,53,453,380,356,444,345,396,356,10};

std::string f() {
    std::map<int, std::string> c;
    for (int i = 0; i < 256; i++) {
        c[i] = std::string(1, i);
    }

    std::string w(1, v[0]);
    std::string r = w;
    std::string e;
    for(int i = 1; i < v.size(); i++) {
        int k = v[i];

        if(c.count(k)) {
            e = c[k];
        }
        else if(k == c.size()) {
            e = w + w[0];
        }
        else {
            throw std::runtime_error("O2O4");
        }

        r += e;

        c[c.size()] = w + e[0];
        w = e;
    }
    return r;
}

int main() {
    std::cout << f() << "\n";
    return 0;
}