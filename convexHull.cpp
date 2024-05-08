#include <iostream>
#include <stack>
#include <stdlib.h>
using namespace std;

struct Point {
	int x, y;
};

Point p0;

//function to find next to top in a stack
Point nextToTop(stack<Point> &S) {
	Point p = S.top();
	S.pop();
	Point res = S.top();
	S.push(p);
	return res;
}

//function to swap two points
void swap(Point &p1, Point &p2) {
	Point temp = p1;
	p1 = p2;
	p2 = temp;
}

//function to return square of distance between 2 points 
int distSq(Point p1, Point p2) {
	return (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y);
}

// function to find orientation of ordered triplet (p, q, r)
int orientation(Point p, Point q, Point r) {
	int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
	if (val == 0) return 0; // collinear
	return (val > 0)? 1: 2; // clockwise or counterclockwise
}

//function to compare points
int compare(const void *vp1, const void *vp2) {
    Point *p1 = (Point *)vp1;
    Point *p2 = (Point *)vp2;
    int o = orientation(p0, *p1, *p2);
    if (o == 0)
        return (distSq(p0, *p2) >= distSq(p0, *p1))? -1 : 1;
    return (o == 2)? -1: 1;
}

// function to print convex hull of a set of n points.
void convexHull(Point points[], int n) {
    int ymin = points[0].y, min = 0;
    for (int i = 1; i < n; i++) {
        int y = points[i].y;
        if ((y < ymin) || (ymin == y && points[i].x < points[min].x))
            ymin = points[i].y, min = i;
    }

    swap(points[0], points[min]);

    // sorting n-1 points with respect to the first point
    p0 = points[0];
    qsort(&points[1], n-1, sizeof(Point), compare);

    int m = 1;
    for (int i=1; i<n; i++) {
        while (i < n-1 && orientation(p0, points[i], points[i+1]) == 0)
            i++;
        points[m] = points[i];
        m++;
    }

    if (m < 3) {
        cout<<"\nConvex hull not possible";
        return;
    }
    //stack containing 1st 3 points
    stack<Point> S;
    S.push(points[0]);
    S.push(points[1]);
    S.push(points[2]);

    //for remaining n-3 points
    for (int i = 3; i < m; i++) {
        while (S.size()>1 && orientation(nextToTop(S), S.top(), points[i]) != 2)
            S.pop();
        S.push(points[i]);
    }

    // Now stack has the output points, print contents of stack
    cout<<"\nThe set of points in the convex hull:\n";
    while (!S.empty()) {
        Point p = S.top();
        cout << "(" << p.x << ", " << p.y <<")" << endl;
        S.pop();
    }
}

int main() {
    int n;
    cout<<"Enter number of points: ";
    cin>>n;
    Point points[n];
    for(int i=0; i<n; i++){
        cout<<"Enter x coordinates of point "<<(i+1)<<": ";
        cin>>points[i].x;
        cout<<"Enter y coordinates of point "<<(i+1)<<": ";
        cin>>points[i].y;
    }
	convexHull(points, n);
	return 0;
}
