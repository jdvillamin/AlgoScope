#include<stdio.h>
#include<string.h>

int main(void){
	int H,W,o;int QWE;
	char HW[100][102];//農場データ
	char SoldFlag[100][102];//売約済みフラグ
	char Queue[100*102][2];
	int QueueStart=0,QueueEnd=1;
	int QueueNow=0;
	int Answer=0;
	int Count,CountH,CountW,CountQ,CountH2,CountW2;
	int MH,MW;
	int Ancn=0;
	//char *FinalAnswer={0};//こいつを最後に出力
	int Ansbuff[100];
	for(CountH=0;CountH<100;CountH++){
		Ansbuff[CountH]=0;
		for(CountW=0;CountW<102;CountW++){
			SoldFlag[CountH][CountW]=0;
		}
	}
	for(CountH2=0;CountH2<10200;CountH2++){Queue[CountH2][0]=-1;Queue[CountH2][1]=-1;}//初期化
	//入力処理
	Ancn=0;
	while(1){
		scanf("%d %d",&H,&W);
		if(H==0&&W==0){
			//ここで回答出力
			int Q=0;
			for(Q=0;Q<100;Q++){
				if(Ansbuff[Q]==0)return 0;
				printf("%d\n",Ansbuff[Q]);
			}
		}
		for(Count=0;Count<H;Count++){
			scanf("%s",HW[Count]);
		}
	//}	
	
	//while(1){//からになったらbreak;で
		//ここで扱うマップを代入していく
			
		for(CountH=0;CountH<H;CountH++){
			for(CountW=0;CountW<W;CountW++){
				if(SoldFlag[CountH][CountW]!=1){//始点が売約済みでないことを確認
					// 1
					//4 2
					// 3
					Queue[0][0]=CountH;//始点をセット
					Queue[0][1]=CountW;
					SoldFlag[CountH][CountW]=1;
					while(1){
						//printf("chk %d,%d,%d\n",QueueStart,QueueEnd,QueueNow);
						for(CountQ=QueueStart;CountQ<QueueEnd;CountQ++){
							if(Queue[CountQ][0]!=0){//Up
								if(SoldFlag[Queue[CountQ][0]-1][Queue[CountQ][1]]==0&&
									HW[Queue[CountQ][0]][Queue[CountQ][1]]==HW[Queue[CountQ][0]-1][Queue[CountQ][1]]){
									Queue[QueueEnd+QueueNow][0]=Queue[CountQ][0]-1;
									Queue[QueueEnd+QueueNow][1]=Queue[CountQ][1];
									SoldFlag[Queue[CountQ][0]-1][Queue[CountQ][1]]=1;
									QueueNow++;
								}
							}
							
							if(Queue[CountQ][1]<W-1){//Right
								if(SoldFlag[Queue[CountQ][0]][Queue[CountQ][1]+1]==0&&
									HW[Queue[CountQ][0]][Queue[CountQ][1]]==HW[Queue[CountQ][0]][Queue[CountQ][1]+1]){
									Queue[QueueEnd+QueueNow][0]=Queue[CountQ][0];
									Queue[QueueEnd+QueueNow][1]=Queue[CountQ][1]+1;
									SoldFlag[Queue[CountQ][0]][Queue[CountQ][1]+1]=1;
									QueueNow++;
								}
							}
							if(Queue[CountQ][0]<H-1){//Down
								if(SoldFlag[Queue[CountQ][0]+1][Queue[CountQ][1]]==0&&
									HW[Queue[CountQ][0]][Queue[CountQ][1]]==HW[Queue[CountQ][0]+1][Queue[CountQ][1]]){
									Queue[QueueEnd+QueueNow][0]=Queue[CountQ][0]+1;
									Queue[QueueEnd+QueueNow][1]=Queue[CountQ][1];
									SoldFlag[Queue[CountQ][0]+1][Queue[CountQ][1]]=1;
									QueueNow++;
								}
							}
							if(Queue[CountQ][1]!=0){//Left
								if(SoldFlag[Queue[CountQ][0]][Queue[CountQ][1]-1]==0&&
									HW[Queue[CountQ][0]][Queue[CountQ][1]]==HW[Queue[CountQ][0]][Queue[CountQ][1]-1]){
									Queue[QueueEnd+QueueNow][0]=Queue[CountQ][0];
									Queue[QueueEnd+QueueNow][1]=Queue[CountQ][1]-1;
									SoldFlag[Queue[CountQ][0]][Queue[CountQ][1]-1]=1;
									QueueNow++;
								}
							}
						}
						if(QueueNow==0){Answer++;QueueStart=0;QueueEnd=1;QueueNow=0;break;}
						QueueStart=QueueEnd;
						QueueEnd+=QueueNow;
						QueueNow=0;
					}
				}
				for(CountH2=0;CountH2<10200;CountH2++){Queue[CountH2][0]=-1;Queue[CountH2][1]=-1;}//初期化
			}
		}

		Ansbuff[Ancn]=Answer;
		Ancn++;
	}
}
//次回5/21 西９　５１９