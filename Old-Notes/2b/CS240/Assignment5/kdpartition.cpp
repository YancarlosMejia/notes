#include <vector>
#include <algorithm>
#include <iostream>


using namespace std;


class point {
public:
    int x;
    int y;
    point(int X, int Y) : x(X), y(Y){}
    point() : x(0), y(0){}
};

class sorter {
    char by;
public:
    sorter(char b) : by(b) {}
    bool operator()(point l, point r) {
        if(by == 'x') {
            return  l.x < r.x;
        } else {
            return l.y < r.y;
        }
    }
};


void sortBy(vector<point> &points, char by ) {
    sort(points.begin(), points.end(), sorter(by));
}

void KDify(vector<point> v, char by) {
    if(v.size() == 1) {
        cout<<v[0].x<< " " << v[0].y << endl;
        return;
    } else if(v.size() == 0) {
        return;
    }

    sortBy(v, by);

    if(by == 'x'){
        by = 'y';
    } else {
        by = 'x';
    }


    int middle = v.size() / 2;

    vector<point> low;
    vector<point> high;

    copy(v.begin(), v.begin() + middle, back_inserter(low));
    copy(v.begin() + middle + 1, v.end(), back_inserter(high));

    KDify(low, by);

    cout<<v[middle].x << " " << v[middle].y << endl;

    KDify(high, by);
}



int main(int argc, char **argv) {
    int amount;
    int x;
    int y;
    vector<point> points;

    cin >> amount;

    while(amount != 0){
        cin >> x;
        cin >> y;
        points.push_back(point(x,y));
        amount -=1;
    }

    KDify(points, 'x');

    return 0;
}
