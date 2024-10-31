#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

using namespace std;

const double EPSILON = 1e-9;

// LUP Decomposition with partial pivoting
bool lupDecomposition(vector<vector<double> > &A, vector<vector<double> > &L, vector<vector<double> > &U, vector<int> &P) {
    int n = A.size();
    P.resize(n);
    L.assign(n, vector<double>(n, 0));
    U.assign(n, vector<double>(n, 0));

    // Initialize the permutation vector
    for (int i = 0; i < n; i++) {
        P[i] = i;
    }

    for (int k = 0; k < n; k++) {
        // Find pivot
        double maxVal = 0.0;
        int pivot = k;
        for (int i = k; i < n; i++) {
            if (abs(A[i][k]) > maxVal) {
                maxVal = abs(A[i][k]);
                pivot = i;
            }
        }

        if (maxVal < EPSILON) {
            return false; // Singular matrix
        }

        // Swap rows in permutation vector
        swap(P[k], P[pivot]);
        swap(A[k], A[pivot]);

        // U and L formation
        for (int i = 0; i < n; i++) {
            U[k][i] = A[k][i];
            if (i >= k) {
                L[i][k] = A[i][k] / U[k][k];
            }
        }

        for (int i = k + 1; i < n; i++) {
            for (int j = k + 1; j < n; j++) {
                A[i][j] -= L[i][k] * U[k][j];
            }
        }
    }
    return true;
}

// Forward and Backward substitution
void lupSolve(const vector<vector<double> > &L, const vector<vector<double> > &U, const vector<int> &P, const vector<double> &b, vector<double> &x) {
    int n = L.size();
    vector<double> y(n, 0);

    // Apply permutation to b
    for (int i = 0; i < n; i++) {
        y[i] = b[P[i]];
    }

    // Forward substitution to solve Ly = Pb
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            y[i] -= L[i][j] * y[j];
        }
    }

    // Backward substitution to solve Ux = y
    x.resize(n, 0);
    for (int i = n - 1; i >= 0; i--) {
        x[i] = y[i];
        for (int j = i + 1; j < n; j++) {
            x[i] -= U[i][j] * x[j];
        }
        x[i] /= U[i][i];
    }
}

int main() {
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif

    int n;
    cout << "Enter the dimension of matrix: ";
    cin >> n;

    vector<vector<double> > A(n, vector<double>(n, 0));
    vector<vector<double> > L, U;
    vector<int> P;
    vector<double> b(n, 0), x;

    cout << "Enter matrix A elements: ";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> A[i][j];
        }
    }

    cout << "Enter vector b elements: ";
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }

    if (lupDecomposition(A, L, U, P)) {
        cout << "L matrix:" << endl;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << L[i][j] << " ";
            }
            cout << endl;
        }

        cout << "U matrix:" << endl;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << U[i][j] << " ";
            }
            cout << endl;
        }

        lupSolve(L, U, P, b, x);

        ofstream output("output.txt");
        output << "Solution vector (x): ";
        for (int i = 0; i < n; i++) {
            output << x[i] << " ";
        }
        output.close();

        cout << "Solution vector written to output.txt" << endl;
    } else {
        cout << "Matrix is singular, decomposition not possible." << endl;
    }

    return 0;
}

//3
//2 -1 1
//-3 -1 2
//-2 1 2
//8 -11 -3
//
//Lower triangular matrix (L):
//1 0 0 
//-1.5 1 0 
//-1 0.333333 1 
//
//Upper triangular matrix (U):
//2 -1 1 
//0 -2.5 3.5 
//0 0 0.833333 
//
//Permutation vector (P): 0 1 2 
//
//Solution vector (x):
//2 -3 1 

