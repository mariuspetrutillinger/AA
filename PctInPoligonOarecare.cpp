#include <bits/stdc++.h>

using namespace std;

long long n, m;
vector<pair<long long, long long>> poligon;


long long
testOrientare(pair<long long, long long> pct1, pair<long long, long long> pct2, pair<long long, long long> pct3) {
    long long to = (pct2.second - pct1.second) * (pct3.first - pct2.first) -
                   (pct2.first - pct1.first) * (pct3.second - pct2.second);
    return to;
}


long long x, y;

ifstream in("in2");

long long xMx = INT64_MIN, yMx = INT64_MIN, xMn = INT64_MAX, yMn = INT64_MAX;

int main() {

    // read polygon
    cin >> n;
    for (long long i = 0; i < n; i++) {
        cin >> x >> y;
        if (x > xMx)
            xMx = x;
        if (x < xMn)
            xMn = x;
        if (y > yMx)
            yMx = y;
        if (y < yMn)
            yMn = y;
        poligon.emplace_back(x, y);
    }
    cin >> m;
    // we have an infinite ray that is parallel with Ox and has a point on it
    for (long long i = 0; i < m; i++) {
        cin >> x >> y;
        long long nr = 0; // total number of intersections or -1 for BOUNDARY
        pair<long long, long long> cPct = make_pair(x, y);
        for (long long j = 0; j < n; j++) {
            int inter = 0; // intersection with current edge
            pair<long long, long long> p1, p2;
            p1 = poligon[j];
            p2 = poligon[(j + 1) % n];

            // we choose the points of an edge in trigonometric order
            if (p1.second > p2.second) {
                p1 = poligon[(j + 1) % n];
                p2 = poligon[j];
            }


            // if it doesn't intersect the edge we can go to the next one
            if ((p1.second > cPct.second && p2.second > cPct.second) ||
                (p1.second < cPct.second && p2.second < cPct.second)) {
                inter = 0;
                continue;
            }

            // if all the points have the same y, they are collinear and on the ray
            if (p1.second == p2.second && p1.second == cPct.second) {
                // we check the x to see if it's on the edge
                if ((cPct.first > p1.first && cPct.first < p2.first) ||
                    (cPct.first > p2.first && cPct.first < p1.first)) {
                    nr = -1; // -1 translates to BOUNDARY
                    break;
                } else {
                    inter = 0;
                    continue;
                }
            }

            // if none of the above special cases are fulfilled we use the orientation test
            long long to = testOrientare(p1, cPct, p2);
            // 0 means is on an edge
            if (to == 0) {
                nr = -1;
                break;
            }

            // right turn means no intersection
            if (to > 0) {
                inter = 0;
                continue;
            }

            // collinear with the second point means intersection
            if (p2.second == cPct.second) {
                inter = 1;
                nr+=inter;
                continue;
            }
            // if point's y is greater than the first point and smaller than the other we have an intersection
            //              or the other way
            // (because none of the above cases was satisfied it means we are in polygon y boundaries)
            if ((cPct.second < p1.second && cPct.second > p2.second) ||
                (cPct.second > p1.second && cPct.second < p2.second)) {
                inter = 1;
                nr+=inter;
                continue;
            }

        }

        if (nr == -1)
            cout << "BOUNDARY\n";
        else if (nr % 2)
            cout << "INSIDE\n";
        else
            cout << "OUTSIDE\n";
    }


    return 0;
}