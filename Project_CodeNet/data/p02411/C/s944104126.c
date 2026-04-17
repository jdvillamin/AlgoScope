#include <stdio.h>

int main( void ){
    int middle_score[1024];
    int term_score[1024];
    int again_scoer[1024];
    int score[1024];
    int i;
    i = 0;

    while( 1 ){
        scanf( " %d %d %d", &middle_score[i], &term_score[i], &again_scoer[i] );
        if ( middle_score[i] == -1 && term_score[i] == -1 && again_scoer[i] == -1 ) break;
        i++;
    }

    for ( int j = 0; j < i; j++ ){
        if ( middle_score[j] == -1 ) middle_score[j] = 0;
        if ( term_score[j] == -1 ) term_score[j] = 0;
        score[j] = middle_score[j] + term_score[j];
        if ( score[j] >= 80 ){
            printf("A\n");
        } else if ( score[j] >= 65 ){
            printf("B\n");
        } else if ( score[j] >= 50 || ( score[j] >= 30 && again_scoer[i] >= 50 ) ){
            printf("C\n");
        } else if( score[j] >= 30 && middle_score[j] !=-1 && term_score[j] !=-1 ){
            printf("D\n");
        } else {
            printf("F\n");
        }
    }
    return 0;
}
