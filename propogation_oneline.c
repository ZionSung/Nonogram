#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 25
int initializeC();
int initializeD();
int initializeStoreJ();
int initialized();
int getInt( char character );
int propagationCol( int row );
int propagationRow( int row );
int print();
int printS();
int conflict = 0;

// propagation function
int paint( int i, int j );
int paintP( int i, int j );
int paintZero( int i, int j );
int paintOne( int i, int j );
int merge( int i, int j );
int mergeC( char one[], char two[] );
int fix( int i, int j );
int fixZero( int i ,int j );
int fixOne( int i, int j );

char C[SIZE+1][SIZE+1];
char S[SIZE+1];
int D[2*SIZE][SIZE/2 + 1];
int d[SIZE/2 + 1];
int J = 0; //  counter for jj
int x = 0; // counter for row
int storeJ[2 * SIZE];
int getNumber = 0;

int main(){
    FILE *pFile;
    char ch;
    
    initializeC();
    initializeD();
    initializeStoreJ();
    
    C[0][1] = '0';
    C[1][1] = '0';
    C[2][1] = '0';
    C[3][1] = '0';
    C[4][1] = '0';
    C[5][1] = '0';
    C[6][1] = '0';
    C[7][1] = '0';
    C[8][1] = '0';
    C[9][1] = '0';
    C[10][1] = '0';
    C[11][1] = '0';
    C[12][1] = '0';
    C[13][1] = '0';
    C[14][1] = '0';
    C[15][1] = '0';
    C[16][1] = '0';
    C[17][1] = '0';
    C[18][1] = '0';
    C[19][1] = '0';
    C[20][1] = '0';
    C[21][1] = '0';
    C[22][1] = '0';
    C[23][1] = '0';
    C[24][1] = '0';
    C[25][1] = '1';
    
    
    pFile = fopen("nonogram.txt", "r");
    if( NULL == pFile ){
        printf("Open failure");
        return 1;
    }
    else{
        while( (ch = getc(pFile)) ){
            if( ch == EOF ) break;
            
            if( ch == '$'){
                ch = getc(pFile);
                printf("Question %c\n", ch );
                ch = getc(pFile); // skip first \n
                ch = getc(pFile);
            }
        
            while(1){
                int counter = 0;
                while( ch == '1' || ch == '2' || ch == '3' || ch == '4' || ch == '5' || ch == '6' || ch == '7' || ch == '8' || ch == '9'){
                    if( counter == 0 ){
                        if( ch == '1' )getNumber = 1;
                        if( ch == '2' )getNumber = 2;
                        if( ch == '3' )getNumber = 3;
                        if( ch == '4' )getNumber = 4;
                        if( ch == '5' )getNumber = 5;
                        if( ch == '6' )getNumber = 6;
                        if( ch == '7' )getNumber = 7;
                        if( ch == '8' )getNumber = 8;
                        if( ch == '9' )getNumber = 9;
                    }
                    else if( counter == 1 ){
                        if( ch == '1' )getNumber = getNumber*10 + 1;
                        if( ch == '2' )getNumber = getNumber*10 + 1;
                        if( ch == '3' )getNumber = getNumber*10 + 1;
                        if( ch == '4' )getNumber = getNumber*10 + 1;
                        if( ch == '5' )getNumber = getNumber*10 + 1;
                        if( ch == '6' )getNumber = getNumber*10 + 1;
                        if( ch == '7' )getNumber = getNumber*10 + 1;
                        if( ch == '8' )getNumber = getNumber*10 + 1;
                        if( ch == '9' )getNumber = getNumber*10 + 1;
                    }
                    
                    ch = getc(pFile);
                    counter++;
                }
                if( getNumber >= 1 ){
                    
                    D[x][J] = getNumber;
                    J++;
                    printf("%d ", getNumber );
                }
                if( ch == '\n' )break;
                if( ch  == EOF )break;
                if( ch != '1' || ch != '2' || ch != '3' || ch != '4' || ch != '5' || ch != '6' || ch != '7' || ch != '8' || ch != '9'){
                    ch = getc(pFile);
                }
            } // end switch line
                
            storeJ[x] = J;
            J = 0;
            x++; // 會多加一個 1
            
        }
            
            x = 0;
            while( x < 2*SIZE ){
                
                if( x < SIZE ){
                    propagationCol(x);
                    if(conflict == 1 ){
                        printf("conflict\n");
                    }
                    break;
                    for( int i = 0; i < SIZE+1; i++ ){
                        C[i][x+1] = S[i];
                    }
                    print();
                }
                else{
                    propagationRow(x);
                    for( int i = 0; i < SIZE+1; i++ ){
                        C[(x%25)+1][i] = S[i];
                    }
                }
                break;
                initialized();
                x++;
            }
            
            initializeC();
            initializeD();
            initializeStoreJ();
        printf("S[i] = > ");
        printS();
        printf("end!!!");
            // scanning question
            /*(
            ch = getc(pFile);
            if( ch == EOF ) break;
            printf("Question %c\n", ch );
            ch = getc(pFile); // skip the first '\n' from question
            
        } // end while
             */
    }
    fclose(pFile);
    return 0;
}




