#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "input.h"

void strip_newline(char * str) {
  char * p = strchr(str, '\n');
  if (p != NULL) {
    *p = '\0';
  }
}

deck_t * hand_from_string(const char * str, future_cards_t * fc){
    char *token;
    card_t * ptr_c;
    card_t c;
    deck_t * deck = malloc(sizeof(*deck));

    deck->n_cards = 0;
    deck->cards = NULL;

    /* get the first token */
    char s[2] = " ";
    char * hand_str = strdup(str); //can't call strtok on a const char *
    strip_newline(hand_str);
    token = strtok(hand_str, s);
    int card_count = 0;
    /* walk through other tokens */
    while( token != NULL ) {
        if(token[0] == '?'){
            //printf("index: %s\n", token);
            ptr_c = add_empty_card(deck);
            size_t index = strtol(&token[1], NULL, 0);
            add_future_card(fc, index, ptr_c);
        }
        else{
            //printf("token: %s token[0]: %c token[1]: %c\n", token, token[0], token[1]);
            assert(strlen(token) == 2);
            c = card_from_letters(token[0], token[1]);
            add_card_to(deck, c);
        }
        card_count++;
        token = strtok(NULL, s);
    }
    if(fc != NULL && card_count < 5) { // fc set to NULL means we're reading draws, not hands
        fprintf(stderr, "At least five cards per hand needed. %d cards found.\n", card_count);
    
        for (int i=0; i < fc->n_decks; i++) {
            if (fc->decks[i].n_cards > 0) {
                free(fc->decks[i].cards);
                fc->decks[i].cards = NULL;
            }
        }
        free(fc->decks);
        free_deck(deck);
        free(hand_str);
        return NULL;
    }
    return deck;
}

deck_t ** read_input(FILE * f, size_t * n_hands, future_cards_t * fc){
    size_t size = 0;
    char * linep = NULL;
    deck_t ** decks = malloc(sizeof(*decks));

    int n_decks = 0;
    while(getline(&linep, &size, f) >= 0){
        n_decks++;
        decks = realloc(decks, n_decks * sizeof(*decks));
        printf("line from hands: %s\n", linep);
        decks[n_decks - 1] = hand_from_string(linep, fc);
        //print_hand(decks[n_decks - 1]);
        if (decks[n_decks-1] == NULL) {
            for (int i = 0; i < n_decks-1; i++) {
                free_deck(decks[i]);
            }
            free(decks);
            free(linep);
            n_decks = 0;
            return NULL;
        }
    }
    *n_hands = n_decks;
    free(linep);
    return decks;
}