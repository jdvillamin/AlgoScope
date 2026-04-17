#include<stdio.h>
#include<string.h>

#define A  0
#define B  1
#define C  2
#define D  3
#define E  4
#define F  5
#define G  6
#define H  7
#define I  8
#define J  9
#define K 10
#define L 11
#define M 12
#define N 13
#define O 14
#define P 15
#define Q 16
#define R 17
#define S 18
#define T 19
#define U 20
#define V 21
#define W 22
#define X 23
#define Y 24
#define Z 25

#define AZ 26
#define NUM 257


void input_tango(int *max_tango, int *max_mozi, char *text, char affine[NUM][NUM] );
void mozi_number(int *max_tango, int *tango_mozicount, char affine[NUM][NUM], int m[NUM][NUM]);

int main(void)
{
	int a = 0 ,v = 0, b = 0;
	int n = 0;
	char affine[NUM][NUM];
	char text[NUM];
	int m[NUM][NUM];
	int i = 0, j = 0, k = 0;
	int c = 0;
	int max_tango = 0;
	int max_mozi = 0;
	int tango4[NUM];
	int flag =0;
	int t4[NUM][NUM];
	int t = 0;
	scanf("%d", &n);
	int tango_mozicount[NUM];

	for(c = 0; c < n; c++)
	{
		for(i = 0;i < NUM;i++)
		{
			for(j = 0;j < NUM;j++ )
			{
               			affine[i][j] = '\0';
				t4[i][j] = 0;
				 m[i][j] = 0;
			}
		}
        	for(j = 0; j < NUM; j++)
        	{
			tango_mozicount[i] = 0;
               	 	text[j] = '\0';
			tango4[i] = 0; 
        	}
		scanf("\n");
		gets(text);

		input_tango(&max_tango, &max_mozi, text, affine);
/*
		for(i = 0;i < max_tango; i++)
		{
			printf("%s\n", affine[i]);
		}
*/		


		
		j = 0;
		for(i = 0; i < max_tango ;i++ )
		{
			while(1)
			{
				if(affine[i][j] == '\0')
				{
					tango_mozicount[i] = j;
					if(j == 4)
					{
						tango4[k] = i;
						k++;
					}
					j = 0;
					break;
				}
				j++;
			}
		}
		mozi_number(&max_tango, tango_mozicount, affine, m);
/*
		for(i = 0;i < max_tango; i++)
		{
			for(j = 0;j < tango_mozicount[i];j++)
			{
				printf("%d ",m[i][j]);
			}
			printf("\n");
		}
*/
		for(i = 0;i < k ;i++)
		{
			for(j = 0;j < 4; j++)
			{
				for(t = 0; t < AZ; t++)	
				{
					if(affine[ tango4[i] ][j] == 0x61 + t)
					{	
						t4[i][j] = t;
						break; 
					}
				}
			}
		}
		for(i = 0; i < max_mozi; i++)
		{
			for(a = 0; a <= AZ; a++)
			{
				for(b = 0; b <= AZ; b++)
				{
					if((t4[i][0] == (a * T + b) % AZ &&
					    t4[i][1] == (a * H + b) % AZ &&
					    t4[i][2] == (a * I + b) % AZ &&
					    t4[i][3] == (a * S + b) % AZ)||
					   (t4[i][0] == (a * T + b) % AZ &&
					    t4[i][1] == (a * H + b) % AZ &&
					    t4[i][2] == (a * A + b) % AZ &&
					    t4[i][3] == (a * T + b) % AZ))
					{
						a = a;
						b = b;
						flag = 1;
						break;
					}
				
				}
				if(flag == 1)
				{
					break;
				}
			}
			if(flag == 1)
			{
				break;
			}
		}


		for(i = 0;i < max_tango; i++)
		{
			for(j = 0;j < tango_mozicount[i]; j++)
			{
				for(v = 0;v < AZ; v++)
				{
					if(m[i][j] == (a * v + b) % AZ)
					{
						printf("%c",0x61 + v);		
					}
				}
			}
			if(max_tango > i+1)
			{
				printf(" ");
			}
		}
		printf("\n");
		for(i = 0;i < NUM;i++)
		{
			for(j = 0;j < NUM;j++ )
			{
               			affine[i][j] = '\0';
				t4[i][j] = 0;
				 m[i][j] = 0;
			}
		}
        	for(j = 0; j < NUM; j++)
        	{
			tango_mozicount[i] = 0;
               	 	text[j] = '\0';
			tango4[i] = 0; 
        	}
		flag = 0;
		i = 0;
		j = 0;
		k = 0;
        }
	return 0;
}

void input_tango(int *max_tango, int *max_mozi, char *text, char affine[NUM][NUM] )
{
	int i = 0;
	int j = 0;
	int k = 0;


                while(1)
                {
                	if(text[i] == 0x20)
                	{
                        	i++;
                		j++;
                           	k = 0;
                        }
                        affine[j][k] = text[i];
                        k++;
                        i++;
			if(text[i] == '\0')
                	{
                		break;
                	}
		}
		*max_tango = j+1;
		*max_mozi  = i;

}
void mozi_number(int *max_tango, int *tango_mozicount, char affine[NUM][NUM], int m[NUM][NUM])
{
	int i = 0;
	int j = 0;
	int k = 0;
	int t = 0;


		for(i = 0; i < *max_tango; i++)
		{
			for(j = 0; j < tango_mozicount[i] ; j++)
			{
				if(affine[i][j] == '\0')
				{
					break;
				}
				for(k = 0; k < AZ; k++)
				{
					if(affine[i][j] == 0x61 + k)
					{
						m[i][t] = k;
						t++;
						break;
					}
				}
			}
			t = 0;
		}
}