include<stdio.h>
int main(){
  double a,b;
  int c,d,e;
  while(scanf("%lf %lf",&a,&b)!=EOF){
    if(a<35.50)c=1;
    else if(a<37.50)c=2;
    else if(a<40.00)c=3;
    else if(a<43.00)c=4;
    else if(a<50.00)c=5;
    else if(a<55.00)c=6;
    else if(a<70.00)c=7;
    else c=0;
    
    if(b<71.00)d=1;
    else if(b<77.00)d=2;
    else if(b<83.00)d=3;
    else if(b<89.00)d=4;
    else if(b<105.00)d=5;
    else if(b<116.00)d=6;
    else if(b<148.00)d=7;
    else d=0;
    
    if(c==0||d==0)printf("NA\n");
    else{
      if(d>c)c=d;

      if(c==1)printf("AAA\n");
      else if(c==2)printf("AA\n");
      else printf("%c\n",c+'A'-3);
    }
  }
  return 0;
}