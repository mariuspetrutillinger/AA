#include <iostream>
#include <vector>
using namespace std;

struct Point {
    float x, y;
}; // punctul (x,y) din plan

int n; //n este numarul de puncte
vector<Point> P; //P este vectorul de puncte in plan
int turnLeft = 0, turnRight = 0, touch = 0; //turnLeft, turnRight, touch sunt numarul de puncte care se afla la stanga, dreapta si pe dreapta PQ

// determina pozitia punctului R fata de dreapta PQ
string pointPositionDeterminant(Point P, Point Q, Point R) {
    float det = Q.x*R.y + P.x*Q.y + R.x*P.y - P.x*R.y - Q.x*P.y - R.x*Q.y;
    if (det > 0)
        return "LEFT";
    if (det < 0)
        return "RIGHT";
    return "TOUCH";
}

int main () {
    cin >> n;
    P.resize(n+2);

    for (int i = 1; i <= n; i++) {
        cin >> P[i].x >> P[i].y;
    }
    P[n+1]= P[1];

    // pentru fiecare punct din P il consideram R si determinam pozitia fata de dreapta PQ
    for (int i = 1; i < n; i++) {
        string position = pointPositionDeterminant(P[i], P[i+1], P[i+2]);
        if (position == "LEFT")
            turnLeft++;
        else if (position == "RIGHT")
            turnRight++;
        else
            touch++;
    }

    cout << turnLeft << " " << turnRight << " " << touch << "\n";

    return 0;
}