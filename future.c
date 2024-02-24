#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "future.h"

void add_future_card(future_cards_t * fc, size_t index, card_t * ptr){
    if (fc == NULL) {
        fprintf(stderr, "No memory allocated for future cards in future.c:add_future_card\n");
        return;
    }
    if(index >= fc->n_decks){
      int old_n_decks = fc->n_decks;
      fc->n_decks = index + 1;
      fc->decks = realloc(fc->decks, fc->n_decks * sizeof(*fc->decks));
      for(int i = old_n_decks; i <= index; i++){
        fc->decks[i].n_cards = 0;
        fc->decks[i].cards = NULL;
      }
      fc->decks[index].n_cards++;
      fc->decks[index].cards = malloc(fc->decks[index].n_cards * sizeof(*fc->decks[index].cards));
      fc->decks[index].cards[fc->decks[index].n_cards - 1] = ptr;
      //print_card(*ptr);
      //printf("index: %ld\n", index);
    }
    else{
      fc->decks[index].n_cards++;
      fc->decks[index].cards = realloc(fc->decks[index].cards, fc->decks[index].n_cards * sizeof(*fc->decks[index].cards));
      fc->decks[index].cards[fc->decks[index].n_cards - 1] = ptr;
    }
}

void future_cards_from_deck(deck_t * deck, future_cards_t * fc){
  for(int i = 0; i < fc->n_decks; i++){
    //printf("hello200: %ld\n", fc->n_decks);
    if (fc->decks[i].n_cards > 0) {
      //printf("hello2: %ld\n", fc->decks[i].n_cards);
      for(int j = 0; j < fc->decks[i].n_cards; j++){
        // printf("hello3: %d\n", deck->cards[i]->value);
        // printf("hello4: %d\n", (int)deck->cards[i]->suit);
        //print_card(*deck->cards[i]);
        //printf("hello10\n");
        fc->decks[i].cards[j]->value = deck->cards[i]->value;
        //printf("i: %d, j: %d  ", i, j);
        //printf("hello11\n");
        fc->decks[i].cards[j]->suit = deck->cards[i]->suit;
        //print_card(*fc->decks[i].cards[j]);
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