#include <iostream>
#include <vector>
using namespace std;

struct Point {
    float x, y;
}; // punctul (x,y) din plan

int n; //n este numarul de puncte
vector<Point> P; //P este vectorul de puncte in plan
vector<Point> convexHull; //convexHull este vectorul de puncte din acoperirea convexa

// determina pozitia punctului R fata de dreapta PQ
int pointPositionDeterminant(const Point &P, const Point &Q, const Point &R) {
    float det = Q.x*R.y + P.x*Q.y + R.x*P.y - P.x*R.y - Q.x*P.y - R.x*Q.y;
    if (det == 0)
        return 0;
    return (det > 0) ? 1 : -1;
}

// determina punctul din P cu coordonata x minima (cel mai din stanga punct)
int leftMostPoint(const vector<Point> &P) {
    int leftMost = 1;
    for (int i = 2; i <= n; ++i) {
        if (P[i].x < P[leftMost].x)
            leftMost = i;
    }
    return leftMost;
}

// determina acoperirea convexa folosind algoritmul Jarvis March
void JarvisMarch(vector<Point> &P, vector<Point> &convexHull) {
    int leftMost = leftMostPoint(P);
    int p = leftMost, q;
    do {
        convexHull.push_back(P[p]);
        q = (p % n) + 1;
        for (int i = 1; i <= n; ++i) {
            if (pointPositionDeterminant(P[p], P[q], P[i]) == 1)
                q = i;
        }
        p = q;
    } while (p != leftMost);
}

int main() {
    cin >> n;
    P.resize(n+1);

    for (int i = 1; i <= n; ++i) {
        cin >> P[i].x >> P[i].y;
    }

    JarvisMarch(P, convexHull);

    cout << convexHull.size() << "\n";
    // afisam punctele din convexHull in ordine trigonometrica
    for (int i = convexHull.size()-1; i >= 0; --i) {
        cout << convexHull[i].x << " " << convexHull[i].y << "\n";
    }
}