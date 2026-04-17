#include <stdio.h>
#include <string.h>

int main() {
	char str[1000];
	char str1[] = "s";
	char str2[] = "es";
	int i = 0;
	scanf("%s", str);
	while (str[i] != '\0') {
		i++;
	}
	i--;
	if (str[i] != 's') {
		strcat(str, str1);
		printf("%s", str);
		
	}

	if (str[i] == 's') {
		strcat(str, str2);
		printf("%s", str);
	}
	return 0;
}