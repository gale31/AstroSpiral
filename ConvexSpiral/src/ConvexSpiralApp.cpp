#include "cinder/app/AppBasic.h"
#include "cinder/Text.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/Utilities.h"

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <cmath>

using namespace ci;
using namespace ci::app;
using namespace std;

class ConvexSpiralApp : public AppBasic
{
    public:
    void setup();
    void draw();
    void main();

    gl::Texture myImage;

};

typedef struct
{
    int x, y;
    int number;
} point;


vector <point> points;
vector<point> pixels;

int br=0;

bool gr[10000][10000]={0}, used[10000]={0};

set <int> brightness;

int averageb;
Surface::Iter AverageBrightness( Surface *surface, Area area )
{
    Surface::Iter iter = surface -> getIter(area);
    
    set <int> brightness;
    
    while( iter.line() )
    {
        while( iter.pixel() )
        {
            brightness.insert(iter.r());
        }
    }
    
    int sum=0;
    set<int>::iterator it;
    
    for (it=brightness.begin(); it!=brightness.end(); it++) sum = sum + *it;
    
    averageb = sum / brightness.size();
    
    return iter;
}


Surface::Iter TurnBinary( Surface *surface, Area area )
{
    Surface::Iter iter = surface->getIter( area );
    
    while( iter.line() )
    {
        while( iter.pixel() )
        {
            if((iter.r()>=0 && iter.r()<=averageb) && (iter.g()>=0 && iter.g()<=averageb) && (iter.b()>=0 && iter.b()<=averageb))
            { iter.r() = 0; iter.g() = 0; iter.b() = 0;}
        
            else { iter.r() = 255; iter.g() = 255; iter.b() = 255; }
        }
    }
    
    return iter;
}

int num = 0;

void TurnPixel( Surface *surface, Area area )
{
    Surface::Iter iter = surface -> getIter(area);
    
    while(iter.line())
    {
        while(iter.pixel())
        {
            if(iter.r()==255 && iter.g()==255 && iter.b()==255)
            {
                br++;
                point p;
                
                p.number=br;
                
                p.x=iter.x();
                p.y=iter.y();
                
                if(iter.r(-1, 0)==255 && iter.g(-1, 0)==255 && iter.b(-1, 0)==255) //if the left pixel was white
                {
                    gr[br][br-1]=1;
                    gr[br-1][br]=1;
                }
                
                if(iter.r(0, -1)==255 && iter.g(0, -1)==255 && iter.b(0, -1)==255) //if the right pixel was white
                {
                    for(int i=br-1; i>=0; i--)
                    {
                        if(pixels[i].x==iter.x() && pixels[i].y==iter.y()-1)
                        {
                            gr[br][i+1]=1;
                            gr[i+1][br]=1;
                            break;
                        }
                    }
                }
                pixels.push_back(p);
            }
        }
    }
    
}

int maxx, minx, maxy, miny;
void find_component(int v)
{
    used[v]=1;
    
    if(maxx<pixels[v-1].x) maxx=pixels[v-1].x;
    if(maxy<pixels[v-1].y) maxy=pixels[v-1].y;
    if(minx>pixels[v-1].x || minx==-1) minx=pixels[v-1].x;
    if(miny>pixels[v-1].y || miny==-1) miny=pixels[v-1].y;
    
    for(int i=1; i<=br; i++)
    {
        if(gr[v][i]==1 && !used[i]) find_component(i);
    }
}

