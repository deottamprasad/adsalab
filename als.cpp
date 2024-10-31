#include <bits/stdc++.h>
using namespace std;

int findOptimalTime(int stationCount, const vector<vector<int> >& processTime, const vector<vector<int> >& transferTime, vector<int> entryTime, vector<int> exitTime) {
    if (stationCount <= 0) {
        cout << "Invalid number of stations." << endl;
        return -1;
    }
    if (processTime.size() != 2 || transferTime.size() != 2 || processTime[0].size() != stationCount || processTime[1].size() != stationCount || transferTime[0].size() != stationCount - 1 || transferTime[1].size() != stationCount - 1) {
        cout << "Input dimensions are incorrect." << endl;
        return -1;
    }

    vector<int> line1(stationCount), line2(stationCount), route1(stationCount), route2(stationCount);
    line1[0] = entryTime[0] + processTime[0][0];
    line2[0] = entryTime[1] + processTime[1][0];
    route1[0] = 1;
    route2[0] = 2;

    for (int i = 1; i < stationCount; i++) {
        line1[i] = min(line1[i - 1] + processTime[0][i], line2[i - 1] + transferTime[1][i - 1] + processTime[0][i]);
        route1[i] = (line1[i - 1] + processTime[0][i] <= line2[i - 1] + transferTime[1][i - 1] + processTime[0][i]) ? 1 : 2;

        line2[i] = min(line2[i - 1] + processTime[1][i], line1[i - 1] + transferTime[0][i - 1] + processTime[1][i]);
        route2[i] = (line2[i - 1] + processTime[1][i] <= line1[i - 1] + transferTime[0][i - 1] + processTime[1][i]) ? 2 : 1;
    }

    int finalTime = min(line1[stationCount - 1] + exitTime[0], line2[stationCount - 1] + exitTime[1]);
    int lastRoute = (line1[stationCount - 1] + exitTime[0] <= line2[stationCount - 1] + exitTime[1]) ? 1 : 2;

    cout << "Optimal assembly route:\nLine " << lastRoute << ", Station " << stationCount << endl;
    for (int i = stationCount - 1; i > 0; i--) {
        lastRoute = (lastRoute == 1) ? route1[i] : route2[i];
        cout << "Line " << lastRoute << ", Station " << i << endl;
    }

    return finalTime;
}

int main() {
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif

    int stationCount;
    cout << "Enter the number of stations: ";
    cin >> stationCount;
    if (stationCount <= 0) {
        cout << "Station count must be positive." << endl;
        return 0;
    }

    vector<vector<int> > processTime(2, vector<int>(stationCount)), transferTime(2, vector<int>(stationCount - 1));
    cout << "Enter processing times for each line:\n";
    for (int line = 0; line < 2; line++) {
        for (int station = 0; station < stationCount; station++) {
            cin >> processTime[line][station];
            if (processTime[line][station] < 0) {
                cout << "Processing times must be non-negative." << endl;
                return 0;
            }
        }
    }

    cout << "Enter transfer times between lines:\n";
    for (int line = 0; line < 2; line++) {
        for (int station = 0; station < stationCount - 1; station++) {
            cin >> transferTime[line][station];
            if (transferTime[line][station] < 0) {
                cout << "Transfer times must be non-negative." << endl;
                return 0;
            }
        }
    }

    vector<int> entryTime(2), exitTime(2);
    cout << "Enter entry times for each line: ";
    for (int i = 0; i < 2; i++) {
        cin >> entryTime[i];
        if (entryTime[i] < 0) {
            cout << "Entry times must be non-negative." << endl;
            return 0;
        }
    }
    cout << "Enter exit times for each line: ";
    for (int i = 0; i < 2; i++) {
        cin >> exitTime[i];
        if (exitTime[i] < 0) {
            cout << "Exit times must be non-negative." << endl;
            return 0;
        }
    }

    cout << "Minimum assembly time: " << findOptimalTime(stationCount, processTime, transferTime, entryTime, exitTime) << endl;
    return 0;
}


//4
//4 5 3 2
//2 10 1 4
//7 4 5
//9 2 8
//10 12
//18 7
//
//35
