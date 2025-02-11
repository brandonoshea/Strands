#include "strand.h"

#include <ctype.h>

// REQUIRED
strand_t * create_strand(FILE * dataFP, FILE * dictFP) {
  // create strand
    strand_t *strand = (strand_t *)malloc(sizeof(strand_t));
    if (fscanf(dataFP, "%d %d", &strand->rows, &strand->cols)!= 2){
        fprintf(stderr, "Error");
    }
    if (fscanf(dataFP, "%d", &strand->wordLen) != 1){
        fprintf(stderr, "Error");
    }
    strand->letters = (char**)malloc(strand->rows * sizeof(char*));
    for (int i = 0; i < strand->rows; i++){
        strand->letters[i] = (char *)malloc(strand->cols * sizeof(char));
    }
    for (int i = 0; i < strand->rows; i++) {
        for(int j = 0; j < strand->cols; j++) {
            if (fscanf(dataFP, " %c", &strand->letters[i][j]) != 1){
                fprintf(stderr, "Error\n");
            }
        }
    }

    strand->words = (char **)malloc(MAX_WORD_LENGTH * sizeof(char *));
    int num = 0;
    char word[31];
    rewind(dictFP);
    while (fscanf(dictFP, "%s", word) != EOF) {
        if (strlen(word) == strand->wordLen && valid_word(word, strand->letters, strand->rows, strand->cols)){
            strand->words[num] = strdup(word);
            num++;
        }
    }
    strand->numWords = num;
    fclose(dictFP);
    return strand;
}
bool valid_word(const char *word, char **letters, int rows, int cols) {
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            
            if (check_word_sequence(word, letters, row, col, rows, cols)) {
                return true;  // Word found
            }
        }
    }
    
    return false;
}
bool check_word_sequence(const char *word, char **letters, int row, int col, int rows, int cols) {
    // Base case: if the first character of the word does not match the current cell
    if (letters[row][col] != word[0]) {
        return false;
    }

    
    if (word[1] == '\0') {
        return true;
    }

    // positions
    int dr[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dc[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    // Iterate over all adjacent and diagonal positions
    for (int i = 0; i < 8; i++) {
        int new_row = row + dr[i];
        int new_col = col + dc[i];

        // Check new position
        if (new_row >= 0 && new_row < rows && new_col >= 0 && new_col < cols) {
            // Recursively check 
            if (check_word_sequence(word + 1, letters, new_row, new_col, rows, cols)) {
                return true;  // Word found
            }
        }
    }

    // Word not found
    return false;
}

bool is_word_in_strand(strand_t * strand, char * word) {
    for (int i = 0; i < strand->numWords; i++){
        if (strcmp(strand->words[i], word) == 0) {
            return true;
        }
    }
    return false;
}

// REQUIRED
void print_strand_matrix(strand_t * strand) {
    printf("\n");
    
    printf("\t+");
    for (int i = 0; i < strand->cols; i++) {
        printf("---+");
    }
    printf("\n");

    // Print matrix
    for (int i = 0; i < strand->rows; i++) {
        printf("\t|");
        for (int j = 0; j < strand->cols; j++) {
            printf(" %c |", strand->letters[i][j]);
        }
        printf("\n");
        printf("\t+");
        for (int k = 0; k < strand->cols; k++) {
            printf("---+");
        }
        printf("\n");
    }
}

// REQUIRED
void free_strand(strand_t * strand) {
    for (int i = 0; i < strand->rows; i++) {
        free(strand->letters[i]);
    }
    free(strand->letters);
    for (int i = 0; i < strand->numWords; i++) {
        free(strand->words[i]);
    }
    free(strand->words);
    free(strand);
    //deallocate memory
}
