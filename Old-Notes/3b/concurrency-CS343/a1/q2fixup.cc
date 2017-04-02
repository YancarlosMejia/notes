#include <iostream>
#include <functional>
using namespace std;

#ifdef NOOUTPUT
#define print( x )
#else
#define print( x ) x
#endif

//Resume = throw (calls constructor)
//CatchResume = changes parameters of c to be current values of a and recall try block

class E1 {
  public:
    int &a, &b;
    E1( int &i, int &j ) : a( i ), b( i ) {}
};
class E2 {
  public:
    int &a;
    E2( int &i ) : a( i ) {}
};
class E3 {
  public:
    int a;
    E3( int i ) : a( i ) {}
};

int C( int m, int n, function<void(E1)> fixup1, function<void(E2)> fixup2, function<void(E3)> fixup3 ) {
    print( cout << m << " " << n << endl );
    fixup1(E1( m, n ));
    print( cout << m << " " << n << endl );
    fixup2(E2( n ));
    print( cout << m << " " << n << endl );
    fixup3(E3( 27 ));
    return m;
}
int B( int m, int n, function<void(E1)> fixup1, function<void(E2)> fixup2, function<void(E3)> fixup3 ) {
    if ( m > 0 ) B( m - 1, n, fixup1, fixup2, fixup3);
    return C( m, n, fixup1, fixup2, fixup3);
}
int A( int m, int n, int times ) {
    int k = 27, ret;
    for ( int m = 0; m < times; m += 1 ) {
        auto fixup1 = [m,n](E1 e) {
            e.a = m;
            e.b = n;
        };
        auto fixup2 = [k](E2 e){
            e.a = k;
        };
        auto fixup3 = [n](E3 e) {
            print( cout << e.a << " " << n << endl );
        };
        ret = B( m, n, fixup1, fixup2, fixup3);
    }

    return ret;

}
int main( int argc, const char *argv[] ) {
    long int m = 4, n = 6, times = 1;    // default values

    switch ( argc ) {
      case 4: times = atoi( argv[3] );
      case 3: n = atoi( argv[2] );
      case 2: m = atoi( argv[1] );
    } // switch
    cout << m << " " << n << " " << A( m, n, times ) << endl;
}
