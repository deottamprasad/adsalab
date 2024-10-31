#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

struct Point { double x, y; };
struct LineSegment { Point p1, p2; };

bool nearlyEqual(double a, double b, double epsilon = 1e-9) { return abs(a - b) < epsilon; }

int orientation(Point p, Point q, Point r) {
    double val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    return nearlyEqual(val, 0) ? 0 : (val > 0 ? 1 : 2);
}

bool onSegment(Point p, Point q, Point r) {
    return q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) && q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y);
}

bool doIntersect(LineSegment l1, LineSegment l2, Point &intersection) {
    Point p1 = l1.p1, q1 = l1.p2, p2 = l2.p1, q2 = l2.p2;
    int o1 = orientation(p1, q1, p2), o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1), o4 = orientation(p2, q2, q1);

    if (o1 != o2 && o3 != o4) {
        double a1 = q1.y - p1.y, b1 = p1.x - q1.x, c1 = a1 * p1.x + b1 * p1.y;
        double a2 = q2.y - p2.y, b2 = p2.x - q2.x, c2 = a2 * p2.x + b2 * p2.y;
        double det = a1 * b2 - a2 * b1;
        if (!nearlyEqual(det, 0)) {
            intersection.x = (b2 * c1 - b1 * c2) / det;
            intersection.y = (a1 * c2 - a2 * c1) / det;
            return true;
        }
    }
    if (o1 == 0 && onSegment(p1, p2, q1)) { intersection = p2; return true; }
    if (o2 == 0 && onSegment(p1, q2, q1)) { intersection = q2; return true; }
    if (o3 == 0 && onSegment(p2, p1, q2)) { intersection = p1; return true; }
    if (o4 == 0 && onSegment(p2, q1, q2)) { intersection = q1; return true; }
    return false;
}

void checkIntersections() {
    int n;
    cout << "Enter the number of line segments: ";
    cin >> n;
    vector<LineSegment> segments(n);
    cout << "Enter the line segments in the format 'x1,y1,x2,y2' (one per line):" << endl;

    for (int i = 0; i < n; ++i) {
        string line;
        cin >> ws;
        getline(cin, line);
        stringstream ss(line);
        vector<double> coords;
        string temp;
        while (getline(ss, temp, ',')) coords.push_back(stod(temp));
        segments[i] = {{coords[0], coords[1]}, {coords[2], coords[3]}};
    }

    bool hasIntersection = false;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            Point intersection;
            if (doIntersect(segments[i], segments[j], intersection)) {
                cout << "Intersection found between segments: " << i << " and " << j;
                cout << " at point (" << intersection.x << ", " << intersection.y << ")" << endl;
                hasIntersection = true;
            }
        }
    }
    if (!hasIntersection) cout << "No intersecting line segments found." << endl;
}

int main() {
	#ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    checkIntersections();
    return 0;
}

//4
//0,0,3,3
//1,1,4,4
//2,0,2,5
//3,1,5,1

