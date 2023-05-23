#include <bits/stdc++.h>

using namespace std;

vector<pair<long long, long long>> points;
long long n;
long long xMinInd, yMinInd;


// Plecand de la punctul cu cel mai mic x, mergem de la stanga la dreapta. 
// Cand ajungem la punctul cu cel mai mare x, schimbam directia si mergem de la dreapta la stanga

bool compare(pair<long long, long long> p, pair<long long, long long> q){
    return  p.second < q.second;
}

bool xMonotonie(){
    bool orientation = true;
    // Ne dorim sa pastram ordinea trigonometrica, dar vrem sa shiftam fiecare punct astfel incat sa le ordonam in functie de x
    rotate(points.begin(), points.begin() + xMinInd, points.end());
    for(long long i = 0; i < n ; ++i){
        long long currentPct_x = points[(i+1) % n].first;
        long long anteriorPct_x = points[i].first;

        // Punctul anterior va avea x mai mic daca mergem de la stanga la dreapta si invers pt dreapta la stanga
        if (currentPct_x > anteriorPct_x && !orientation){
            return false;
        }

        // Putem sa ne miscam in directia opusa cand gasim un punct cu x mai mic decat x ul punctului anterior
        if(currentPct_x < anteriorPct_x && orientation)
            orientation = false;

        // Daca ajungem inapoi la punctul de start, verificam coliniaritatea cu alt punct si schimbam orientarea
        if(currentPct_x == anteriorPct_x && orientation){
            if(points[(i+2)%n].first < currentPct_x)
                orientation = false;
        }
    }
    return true;
}

bool yMonotonie(){
    bool orientation = true;
    yMinInd = min_element(points.begin(), points.end(), compare) - points.begin();
    rotate(points.begin(), points.begin() + yMinInd, points.end());
    for(long long i = 0; i < n ; ++i){
        long long currentPct_y = points[(i + 1) % n].second;
        long long anteriorPct_y = points[i].second;
        if (currentPct_y > anteriorPct_y && !orientation){
            return false;
        }
        if(currentPct_y < anteriorPct_y && orientation)
            orientation = false;
        if(currentPct_y == anteriorPct_y && orientation){
            if(points[(i+2)%n].second < currentPct_y)
                orientation = false;
        }
    }
    return true;
}

int main() {
    cin >> n;
    long long x, y;
    long long xMin = 100000000;
    xMinInd = 0, yMinInd = 0;
    for (long long i = 0; i < n; ++i) {
        cin >> x >> y;
        if(x < xMin)
        {
            xMin = x;
            xMinInd = i;
        }
        else if(x == xMin)
        {
            if(y < points[xMinInd].second)
            {
                xMin = x;
                xMinInd = i;
            }
        }
        points.emplace_back(x,y);
    }
    if(xMonotonie())
        cout<<"YES\n";
    else
        cout<<"NO\n";
    if(yMonotonie())
        cout<<"YES\n";
    else
        cout<<"NO\n";
}