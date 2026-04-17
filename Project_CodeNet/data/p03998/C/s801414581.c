#include <stdio.h>
#include <string.h>

int main(void) {
	// variables
	char sa[100], sb[100], sc[100]; // strings
	int ia, ib, ic; // index
	char res;
	int lena, lenb, lenc;
	
	// get inputs
	scanf("%s", sa);
	scanf("%s", sb);
	scanf("%s", sc);
	
	// get length of each string
	lena = strlen(sa);
	lenb = strlen(sb);
	lenc = strlen(sc);
	
	// initialize
	ia = 0;
	ib = 0;
	ic = 0;
	res = 'a';
	
	while(ia < lena-1 && ib < lenb-1 && ic < lenc-1){
	   // printf("%c", res);
	   if(res == 'a'){
		ia++;
		if(ia == lena-1){
			break;
		}
		res = sa[ia];
	   } else if(res == 'b'){
	   	ib++;
	   	if(ib == lenb-1){
	   		break;
	   	}
	   	res = sb[ib];
	   } else if(res == 'c'){
	   	ic++;
	   	if(ic == lenc-1){
	   		break;
	   	}
	   	res = sc[ic];
	   }
	}
	
	// output
	if(res == 'a'){
		res = 'A';
	} else if(res == 'b'){
		res = 'B';
	} else if(res == 'c'){
		res = 'C';
	}
	printf("%c", res);
	
	return 0;
}
