#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int getInt( char character );
int putIntoC_col( int s1 );
int putIntoC_row( int s2 );
int print(void);
int storeNum( int number );
int initializeN();
int makeupZero_col();
int makeupZero_row();
int initializeC();

int plusA = 0;
int A[25], B[25];
int C[25][25];
int row = 0;
int col = 0;
int counting = 1;
int shift = 0;
int N[13];
int numberCounter = 0;

int main(){
    
    clock_t start_time, end_time;
    float total_time = 0;
    start_time = clock();
    
    FILE *pFile;
    char ch;
    int num = 0;
    int total = 0;
    int trans = 0;
    
    
    pFile = fopen( "nonogram.txt", "r" ); // "r" 開啟用來讀取的檔案
    if ( NULL == pFile ){
        printf( "Open failure" );
        return 1;
    }else{
        while( ( ch = getc(pFile)) ){
            if( ch == EOF) break;
            if( ch == '$'){
                ch = getc(pFile);
                
                
                int question = 0;
                question = getInt(ch);
                if( question > 1){
                    print();
                    initializeC();
                    trans = 0;
                    row = 0;
                    col = 0;
                }
                
                
                printf("Question %c\n", ch );
                ch = getc(pFile); // skip the first '\n'
            }
            else{
                while( ch != '\n'){
                    if( ch == ' '){
                        continue; // ignore empty character
                    }else{
                        num = getInt(ch);
                        
                        if( num != 0){
                            total += num;
                            total++;
                            storeNum(num);
                        }
                    }
                    ch = getc(pFile); // important!!!
                    if( ch == EOF) break;
                }  // end while
                shift = 25 - total + 1;
                total = 0;
                printf("")
                
                if( trans < 25 ){
                    putIntoC_row(shift);
                    col++;
                }
                else{
                    putIntoC_col(shift);
                    row++;
                }
                trans++;
                plusA = 0;
            } // end else
        } // end while
    }
    print(); // print the last question
    fclose(pFile);
    
    end_time = clock();
    total_time = (float)(end_time - start_time)/CLOCKS_PER_SEC;
    printf("Time = %f sec\n", total_time );
    
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

 int putIntoC_col( int s1 ){
     
     int change = 0, point = 0, k = 0, i = 0;
     while( numberCounter != 0 ){
         change = N[k] - s1;
 
         if( change > 0 ){
             for( int j = 0; j < change; j++ ){
                 i = point + s1 + j;
                 C[row][i] = 1;
             }
             
             point += ( N[k] + 1 );
             numberCounter--;
             k++;
         }
         else{
             numberCounter--;
             k++;
         }
     }
     makeupZero_col();
     initializeN();
     return 0;
 }

int putIntoC_row( int s2 ){
    int change = 0, point = 0, k = 0, i = 0;
    
    while( numberCounter != 0 ){
        change = N[k] - s2;
        
        if( change > 0 ){
            for( int j = 0; j < change; j++ ){
                i = point + s2 + j;
                C[i][col] = 1;
            }
            point += ( N[k] + 1 );
            numberCounter--;
            k++;
        }
        else{
            numberCounter--;
            k++;
        }
    }
    makeupZero_row();
    initializeN();
    return 0;
}

int print(void){
    for( int i = 0; i < 25; i++ ){
        for( int j = 0; j < 25; j++ ){
            if( C[i][j] == 1 ){
                printf("%-3s", "1");
            }
            else{
                printf("%-3s", "?");
            }
        }
        printf("\n");
    }
    return 0;
}

int storeNum( int number ){
    N[numberCounter] = number;
    numberCounter++;
    return 0;
}

int initializeN(){
    for( int i = 0; i < 13; i++ ){
        N[i] = 0;
    }
    return 0;
}

int makeupZero_col(){
    for( int i=0; i<25; i++ ){
        if( C[row][i] != 1 ){
            C[row][i] = 0;
        }
    }
    return 0;
}

int makeupZero_row(){
    for( int i=0; i<25; i++ ){
        if( C[i][col] != 1 ){
            C[i][col] = 0;
        }
    }
    return 0;
}


int initializeC(){
    for( int i = 0; i < 25; i++ ){
        for( int j = 0; j < 25; j++ ){
            C[i][j] = 0;
        }
    }
    return 0;
}
