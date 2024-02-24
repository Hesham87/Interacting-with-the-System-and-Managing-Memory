#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "cards.h"
#include "deck.h"
#include "eval.h"
#include "future.h"
#include "input.h"
#include <inttypes.h> 


int main(int argc,char **argv){
    int num_trials = 10000;
    if(argc > 3){
        fprintf(stderr, "wrong number of arrguments expected <input file name> and optinaly <number of trials> found: %d", argc);
        return 0;
    }
    else if(argc == 3){
        num_trials = atoi(argv[2]);
    }
    FILE* f_hands = fopen(argv[1], "r");
    size_t* n_hands = malloc(sizeof(*n_hands));
    future_cards_t* fc = malloc(sizeof(*fc));
    fc->n_decks = 0;
    fc->decks = NULL; 
    deck_t** hands = NULL;

    if(f_hands != NULL){
        hands = read_input(f_hands, n_hands, fc);
    }
    else{
        fprintf(stderr, "empty file");
        fclose(f_hands);
        free_future_cards(fc);
        free(n_hands);
        return 0;
    }
    unsigned* result = malloc((*n_hands  + 1) * sizeof(*result));
    for(int i = 0; i <= *n_hands; i++){
        result[i] = 0;
    }

    deck_t* draw_deck  = build_remaining_deck(hands, *n_hands);


    for(int i = 0; i < num_trials; i++){
        shuffle(draw_deck);
        future_cards_from_deck(draw_deck, fc);
        // for(int k = 0; k < *n_hands; k++){
        //     print_hand(hands[k]);
        //     printf("\n");
        // }
        // printf("_____________________________\n");
        deck_t* highest_hand = hands[0];
        int index = 0;
        bool tie = false;
        for(int j = 1; j < *n_hands; j++){
            int comp =  compare_hands(highest_hand, hands[j]);
            if(comp < 0){
                highest_hand = hands[j];
                tie = false;
                index = j;
            }
            else if(comp == 0){
                tie = true;
            }
        }
        if(tie){
            result[*n_hands]++;
            tie = false;
        }
        else{
            result[index]++;
        }
    }
    for(size_t i = 0; i < *n_hands; i++){
        printf("Hand %zu won %u / %u times (%.2f%%)\n", i, result[i], num_trials, (result[i]*1.0)/num_trials);
    }

    for(int i = 0; i < *n_hands; i++){
        free_deck(hands[i]);
    }
    free(hands);
    free_deck(draw_deck);
    free(n_hands);
    free_future_cards(fc);
    fclose(f_hands);
    free(result);
    return 0;


}