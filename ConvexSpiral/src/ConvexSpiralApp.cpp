#include "cinder/app/AppBasic.h"
#include "cinder/Text.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/Utilities.h"

#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace ci;
using namespace ci::app;
using namespace std;

class ConvexSpiralApp : public AppBasic {
  public:
	void setup();
    void prepareSettings();
	void draw();
    void main();
    void mouseDown( MouseEvent event );
    
    gl::Texture myImage;
};

typedef struct
{
    int x, y;
    int numgf;
} point;

vector <point> points;
vector<point> spiral;

bool cmp(point a, point b)
{
    return atan2(-(a.y-points[0].y), a.x-points[0].x) < atan2(-(b.y-points[0].y), b.x-points[0].x);
}

int det(point a, point b, point c)
{
    int dxa = a.x-c.x, dya = c.y-a.y;
    int dxb = b.x-c.x, dyb = c.y-b.y;
    
    return (dxa*dyb - dxb*dya);
}

bool used[1024]={0};

void dfs(int v)
{
    cout<<v+1;
    used[v]=1;
    
    for(int i=0; i<n; i++)
    {
        if(gr[v][i]!=0 && !used[i]) dfs(i);
    }
}

Surface::Iter TurnBinary( Surface *surface, Area area )
{
    Surface::Iter iter = surface->getIter( area );
    
    while( iter.line() )
    {
        while( iter.pixel() )
        {
            if((iter.r()>=0 && iter.r()<=139) && (iter.g()>=0 && iter.g()<=139) && (iter.b()>=0 && iter.b()<=139))
            {
                iter.r() = 0;
                iter.g() = 0;
                iter.b() = 0;
            }
            else
            {
                iter.r() = 255;
                iter.g() = 255;
                iter.b() = 255;
                
            }
        }
    }
    
    return iter;
}

int gf[1024][1024]={0}, num=0;

void TurnPixel( Surface *surface, Area area )
{
    Surface::Iter iter = surface->getIter( area );
    
    while( iter.line() )
    {
        while( iter.pixel() )
        {
            point tmppoint;
            tmppoint.x=iter.x(); tmppoint.y=iter.y();
            tmppoint.numgf=-1;
            
            if(iter.r()==255 && iter.g()==255 && iter.b()==255)
            {
                tmppoint.numgf=num+1;
                num++;
                
                if(iter.x()==0 && iter.y()==0)
                {
                    points.push_back(tmppoint);
                }
                
                else if(iter.y()==0)
                {
                    int prevx=-1;
                    int prevy=0;
                    
                    point prevpoint;
                    prevpoint.x=iter.x()+prevx; prevpoint.y=iter.y()+prevy;
                    //prevpoint.nymgf=???;
                    
                    if(iter.r(prevx, prevy)==255 && iter.g(prevx, prevy)==255 && iter.b(prevx, prevy)==255)
                    {
                        gf[tmppoint.numgf][prevpoint.numgf]=1;
                        gf[prevpoint.numgf][tmppoint.numgf]=1;
                    }
                }
                
                else if(iter.x()==0)
                {
                    int upx=0;
                    int upy=-1;
                    
                    point uppoint;
                    uppoint.x=iter.x()+upx; uppoint.y=iter.y()+upy;
                    //uppoint.nymgf=???;
                    
                    if(iter.r(upx, upy)==255 && iter.g(upx, upy)==255 && iter.b(upx, upy)==255)
                    {
                        gf[tmppoint.numgf][uppoint.numgf]=1;
                        gf[uppoint.numgf][tmppoint.numgf]=1;
                    }
                    
                }
                
                else if(iter.x()==iter.getWidth())
                {
                    int prevx=-1;
                    int prevy=0;
                    
                    int upx=0;
                    int upy=-1;
                    
                    if((iter.r(upx, upy)==0 && iter.g(upx, upy)==0 && iter.b(upx, upy)==0) && (iter.r(prevx, prevy)==0 && iter.g(prevx, prevy)==0 && iter.b(prevx, prevy)==0))
                    {
                        iter.r() = 15;
                        iter.g() = 210;
                        iter.b() = 100;
                        
                        num++;
                        
                        points.push_back(tmppoint);
                    }
                    
                    else
                    {
                        point uppoint;
                        uppoint.x=iter.x()+upx; uppoint.y=iter.y()+upy;
                        //uppoint.nymgf=???;
                        
                        point prevpoint;
                        prevpoint.x=iter.x()+prevx; prevpoint.y=iter.y()+prevy;
                        //prevpoint.nymgf=???;
                        
                        if(iter.r(upx, upy)==255 && iter.g(upx, upy)==255 && iter.b(upx, upy)==255)
                        {
                            gf[tmppoint.numgf][uppoint.numgf]=1;
                            gf[uppoint.numgf][tmppoint.numgf]=1;
                        }
                        
                        if(iter.r(prevx, prevy)==255 && iter.g(prevx, prevy)==255 && iter.b(prevx, prevy)==255)
                        {
                            gf[tmppoint.numgf][prevpoint.numgf]=1;
                            gf[prevpoint.numgf][tmppoint.numgf]=1;
                        }
                    }
                }
                
                else
                {
                    int upx=0;
                    int upy=-1;
                    
                    point uppoint;
                    uppoint.x=iter.x()+upx; uppoint.y=iter.y()+upy;
                    //uppoint.nymgf=???;
                    
                    int prevx=-1;
                    int prevy=0;
                    
                    point prevpoint;
                    prevpoint.x=iter.x()+prevx; prevpoint.y=iter.y()+prevy;
                    //prevpoint.nymgf=???;
                    
                    if(iter.r(upx, upy)==255 && iter.g(upx, upy)==255 && iter.b(upx, upy)==255)
                    {
                        gf[tmppoint.numgf][uppoint.numgf]=1;
                        gf[uppoint.numgf][tmppoint.numgf]=1;
                    }
                    
                    if(iter.r(prevx, prevy)==255 && iter.g(prevx, prevy)==255 && iter.b(prevx, prevy)==255)
                    {
                        gf[tmppoint.numgf][prevpoint.numgf]=1;
                        gf[prevpoint.numgf][tmppoint.numgf]=1;
                    }
                }
            }
        }
    }
}

