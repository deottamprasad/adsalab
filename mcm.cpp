#include <iostream>
#include <vector>
#include <limits>
#include <sstream>
#include <string>

using namespace std;

int matrixChainOrder(const vector<int>& p, int n, vector<vector<int> >& m, vector<vector<int> >& s) {
    for (int chainLength = 2; chainLength <= n; ++chainLength) {
        for (int i = 0; i < n - chainLength + 1; ++i) {
            int j = i + chainLength - 1;
            m[i][j] = numeric_limits<int>::max();
            for (int k = i; k < j; ++k) {
                int q = m[i][k] + m[k + 1][j] + p[i] * p[k + 1] * p[j + 1];
                if (q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }
    return m[0][n - 1];
}

void printParenthesization(const vector<vector<int> >& s, int i, int j) {
    if (i == j) {
        cout << "A" << i + 1;
    } else {
        cout << "(";
        printParenthesization(s, i, s[i][j]);
        printParenthesization(s, s[i][j] + 1, j);
        cout << ")";
    }
}

int main() {
	#ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    vector<int> dimensions;
    int value;

    cout << "Enter the dimensions of the matrices (in the format: d1 d2 d3 ... dn, where di represents the dimensions of Ai): ";
    
    while (cin >> value) {
        dimensions.push_back(value);
        if (cin.peek() == '\n') break;
    }

    int n = dimensions.size() - 1;
    vector<vector<int> > m(n, vector<int>(n, 0));
    vector<vector<int> > s(n, vector<int>(n, 0));

    int minMultiplications = matrixChainOrder(dimensions, n, m, s);

    cout << "Minimum number of multiplications is: " << minMultiplications << endl;
    cout << "MCM Table:" << endl;
    for (int i = 0; i < n; ++i) {
	    for (int j = 0; j < n; ++j) {
	        cout << m[i][j] << "\t";
	    }
	    cout << endl;
	}

    cout << "Optimal Parenthesization: ";
    printParenthesization(s, 0, n - 1);
    cout << endl;

    return 0;
}
//30 35 15 5 10 20 25
