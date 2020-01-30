#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define SIZE 25

int initializeG();
int initializeC();
int initializeD();
int initializeStoreJ();
int initialized();
int initializetempC();
int initializeRowChange();
int initializeColChange();
int getInt(char character);
int propagationCol( int row );
int propagationRow( int row );
int print();
int printS();
int storeChange();
int printCol();
void propagate();
void fb1();
void initializeG0();
void initializeG1();
void upDateOnAllG();
void initializeSotoreij();
void probe( int x, int y );
void mergeG();
void checkSolve();
void backtracking();
void find_pixel();

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
char tempC[SIZE+1][SIZE+1];
int rowChange[SIZE+1];
int colChange[SIZE+1];
char G[SIZE+1][SIZE+1];
char G0[SIZE+1][SIZE+1];
char G1[SIZE+1][SIZE+1];
int isConflict = 0;
int complete = 0;
int storei[SIZE*SIZE];
int storej[SIZE*SIZE];
int pi = 1;
int hasPainted = 0;
int storeijCounter = 0;
int unPaintedCounting = 0;
int skip_first_q = 0;
int getNumber = 0;
int find_pixel1 = 0;
int find_pixel2 = 0;

int main(){
    
    clock_t start_time, end_time;
    float total_time = 0;
    start_time = clock();
    
    FILE *pFile;
    char ch;
    
    pFile = fopen("nonogram.txt", "r");
    if( NULL == pFile ){
        printf("Open failure");
        return 1;
    }
    else{
        while(1){
            x = 0;
            J = 0;
            initializeC();
            initializeD();
            initializeStoreJ();
            initializetempC();
            initializeRowChange();
            initializeColChange();
            
            if(skip_first_q == 1 ){
                ch = getc(pFile);
                printf("Question %c", ch );
                while((ch = getc(pFile))!='\n'){
                    printf("%c", ch );
                }
                printf("\n");
            }
            while( (ch = getc(pFile)) ){
                if( ch == EOF ) break;
                
                if(skip_first_q == 0 ){
                    skip_first_q = 1;
                    if( ch == '$'){
                        ch = getc(pFile);
                        printf("Question %c\n", ch );
                        ch = getc(pFile); // skip first \n
                        ch = getc(pFile);
                    }
                }
                else{
                    if( ch == '$')break;
                }
                /*
                 while( ch != '\n' ){
                 if( getInt(ch) >= 1 ){
                 
                 D[x][J] = getInt(ch);
                 J++;
                 }
                 ch = getc(pFile);
                 if( ch  == EOF )break;
                 } // end switch line
                 */
                
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
                        //printf("%d ", getNumber );
                    }
                    if( ch == '\n' )break;
                    if( ch  == EOF )break;
                    if( ch != '1' || ch != '2' || ch != '3' || ch != '4' || ch != '5' || ch != '6' || ch != '7' || ch != '8' || ch != '9'){
                        ch = getc(pFile);
                    }
                } // end switch line
                //printf("\n");
                storeJ[x] = J;
                J = 0;
                x++; // 會多加一個 1
            }
            //printf("START!!\n");
            backtracking();
            if( complete == 1 ){
                print();
            }
            else{
                printf("\n\nUNSOLVED!!!\n\n");
            }
            complete = 0;
            isConflict = 0;
            pi = 1;
            
            if( ch == EOF ) break;
        }
        fclose(pFile);
    }
    //fclose(pFile);
    end_time = clock();
    total_time = (float)(end_time - start_time)/CLOCKS_PER_SEC;
    printf("Time = %f sec\n", total_time );
    return 0;
}

