//#include<fstream>
#include<iostream>
#include<cmath>
using namespace std;

struct dpoint
{double x; double y; char c[2];};
dpoint p[99];
int n;

/*void read_data()
{//ifstream f;
 //f.open("data.txt");
 //f >> n;



 //for(int i=0; i<n; i++)
 // {f >> p[i].x >> p[i].y >> p[i].c;}

 //f.close();
 

}*/

void findFirst()
{
 int j=0;
 for(int i=1; i<n; i++) if(p[i].y<p[j].y) j=i;
 for(int i=0; i<n; i++) if(p[i].y==p[j].y) if(p[i].x > p[j].x) j=i;
 swap(p[0],p[j]);
}

double value(dpoint p0, dpoint p1, dpoint p2)
{
  double ax=p1.x-p0.x;
  double ay=p1.y-p0.y;
  double bx=p2.x-p1.x;
  double by=p2.y-p1.y;
  double L=sqrt(bx*bx+by*by);
  return (ax*bx+ay*by)/L;
}

void findSecond()
{
 dpoint p1;
 p1.x=p[0].x+1.0;
 p1.y=p[0].y;

 int j=1;
 double v=-1e10;;
 for(int i=1;i<n;i++)
 {
   if(value(p[0],p1,p[i])>v)
   {v=value(p[0],p1,p[i]);
    j=i;
   }
 }
 swap(p[1],p[j]);
}

void findNext(int k)
{
 int j=1;
 double v=-1e10;
 for(int i=k+1;i<n;i++)
 {
   double w=value(p[k-1],p[k],p[i]);
   if(w>v) {v=w; j=i;}
 }
 swap(p[k+1],p[j]);
}

void showOrder()
{
 cout << n << endl;
 for(int i=0;i<n;i++) cout << p[i].c[0];
 cout << endl;
}


int main()
{ //read_data();
  //showOrder();

  cin>>n;
  
  for(int i=0; i<n; i++)
    {cin >> p[i].x >> p[i].y >> p[i].c;}
  findFirst();
  //showOrder();
  findSecond();
  //showOrder();
  for(int k=1;k<n-3;k++)
  {findNext(k);
   //cout << "k=" << k << endl;
   //showOrder();
  }
   showOrder();

   return 0;
}

