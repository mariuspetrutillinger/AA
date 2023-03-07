#include <iostream>

using namespace std;

struct Point {
    float x, y;
}; // punctul (x,y) din plan

Point P,Q,R; // P,Q,R sunt puncte in plan
long t; //t este numarul de teste
float xp,yp,xq,yq,xr,yr; //xp,yp,xq,yq,xr,yr sunt coordonatele punctelor P,Q,R

// determina pozitia punctului R fata de dreapta PQ
string pointPositionDeterminant(Point P, Point Q, Point R) {
    float det = Q.x*R.y + P.x*Q.y + R.x*P.y - P.x*R.y - Q.x*P.y - R.x*Q.y;
    if (det > 0)
        return "LEFT";
    if (det < 0)
        return "RIGHT";
    return "TOUCH";
}

//input 
// 3
// 1 1 5 3 2 3
// 1 1 5 3 4 1
// 1 1 5 3 3 2

int main () {
    cin>>t;

    for(int i=1;i<=t;i++)
    {
        cin>>xp>>yp>>xq>>yq>>xr>>yr;
        P.x=xp;
        P.y=yp;
        Q.x=xq;
        Q.y=yq;
        R.x=xr;
        R.y=yr;

        cout<<pointPositionDeterminant(P,Q,R)<<endl;

    }

    return 0;
}