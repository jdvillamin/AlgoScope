#include<stdio.h>
#include<stdlib.h>


int comp(const void *p1,const void *p2){
  long long int n1,n2;
  n1=*((const long long int *)p1);
  n2=*((const long long int *)p2);
  return (n2>n1)?1:-1;
}

int main(void){
  long long int *a;
  long long int i,n,b=0,sum1=0,sum2=0,k1,k2,k3,k4,k5,k6,k;
  //FILE *fp;
  //fp=fopen("sort_test.txt","w");

  scanf("%lld",&n);
  a=(long long int *)calloc(n,sizeof(long long int));
  for(i=0;i<n;i++) scanf("%lld",a+i);
  qsort(a,n,sizeof(long long int),comp);
  //for(i=0;i<n;i++) fprintf(fp,"%lld\n",a[i]);
  //fclose(fp);
  //連続した6つのパターン
  for(i=0;i<n-5;i++){
    //a[i]~a[i+5]までを総当たりで検索　できたらその時点でbreakしての総和を求める 
    //for(k1=0;k1<4;k1++){
      for(k2=1;k2<5;k2++){
	for(k3=k2+1;k3<6;k3++){
	  if(a[i]>=a[i+k2]+a[i+k3]) continue;
	  for(k4=1;k4<4;k4++){
	    if(/*k4==k1||*/k4==k2||k4==k3) continue;
	    for(k5=k4+1;k5<5;k5++){
	      if(/*k5==k1||*/k5==k2||k5==k3) continue;
	      for(k6=k5+1;k6<6;k6++){
		if(/*k6==k1||*/k6==k2||k6==k3) continue;
		if(a[i+k4]>=a[i+k5]+a[i+k6]) continue;
		//printf("0%lld%lld-%lld%lld%lld\n",k2,k3,k4,k5,k6);
		sum1=0;
		for(k=0;k<6;k++){
		  sum1+=a[i+k];
		}
		//goto label;
	      }
	    }
	  }
	}
      }
      //}
    if(sum1!=0) break;
  }
  //label:
  for(i=0;i<n-2;i++){
    if(a[i]<a[i+1]+a[i+2]){
      sum2+=(a[i]+a[i+1]+a[i+2]);
      i+=2;
      b++;
      if(b==2) break;
    }
  }
  
  if(sum1>sum2){
    printf("%lld\n",sum1);
  }else{
    printf("%lld\n",sum2);
  }
  
  
  free (a);
  return 0;
}