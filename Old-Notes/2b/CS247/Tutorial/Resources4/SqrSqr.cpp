#include <memory>
using namespace std;

void sqr(auto_ptr<int> x) {
    *x = *x * *x;
}

int main() {
    auto_ptr<int> x(new int);
    *x = 5;
    sqr(x);
    sqr(x);
}
