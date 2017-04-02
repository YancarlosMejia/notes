
#include <iostream>

using namespace std;

//*****************************************
// Rational Declaration
//  - Private Implementation (PImpl idiom)
//  - Immutable ADT
//      - no mutators
//      - assignment and copy are deep copies
//      - all new values are constructed
//*****************************************

class Rational {
public:
    Rational (int numer = 0, int denom = 1) ;   // Constructor for user-provided values
    ~Rational ();
    Rational (const Rational&);                 // Copy Constructor
    Rational& operator= ( const Rational& );    // Assignment
    int numerator() const;                      // Accessor
    int denominator() const;                    // Accessor no mutators because it is immutable
private:
    struct Impl;
    Impl* rat_;
    void reduce();
    static int serials_;            // generate serial numbers for objects
    int serialNo_;                  // this object's serial number
};

int Rational::serials_ = 0;
									 
// Arithmetic Operations
Rational operator+ (const Rational&, const Rational&);
Rational operator* (const Rational&, const Rational&);
						 
// Comparison Operations
bool operator== (const Rational&, const Rational&);
bool operator!= (const Rational&, const Rational&);
bool operator< (const Rational&, const Rational&);
bool operator<= (const Rational&, const Rational&);
bool operator> (const Rational&, const Rational&);
bool operator>= (const Rational&, const Rational&);
									 
// Streaming Operations
ostream& operator<< (ostream &sout, const Rational &r);
istream& operator>> (istream &sin,  Rational &s);

									 

//*****************************************
// Rational Declaration
//*****************************************

struct Rational::Impl {
	int numerator_;
	int denominator_;
};


//*******************************************
// Helper functions (used to reduce rationals)
//*******************************************

namespace { //hidden in the name space

int gcd (int small, int large) {
    if ( small == 0 ) return 1;
	
    int rem = large%small;
    while ( rem != 0 ) {
        large = small;
        small = rem;
        rem = large%small;
	}
	
    return small;
}
    
} // namespace

void Rational::reduce() {
    int divisor = 0;
	
    if ( numerator() > denominator() ) {
        divisor = gcd( denominator(), numerator() );
    }
    else {
        divisor = gcd( numerator(), denominator() );
    }
	
    if (divisor > 1) {
        rat_->numerator_ /= divisor;
        rat_->denominator_ /= divisor;
    }
}




//*******************************************
// Constructors, Destructors, Assignment
//*******************************************
//all of these use deep copy because it is an immutable type
Rational::Rational(int numer, int denom) : rat_(new Rational::Impl), serialNo_(++serials_) {
    if (denom == 0) {
        throw "Panic! Denominator = 0";
    }
    rat_->numerator_ = numer;
    rat_->denominator_ = denom;
    reduce();
    
    cerr << "Created Rational #" << serialNo_ << endl;
}

Rational::~Rational() { 
    delete rat_;
    rat_ = NULL;
}

Rational::Rational( const Rational &r ) : rat_(new Rational::Impl (*r.rat_) ), serialNo_(++serials_) {
    cerr << "Created Rational #" << serialNo_ << endl;
}


Rational& Rational::operator=( const Rational &r ) {
    Rational copy(r);
    Rational::Impl* temp;
    
    temp = copy.rat_;
    copy.rat_ = rat_;
    rat_ = temp;
    
    return *this;
}


//*******************************************
// Accessors
//*******************************************

int Rational::numerator() const {
    return rat_->numerator_;
}


int Rational::denominator() const {
    return rat_->denominator_;
}


//*******************************************
// Mutators
//*******************************************
//none because this is immutable

//*******************************************
// Streaming Functions
//*******************************************

ostream& operator<< (ostream& sout, const Rational &r) {
    const char slash ='/';
	
    sout << r.numerator() << slash << r.denominator();	
    return sout;
}


 istream& operator>> (istream& sin, Rational &r) {
    int newNumerator;
    int newDenominator;
    char slash;
	
    sin >> newNumerator >> slash >> newDenominator;
	//since this is an immutable type we need to make a new object and assign that to the thingy we want to deal wit
    r = Rational( newNumerator, newDenominator );
	
    return sin;
}

//*******************************************
// Arithmetic Operations
//*******************************************
//all of these must return new objects  that are the result of the action since we cannot change shit
Rational operator+ (const Rational &r, const Rational &s) {
    int a = r.numerator();
    int b = r.denominator();
    int c = s.numerator();
    int d = s.denominator();
	
    return Rational(a*d + b*c, b*d);
	
}

Rational operator* (const Rational &r, const Rational &s) {
    int a = r.numerator();
    int b = r.denominator();
    int c = s.numerator();
    int d = s.denominator();
	
    return Rational(a*c, b*d);
}


//*******************************************
// Comparison Operations
//*******************************************

bool operator== (const Rational &r, const Rational &s) {
    return ( (r.numerator() == s.numerator()) && (r.denominator() == s.denominator()) );
}

bool operator!= (const Rational &r, const Rational &s) {
    return ( !(r==s) );
}

bool operator< (const Rational &r, const Rational &s) {
    return ( (r.numerator() * s.denominator()) < (s.numerator() * r.denominator()) );
}

bool operator<= (const Rational &r, const Rational &s) {
    return ( (r==s) || (r<s) );
}

bool operator> (const Rational &r, const Rational &s) {
    return ( !(r<=s) );
}

bool operator>= (const Rational &r, const Rational &s) {
    return ( !(r<s) );
}

//*****************************************
// Main Program
//*****************************************


int main () {
    cerr << "2 CONSTRUCTORS" << endl;
    Rational r, s;
	
    cerr << endl << "STREAMING OPERATORS" << endl;
    cout << "   Enter rational number (a/b): ";
    cin >> r;
    cout << "   r = " << r << endl;
    
    cerr << endl << "COPY CONSTRUCTOR" << endl;
    Rational t = r;
    cout << "   r = " << r << ", and t = " << t << endl;

    cerr << endl << "ASSIGNMENT" << endl;
    s = t;
    cout << "   s = " << s << ", and t = " << t << endl;

    
    cerr << endl << "ARITHMETIC (and copy constructor)" << endl;
    Rational u = r+s;
    Rational w = r*s;
    cout << "   r + s = " << u << ", and r * s = " << w << endl;

    cerr << endl << "COMPARISON" << endl;
    cout << "   " << r << " == " << s << " is " <<  (r==s) << endl;
    
    return 0;
}