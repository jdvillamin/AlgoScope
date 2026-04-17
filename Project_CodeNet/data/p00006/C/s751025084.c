#include <stdio.h>
#include <string.h>

#define SIZE 256

int main(void){
	char str[SIZE];
	char reversestr[SIZE];
	int i;
	int length;
	fgets(str, SIZE, stdin);
	length = strlen(str);
	for (i = 0; i < length; i++) {
		reversestr[(length - 1) - i] = str[i];
	}
	printf("%s\n", reversestr);
	return 0;
}