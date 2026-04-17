#include<stdio.h>
struct node{
	int id;
	int l;
	int r;
}tree[100100];

void Preorder(int a)
{
	printf(" %d",a);
	if(tree[a].l!=-1)
	{
		Preorder(tree[a].l);
	}
	if(tree[a].r!=-1)
	{
		Preorder(tree[a].r);
	}
}

void Inorder(int a)
{
	
	if(tree[a].l!=-1)
	{
		Inorder(tree[a].l);
	}
	printf(" %d",a);
	if(tree[a].r!=-1)
	{
		Inorder(tree[a].r);
	}
}
void Postorder(int a)
{
		if(tree[a].l!=-1)
	{
		Postorder(tree[a].l);
	}

	if(tree[a].r!=-1)
	{
		Postorder(tree[a].r);
	}	
	printf(" %d",a);
}
int main()
{
	int n,a[30],b[30],j=0;
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		int d;
		scanf("%d",&d);
		tree[d].id=d;
		scanf("%d%d",&tree[d].l ,&tree[d].r);
		a[i]=d;
		if(tree[d].l!=-1)
		b[j++]=tree[d].l;
		if(tree[d].r!=-1)
		b[j++]=tree[d].r;
		
	}
	int g,h=j;
	for(int i=0;i<n;i++)
	{
		for(j=0;j<h;j++)
		{
			if(a[i]==b[j])
			break;
		}
		if(j==h)
		{
			g=a[i];
		}
	}

	printf("\nPreorder\n");
	Preorder(g);
	printf("\nInorder\n");
	Inorder(g);
	printf("\nPostorder\n");
	Postorder(g);
 } 
/*
Preorder
 0 1 2 3 4 5 6 7 8
Inorder
 2 1 3 0 6 5 7 4 8
Postorder
 2 3 1 6 7 5 8 4 0
Preorder
 0 1 2 3 4 5 6 7 8
Inorder
 2 1 3 0 6 5 7 4 8
Postorder
 2 3 1 6 7 5 8 4 0
 */