void MakeLine(Surface *surface, Area area, int x1, int y1, int x2, int y2)
{
    Surface::Iter iter = surface->getIter( area );
    int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;

    dx = x2 - x1; dy = y2 - y1;
    dx1 = fabs(dx); dy1 = fabs(dy);
    px = 2 * dy1 - dx1; py = 2 * dx1 - dy1;
    
    if( dy1 <= dx1)
    {
        if( dx >= 0)
        {
            x = x1; y = y1;
            xe = x2;
        }
        else
        {
            x = x2; y = y2;
            xe = x1;
        }

        iter.r(x, y) = 255;
        iter.g(x, y) = 255;
        iter.b(x, y) = 255;

        for(i = 0; x < xe;i ++)
        {
            x = x + 1;
            if( px < 0) px = px + 2 * dy1;
            
            else
            {
                if((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) y = y + 1;
                else y = y - 1;
                
                px = px + 2 * ( dy1 - dx1);
            }
            
            iter.r(x, y) = 255;
            iter.g(x, y) = 255;
            iter.b(x, y) = 255;
            
        }
    }
    
    else
    {
        if(dy>=0)
        {
            x = x1;
            y = y1;
            ye = y2;
        }
        
        else
        {
            x = x2;
            y = y2;
            ye = y1;
        }
        
        iter.r(x, y) = 255;
        iter.g(x, y) = 255;
        iter.b(x, y) = 255;
        
        for(i = 0; y < ye; i ++)
        {
            y = y + 1;
            
            if(py <= 0) py = py + 2 * dx1;
            else
            {
                if((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) x = x + 1;
                else x = x - 1;

                py = py + 2 * ( dx1 - dy1);
            }

            iter.r(x, y) = 255;
            iter.g(x, y) = 255;
            iter.b(x, y) = 255;
        }
    }
}

Surface processImage(const Surface input )
{
    Surface resultSurface( input.clone() );
    
    AverageBrightness( &resultSurface, Area (input.getWidth(), input.getHeight(), 0 , 0));
    TurnBinary( &resultSurface, Area (input.getWidth(), input.getHeight(), 0 , 0));
    TurnPixel( &resultSurface, Area (input.getWidth(), input.getHeight(), 0 , 0));
    
    return resultSurface;
}

Surface processImage2( const Surface input )
{
    Surface resultSurface( input.clone() );
    
    for(int i=0; i < points.size()-1; i++)
        MakeLine(&resultSurface, Area (input.getWidth(), input.getHeight(), 0, 0), points[i].x, points[i].y, points[i+1].x, points[i+1].y);
    
    return resultSurface;
}

int det(point a, point b, point c)
{
    int dxa = a.x-c.x, dya = c.y-a.y;
    int dxb = b.x-c.x, dyb = c.y-b.y;
    
    return (dxa*dyb - dxb*dya);
}

bool oriant(point a, point b, point c)
{
    double tmp = det(a, b, c);
    if(tmp >= 0) return 1;
    else return 0;
}

void findFirst()
{
    int maxind=0;
    for(int i=1; i<points.size(); i++)
        if(points[i].y > points[maxind].y) maxind=i;
    for(int i=1; i<points.size(); i++)
        if(points[i].y == points[maxind].y) if(points[i].x < points[maxind].x) maxind=i;
    
     swap(points[0], points[maxind]);
}

double value (point p0, point p1, point p2)
{
    double ax = p1.x - p0.x;
    double ay = p1.y - p0.y;
    double bx = p2.x - p1.x;
    double by = p2.y - p1.y;
    double L = sqrt ( bx * bx + by * by );
    return ( ax * bx + ay * by ) / L;
}

void findSecond()
{
    point p1;
    
    p1.x = points[0].x + 1.0;
    p1.y = points[0].y;
    
    int j = 1;
    double v = -1e10;
    
    for(int i = 1; i < points.size(); i++)
    {
        if ( value( points[0] , p1 , points[i] ) > v)
        {
            v = value ( points[0] , p1, points[i]);
            j = i;
        }
    }
    swap(points[1], points[j]);
}

void findNext(int k)
{
    int j=1;
    
    double v=-1e10;
    
    for(int i = k + 1 ; i < points.size(); i ++)
    {
        double w = value (points[k-1], points[k], points[i]);
        if(w > v) { v = w; j = i;}
    }
    swap( points[k+1], points[j]);
}

void MakeSpiral()
{
    findFirst();
    findSecond();
         
    for(int k = 1; k < points.size() - 3; k ++) findNext(k);
    
    bool w = oriant (points[points.size() - 3], points[points.size() - 2], points[points.size() - 1]);
    bool prevw = oriant (points[points.size() - 5], points[points.size() - 4], points[points.size() - 3]);

    if((prevw == 1 && w == 0) || (prevw == 0 && w == 1)) swap(points[points.size() - 2], points[points.size() - 1]);
}

vector<point> mark;

point pnt1, pnt2, pnt3;

void ConvexSpiralApp::setup()
{
    try
    {
        ci::fs::path img = getOpenFilePath( "", ImageIo::getLoadExtensions());
        
        if( ! img.empty() ) // an empty string means the user canceled
        {
            Surface processedImage( processImage( loadImage( img ) ) );
            myImage = gl::Texture( processedImage );
            
            for(int i=1; i<=br; i++)
            {
                if(used[i]==0)
                {
                    maxx = -1; minx = -1; maxy = -1; miny = -1;
                    
                    find_component(i);
                    
                    cout<<endl;
                    
                    point newcenter;
                    
                    int centerx = minx + (maxx-minx)/2;
                    int centery = miny + (maxy-miny)/2;
                    
                    newcenter.x = centerx;
                    newcenter.y = centery;
                    
                    points.push_back(newcenter);
                }
            }
            
            
            vector <point> points1;
            
            for(int i = 0; i < points.size(); i++)
                points1.push_back(points[i]);
            
            pnt1 = points[1]; pnt2 = points[3]; pnt3 = points[5];
            
            MakeSpiral();
            
            Surface processedImage3( processImage2( loadImage( img ) ) );
            myImage = gl::Texture( processedImage3 );
            
        }
    }

    catch( ... )
    {
        console() << "Unable to load the image." << std::endl;
    }
}

bool write1 = true;
void ConvexSpiralApp::draw()
{
    setWindowSize(myImage.getWidth(), myImage.getHeight() );
    gl::draw( myImage, getWindowBounds());
    writeImage( getHomeDirectory() /"Documents"/"AstroSpiral"/"res"/"result1.png", copyWindowSurface() );
}

CINDER_APP_BASIC( ConvexSpiralApp, RendererGl );