// calculate for col
int propagationCol( int row ){
    
    int ii = SIZE+1;
    int jj = 0;
    int fixZero = 0;
    int fixOne = 0;
    int total = 0;
    
    initialized( );

    // load j
    jj = storeJ[row];
    printf("j = %d\n", jj );
    
    // load d
    for( int i = 0; i < jj; i++ ){
        d[i] = D[row][i];
    }
    
    // print d[j]
    printf("d[j] = ");
    for ( int i = 0; i < jj; i++ ){
        printf("%d " , d[jj-1-i] );
    }
    printf("\n");

    // load C[][] to S[]
    for( int i = 0; i < SIZE+1; i++ ){
        S[i] = C[i][x+1];
    }
    printf("...........\n");
    printS();
    printf("...........\n");
    
    int ss = SIZE+1;
    paint( ss, jj );
    return 0;
}

// calculate for row
// row = row % 25
int propagationRow( int row ){
    
    int ii = SIZE+1;
    int jj = 0;
    int fixZero = 0;
    int fixOne = 0;
    int total = 0;
    
    initialized( );
    
    // load j
    jj = storeJ[row];
    
    // load d
    for( int i = 0; i < jj; i++ ){
        d[i] = D[row][i];
    }
    
    x = row % SIZE;
    // load C[][] to S[]
    for( int i = 0; i < SIZE+1; i++ ){
        S[i] = C[x+1][i];
    }

    paint( SIZE+1, jj );
    return 0;
}



int paint( int i, int j ){

    if( i == 0 ){
        return 0;
    }
    else{
        paintP( i, j );
    }
    return 0;
}

int paintP( int i, int j ){
    
    printf("i = %d, j = %d\n", i, j );
    if( fixOne( i, j ) == 0 )printf("fixone = 0 \n");
    if( fixZero( i, j ) == 0 )printf("fixzero = 0 \n");
    if( fixOne( i, j ) == 1 )printf("fixone = 1 \n");
    if( fixZero( i, j ) == 1 )printf("fixzero = 1 \n");
    
    if( fixOne( i, j ) == 0 && fixZero( i, j ) == 1 ){
        printf("paint zero ");
        printf("i = %d, j = %d\n", i, j );
        paintZero( i, j );
    }
    else if( fixOne( i, j ) == 1 && fixZero( i, j ) == 0 ){
        printf("paint one ");
        printf("i = %d, j = %d\n", i, j );
        paintOne( i, j );
    }
    else if( fixOne( i, j ) == 1 && fixZero( i, j ) == 1 ){
        printf("merge ");
        printf("i = %d, j = %d\n", i, j );
        merge( i, j );
    }
    else{
        conflict = 1;
        return 0;
    }
    
    return 0;
}

int fix( int i, int j ){
    
    if( i == 0 && j == 0 ){
        return 1;
    }
    else if( i == 0 && j >= 1 ){
        return 0;
    }
    else{
        if( fixZero( i, j ) == 1 || fixOne( i, j ) == 1 ){
            return 1;
        }
        else{
            return 0;
        }
    }
}

int fixZero( int i, int j ){
    
    if( S[i-1] != '1' ){ // for col
        
        
        return ( fix( i - 1, j ) );
    }
    else{
        return 0;
    }
}

int fixOne( int i, int j ){
    
    
    int countone = 0;
    int shouldone = 0;
    
    int total = 0;
    for( int counter = 0; counter < j; counter++ ){
        total += (d[counter]+1);
    }
    
    if( j >= 1 && i >= ( d[j-1] + 1 ) && i >= total ){
        
        for( int counter = 0; counter < d[j-1]; counter++ ){
            if(S[i-1-counter] == '0'){
                return 0;
            }
        }
        
        if( S[i-d[j-1]] == '0' ){
            return 0;
        }
        
        if( S[i-d[j-1] - 1] == '1' ){
            return 0;
        }
        
        
        for( int counter = 0; counter < i-(d[j-1]); counter++ ){
            if(S[counter] == '1'){
                countone++;
                //printf("counter = %d\n", counter );
            }
        }
        
        for( int counter = 0; counter < (j-1); counter++ ){
            shouldone += d[counter];
        }
        
        //printf("countone = %d\n", countone);
        //printf("shouldone = %d\n", shouldone );
        
        if( countone > shouldone ){
            return 0;
        }
        
        
        return ( fix( i - d[j-1] - 1, j - 1 ) );
    }
    else{
        return 0;
    }
}

