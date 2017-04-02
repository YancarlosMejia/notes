struct Rational {
public:
    Rational (int numer = 0, int denom = 1);    // Constructor for user-provided values
    int numerator_;
    int denominator_;
};

Rational::Rational(int numer, int denom) : numerator_(numer), denominator_(denom) {}

bool operator< (const Rational&, const Rational&);
bool operator<= (const Rational&, const Rational&);
bool operator> (const Rational&, const Rational&);
bool operator>= (const Rational&, const Rational&);
						 
// Comparison Operations
bool operator== (const Rational& a, const Rational& b) {
    return (a <= b && a >= b);
}

bool operator!= (const Rational& a, const Rational& b) {
    return !(a == b);
}

bool operator< (const Rational& a, const Rational& b) {
    return ((a != b) && !(a > b));
}

bool operator<= (const Rational& a, const Rational& b) {
    return !(a > b);
}

bool operator> (const Rational& a, const Rational& b) {
    return (b < a);
}

bool operator>= (const Rational& a, const Rational& b) {
    return !(a < b);
}

int main() {
    Rational rat1(3, 42);
    Rational rat2(7, 100);

    return (rat1 == rat2);
}
