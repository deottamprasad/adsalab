#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

void decom(vector<vector<double> >& A, vector<vector<double> >& L, vector<vector<double> >& U) {
    int n = A.size();
    for(int k = 0; k < n; k++) {
        L[k][k] = 1;
        U[k][k] = A[k][k];
        for(int i = k + 1; i < n; i++) {
            L[i][k] = A[i][k] / U[k][k];
            U[k][i] = A[k][i];
        }
        for(int i = k + 1; i < n; i++) {
            for(int j = k + 1; j < n; j++) {
                A[i][j] = A[i][j] - L[i][k] * U[k][j];
            }
        }
    }
}

void solve(vector<vector<double> >& L, vector<vector<double> >& U, vector<double>& b, vector<double>& x, ostream& out) {
    int n = L.size();
    vector<double> y(n, 0);

    for(int i = 0; i < n; i++) {
        double lySum = 0;
        for(int j = 0; j <= i - 1; j++) {
            lySum += L[i][j] * y[j];
        } 
        y[i] = b[i] - lySum;
    }

    out << "y vector: " << endl;
    for(int m = 0; m < n; m++) {
        out << y[m] << " ";
    }
    out << endl;

    for(int i = n - 1; i >= 0; i--) {
        double uxSum = 0;
        for(int j = i + 1; j < n; j++) {
            uxSum += U[i][j] * x[j];
        }
        x[i] = (y[i] - uxSum) / U[i][i];
    }
}

int main() {
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif

    int n = 0;
    cout << "Enter the dimension of matrix: ";
    cin >> n;

    vector<vector<double> > A(n, vector<double>(n, 0)); 
    vector<double> b(n, 0);
    vector<vector<double> > L(n, vector<double>(n, 0));
    vector<vector<double> > U(n, vector<double>(n, 0));
    vector<double> x(n, 0);

    cout << "Enter A matrix elements: ";
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cin >> A[i][j];
        }
    }

    cout << "Enter b vector elements: ";
    for(int i = 0; i < n; i++) {
        cin >> b[i];
    }

    decom(A, L, U);

    cout << "Lower unit triangular matrix (L):" << endl;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cout << L[i][j] << " ";
        }
        cout << endl;
    }

    cout << "Upper triangular matrix (U):" << endl;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cout << U[i][j] << " ";
        }
        cout << endl;
    }

    solve(L, U, b, x, cout);

    cout << "Solution vector (x):" << endl;
    for(int i = 0; i < n; i++) {
        cout << x[i] << " ";
    }
    cout << endl;

    return 0;
}

/*
README - Input and Output Example
=================================

Input Example (input.txt):
--------------------------
4
2 3 1 5
6 13 5 19
2 19 10 23
4 10 11 31
3 2 1 4

Output Example (output.txt):
----------------------------
Lower unit triangular matrix (L):
1 0 0 0
3 1 0 0
4 2 1 
*/







