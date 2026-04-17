#include<stdio.h>
 
#define MAXLEN 20000
 
int garea,gareas[(MAXLEN/2)+1],gcnt,gend;
 
 
int getArea( char *inputs, int start, int end )
{
    int i;
    int ravine,water;
    
    gareas[gcnt]=ravine=water=0;
    for( i=start; i!=end; i++ ) {
        if( '\\'== *(inputs+i) ) {
           	water+=(ravine*2);
            ravine++;
            water++;
        } else if( 0 != ravine && '/' == *(inputs+i) ) {
        	ravine--;
        } else {
	     	water+=ravine;
        }       
    }
	gareas[gcnt]+=water;
    
    return gareas[gcnt];
}
  
int checkRavine( char *inputs, int start )
{
    int i;
    int ravine, minh, tmpi;
    
    ravine=0;
    tmpi=minh=MAXLEN;
    for( i=start; i<=gend && '\0'!=*(inputs+i); i++ ) {
        if( 0 <= ravine && '\\'== *(inputs+i) ) {
            ravine++;
        } else if( 0 != ravine && '/' == *(inputs+i) ) {
            ravine--;
            if( ravine < minh ) {
        		minh=ravine;
        		tmpi=i;
            }
            if( 0 == ravine ) {
            	garea+=getArea( inputs, start, i+1 );
            	gcnt++;
			    gend=MAXLEN;           	
                return i-start;
            }
        }
    }
	gend=tmpi;
    return 0;
}
 
 
void getAreas( char *inputs )
{
    int i,next;
     
    next=0;
    for( i=0; i<=gend && '\0'!=inputs[i]; i++ ) {
    	if( '_' !=inputs[i] && '/' !=inputs[i] ) {
	        next=checkRavine( inputs, i );
	        i+=next;
        }
    }
 
    return;
}
 
int main( void ) 
{
    char inputs[MAXLEN+1];
    int i;
 
    scanf( "%s", inputs );
    garea=gcnt=0;
    gend=MAXLEN;
    getAreas( inputs );
     
    printf( "%d\n", garea );
    
    if( gcnt ) {
        printf( "%d ", gcnt );
        for( i=0; i<gcnt; i++ ) {
            printf( "%d", gareas[i] );
            if( i < gcnt-1 ) {
            	printf( " " );  
            }
        }
        printf( "\n" );
       
    } else {
        printf( "0\n" );
    }
     
    return 0;
}