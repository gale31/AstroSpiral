#include<iostream>
#include<stack>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;

typedef struct
{
    double x, y;
    int number;
} point;

vector <point> points;

bool cmp(point a, point b)
{
    return atan2(a.y-points[0].y, a.x-points[0].x) <= atan2(b.y-points[0].y, b.x-points[0].x);
}

int myf(point a, point b)
{
    return a.number<b.number;
}

int det(point a, point b, point c)
{
    int dxa=a.x-c.x, dya=a.y-c.y;
    int dxb=b.x-c.x, dyb=b.y-c.y;
    return (dxa*dyb - dxb*dya);
}

int main(){

vector<point> spiral;
int n;

cin>>n;

point tmppoint;
for(int i=0; i<n; i++)
{
    cin>>tmppoint.x>>tmppoint.y;
    tmppoint.number=i+1;
    points.push_back(tmppoint);
}

int minind=0;
for(int i=1; i<points.size(); i++)
    if(points[i].y < points[minind].y) minind=i;
for(int i=1; i<points.size(); i++)
    if(points[i].y == points[minind].y) if(points[i].x < points[minind].x) minind=i;
swap(points[0], points[minind]);

spiral.push_back(points[0]);

for(; ;)
{
    if(points.size()==1) break;

    sort(points.begin()+1, points.end(), cmp);
    points.push_back(points[0]);

    int k=2;
    for(int i=3; i<points.size(); i++)
    {
        while(det(points[k], points[k-1], points[i])>0) k--;
        k++;
        swap(points[i], points[k]);
    }

    for(int i=1; i<k; i++) spiral.push_back(points[i]);

    points.erase(points.begin(), points.begin()+(k-1));
    points.erase(points.begin()+1, points.begin()+2);
}

for(int i=0; i<spiral.size(); i++) cout<<spiral[i].number<<" ";
cout<<endl;

return 0;
}