void MakeLine(Surface *surface, Area area, int x1, int y1, int x2, int y2)
{
    Surface::Iter iter = surface->getIter( area );
    int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;
    
    dx=x2-x1; dy=y2-y1;
    dx1=fabs(dx); dy1=fabs(dy);
    px=2*dy1-dx1; py=2*dx1-dy1;
    
    if(dy1<=dx1)
    {
        if(dx>=0)
        {
            x=x1; y=y1;
            xe=x2;
        }
        else
        {
            x=x2; y=y2;
            xe=x1;
        }
        
        iter.r(x, y) = 255;
        iter.g(x, y) = 255;
        iter.b(x, y) = 255;
        
        for(i=0;x<xe;i++)
        {
            x=x+1;
            if(px<0)
            {
                px=px+2*dy1;
            }
            else
            {
                if((dx<0 && dy<0) || (dx>0 && dy>0))
                {
                    y=y+1;
                }
                else
                {
                    y=y-1;
                }
                px=px+2*(dy1-dx1);
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
            x=x1;
            y=y1;
            ye=y2;
        }
        else
        {
            x=x2;
            y=y2;
            ye=y1;
        }
        
        iter.r(x, y) = 255;
        iter.g(x, y) = 255;
        iter.b(x, y) = 255;
        
        for(i=0;y<ye;i++)
        {
            y=y+1;
            if(py<=0)
            {
                py=py+2*dx1;
            }
            else
            {
                if((dx<0 && dy<0) || (dx>0 && dy>0))
                {
                    x=x+1;
                }
                else
                {
                    x=x-1;
                }
                py=py+2*(dx1-dy1);
            }
            
            iter.r(x, y) = 255;
            iter.g(x, y) = 255;
            iter.b(x, y) = 255;
        }
    }
}


Surface processImage( const Surface input )
{
    // make the result be a copy of input
    Surface resultSurface( input.clone() );
    
    TurnBinary( &resultSurface, Area (input.getWidth(), input.getHeight(), 0 , 0));
    TurnPixel( &resultSurface, Area (input.getWidth(), input.getHeight(), 0 , 0));
    
    return resultSurface;
}

Surface processImage2( const Surface input )
{
    // make the result be a copy of input
    Surface resultSurface( input.clone() );
    
    for(int i=0; i<spiral.size()-1; i++)
    {
        MakeLine(&resultSurface, Area (input.getWidth(), input.getHeight(), 0, 0), spiral[i].x, spiral[i].y, spiral[i+1].x, spiral[i+1].y);
    }
    
    return resultSurface;
}

void MakeSpiral()
{
    spiral.clear();
    int maxind=0;
    for(int i=1; i<points.size(); i++)
        if(points[i].y > points[maxind].y) maxind=i;
    for(int i=1; i<points.size(); i++)
        if(points[i].y == points[maxind].y) if(points[i].x < points[maxind].x) maxind=i;
    swap(points[0], points[maxind]);
    
    spiral.push_back(points[0]);
    
    for(; ;)
    {
        if(points.size()==1) break;
        if(points.size()==3)
        {
            if(det(points[0], points[1], points[2])>=0)
            {
                spiral.push_back(points[0]);
                spiral.push_back(points[1]);
                spiral.push_back(points[2]);
            }
            else if(det(points[0], points[2], points[1])>=0)
            {
                spiral.push_back(points[0]);
                spiral.push_back(points[2]);
                spiral.push_back(points[1]);
            }
            break;
        }
        
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
}


void ConvexSpiralApp::mouseDown( MouseEvent event )
{
    // pull down the current window as a surface and pass it to writeImage
    writeImage( getHomeDirectory() /"Documents"/"AstroSpiral"/ "IMG" / "RESULT.png", copyWindowSurface() );
}

void ConvexSpiralApp::setup()
{
    try
    {
        ci::fs::path img = getOpenFilePath( "", ImageIo::getLoadExtensions());
        
        if( ! img.empty() ) // an empty string means the user canceled
        {
            Surface processedImage( processImage( loadImage( img ) ) );
            myImage = gl::Texture( processedImage );
            
            setWindowSize(myImage.getWidth(), myImage.getHeight() );
            
            MakeSpiral();
            
            Surface processedImage2( processImage2( loadImage( img ) ) );
            myImage = gl::Texture( processedImage2 );
        }
    }
    
    catch( ... )
    {
        console() << "Unable to load the image." << std::endl;
    }
}


void ConvexSpiralApp::draw()
{
    gl::draw( myImage, getWindowBounds());
}

CINDER_APP_BASIC( ConvexSpiralApp, RendererGl );
