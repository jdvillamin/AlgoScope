1){
      printf("-1");
      return 0;
    }
  }
 for(int i=0;i<M-1;i++){
   if(s[i]==s[i+1]&&c[i]!=c[i+1]){
     printf("-1");
  return 0;
}
 }
  
  int cc=0;
  for(int i=0;i<M;i++){
    cc+=c[i];
  }
  if(N==1&&cc==0){
    printf("0");
    return 0;
  }
  
  for(int i=0;i<M;i++){
ans[s[i]-1]=c[i];
  }
  int count=0;
  for(int i=0;i<M;i++){
    if(count==0&&ans[i]==0){continue;}
    else {count++;
         printf("%d",ans[i]);
         }
  }
  
 
  
  return 0;
}
