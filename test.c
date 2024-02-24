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

deck_t * test_add_card_to(int num){
    deck_t * deck = malloc(sizeof(*deck));
    deck->n_cards = 0;
    deck->cards = malloc(deck->n_cards * sizeof(*deck->cards));
    for(int i = 0; i < 4; i++){
        //printf("%d\n", num + (i*10));
        card_t c = card_from_num(num + (i * 13));
        // print_card(c);
        // printf("\n");
        add_card_to(deck, c);
    }
    card_t c = card_from_num(12);
    add_card_to(deck, c);
    unsigned * result = get_match_counts(deck);
    for(int i = 0; i < deck->n_cards; i ++){
        printf("%d\n", result[i]);
    }
    free(result);
    return deck;
}

deck_t * test_build_remaining_deck(deck_t ** hands, size_t n_hands){
    return build_remaining_deck(hands, n_hands);
}

int main(int argc,char **argv){
    // size_t n_hands = 5;
    // deck_t ** hands = malloc(5 * sizeof(*hands));
    // for(int i = 0; i < n_hands; i++){
    //     hands[i] = test_add_card_to(i + 3);
    // }
    // deck_t * deck = test_build_remaining_deck(hands, n_hands);
    // free_deck(deck);
    // for(int i = 0; i < n_hands; i++){
    //     free_deck(hands[i]);
    // }
    // free(hands);
    FILE* f_hands = fopen(argv[1], "r");
    size_t* n_hands = malloc(sizeof(*n_hands));
    future_cards_t* fc = malloc(sizeof(*fc));
    fc->n_decks = 0;
    fc->decks = NULL; 
    deck_t** hands = NULL;

    if(f_hands != NULL){
        hands = read_input(f_hands, n_hands, fc);
        // for(int i = 0; i < *n_hands; i++){
        //     print_hand(hands[i]);
        //     printf("\n");
        // }
        // printf("_____________________________\n");
    }
    else{
        fprintf(stderr, "empty file");
        fclose(f_hands);
        free_future_cards(fc);
        free(n_hands);
        return 0;
    }
    FILE* f_draws = fopen(argv[2], "r");
    size_t* n_draws = malloc(sizeof(*n_draws)); 
    if(f_draws != NULL){
        deck_t** deck = read_input_drawing(f_draws, n_draws, fc);
        // for(int i = 0; i < *n_draws; i++){
        //     //printf("hello: %ld\n", *n_draws);
        //     //future_cards_from_deck(deck[i], fc);
        //     //print_hand(hands[i]);
        //     //printf("\n");
        // }
        future_cards_from_deck(deck[0], fc);
        printf("\n");
        // printf("ptr: %lX\n", (uintptr_t) hands[4]->cards[4]);
        // printf("ptr2: %lX\n", (uintptr_t) fc->decks[0].cards[0]);
        for(int i = 0; i < *n_hands; i++){
            print_hand(hands[i]);
            printf("\n");
        }
        printf("_____________________________\n");
        for(int i = 0; i < *n_draws; i++){
            free_deck(deck[i]);
        }
        free(deck);
    }
    for(int i = 0; i < *n_hands; i++){
        free_deck(hands[i]);
    }
    free(hands);
    free(n_hands);
    free(n_draws);
    free_future_cards(fc);
    fclose(f_hands);
    fclose(f_draws);
    //print_hand(deck);
    return 0;

}