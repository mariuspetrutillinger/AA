#include <bits/stdc++.h>

using namespace std;


long long orientare(const pair<long long, long long> &p, const pair<long long, long long> &q, const pair<long long, long long> &r) {
    return (q.first - p.first) * (r.second - q.second) - (q.second - p.second) * (r.first - q.first);
}

vector<pair<long, long>> poligon;
long long n;
long long xMax, yMax2, xMin, yMin, yMax;

long long test(pair<long long, long long> pct) {
    pair<long long, long long> p, q;
    p = poligon[n - 1];
    q = poligon[1];

    // Folosim cautarea binara

    long o1 = orientare(poligon[0], p, pct);
    long o2 = orientare(poligon[0], q, pct);

    if (!(pct.first <= xMax && pct.second <= yMax && pct.first >= xMin && pct.second >= yMin))
        return 0; // 0 este  OUTSIDE
    if (o1 == 0 || o2 == 0)
        return 2; // 2 este BOUNDARY

    // cautare binara
    long long mid, left, right;
    left = 0;
    right = n;
    while (right - left > 1) {
        mid = (right + left) / 2;
        if (orientare(poligon[0], poligon[mid], pct) < 0)
            right = mid;
        else
            left = mid;
    }

    long long tt = orientare(poligon[left], poligon[(left + 1) % n], pct);
    if (tt > 0)
        return 1; // 1 este INSIDE
    else if (tt == 0)
        return 2;
    return 0;
}

ifstream in("in");

int main() {
    long long x, y;
    xMin = 100000000;
    yMin = 100000000;
    yMax = -1000000;
    xMax = -1000000;
    yMax2 = -1000000;
    long long xMinInd = 0;
    cin >> n;
    for (long long i = 0; i < n; i++) {
        cin >> x >> y;
        if (x < xMin || (x == xMin && y > yMax2)) {
            xMin = x;
            yMax2 = y;
            xMinInd = i;
        }
        if (y > yMax)
            yMax = y;
        if (x > xMax)
            xMax = x;
        if (y < yMin)
            yMin = y;
        poligon.emplace_back(x, y);
    }
    rotate(poligon.begin(), poligon.begin() + xMinInd, poligon.end());


    long long m;
    cin >> m;
    for (long long i = 0; i < m; i++) {
        cin >> x >> y;
        long long t = test(make_pair(x, y));
        if (t == 1)
            cout << "INSIDE\n";
        else if (t == 2)
            cout << "BOUNDARY\n";
        else
            cout << "OUTSIDE\n";
    }
    return 0;
}