#include <iostream>
#include <complex>
#include <vector>
#include <cmath>
const double PI = 3.14159265358979323846;

// FFT function
void fft(std::complex<double>* a, int n, bool inverse = false) {
    if (n <= 1) return;

    std::vector<std::complex<double>> even(n/2), odd(n/2);
    for (int i = 0; i < n/2; ++i) {
        even[i] = a[i*2];
        odd[i] = a[i*2 + 1];
    }

    fft(even.data(), n/2, inverse);
    fft(odd.data(), n/2, inverse);
    double angle = 2 * PI / n * (inverse ? -1 : 1);
    std::complex<double> w(1, 0), wn(std::cos(angle), std::sin(angle));

    for (int i = 0; i < n/2; ++i) {
        a[i] = even[i] + w * odd[i];
        a[i + n/2] = even[i] - w * odd[i];
        if (inverse) {
            a[i] /= 2;
            a[i + n/2] /= 2;
        }
        w *= wn;
    }
}

// function to evaluate polynomial at a point x using FFT
double evaluate_polynomial(std::vector<double>& coefficients, double x) {
    int n = coefficients.size();

    // Convert coefficients to complex numbers
    std::vector<std::complex<double>> A(n);
    for (int i = 0; i < n; ++i) {
        A[i] = coefficients[i];
    }

    fft(A.data(), n);
    std::complex<double> x_complex(std::cos(2 * PI * x / n), std::sin(2 * PI * x / n));
    std::complex<double> result = 0;
    std::complex<double> x_power = 1;

    for (int i = 0; i < n; ++i) {
        result += A[i] * x_power;
        x_power *= x_complex;
    }
    return result.real();
}

int main() {
    int degree;
    std::cout << "Enter the degree of the polynomial: ";
    std::cin >> degree;

    std::vector<double> coefficients(degree + 1);
    std::cout << "Enter the coefficients of the polynomial (from highest degree to lowest): ";
    for (int i = degree; i >= 0; --i) {
        std::cin >> coefficients[i];
    }

    double x;
    std::cout << "Enter the value of x to evaluate the polynomial at: ";
    std::cin >> x;

    double result = evaluate_polynomial(coefficients, x);
    std::cout << "Value of the Polynomial at x = " << x << " is: " << result << std::endl;
    return 0;
}
