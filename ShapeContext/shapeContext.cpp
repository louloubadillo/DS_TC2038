/**
 * @author Lourdes Badillo Granillo, Eduardo Villalpando Mello
 * @date 2021-11-25
 * Shape context algorithm 
 * 
 * 
*/

#include <bits/stdc++.h>
using namespace std;


struct point{
    float x; 
    float y; 
    int index; 
    point(float x, float y, int index) : x(x), y(y), index(index) {}
    friend bool operator==(const point &p1, const point &p2){
        return p1.x == p2.x && p1.y && p2.y;
    }
    friend bool operator<(const point &p1, const point &p2){
        return p1.index < p2.index;
    }
}; 


struct histograma{
    vector<vector<int>> data;
    histograma(vector<vector<int>> data) : data(data){}
};

bool sortPoints(point left, point right){
    return (left.x < right.x) || (left.x == right.x && left.y < right.y);
}

bool sortByIndex(point left, point right){
    return left.index < right.index;
}

float getDistanceBetweenPoints(point origin, point p){
    float deltaX = origin.x - p.x;
    float deltaY = origin.y - p.y;
    return sqrt( pow(deltaX, 2) + pow(deltaY, 2) );
}

float getAngleBetweenPoints(point origin, point p){
    float deltaX = origin.x - p.x;
    float deltaY = origin.y - p.y;
    float angle = atan2(deltaY, deltaX);
    //transform to degrees
    angle = angle * (180 / M_PI);
    //handle negative angles
    if(angle < 0){
        angle += 360;
    }
    return angle;
}

// program to find modulo of floating point number
float findMod(float a, float b){
    float mod; 
    if(a < 0){
        mod = -a; 
    }
    else{
        mod = a; 
    }
    if(b < 0){
        b = -b;
    }
    while(mod >= b){
        mod -= b; 
    }
    if(a<0){
        return -mod; 
    }
    return mod; 
}

histograma descriptorPoint(vector<point>& points, point p){
    // Size
    int t_points = points.size();
    // Generate histogram (12 x 5)
    // int histogram[12][5] = {0};
    vector<vector<int>> histogram(5, vector<int>(12, 0));

    // Distances and angles
    float distances[t_points];
    float angles[t_points];

    // Iterate over each point to find distance and angle
    for(int i = 0; i < t_points; i++){
        distances[i] = getDistanceBetweenPoints(points[i], p);
        angles[i] = getAngleBetweenPoints(points[i], p);
    }

    // Bin sizes
    float angleSize = 360 / 12;
    float radialSize = 10 / 5;

    // Make histogram
    for(int i = 0; i < t_points; i++){
        // Get distance and angle
        float distance = distances[i];
        float angle = angles[i];
        // if (points[i] == p) continue;
        // if (angle == 0 && distance == 0) continue;
        // Get indices from distance and angle
        if (distance > 10) continue;
        
        // Case for angle % angleSize == 0

        // if((int)angle%30 == 0 && indexAngle != 0) {
        if(fmod(angle, 30.0f) == 0 && angle != 0){
            angle--;
        }
        if (distance == 10){
            distance--;
        }
        if(fmod(distance, 2.0f) == 0 && distance !=0){
          distance--;
        }
        // Breaks
        int indexAngle = floor(angle/angleSize);
        int indexDistance = floor(distance/radialSize);
        // Increment count on distances
        histogram[indexDistance][indexAngle]++;
    }
    histogram[0][0]--;

    //Print histogram
    for(int i = 0; i < histogram.size(); i++){
        for(int j = 0; j < histogram[i].size(); j++){
            cout << histogram[i][j];
            if(j != histogram[i].size() - 1){
              cout << " ";
            }
        }
        cout << endl;
    }

    return histograma(histogram);
}

map<point, histograma> contextShape(vector<point> points){
    map<point, histograma> result;
    // for all points in points
    for(int i = 0; i < points.size(); i++){
        // get descriptor of point
        // cout << "Point " << i+1 << ": " << endl; 
        histograma h = descriptorPoint(points, points[i]);
        if(i != points.size() - 1){
          cout << endl;
        }
        result.insert(make_pair(points[i], h));
    }
    return result;
    // descriptorPoint(points, points[0]);
}

/*Extra function :D*/
//Matching costs
 
float matchingCostBetweenTwoPoints(histograma pointAMatrix, histograma pointBMatrix){
    //crear matriz de costos
    //tomar descriptor para la forma de la izq y para la forma de la derecha
    //para cada uno de los valores en la matriz
        //m[i,j] = formula
    float result = 0;
    for(int i = 0; i < pointAMatrix.data.size(); i++){
        for(int j = 0; j < pointAMatrix.data[0].size(); j++){
            result += 0.5*pow(abs( pointAMatrix.data[i][j] - pointBMatrix.data[i][j] ), 2)/(pointAMatrix.data[i][j] + pointBMatrix.data[i][j]);
        }
    }
    return result;
}

vector<vector<float>> matchingCostMatrix(vector<point> image1, vector<point> image2){
    vector<vector<float>> result(image1.size(), vector<float>(image2.size()));
    for(int i = 0; i < image1.size(); i++){
        for(int j = 0; j < image2.size(); j++){
            result[i][j] = matchingCostBetweenTwoPoints(descriptorPoint(image1, image1[i]), descriptorPoint(image2, image2[j]));
        }
    }
    return result;
}

int main(int argc, char **argv){
    //N is the number of points
    int N = atoi(argv[1]);
    //Vector of pairs p
    vector<point> P;
    sort(P.begin(), P.end());
    for(int i = 0; i < N; i++){
        float x = atof(argv[i+2]);
        float y = atof(argv[i+2+N]);
        P.push_back(point(x,y,i));

        // cout << "("<<i<<") " << x << ", " << y << endl;
    }

    // descriptor(P);
    contextShape(P);
    
    return 0;
}