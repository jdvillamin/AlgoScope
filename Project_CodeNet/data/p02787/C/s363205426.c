#include<stdio.h>

typedef struct mag
{
  int A;	//atk
  int B;	//mp
  float E;	//efficiency
} magic;

void sort_by_efficiency(magic m[],int N)
{
  magic tmp;
  int i,j = 0;
  
  for(i=0;i<N-1;i++)
  {
    for(j=i+1;j<N;j++)
    {
      if(m[i].E<m[j].E)
      {
        tmp = m[i];
        m[i] = m[j];
        m[j] = tmp;
      }
    }
  }
  
}

int main(void)
{
  int H,N,i,j = 0;
  magic m[10000];
  int sum = 0;
  
  scanf("%d %d",&H,&N);
  
  for(i=0;i<N;i++){
    scanf("%d %d",&m[i].A,&m[i].B);
    //mp当たり与ダメージをEとする
    m[i].E = (float)m[i].A / m[i].B;
  }
  
  // 効率順にソート（0番目が一番高効率）
  sort_by_efficiency(m,N);

/*
  // テスト表示
  for(i=0;i<N;i++)
  {
    printf("%d %d %f\n",m[i].A,m[i].B,m[i].E);
  }
*/
  //基本
  //最も効率の良い魔法でギリギリまで削る
  
  //例外
  //一回で倒せる魔法がある場合（オーバーキルの考慮）
  //その中で最もmp消費の少ないものを選択
  
  for(i=0;i<N;i++)
  {
    if(H/m[i].A>0)
    {
      int n = H/m[i].A;
      sum = sum + n*m[i].B;
      H = H % m[i].A;
//      printf("att=%d*%d,mp=-%d*%d,sum=-%d,HP=%d\n",m[i].A,n,m[i].B,n,sum,H);
    }
//    else
    {
      int att_index=0;
      int flag = 0;
      for(j=0;j<N;j++)
      {
        if(H-m[j].A<=0)flag = 1;
      }
      if(flag)
      {
        for(j=1;j<N;j++)
        {
          if(H-m[j].A<=0 && m[att_index].B > m[j].B) att_index = j;
        }
        sum = sum + m[att_index].B;
        H = H - m[att_index].A;    
//        printf("att=%d,mp=-%d,sum=-%d,HP=%d\n",m[att_index].A,m[att_index].B,sum,H);
      }
    }
    if(H<=0) break;
  }
  
  // 結果表示
  printf("%d\n",sum);
  
  return 0;
}