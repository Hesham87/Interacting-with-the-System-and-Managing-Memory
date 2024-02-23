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
    size_t n_hands = 5;
    deck_t ** hands = malloc(5 * sizeof(*hands));
    for(int i = 0; i < n_hands; i++){
        hands[i] = test_add_card_to(i + 3);
    }
    deck_t * deck = test_build_remaining_deck(hands, n_hands);
    free_deck(deck);
    for(int i = 0; i < n_hands; i++){
        free_deck(hands[i]);
    }
    free(hands);
    //print_hand(deck);
    return 0;

}