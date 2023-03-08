#include <bits/stdc++.h>

using namespace std;

// deoarece calculul folosind determinantul de mai devreme nu merge, am folosit o alta metoda
long pointPositionDeterminant(pair<long, long> P, pair<long, long> Q, pair<long, long> R) {
    long det = (Q.second - P.second) * (R.first - Q.first) -
             (Q.first - P.first) * (R.second - Q.second);
    if(det == 0)
        return 0;
    return (det > 0) ? 1 : -1;
}

int main() {
    long n;
    cin >> n;
    vector<pair<long, long>> P;

    for (long i = 1; i <= n; i++) {
        long x, y;
        cin >> x >> y;
        P.emplace_back(make_pair(x, y));
    }

    // incepem algoritmul Graham Scan
    // stiu ca nu aveam nevoie de sortari insa m-am gandit sa il fac asa ca sa am forma asta pentru copy paste
    // mai tarziu cand am nevoie
    sort(P.begin(), P.end());
    stack<pair<long, long>> s;

    s.push(P[0]);
    s.push(P[1]);

    for (long i = 2; i < n; i++) {
        pair<long, long> last = s.top();
        s.pop();
        pair<long, long> nextToLast = s.top();
        s.push(last);
        s.push(P[i]);

        while (s.size() > 2 && pointPositionDeterminant(nextToLast, last, P[i]) != 1) {
            s.pop();
            s.pop();
            s.push(P[i]);

            if(s.size()<=2)
                break;
            s.pop();
            last = s.top();
            s.pop();
            nextToLast = s.top();
            s.push(last);
            s.push(P[i]);

        }

    }

    vector<pair<long, long>> ConvexHull;
    while (!s.empty()) {
        ConvexHull.emplace_back(s.top());
        s.pop();
    }

    s.push(P[0]);
    s.push(P[1]);

    for (long i = 2; i < n; i++) {
        pair<long, long> last = s.top();
        s.pop();
        pair<long, long> nextToLast = s.top();
        s.push(last);
        s.push(P[i]);

        while (s.size() > 2 && pointPositionDeterminant(nextToLast, last, P[i]) != -1) {
            s.pop();
            s.pop();
            s.push(P[i]);

            if(s.size()<=2)
                break;

            s.pop();
            last = s.top();
            s.pop();
            nextToLast = s.top();
            s.push(last);
            s.push(P[i]);

        }

    }
    reverse(ConvexHull.begin(), ConvexHull.end());
    while (!s.empty()) {
        if(!count(ConvexHull.begin(), ConvexHull.end(), s.top()))
            ConvexHull.emplace_back(s.top());
        s.pop();
    }
    cout << ConvexHull.size() << endl;
    for (long i = ConvexHull.size() - 1; i >= 0; i--)
        cout << ConvexHull[i].first << " " << ConvexHull[i].second << endl;
    // afisarea punctelor din convex hull in ordine trigonometrica

    return 0;
}