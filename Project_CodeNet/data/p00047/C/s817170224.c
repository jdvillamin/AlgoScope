#include <stdio.h>
#define CUP 3

int cup[CUP];

void init();
void swap(char a, char b);
void answer();

int main(int argc, const char *argv[])
{
	char ch1, ch2;
	init();
	while(scanf("%c,%c\n", &ch1, &ch2)!=EOF){
		swap(ch1, ch2);
	}
	answer();	
	return 0;
}

void init()
{
	cup[0] = 1; // cup A
	cup[1] = 0; // cup B
	cup[2] = 0; // cup C
}

void swap(char a, char b)
{
	int c1 = a-'A', c2 = b-'A';
 	int tmp;
	
	tmp = cup[c1];
	cup[c1] = cup[c2];
	cup[c2] = tmp;	
}

void answer()
{
	if(cup[0]) printf("A\n");
	if(cup[1]) printf("B\n");
	if(cup[2]) printf("C\n");
}