void backtracking(){
    
    propagate();
    if( isConflict == 1 )return;
    fb1();
    checkSolve();
    if( isConflict == 1 )return;
    if( complete == 1 )return;
    
    find_pixel();
    
    // transfer C to tempC
    initializetempC();
    for( int a = 0; a < SIZE+1; a++ ){
        for( int b = 0; b < SIZE+1; b++ ){
            tempC[a][b] = C[a][b];
        }
    }
    
    
    // G0
    C[find_pixel1][find_pixel2] = '0';
    backtracking();
    if( isConflict == 1 ){
        // recover C
        for( int a = 0; a < SIZE+1; a++ ){
            for( int b = 0; b < SIZE+1; b++ ){
                C[a][b] = tempC[a][b];
            }
        }
        isConflict = 0;
    }
    
    find_pixel();
    
    // G1
    C[find_pixel1][find_pixel2] = '1';
    backtracking();
    if( isConflict == 1){
        // recover C
        for( int a = 0; a < SIZE+1; a++ ){
            for( int b = 0; b < SIZE+1; b++ ){
                C[a][b] = tempC[a][b];
            }
        }
        isConflict = 0;
    }
}

void find_pixel(){
    
    find_pixel1 = 0;
    find_pixel2 = 0;
    
    int i = 1;
    int j = 1;
    for( i = 1; i < SIZE+1; i++ ){
        for( j = 1; j < SIZE+1; j++ ){
            if( C[i][j] == '?' ){
                find_pixel1 = i;
                find_pixel2 = j;
                break;
            }
        }
        if( C[i][j] == '?' )break;
    }
}

// ====================================================================
// fully probing
// ====================================================================

void fb1(){
    
    initializeG0();
    initializeG1();
    
    while( pi != 0 ){
        pi = 0;
        propagate();
        checkSolve();
        if( isConflict == 1 )return;
        if( complete == 1 )return;
        upDateOnAllG();
        storeijCounter = 0;
        while( unPaintedCounting > 0 ){
            int x = 0, y = 0;
            
            x = storei[storeijCounter];
            y = storej[storeijCounter];
            storeijCounter++;
            
            probe( x, y );
            checkSolve();
            if( isConflict == 1 || complete == 1 ){
                return;
            }
            if( hasPainted == 1 ){
                hasPainted = 0;
                break;
            }
            unPaintedCounting--;
        }
    }
}

void probe( int i, int j ){
    
    int G0isConflict = 0;
    int G1isConflict = 0;
    
    
    
    // transfer C to tempC
    initializetempC();
    for( int a = 0; a < SIZE+1; a++ ){
        for( int b = 0; b < SIZE+1; b++ ){
            tempC[a][b] = C[a][b];
        }
    }
    
    // G0
    C[i][j] = '0';
    propagate();
    for( int a = 0; a < SIZE+1; a++ ){
        for( int b = 0; b < SIZE+1; b++ ){
            G0[a][b] = C[a][b];
        }
    }
    if( isConflict == 1 ){
        G0isConflict = 1;
        isConflict = 0;
    }
    
    
    // recover C
    for( int a = 0; a < SIZE+1; a++ ){
        for( int b = 0; b < SIZE+1; b++ ){
            C[a][b] = tempC[a][b];
        }
    }
    
    // G1
    C[i][j] = '1';
    propagate();
    for( int a = 0; a < SIZE+1; a++ ){
        for( int b = 0; b < SIZE+1; b++ ){
            G1[a][b] = C[a][b];
        }
    }
    if( isConflict == 1 ){
        G1isConflict = 1;
        isConflict = 0;
    }
    
    
    // recover C
    for( int a = 0; a < SIZE+1; a++ ){
        for( int b = 0; b < SIZE+1; b++ ){
            C[a][b] = tempC[a][b];
        }
    }
    
    if( G0isConflict == 1 && G1isConflict == 1 ){
        isConflict = 1;
        return;
    }
    else if( G0isConflict == 1 && G1isConflict == 0 ){
        for( int a = 0; a < SIZE+1; a++ ){
            for( int b = 0; b < SIZE+1; b++ ){
                if(C[a][b] != G1[a][b]){
                    pi++;
                }
                C[a][b] = G1[a][b];
            }
        }
    }
    else if( G1isConflict == 1 && G0isConflict == 0 ){
        for( int a = 0; a < SIZE+1; a++ ){
            for( int b = 0; b < SIZE+1; b++ ){
                if(C[a][b] != G0[a][b]){
                    pi++;
                }
                C[a][b] = G0[a][b];
            }
        }
    }
    else{
        mergeG();
    }
    
    
    // debug
    if(  G0isConflict == 1 && G1isConflict == 0 && pi == 0 ){
        hasPainted = 1;
    }
    if(  G0isConflict == 0 && G1isConflict == 1 && pi == 0 ){
        hasPainted = 1;
    }
    
    
    if( pi != 0 ){
        upDateOnAllG();
        hasPainted = 1;
    }
    
}

