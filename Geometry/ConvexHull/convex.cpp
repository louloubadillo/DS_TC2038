/**
 * @author Lourdes Badillo Granillo, Eduardo Villalpando Mello
 * @date 2021-11-03
 * Give an algorithm that computes the convex hull of any given set of n points in the plane efficiently 
*/

#include <bits/stdc++.h>
using namespace std;


struct point{
    int x; 
    int y; 
    point(int x, int y) : x(x), y(y) {}
    friend bool operator==(const point &p1, const point &p2){
        return p1.x == p2.x && p1.y && p2.y;
    }
}; 

bool sortPoints(point left, point right){
    return (left.x < right.x) || (left.x == right.x && left.y < right.y);
}

bool right_turn(const point &P1, const point &P2, const point &P3){
    return ((P3.x-P1.x)*(P2.y-P1.y) - (P3.y-P1.y)*(P2.x-P1.x)) > 0;
}


vector<point> convexHull(vector<point> P){
    //sort points
    sort(P.begin(), P.end(), sortPoints);

    vector<point> L_upper;
    vector<point> L_lower;
    vector<point> results;

    L_upper.push_back(P[0]);
    L_upper.push_back(P[1]);

    for(int i = 2; i < P.size(); i++){
        while(L_upper.size() > 1 && (!right_turn(L_upper[L_upper.size() - 2], L_upper[L_upper.size() - 1], P[i]))){
            L_upper.pop_back();
        }
        L_upper.push_back(P[i]);
    }

    L_lower.push_back(P[P.size() - 1]);
    L_lower.push_back(P[P.size() - 2]);

    for(int i = 2; i < P.size(); i++){
        while(L_lower.size() > 1 && (!right_turn(L_lower[L_lower.size() - 2], L_lower[L_lower.size() - 1], P[P.size() - i - 1]))){
            L_lower.pop_back();
        }
        L_lower.push_back(P[P.size() - i - 1]);
    }

    // Remove first and last element from L_lower
    L_lower.pop_back();
    L_lower.erase(L_lower.begin());

    //concatenate L_upper and L_lower in results
    results.insert(results.end(), L_upper.begin(), L_upper.end());
    results.insert(results.end(), L_lower.begin(), L_lower.end());  

    return results;
    
}

int main(int argc, char **argv){
    //N is the number of points
    int N = atoi(argv[1]);
    //vector of pairs p
    vector<point> P;

    for(int i = 0; i < N; i++){
        int x = atoi(argv[i+2]);
        int y = atoi(argv[i+2+N]);
        P.push_back(point(x,y));
    }

    vector<point> hull = convexHull(P);
    //print hull 
    for(int i = 0; i < hull.size(); i++){
        cout << "(" << hull[i].x << ", " << hull[i].y << ")" << endl;
    } 

    //TODO: Verificar orden de los puntos
    
    return 0;
}
