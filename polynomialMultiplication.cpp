#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
#include <algorithm>
using namespace std;

//function to perform the Fast Fourier Transform (FFT) recursively
void fft(vector<complex<double>>& polynomial, bool inverse = false) {
    int n = polynomial.size();
    if (n <= 1) {
        return;
    }

    //split the polynomial into even and odd indices
    vector<complex<double>> even(n / 2);
    vector<complex<double>> odd(n / 2);
    for (int i = 0; i < n / 2; i++) {
        even[i] = polynomial[2 * i];
        odd[i] = polynomial[2 * i + 1];
    }

    //apply FFT recursively to even and odd parts
    fft(even, inverse);
    fft(odd, inverse);

    //calculate the twiddle factors
    double angle = 2 * M_PI / n * (inverse ? -1 : 1);
    complex<double> w(1);
    complex<double> wn(cos(angle), sin(angle));

    //combine the results of even and odd parts
    for (int i = 0; i < n / 2; i++) {
        complex<double> temp = w * odd[i];
        polynomial[i] = even[i] + temp;
        polynomial[i + n / 2] = even[i] - temp;
        if (inverse) {
            polynomial[i] /= 2;
            polynomial[i + n / 2] /= 2;
        }
        w *= wn;
    }
}

//function to multiply two polynomials using the Fast Fourier Transform (FFT)
vector<int> multiplyPolynomialsFFT(const vector<int>& polynomial1, const vector<int>& polynomial2) {
    // Determine the size of the resulting polynomial
    int size = 1;
    while (size < polynomial1.size() + polynomial2.size() - 1) {
        size *= 2;
    }

    //convert the polynomials to complex numbers
    vector<complex<double>> complexPoly1(size);
    vector<complex<double>> complexPoly2(size);
    for (int i = 0; i < polynomial1.size(); i++) {
        complexPoly1[i] = complex<double>(polynomial1[i], 0);
    }
    for (int i = 0; i < polynomial2.size(); i++) {
        complexPoly2[i] = complex<double>(polynomial2[i], 0);
    }

    //perform FFT on the complex polynomial representations
    fft(complexPoly1);
    fft(complexPoly2);

    //multiply the polynomial representations element-wise
    vector<complex<double>> product(size);
    for (int i = 0; i < size; i++) {
        product[i] = complexPoly1[i] * complexPoly2[i];
    }

    //perform inverse FFT on the multiplied results
    fft(product, true);

    //extract the real parts of the inverse FFT results as the product polynomial
    vector<int> result(size);
    for (int i = 0; i < size; i++) {
        result[i] = round(product[i].real());
    }
    return result;
}

//function to display a polynomial
void displayPolynomial(const vector<int>& polynomial) {
    for (int i = polynomial.size()-1; i > -1  ; i--) {
        cout << polynomial[i] << "x^" << i;
        if (i != 0) {
            cout << " + ";
        }
    }
    cout << endl;
}

//function to enter a polynomial
vector<int> readPolynomial() {
    int degree;
    cout << "Enter the degree of the polynomial: ";
    cin >> degree;
    vector<int> polynomial(degree + 1);
    for (int i = 0; i <= degree; i++) {
        cout << "Enter the coefficient of x^" << i << ": ";
        cin >> polynomial[i];
    }
    return polynomial;
}

int main() {
    cout << "Polynomial 1" << endl;
    vector<int> polynomial1 = readPolynomial();
    cout << "\nPolynomial 2" << endl;
    vector<int> polynomial2 = readPolynomial();

    cout << "\nPolynomial 1: ";
    displayPolynomial(polynomial1);
    cout << "Polynomial 2: ";
    displayPolynomial(polynomial2);

    vector<int> product = multiplyPolynomialsFFT(polynomial1, polynomial2);
    cout << "\nProduct: ";
    displayPolynomial(product);
    return 0;
}
