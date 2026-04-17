long a[2<<17],S,w,m;f,i;
main(){
	for(gets(a);~scanf("%d",a+i);S+=++i-f)for(w^=a[i],m+=a[i];w-m;w^=a[f++])m-=a[f];
	printf("%ld",S);
}