int paintZero( int i, int j ){
    S[i-1] = '0';
    paint( i - 1, j );
    return 0;
}

int paintOne( int i, int j ){

    int total = 0;
    for( int counter = 0; counter < j; counter++ ){
        total += ( d[counter] + 1 );
    }
    
    if( i >= total && j >= 0 ){
        for( int counteri = 0; counteri < d[j-1]; counteri++ ){
            S[i-1] = '1';
            i--;
        }
        S[i-1] = '0';
        i--;
        printf("%d\n", i );
        printS();
        paint( i, j - 1 );
    }
    else{
        paint( 0, j );
    }
    return 0;
}

int merge( int i, int j ){
    
    char s1[SIZE+1];
    char s2[SIZE+1];
    char temp[SIZE+1];
    
    for( int counteri = 0; counteri < SIZE+1; counteri++ ){
        s1[counteri] = 'u';
        s2[counteri] = 'u';
        temp[counteri] = 'u';
    }
    
    // put S[] into temp[]
    for( int counteri = 0; counteri < SIZE+1; counteri++ ){
        temp[counteri] = S[counteri];
    }
    
    paintZero( i, j );
    //printf("After paintZero %d %d\n", i, j );
    //printS();
    
    // put S to s1
    for( int counteri = 0; counteri < SIZE+1; counteri++ ){
        s1[counteri] = S[counteri];
    }
    
    // recover S
    for( int counteri = 0; counteri < SIZE+1; counteri++ ){
        S[counteri] = temp[counteri];
    }
    
    paintOne( i, j );

    //printf("After paintOne %d %d\n", i, j );
    //printS();
    
    // put S to s2
    for( int counteri = 0; counteri < SIZE+1; counteri++ ){
        s2[counteri] = S[counteri];
    }
    
    mergeC( s1, s2 );
    return 0;
}

int mergeC( char one[], char two[] ){
    
    char s1[SIZE+1];
    char s2[SIZE+1];
    
    for( int counteri = 0; counteri < SIZE+1; counteri++ ){
        s1[counteri] = one[counteri];
        s2[counteri] = two[counteri];
    }
    
    printf("s1 = ");
    for(int i = 0; i < SIZE+1; i++ ){
        printf("%-3c", s1[i] );
    }

    printf("\ns2 = ");
    
    for(int i = 0; i < SIZE+1; i++ ){
        printf("%-3c", s2[i] );
    }
    printf("\n\n");
    
    for( int i = 0; i < SIZE+1; i++ ){
        if( s1[i] == '1' && s2[i] == '1' ){
            S[i] = '1';
        }
        else if( s1[i] == '0' && s2[i] == '0' ){
            S[i] = '0';
        }
        else{
            S[i] = 'u';
        }
    }
    printf("mC = ");
    printS();
    return 0;
}

// ****************************************************************


int initializeC( ){
    for( int i=0; i<SIZE+1; i++ ){
        for( int j=0; j<SIZE+1; j++ ){
            C[i][j] = 'u';
        }
    }
    return 0;
}

int initializeD(){
    for( int i = 0; i<2*SIZE; i++ ){
        for( int j = 0; j < SIZE/2+1; j++ ){
            D[i][j] = 0;
        }
    }
    return 0;
}

int initializeStoreJ(){
    for( int i = 0; i < 2*SIZE; i++ ){
        storeJ[i] = 0;
    }
    return 0;
}

int initialized(){
    for( int i = 0; i < SIZE/2+1; i++ ){
        d[i] = 0;
    }
    return 0;
}

int getInt( char character ){
    if( character == '1' )return 1;
    if( character == '2' )return 2;
    if( character == '3' )return 3;
    if( character == '4' )return 4;
    if( character == '5' )return 5;
    if( character == '6' )return 6;
    if( character == '7' )return 7;
    if( character == '8' )return 8;
    if( character == '9' )return 9;
    
    return 0;
}

int print(){
    for( int i = 0; i < SIZE+1; i++ ){
        for( int j = 0; j < SIZE+1; j++ ){
            if( C[i][j] == 1 ){
                printf("%-3s", "1");
            }
            else{
                printf("%-3s", "-1");
            }
        }
        printf("\n\n\n\n\n");
    }
    return 0;
}

int printS(){
    for(int i = 0; i < SIZE+1; i++ ){
        printf("%-3c", S[i] );
    }
    printf("\n\n");
    
    return 0;
}