void mergeG(){
    for( int a = 0; a < SIZE+1; a++ ){
        for( int b = 0; b < SIZE+1; b++ ){
            if( G0[a][b] == '1' && G1[a][b] == '1' ){
                
                if(C[a][b] != G1[a][b]){
                    pi++;
                }
                
                C[a][b] = '1';
            }
            else if( G0[a][b] == '0' && G1[a][b] == '0' ){
                
                if(C[a][b] != G1[a][b]){
                    pi++;
                }
                
                C[a][b] = '0';
            }
            else{
                C[a][b] = '?';
            }
        }
    }
}

void upDateOnAllG(){
    initializeSotoreij();
    unPaintedCounting = 0;
    for( int i = 1; i < SIZE+1; i++ ){
        for( int j = 1; j < SIZE+1; j++ ){
            if( C[i][j] == '?' ){
                storei[unPaintedCounting] = i;
                storej[unPaintedCounting] = j;
                unPaintedCounting++;
            }
        }
    }
}

void initializeSotoreij(){
    for( int i = 0; i < SIZE*SIZE; i++ ){
        storei[i] = 0;
        storej[i] = 0;
    }
}

void initializeG0(){
    for( int i = 0; i < SIZE+1; i++ ){
        for( int j = 0; j < SIZE+1; j++ ){
            G0[i][j] = '?';
        }
    }
}

void initializeG1(){
    for( int i = 0; i < SIZE+1; i++ ){
        for( int j = 0; j < SIZE+1; j++ ){
            G1[i][j] = '?';
        }
    }
}

// ===================================================================
// propagate
// ===================================================================

void propagate(){
    // propagate
    
    x = 0;
    while( x < 2*SIZE ){
        
        if( x < SIZE ){
            propagationCol(x);
            if(isConflict == 1 )return;
            if( isConflict != 1){
                for( int i = 0; i < SIZE+1; i++ ){
                    C[i][x+1] = S[i];
                }
            }
        }
        else{
            propagationRow(x);
            if(isConflict == 1 )return;
            if( isConflict != 1){
                for( int i = 0; i < SIZE+1; i++ ){
                    if(C[(x%25)+1][i] != S[i]){
                        colChange[i] = 1;
                    }
                    C[(x%25)+1][i] = S[i];
                }
            }
        }
        initialized();
        x++;
    }
    
    
    while(1){
        
        int rowConfirm = 0;
        int colConfirm = 0;
        
        x = 0;
        while( x < 2*SIZE ){
            
            
            if( x < SIZE ){
                if(colChange[x+1] == 1 ){
                    propagationCol(x);
                    if(isConflict == 1 )return;
                    if( isConflict != 1){
                        for( int i = 0; i < SIZE+1; i++ ){
                            if(C[i][x+1] != S[i]){
                                rowChange[i] = 1;
                                rowConfirm++;
                                C[i][x+1] = S[i];
                            }
                        }
                    }
                }
            }
            else{
                
                if(x == SIZE){
                    initializeColChange();
                }
                
                if( rowChange[(x%SIZE)+1] == 1 ){
                    propagationRow(x);
                    if(isConflict == 1 )return;
                    if( isConflict != 1){
                        for( int i = 0; i < SIZE+1; i++ ){
                            if(C[(x%SIZE)+1][i] != S[i]){
                                colChange[i] = 1;
                                colConfirm++;
                                C[(x%SIZE)+1][i] = S[i];
                            }
                        }
                    }
                }
            }
            initialized();
            x++;
        }
        initializeRowChange();
        if( rowConfirm == 0 && colConfirm == 0 )break;
    }
    
    
    //print();
    //printf("\n");
    //initializeD();
    //initializeStoreJ();
}

