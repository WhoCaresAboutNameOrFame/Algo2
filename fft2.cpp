#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
using namespace std;

typedef complex<double> cd;

//recursive function of FFT
vector<cd> fft(vector<cd>& a) {
    int n = a.size();
    if (n == 1)
        return vector<cd>(1, a[0]);
    
    vector<cd> w(n);
    for (int i = 0; i < n; i++) {
        double alpha = -2 * M_PI * i / n;
        w[i] = cd(cos(alpha), sin(alpha));
    }

    vector<cd> A0(n / 2), A1(n / 2);
    for (int i = 0; i < n / 2; i++) {
        A0[i] = a[i * 2]; //even indexed coefficients
        A1[i] = a[i * 2 + 1]; //odd indexed coefficients
    }

    vector<cd> y0 = fft(A0); //recursive call for even indexed coefficients
    vector<cd> y1 = fft(A1); //recursive call for odd indexed coefficients
    vector<cd> y(n);

    for (int k = 0; k < n / 2; k++) {
        y[k] = y0[k] + w[k] * y1[k];
        y[k + n / 2] = y0[k] - w[k] * y1[k];
    }
    return y;
}

int main() {
    //input for polynomial coefficients
    int n;
    cout << "Enter the degree of Polynomial: ";
    cin >> n;
    vector<cd> a(n + 1);
    cout << "Enter the coefficients Polynomial: ";
    for (int i = n; i >= 0; i--) {
        cin >> a[i];
    }

    //compute FFT of the polynomial
    vector<cd> b = fft(a);

    //output the Fourier transform
    cout << "Fourier Transform of the Polynomial: ";
    for (int i = 0; i <= n; i++) {
        cout << b[i] << " ";
    }
    cout << endl;
    return 0;
}
