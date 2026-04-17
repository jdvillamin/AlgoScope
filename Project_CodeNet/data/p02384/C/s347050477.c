#include<stdio.h>
int main(void){
	int dice1[5],dice2[5],dice3[5],dice4[5],dice5[5],dice6[5];
	int i,num,co=0,work,one,two,k,j;
	
	scanf("%d %d %d %d %d %d",&dice1[0],&dice2[0],&dice3[0],&dice4[0],&dice5[0],&dice6[0]);
	dice1[1]=dice5[0];
	dice1[2]=dice4[0];
	dice1[3]=dice2[0];
	dice1[4]=dice3[0];
	dice2[1]=dice1[0];
	dice2[2]=dice4[0];
	dice2[3]=dice6[0];
	dice2[4]=dice3[0];
	dice3[1]=dice1[0];
	dice3[2]=dice2[0];
	dice3[3]=dice6[0];
	dice3[4]=dice5[0];
	dice4[1]=dice1[0];
	dice4[2]=dice5[0];
	dice4[3]=dice6[0];
	dice4[4]=dice2[0];
	dice5[1]=dice1[0];
	dice5[2]=dice3[0];
	dice5[3]=dice6[0];
	dice5[4]=dice4[0];
	dice6[1]=dice2[0];
	dice6[2]=dice4[0];
	dice6[3]=dice5[0];
	dice6[4]=dice3[0];
	
	scanf("%d",&num);
	int ans[num];
	for(i=0;i<num;i++){
		scanf("%d %d",&one,&two);
		if(one==dice1[0]){
			for(j=0;j<4;j++){
				if(dice1[j+1]==two){
					ans[i]=dice1[(j+1)%4+1];
					break;
				}
			}
		}
		else if(one==dice2[0]){
			for(j=0;j<4;j++){
				if(dice2[j+1]==two){
					ans[i]=dice2[(j+1)%4+1];
					break;
				}
			}
		}
		else if(one==dice3[0]){
			for(j=0;j<4;j++){
				if(dice3[j+1]==two){
					ans[i]=dice3[(j+1)%4+1];
					break;
				}
			}
		}
		else if(one==dice4[0]){
			for(j=0;j<4;j++){
				if(dice4[j+1]==two){
					ans[i]=dice4[(j+1)%4+1];
					break;
				}
			}
		}
		else if(one==dice5[0]){
			for(j=0;j<4;j++){
				if(dice5[j+1]==two){
					ans[i]=dice5[(j+1)%4+1];
					break;
				}
			}
		}
		else if(one==dice6[0]){
			for(j=0;j<4;j++){
				if(dice6[j+1]==two){
					ans[i]=dice6[(j+1)%4+1];
					break;
				}
			}
		}
	}
	for(i=0;i<num;i++){
		printf("%d\n",ans[i]);
	}
	
	return 0;
}
