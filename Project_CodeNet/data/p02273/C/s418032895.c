#include<stdio.h>
#include<math.h>
 
typedef struct{
  double x;
  double y; 
}xy;

void kock(int n,xy p1,xy p2){  
  xy s,t,u;
  if (n==0) return ;
  s.x=(2.0*p1.x+1.0*p2.x)/3.0;
  s.y=(2.0*p1.y+1.0*p2.y)/3.0;
  t.x=(1.0*p1.x+2.0*p2.x)/3.0;
  t.y=(1.0*p1.y+2.0*p2.y)/3.0;
  u.x=(t.x-s.x)*(cos(M_PI/3.0))-(t.y-s.y)*(sin(M_PI/3.0))+s.x;
  u.y=(t.x-s.x)*(sin(M_PI/3.0))+(t.y-s.y)*(cos(M_PI/3.0))+s.y;
  kock(n-1,p1,s);
  printf("%lf %lf\n",s.x,s.y); 
  kock(n-1,s,u);
  printf("%lf %lf\n",u.x,u.y);
  kock(n-1,u,t);
  printf("%lf %lf\n",t.x,t.y);
  kock(n-1,t,p2);
}
int main( ){
  xy p1,p2;
  int n;
  p1.x=0.0;
  p1.y=0.0;
  p2.x=100.0;
  p2.y=0.0;
  scanf("%d",&n); 
  printf("%lf %lf\n",p1.x,p1.y);
  kock(n,p1,p2);
  printf("%lf %lf\n",p2.x,p2.y); 
  return 0;
}
 