// calculate for col
int propagationCol( int row ){
    
    int ii = SIZE+1;
    int jj = 0;
    int fixZero = 0;
    int fixOne = 0;
    int total = 0;
    int isConflict = 0;
    
    initialized( );
    
    // load j
    jj = storeJ[row];
    
    // load d
    for( int i = 0; i < jj; i++ ){
        d[i] = D[row][i];
    }
    
    // load C[][] to S[]
    for( int i = 0; i < SIZE+1; i++ ){
        S[i] = C[i][x+1];
    }
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
    int isConflict = 0;
    
    initialized( );
    
    // load j
    jj = storeJ[row];
    
    // load d
    for( int i = 0; i < jj; i++ ){
        d[i] = D[row][i];
    }
    
    row = row % SIZE;
    // load C[][] to S[]
    for( int i = 0; i < SIZE+1; i++ ){
        S[i] = C[row+1][i];
    }
    
    int ss2 = SIZE+1;
    paint( ss2, jj );
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
    if( fixOne( i, j ) == 0 && fixZero( i, j ) == 1 ){
        paintZero( i, j );
    }
    else if( fixOne( i, j ) == 1 && fixZero( i, j ) == 0 ){
        paintOne( i, j );
    }
    else if( fixOne( i, j ) == 1 && fixZero( i, j ) == 1 ){
        merge( i, j );
    }
    else{
        isConflict = 1;
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
    int confirm = 0;
    
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
        s1[counteri] = '?';
        s2[counteri] = '?';
        temp[counteri] = '?';
    }
    
    // put S[] into temp[]
    for( int counteri = 0; counteri < SIZE+1; counteri++ ){
        temp[counteri] = S[counteri];
    }
    
    paintZero( i, j );
    
    // put S to s1
    for( int counteri = 0; counteri < SIZE+1; counteri++ ){
        s1[counteri] = S[counteri];
    }
    
    // recover S
    for( int counteri = 0; counteri < SIZE+1; counteri++ ){
        S[counteri] = temp[counteri];
    }
    
    paintOne( i, j );
    
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
    
    for( int i = 0; i < SIZE+1; i++ ){
        if( s1[i] == '1' && s2[i] == '1' ){
            S[i] = '1';
        }
        else if( s1[i] == '0' && s2[i] == '0' ){
            S[i] = '0';
        }
        else{
            S[i] = '?';
        }
    }
    return 0;
}

// ****************************************************************


int initializeC( ){
    for( int i=0; i<SIZE+1; i++ ){
        for( int j=0; j<SIZE+1; j++ ){
            C[i][j] = '?';
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

int initializetempC( ){
    for( int i=0; i<SIZE+1; i++ ){
        for( int j=0; j<SIZE+1; j++ ){
            tempC[i][j] = '?';
        }
    }
    return 0;
}

int initializeRowChange(){
    for( int i = 0; i < SIZE+1; i++ ){
        rowChange[i] = 0;
    }
    return 0;
}

int initializeColChange(){
    for( int i = 0; i < SIZE+1; i++ ){
        colChange[i] = 0;
    }
    return 0;
}

void checkSolve(){
    for( int i = 0; i < SIZE+1; i++ ){
        for( int j = 0; j < SIZE+1; j++ ){
            if( C[i][j] == '?'){
                complete = 0;
                return;
            }
        }
    }
    complete = 1;
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
            printf("%-3c", C[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    return 0;
}

int printS(){
    for(int i = 0; i < SIZE+1; i++ ){
        printf("%-3c", S[i] );
    }
    printf("\n");
    
    return 0;
}

int printCol(){
    for(int i = 0; i < SIZE+1; i++ ){
        printf("%-3c", C[i][x+1] );
    }
    printf("\n");
    
    return 0;
}


