#include <iostream>
#include <boost/numeric/ublas/matrix.hpp>

using namespace boost::numeric::ublas;
using ull = unsigned long long int;

matrix<ull> multiply(const matrix<ull>& A, const matrix<ull>& B) {
    matrix<ull> C(2, 2);
    C(0,0) = A(0,0)*B(0,0) + A(0,1)*B(1,0);
    C(0,1) = A(0,0)*B(0,1) + A(0,1)*B(1,1);
    C(1,0) = A(1,0)*B(0,0) + A(1,1)*B(1,0);
    C(1,1) = A(1,0)*B(0,1) + A(1,1)*B(1,1);
    return C;
}

matrix<ull> power(matrix<ull> A, ull n) {
    matrix<ull> res(2, 2);
    res(0,0) = 1; res(0,1) = 0; res(1,0) = 0; res(1,1) = 1;
    while (n > 0) {
        if (n % 2 == 1) res = multiply(res, A);
        A = multiply(A, A);
        n /= 2;
    }
    return res;
}

int main() {
    ull n;
    std::cout << "Enter n: ";
    if (!(std::cin >> n)) return 0;
    if (n == 0) { std::cout << "F(0) = 0\n"; return 0; }
    if (n == 1) { std::cout << "F(1) = 1\n"; return 0; }
    
    matrix<ull> T(2, 2);
    T(0,0) = 1; T(0,1) = 1; T(1,0) = 1; T(1,1) = 0;
    T = power(T, n - 1);
    std::cout << "F(" << n << ") = " << T(0,0) << std::endl;
    return 0;
}