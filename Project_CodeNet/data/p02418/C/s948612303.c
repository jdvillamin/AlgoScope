#include <stdio.h>
#include <string.h>

int main(void)
{
    char ans[120],str[120],ring[220];
    
    scanf("%s%s",ring,str);
    
    strcpy(ans,ring);
    strcat(ring,ans);
    
    if(strstr(ring,str)!=NULL)
        printf("Yes\n");
    else
        printf("No\n");
    return 0;
}
