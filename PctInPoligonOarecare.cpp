#include <bits/stdc++.h>

using namespace std;

long long n, m;
vector<pair<long long, long long>> poligon;


long long orientare(pair<long long, long long> p, pair<long long, long long> q, pair<long long, long long> r) {
    long long o = (q.second - p.second) * (r.first - q.first) - (q.first - p.first) * (r.second - q.second);
    return o;
}


long long x, y;

long long xMax = -1000000, yMax = -1000000, xMin = 1000000, yMin = 1000000;

int main() {

    // citim datele de intrare
    cin >> n;
    for (long long i = 0; i < n; ++i) {
        cin >> x >> y;
        if (x > xMax)
            xMax = x;
        if (x < xMin)
            xMin = x;
        if (y > yMax)
            yMax = y;
        if (y < yMin)
            yMin = y;
        poligon.emplace_back(x, y);
    }
    cin >> m;
    // avem o dreapta infinita paralela cu Ox si care are un punct pe ea

    for (long long i = 0; i < m; ++i) {
        cin >> x >> y;
        long long nr = 0; // numarul total de intersectii cu poligonul
        pair<long long, long long> currentPct = make_pair(x, y);

        for (long long j = 0; j < n; j++) {
            // verificam daca punctul curent intersecteaza muchia poligonului
            int intersection = 0; 
            pair<long long, long long> p, q;
            p = poligon[j];
            q = poligon[(j + 1) % n];

            // mergem in ordine trigonometrica
            if (p.second > q.second) {
                p = poligon[(j + 1) % n];
                q = poligon[j];
            }


            // daca nu avem intersectie, mergem mai departe
            if ((p.second > currentPct.second && q.second > currentPct.second) ||
                (p.second < currentPct.second && q.second < currentPct.second)) {
                intersection = 0;
                continue;
            }

            // coliniaritatea este data de y 
            if (p.second == q.second && p.second == currentPct.second) {
                // verificam daca coordonata x a punctului curent este in interiorul muchiei
                if ((currentPct.first > p.first && currentPct.first < q.first) ||
                    (currentPct.first > q.first && currentPct.first < p.first)) {
                    nr = -1; // -1 este BOUNDARY
                    break;
                } else {
                    intersection = 0;
                    continue;
                }
            }

            // daca nu satisfacem cazurile precedente, facem testul de orientare
            long long o = orientare(p, currentPct, q);
            // 0 inseamna coliniaritate
            if (o == 0) {
                nr = -1;
                break;
            }

            // intoarcerea la dreapta inseamna ca nu avem intersectie
            if (o > 0) {
                intersection = 0;
                continue;
            }

            // coliniaritate inseamna intersectie
            if (q.second == currentPct.second) {
                intersection = 1;
                nr+=intersection;
                continue;
            }
            
            // daca punctul curent are coordonata y mai mare decat prima muchie si mai mica decat a doua muchie
            // sau invers, atunci avem o intersectie
            if ((currentPct.second < p.second && currentPct.second > q.second) ||
                (currentPct.second > p.second && currentPct.second < q.second)) {
                intersection = 1;
                nr+=intersection;
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