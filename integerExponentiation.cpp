#include <iostream>
using namespace std;

double calculatePower(double x, int n) {
    double result = 1;
    while (n > 0) {
        if (n % 2 == 1) {
            result *= x;
        }
        x *= x;
        n /= 2;
    }
    return result;
}

int main() {
    double x;
    int n;
    cout << "Enter base and exponent respectively: ";
    cin >> x >> n;
    cout << x << "^" << n << " = " << calculatePower(x, n);
    return 0;
}