#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct Point {
     int x, y;
}; // punctul (x,y) din plan

 int n; //n este numarul de puncte
 vector<Point> P; //P este vectorul de puncte in plan
 vector<Point> convexHull; //convexHull este vectorul de puncte din acoperirea convexa

 // determina pozitia punctului R fata de dreapta PQ
 int pointPositionDeterminant(const Point &P, const Point &Q, const Point &R) {
     long long det = Q.x*R.y + P.x*Q.y + R.x*P.y - P.x*R.y - Q.x*P.y - R.x*Q.y;
     if (det == 0)
         return 0;
     return (det > 0) ? 1 : -1;
 }

 double distance(const Point &P, const Point &Q) {
    return sqrt(pow((Q.x - P.x), 2) + pow(Q.y - P.y, 2));
}

 // determina acoperirea convexa folosind algoritmul Jarvis March
 void JarvisMarch(int leftMost) {
     int p = leftMost, q;
     q = (p % n) + 1;
     convexHull.push_back(P[p]);
     while (true) {
         q = (p+1) % P.size();
            for (int i = 1; i < P.size(); ++i) {
                if (i == p)
                    continue;
                long long det = pointPositionDeterminant(P[p], P[i], P[q]);
                if (det == -1 || (det == 0 && distance(P[p], P[i]) > distance(P[p], P[q])))
                    q = i;
            }
            p = q;
            if (p == leftMost)
                break;
            convexHull.push_back(P[p]);
     }
 }

 int main() {
     cin >> n;
     P.resize(n+1);

     int leftMost = 1;
     for (int i = 1; i <= n; ++i) {
         cin >> P[i].x >> P[i].y;
         if (P[i].x < P[leftMost].x)
             leftMost = i;
     }

     JarvisMarch(leftMost);

     cout << convexHull.size() << "\n";
     // afisam punctele din convexHull in ordine trigonometrica
     for (int i = convexHull.size()-1; i >= 0; --i) {
         cout << convexHull[i].x << " " << convexHull[i].y << "\n";
     }
 }
