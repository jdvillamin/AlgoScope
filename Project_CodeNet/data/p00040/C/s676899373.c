#include <stdio.h>
#include <string.h>

int main(void) {
	char str[257];
	char ans[257];
	int number;
	int i, j;
	int a, b;
	int n;
	_Bool find;
	scanf("%d", &n);
	getchar();
	while (n--) {
		for (i = 0; i < 257; i++)
			str[i] = str[i] = '\0';
		gets(str);
		find = 0;
		a = 1;
		number = strlen(str);
		while (!find) {
			for (i = 0, b = 0; i < 26 && !find; i++, b++) {
				for (j = 0; j < number; j++) {
					if (str[j] == ' ')
						ans[j] = ' ';
					else
						ans[j] = (a * (str[j] - 'a') + b) % 26 + 'a';
				}
				ans[j] = '\0';
				for (j = 0; j < number; j++) {
					if (strncmp(&ans[j], "that", 4) == 0 || strncmp(&ans[j], "that", 4) == 0) {
						find = 1;
						break;
					}
				}
			}
			a++;
		}
		printf("%s\n", ans);
	}
	return 0;
}