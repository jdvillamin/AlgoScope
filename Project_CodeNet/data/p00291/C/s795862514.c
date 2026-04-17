int main() {
	int c1=0,c5=0,c10=0,c50=0,c100=0,c500=0;
	scanf("%d%d%d%d%d%d",&c1,&c5,&c10,&c50,&c100,&c500);
	if ((c1+c5*5+c10*10+c50*50+c100*100+c500*500)>=1000)
	{
		printf("1\n");
	}
	else
	{
		printf("0\n");
	}
	return 0;
}
