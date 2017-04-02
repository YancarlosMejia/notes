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

std::pair<int, std::vector<point> > DominanceCount(std::vector<point> A) {
    std::pair<int, std::vector<point> > ret;

    if(A.size() <= 1) {
        ret.first = 0;
        ret.second = A;
        return ret;
    }

    std::vector<point> left;
    left.insert(left.begin(), A.begin(), A.begin() + floor(A.size()/2));
    std::vector<point> right;
    right.insert(right.begin(), A.begin() + ceil(A.size()/2), A.end());

    std::pair<int, std::vector<point> > LeftResult = DominanceCount(left);
    std::pair<int, std::vector<point> > RightResult = DominanceCount(right);

    std::vector<point> L = LeftResult.second;
    std::vector<point> R = RightResult.second;

    point end;
    end.x = std::numeric_limits<int>::max();
    end.y = std::numeric_limits<int>::max();
    end.c = 1;

    L.push_back(end);
    R.push_back(end);

    ret.first += LeftResult.first;
    ret.first += RightResult.first;

    int i = 0;
    int j = 0;
    int blueCount = 0;
    int total = 0;


    for(int k = 0; k < A.size(); k++) {
        point l = L[i];
        point r = R[j];

        if(l.y < r.y) {
            if(l.c == 1) {
                blueCount ++;
            }
            ret.second.push_back(l);
            i++;
        } else {
            if(r.c == 0){
                total += blueCount;
            }
            ret.second.push_back(r);
            j++;
        }
    }


    ret.first += total;
    return ret;
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


    std::pair<int, std::vector<point> > result;
    result = DominanceCount(A);
    std::cout << result.first << std::endl;
}
