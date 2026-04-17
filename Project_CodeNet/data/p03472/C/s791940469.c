#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define MAX_STRING 30
#define MAX_WEAPON 100000

int anSlashes[MAX_WEAPON];
int anThrowHits[MAX_WEAPON];
int compar(const int *val1, const int *val2);

int main() {
	char sInput[MAX_STRING+1]="";
	char* psInput;

	int nWeaponNumber=0;
	int nDevilHP=0;
	int nAttackNumber=0;
	int nMaxSlash=0;
	int nThrowHitOfMaxSlash=0;
	int nMaxThrowHit=0;
	int i=0;



	// read line 1
	gets(sInput);
	psInput = strtok(sInput," ");
	nWeaponNumber = atoi(psInput);
	psInput = strtok(NULL," ");
	nDevilHP = atoi(psInput);

	// read line 2
	for (i=0;i<nWeaponNumber;i++){
		gets(sInput);
		psInput = strtok(sInput," ");
		anSlashes[i] = atoi(psInput);
		psInput = strtok(NULL," ");
		anThrowHits[i] = atoi(psInput);
		if (nMaxSlash<anSlashes[i]){
			nMaxSlash=anSlashes[i];
//			nThrowHitOfMaxSlash=anThrowHits[i];
		}
	}
	// sort
    qsort(anThrowHits, nWeaponNumber, sizeof(int),
        (int (*)(const void *, const void *))compar
    );
	for (i=0;i<nWeaponNumber;i++){
		if (anThrowHits[i]>nMaxSlash&&nDevilHP>0){
			nDevilHP = nDevilHP-anThrowHits[i];
			nAttackNumber++;
		} else {
			break;
		}
	}
	if (nDevilHP>0){
//			printf(" %d %d\n",nDevilHP,nAttackNumber);
			if( nDevilHP>nMaxSlash ){
				nAttackNumber=nAttackNumber+(nDevilHP/nMaxSlash);
			}
			if(nDevilHP%nMaxSlash>0){
				nAttackNumber++;
			}
	}

	printf("%d\n",nAttackNumber);

    return 0;
}
int compar(const int *val1, const int *val2) {
    if ( *val1 > *val2 ) {
        return -1;
    } else if ( *val1 == * val2 ) {
        return 0;
    } else {
        return 1;
    }
}
