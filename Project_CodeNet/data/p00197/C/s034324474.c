c,a,b;
G(x,y){return y?c+=x>=y,G(y,x%y):x;}
main(){
	for(;scanf("%d%d",&a,&b),a|b;c=0){
		printf("%d %d\n",G(a,b),c);
	}
	exit(0);
}