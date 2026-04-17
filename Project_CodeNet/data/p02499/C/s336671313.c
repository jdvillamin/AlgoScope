#include <stdio.h>
#include <ctype.h>

int main(void){
	char c;
	int a, cnt[26] = {};
	while((c = getchar()) != EOF){
		if(c == '\n' || c == ' ')
			;
		else{
			c = tolower(c);
			a = c - 'a';
			cnt[a]++;
		}

	}
	for(a = 0; a <= 25 ; a++){
		printf("%c : %d\n", 'a' + a, cnt[a]);
	}
}