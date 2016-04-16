#include <iostream>
#include <primesieve.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/miller_rabin.hpp>
#include <boost/math/common_factor.hpp>


using namespace boost::multiprecision;

cpp_int phi(const cpp_int x) {
    if (x == 1) {
        return 1;
    }
    if (miller_rabin_test(x, 50)) {
        return x-1;
    }
    if (x % 2 == 0){
        cpp_int y = x >> 1;
        if (!(y & 1)) {
            return phi(y) << 1;
        }
        return phi(y);
    }
    primesieve::iterator pi;
    cpp_int prime;
    for (prime = pi.next_prime(); prime < x; prime=pi.next_prime())
    {
        cpp_int k = prime;
        if (x % k) continue;
        cpp_int o = x/k;
        cpp_int d = boost::math::gcd(k, o);
        if (d == 1) {
            return phi(k) * phi(o);
        }
        return phi(k) * phi(o) * d / phi(d);
    }
}

int main(void) {
    cpp_int small = 99;
    cpp_int large = 756928375693284658;
    std::cout << phi(9007199254740881);
    return 0;
}
