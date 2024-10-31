#include <iostream>
#include <vector>
#include <complex>
#include <cmath>

using namespace std;

typedef complex<double> Complex;
const double PI = acos(-1);

void fft(vector<Complex>& x, bool invert) {
    int N = x.size();
    if (N <= 1) return;

    vector<Complex> even(N / 2), odd(N / 2);
    for (int i = 0; i < N / 2; i++) {
        even[i] = x[i * 2];
        odd[i] = x[i * 2 + 1];
    }

    fft(even, invert);
    fft(odd, invert);

    double angle = 2 * PI / N * (invert ? -1 : 1);
    Complex w(1), wn(cos(angle), sin(angle));

    for (int k = 0; k < N / 2; k++) {
        Complex t = w * odd[k];
        x[k] = even[k] + t;
        x[k + N / 2] = even[k] - t;
        if (invert) {
            x[k] /= 2;
            x[k + N / 2] /= 2;
        }
        w *= wn;
    }
}

vector<double> multiplyPolynomials(const vector<double>& a, const vector<double>& b) {
    int n = 1;
    while (n < a.size() + b.size()) n *= 2;

    vector<Complex> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    fa.resize(n);
    fb.resize(n);

    fft(fa, false);
    fft(fb, false);

    for (int i = 0; i < n; i++)
        fa[i] *= fb[i];

    fft(fa, true);

    vector<double> result(n);
    for (int i = 0; i < n; i++)
        result[i] = round(fa[i].real());

    return result;
}

int main() {	
	#ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    int degree1, degree2;
    cout << "Enter the degree of the first polynomial: ";
    cin >> degree1;
    if (degree1 < 0) {
        cout << "Degree must be non-negative." << endl;
        return 0;
    }

    vector<double> poly1(degree1 + 1);
    cout << "Enter the coefficients of the first polynomial (from constant term to highest degree): ";
    for (int i = 0; i <= degree1; i++) {
        cin >> poly1[i];
    }

    cout << "Enter the degree of the second polynomial: ";
    cin >> degree2;
    if (degree2 < 0) {
        cout << "Degree must be non-negative." << endl;
        return 0;
    }

    vector<double> poly2(degree2 + 1);
    cout << "Enter the coefficients of the second polynomial (from constant term to highest degree): ";
    for (int i = 0; i <= degree2; i++) {
        cin >> poly2[i];
    }

    vector<double> result = multiplyPolynomials(poly1, poly2);

    cout << "Resultant polynomial coefficients: " << endl;
    for (size_t i = 0; i < result.size(); i++) {
        if (result[i] != 0 || i == 0)
            cout << result[i] << " ";
    }
    cout << endl;

    return 0;
}


//2
//1 2 3
//1
//4 5

//4 13 22 15 
