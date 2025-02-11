#ifndef STRAND_H
#define STRAND_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#define MAX_ROWS 100
#define MAX_COLS 100
#define MAX_WORD_LENGTH 10000// REQUIRED STRUCT - DO NOT REMOVE STRUCT MEMBERS
typedef struct strand
{
    char** words;
    char** letters;
    int rows, cols;
    int numWords;
    int wordLen;

} strand_t;

// REQUIRED FUNCTIONS
strand_t * create_strand(FILE * dataFP, FILE * dictFP);
bool is_word_in_strand(strand_t * strand, char * word);
void print_strand_matrix(strand_t * strand);
void free_strand(strand_t * strand);

bool valid_word(const char *word, char **letters, int rows, int cols);
bool check_word_sequence(const char *word, char **letters, int row, int col, int rows, int cols);
#endif

