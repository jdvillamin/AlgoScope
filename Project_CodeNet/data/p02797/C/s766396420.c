    #include <stdio.h>
     
    int main(){
       int n,k,i;
       long s,x;
     
       scanf("%d %d %ld",&n,&k,&s);
       if (s<1000000000) x=s+1;
       else              x=s-1;
       if (k>0) printf("%ld",s);
       else     printf("%ld",x);
       for (i=1;i<k;i++) printf(" %ld",s);
       if (k==0) i=1;
       else      i=0;
       for (;i<n-k;i++) printf(" %ld",x);
       puts("");
       return 0;
    }