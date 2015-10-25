#include <iostream>
#include <cstdlib>
using namespace std;
#include <unistd.h>                // getpid
#include <setjmp.h>

#ifdef NOOUTPUT
#define print( x )
#else
#define print( x ) x
#endif

struct E {};

long int freq = 5;

jmp_buf *globalJump;

long int Ackermann( long int m, long int n ) {
    int jumpReturn;
    int ackerReturn;
    jmp_buf localJump;
    jmp_buf *previousJump = globalJump;


    if ( m == 0 ) {
        if ( random() % freq == 0 ) longjmp(*globalJump, 42);
        return n + 1;
    } else if ( n == 0 ) {
        if ( random() % freq == 0 ) longjmp(*globalJump, 42);

        globalJump = &localJump;

        jumpReturn = setjmp(localJump);
        if(jumpReturn){
            print( cout << "E1 " << m << " " << n << endl );
            globalJump = previousJump;
            return 0;
        } else {
            ackerReturn = Ackermann( m - 1, 1 ) ;
            globalJump = previousJump;
            return ackerReturn;
        }
    } else {
        globalJump = &localJump;

        jumpReturn = setjmp(localJump);
        if(jumpReturn){
            print( cout << "E2 " << m << " " << n << endl );
            globalJump = previousJump;
            return 0;
        } else {
            ackerReturn = Ackermann( m - 1, Ackermann( m, n - 1 ) );
            globalJump = previousJump;
            return ackerReturn;
        }
        // try
    } // if
    return 0;
    // recover by returning 0
}

int main( int argc, const char *argv[] ) {
    long int Ackermann( long int m, long int n );
    long int m = 4, n = 6, seed = getpid();    // default values
    int jumpReturn;

    switch ( argc ) {
      case 5: freq = atoi( argv[4] );
      case 4: seed = atoi( argv[3] );
      case 3: n = atoi( argv[2] );
      case 2: m = atoi( argv[1] );
    } // switch
    srandom( seed );
    cout << m << " " << n << " " << seed << " " << freq << endl;


    jmp_buf localJump;
    globalJump = & localJump;
    jumpReturn = setjmp(localJump);

    if(jumpReturn){
        print( cout << "E3" << endl );
    } else {
        cout << Ackermann( m, n ) << endl;
    }
}
