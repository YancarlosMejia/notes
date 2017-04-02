#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <limits>


struct point {
    int c; //blue == 1
    int x;
    int y;
};

int DominanceCount(std::vector<point> A) {
    int total = 0;

    for(std::vector<point>::iterator it = A.begin(); it != A.end(); it ++) {
        for(std::vector<point>::iterator it2 = A.begin(); it2 != A.end(); it2 ++) {
            if(it->x >= it2->x && it->y >= it2->y && it->c == 0 && it2->c == 1){
                total ++;
            }
        }
    }

    return total;
}


int main() {
    int n;
    std::vector<point> A;

    std::cin >> n;
    for(; n > 0; n--){
        point p;

        std::cin >> p.x;
        std::cin >> p.y;
        std::cin >> p.c;

        A.push_back(p);
    }


    int result;
    result = DominanceCount(A);
    std::cout << result << std::endl;
}
