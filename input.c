#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "input.h"

bool drawing = false;
deck_t ** read_input_drawing(FILE * f, size_t * n_hands, future_cards_t * fc){
    drawing = true;
    deck_t** deck = read_input(f, n_hands, fc);
    drawing = false;
    return deck;
}

deck_t * hand_from_string(const char * str, future_cards_t * fc){
    char* card_letters;
    char* str_dub = strdup(str);
    str_dub = strtok(str_dub, "\n");   //removing new line character if it exists
    card_letters = strtok(str_dub, " ");
    deck_t* deck = malloc(sizeof(*deck));
    deck->n_cards = 0;
    deck->cards = NULL;
    int card_counter = 0;
    while(card_letters != NULL){
        card_counter++;
        if(card_letters[0] == '?'){
            card_t* card_ptr = add_empty_card(deck);
            card_letters[strlen(card_letters)] = '\0';
            size_t index = atoi(++card_letters);
            add_future_card(fc, index, card_ptr); 
        }
        else{
            card_t card = card_from_letters(card_letters[0], card_letters[1]);
            add_card_to(deck, card);
        }
        
        card_letters = strtok(NULL, " ");
    }
    if(!drawing && card_counter < 5){
        fprintf(stderr, "no less than 5 cards in a hand are allowed, found %d\n", card_counter);
        free_future_cards(fc);
        free_deck(deck);
        free(str_dub);
        return NULL;
    }
    free(str_dub);
    return deck;
}

deck_t ** read_input(FILE * f, size_t * n_hands, future_cards_t * fc){
    if(f != NULL){
        char* linep = NULL;
        size_t size = 0;
        deck_t** hands = malloc(sizeof(*hands));
        int hand_counter = 0;
        while(getline(&linep, &size, f) >= 0){
            hand_counter++;
            hands = realloc(hands, hand_counter * sizeof(hands));
            hands[hand_counter -1] = hand_from_string((const char*)linep, fc);
            if (hands[hand_counter-1] == NULL) {
                for (int i = 0; i < hand_counter-1; i++) {
                    free_deck(hands[i]);
                }
                free(hands);
                free(linep);
                hand_counter = 0;
                return NULL;
            }
            free(linep);
            linep = NULL;
        }
        *n_hands = hand_counter;
        free(linep);
        return hands;
    }
    return NULL;
}