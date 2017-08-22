/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include <string.h>
#include <stdio.h>

char * X, * Y;

void initialize_edit_distance(){
    
    
}

int64_t memo_edit_distance( int16_t i, int64_t j );

int64_t edit_distance( int16_t i, int64_t j ){
    
}

int64_t memo_edit_distance( int16_t i, int64_t j ){
    
}

static int distance (const char * word1, int len1, const char * word2, int len2){
    
    int matrix[len1 + 1][len2 + 1];
    int i;
    int j;
    char c1;
    char c2;
    int delete;
    int insert;
    int substitute;
    int minimum;
    
    for(i = 0; i <= len1; i++){
        matrix[i][0] = i;
    }
    for(i = 0; i <= len2; i++){
        matrix[0][i] = i;
    }
    for(i = 1; i <= len1; i++){
        c1 = word1[i-1];
        for(j = 1; j <= len2; j++){
            c2 = word2[j-1];
            if(c1 == c2){
                matrix[i][j] = matrix[i-1][j-1];
            } else {
                delete = matrix[i-1][j] + 1;
                insert = matrix[i][j-1] + 1;
                substitute = matrix[i-1][j-1] + 1;
                minimum = delete;
                if( insert < minimum ){
                    minimum = insert;
                }
                if( substitute < minimum ){
                    minimum = substitute;
                }
                matrix[i][j] = minimum;
            }
        }
    }
    return matrix[len1][len2];
}

void solve_edit_distance(int argc, char **argv){
    
    const char * word1;
    const char * word2;
    int len1;
    int len2;
    int d;

    word1 = "pieces";
    word2 = "paces";
    len1 = strlen(word1);
    len2 = strlen(word2);
    d = distance(word1, len1, word2, len2);
    printf ("The edit distance between %s and %s is %d.\n",
            word1, word2, d);
}