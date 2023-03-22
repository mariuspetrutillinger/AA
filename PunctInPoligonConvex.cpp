#include <bits/stdc++.h>
#define pre (i==0)?(n-1):(i-1)
using namespace std;

struct Point {
    int x, y;
};

int orientation(const Point &P, const Point &Q, const Point &R) {
    long long det = Q.x*R.y + P.x*Q.y + R.x*P.y - P.x*R.y - Q.x*P.y - R.x*Q.y;
    if (det == 0)
        return 0;
    return (det > 0) ? 1 : -1;
}

bool compare(const Point &P, const Point &Q) {
    return P.x < Q.x;
}

int isBetween(const Point &a, const Point &b, const Point &c){
    if(orientation(a,b,c) == 0){
        if(min(a.x, b.x) <= c.x && c.x <= max(a.x, b.x) && min(a.y, b.y) <= c.y && c.y <= max(a.y, b.y) )
            return 1;
    }
    return 0;
}

class Polygon {
private:
    int n;
    vector<Point> points;
    int iLeftMost;
public:
    void read();

    int getN() const {
        return n;
    }

    vector<Point> getPoints() const {
        return points;
    }

    int getILeftMost() const {
        return iLeftMost;
    }

    void reorder(){
        vector <Point> list;
        for(int i=0; i<n;i++){
            list.push_back(points[(i+iLeftMost)%n]);
        }

        points = list;
    }

    int positionNonConvex(const Point &p){
        //raycasting on x coordonate
        int intersections = 0;
        for(int i=0; i<n;i++){

            if(isBetween(points[pre], points[i], p))
                return 0;

            if(p.y > min(points[pre].y, points[i].y) )
            if( points[i].y != points[pre].y
               && p.y <= max(points[i].y, points[pre].y) // punctul sa fie la nivelul dreptei
               &&  p.x < points[pre].x + 1.0*(p.y- points[pre].y)/(points[i].y - points[pre].y) * (points[i].x - points[pre].x))
                //punctul sa fie in stanga proiectiei sale pe dreapta
                intersections++;
        }

        return (intersections%2)*2-1;
    }

    int position(const Point &x) {
        int lower = 1;
        int upper = n-1;

        if(isBetween(points[0], points[lower], x)  || isBetween(points[0], points[upper], x) )
            return 0;

        if(orientation(points[0], points[lower], x) > 0 && orientation(points[0], points[upper], x) < 0 ){
            while(upper-lower != 1){

                int mid = (upper + lower)/2;

                if(orientation(points[0], points[mid], x) > 0){
                    lower = mid;
                }else{
                    upper = mid;
                }
            }
            //acum verificam daca este in interiorul triunghiului, sau pe linie
            if(isBetween(points[lower], points[upper], x)){
                return 0;
            }
            if(orientation(points[lower], points[upper], x) > 0 )
                return 1;
        }
        return -1;
    }

    int positionSlow(Point x){
        // trecem prin toate muchiile si verificam daca se afla de aceeasi parte a lor

        int k =1;

        for(int i=1;i<n;i++)
        {
            if(orientation(points[i-1], points[i], x) == 0)
                k = 0;

            if(orientation(points[i-1], points[i], x) < 0)
                return -1;
        }
        return k;
    }

    void isMonotone(){
        int xChanges = 0;
        int yChanges = 0;

        for(int i=2;i<n;i++){
            if( points[i-1].x -points[i].x !=0 &&
                1.0*(points[i-2].x -points[i-1].x) / (points[i-1].x -points[i].x) <0 ){
                xChanges ++;
            }

            if( points[i-1].y -points[i].y !=0 &&
                1.0*(points[i-2].y-points[i-1].y) / (points[i-1].y-points[i].y) <0 ){
                yChanges ++;
            }
        }



        if( points[n-1].x -points[0].x !=0 &&
            1.0*(points[n-2].x -points[n-1].x) / (points[n-1].x -points[0].x) <0 ){
            xChanges ++;
        }

        if( points[n-1].y -points[0].y !=0 &&
            1.0*(points[n-2].y -points[n-1].y) / (points[n-1].y -points[0].y) <0 ){
            yChanges ++;
        }



        if( points[0].x -points[1].x !=0 &&
            1.0*(points[n-1].x -points[0].x) / (points[0].x -points[1].x) <0 ){
            xChanges ++;
        }

        if( points[0].y -points[1].y !=0 &&
            1.0*(points[n-1].y -points[0].y) / (points[0].y -points[1].y) <0 ){
            yChanges ++;
        }

//        cout<<xChanges<<'\n';
//        cout<<yChanges<<'\n';

        (xChanges == 2)?cout<<"YES\n":cout<<"NO\n";
        (yChanges == 2)?cout<<"YES\n":cout<<"NO\n";

    }

    void afisare();

    void removeExtras(){

        for(int i=0;i<n;i++){
            if(orientation(points[i], points[(i+1)%n],points[(i+2)%n]) == 0){
                points.erase(points.begin()+(i+1)%n);
                n--;
                i--;
            }
        }
    }
};

void Polygon::read() {
    cin >> n;
        Point p;
        iLeftMost = 0;
        for (int i = 0; i < n; ++i) {
            cin >> p.x >> p.y;
            points.push_back(p);
            if (p.x < points[iLeftMost].x)
                iLeftMost = i;
            else if (p.x == points[iLeftMost].x && p.y < points[iLeftMost].y)
                iLeftMost = i;
        }
}
void Polygon::afisare() {
    for(int i=0;i<n;i++){
        cout<< points[i].x<<" "<<points[i].y<<'\n';
    }
}

int main() {
    Polygon p;
    p.read();
    // rezolvare
    p.reorder();
    p.removeExtras();
//    p.afisare();

    int m;
    Point x;
    cin>>m;
    while(m--){
        cin>>x.x>>x.y;

        switch(p.position(x)){
            case 1:
                cout<<"INSIDE\n";
                break;
            case 0:
                cout<<"BOUNDARY\n";
                break;
            default:
                cout<<"OUTSIDE\n";
                break;
        }
    }
}