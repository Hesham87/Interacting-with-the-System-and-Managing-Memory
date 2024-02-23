#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "future.h"

void add_future_card(future_cards_t * fc, size_t index, card_t * ptr){
    if (fc == NULL) {
        fprintf(stderr, "No memory allocated for future cards in future.c:add_future_card\n");
        return;
    }
    if (index >= fc->n_decks) {
    fc->decks =  realloc(fc->decks, (index+1) * sizeof(*fc->decks));
    for (int i=fc->n_decks; i <= index; i++) {
      fc->decks[i].n_cards = 0;
      fc->decks[i].cards = NULL;
    }
    fc->n_decks = index + 1;
    }
    fc->decks[index].n_cards++;
    fc->decks[index].cards = realloc(fc->decks[index].cards, fc->decks[index].n_cards * sizeof(*fc->decks[index].cards));
    fc->decks[index].cards[fc->decks[index].n_cards - 1] = ptr;
}

void future_cards_from_deck(deck_t * deck, future_cards_t * fc){
    for(int i = 0; i < fc->n_decks; i++){
        if (fc->decks[i].n_cards > 0) {
            for(int j = 0; j < fc->decks[i].n_cards; j++){
                fc->decks[i].cards[j]->value = deck->cards[i]->value;
                fc->decks[i].cards[j]->suit = deck->cards[i]->suit;
            }
        }
    }
}

void free_decks(deck_t * decks, int n_decks) {
  for (int i=0; i < n_decks; i++) {
    free(decks[i].cards);
  }
  free(decks);
}

void free_future_cards(future_cards_t * fc) {
  free_decks(fc->decks, fc->n_decks);
  free(fc);
}