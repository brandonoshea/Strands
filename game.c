#include "game.h"

// REQUIRED
FILE * open_data_file(int argc, char** argv) {
    FILE *filePtr;
    // check for command line argument
    if (argc > 1) {
        // Open file if argc is over 1
        filePtr = fopen(argv[1], "r");
	if (filePtr == NULL) {
	  return NULL;
	}
    }
    else {
        char filename[51];
        printf("Provide strand data filename: ");
        scanf("%50s", filename);
        filePtr = fopen(filename, "r");
        if (filePtr == NULL) {
            return NULL;
        }
        
    }
    return filePtr;
}
FILE * open_dict_file(int argc, char** argv) {
    FILE *file_dict;
    // Check for command line argument for a dictionary
    if (argc > 2) {
        file_dict = fopen(argv[2], "r");
        if (file_dict == NULL) {
            return NULL;
        }    
    } else {
        // default
        file_dict = fopen(DICT_PATH, "r");
    }
    return file_dict;// return dictionary 
}
// REQUIRED - DO NOT EDIT
void print_instructions(strand_t * strand) {
    printf("\n  +-- Welcome to Strands! --+\n");
    printf("\nInstructions:\n");
    printf("\tFind all %d %d-letter words\n", strand->numWords, strand->wordLen);
    printf("\tEach word's letters must touch\n");
    printf("\tA letter can be repeated in a word\n");
    printf("\tType a word then press 'Enter'\n");
    printf("\tType 'quit' when done\n");
}

// REQUIRED
void play_game(strand_t * strand) {
    int total = strand->numWords;
    int found = 0;
    char user_guess[26];
    while (found < total) {
        printf("\nGuess a word or 'quit': ");
        scanf("%s", user_guess);
        if (strcmp(user_guess, "quit") == 0) {//check if user wants to quit
            printf("\nYou found %d out of %d %d-letter words.\n", found, total, strand->wordLen);
            printf("Thanks for playing!\n");
            return;//end game
        }
        if (is_word_in_strand(strand, user_guess)) {
            printf("%s is a valid word in the strand!\n", user_guess);
            found++;//add to found words
            printf("You have found %d of %d %d-letter words in the strand so far.\n", found, total, strand->wordLen);
        } else {
            printf("%s is not a valid word in the strand.\n", user_guess);
            printf("You have found %d of %d %d-letter words in the strand so far.\n", found, total, strand->wordLen);
        }
    }
    printf("\nYou found all %d %d-letter words!\n", total, strand->wordLen);
    printf("Great job! Thanks for playing!\n");
}
