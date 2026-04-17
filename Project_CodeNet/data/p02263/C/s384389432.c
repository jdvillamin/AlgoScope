#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

// NO ERROR handling implemented!! full, empty

int stack[1000]={0},top=0;

void push(int x)
{
	stack[++top] = x;   // ++top, top-- etc.. incre/decre top permanently, stack[top+1] does not change the top outside the stack[...].
}

int pop()
{
	//top--;
	return stack[top--];
}

int main()
{
    int x,y;
	char op[100];
	

	while( scanf("%s",op) != EOF ){
		if(op[0] == '+'){
			x = pop();
			y = pop();
			push(x + y);
		}else if(op[0] == '-'){
			x = pop();
			y = pop();
			push(y - x);
		}else if(op[0] == '*'){
			x = pop();
			y = pop();
			push(x * y);
		}else{
			push(atoi(op));  // read terminal inputs(空白で区切られた壱文字ずつ読み込む), operatorはpushされない！！
		}
	}

	printf("%d\n",pop());

	return 0;
}
