#include <iostream>
#include <vector>
#include <cmath>

struct disk {
    int x;
    int y;
    int r;
    int c; //color of 1 or 2
};

bool IsIntersecting(disk a, disk b) {
    return pow((a.x - b.x),2) + pow((a.y - b.y),2) <= pow((a.r + b.r),2);;
}

int flipColor(int c){
    if(c == 1){
        return 2;
    } else if(c == 2) {
        return 1;
    } else {
        return -1;
    }
}
int DiskColoring(std::vector<disk> A){
    std::string result = "";
    std::vector<disk>::iterator i = A.begin();
    std::vector<disk>::iterator j = A.begin();

    i->c = 1;
    for(; i != A.end(); i++){
        j = i;
        for(; j != A.end(); j++){
            if(i == j){
                continue;
            }
            if(IsIntersecting(*i, *j)) {
                if(j->c == i->c) {
                    std::cout << "0" <<std::endl;
                    return 0;
                } else {
                    j->c = flipColor(i->c);
                }
            }
        }
    }

    i = A.begin();
    for(; i != A.end(); i++){
        std::cout << i->c << " ";
    }
    std::cout << std::endl;

    return 1;
}

int main() {
    int n;
    std::vector<disk> A;

    std::cin >> n;
    for(; n > 0; n--){
        disk p;

        std::cin >> p.x;
        std::cin >> p.y;
        std::cin >> p.r;
        p.c = -1;

        A.push_back(p);
    }

    DiskColoring(A);
}
