
#include "deck.h"

const int FULL_DECK_SIZE = 52;

void add_card_to(deck_t * deck, card_t c){
    deck->n_cards++;
    deck->cards = realloc(deck->cards, deck->n_cards * sizeof(*deck->cards));
    deck->cards[deck->n_cards - 1] = malloc(sizeof(*deck->cards[deck->n_cards - 1]));
    deck->cards[deck->n_cards - 1]->value = c.value;
    deck->cards[deck->n_cards - 1]->suit = c.suit;
}

card_t * add_empty_card(deck_t * deck){
    deck->n_cards++;
    deck->cards = realloc(deck->cards, deck->n_cards * sizeof(*deck->cards));
    deck->cards[deck->n_cards - 1] = malloc(sizeof(*deck->cards[deck->n_cards - 1]));
    deck->cards[deck->n_cards - 1]->value = 0;
    deck->cards[deck->n_cards - 1]->suit = 0;
    return deck->cards[deck->n_cards - 1]; 
}

deck_t * make_deck_exclude(deck_t * excluded_cards){
    card_t c;
    deck_t * deck = malloc(sizeof(*deck));
    deck->cards = NULL;
    deck->n_cards = 0;
    for(int i = 0; i < FULL_DECK_SIZE; i++){
        c = card_from_num(i);
        if(!deck_contains(excluded_cards, c)){
            add_card_to(deck, c);
        }
    }
    return deck;
}

deck_t * build_remaining_deck(deck_t ** hands, size_t n_hands){
    deck_t * d = malloc(sizeof(*d));
    d->cards = NULL;
    d->n_cards = 0;
    for(int i =0; i < n_hands; i++){
        for(int j = 0; j < hands[i]->n_cards; j++){
            add_card_to(d, *hands[i]->cards[j]);
        }
    }
    deck_t * temp = make_deck_exclude(d);
    free_deck(d);
    return temp;
}

void free_deck(deck_t * deck){
    for(int i = 0; i < deck->n_cards; i++){
        free(deck->cards[i]);
    }
    free(deck->cards);
    free(deck);
}

void print_hand(deck_t * hand){
    for(int i = 0; i < hand->n_cards; i++){
        print_card(*hand->cards[i]);
        printf(" ");
    }
}

// void fprint_hand(FILE *f, deck_t * hand){
//   for(int i=0; i<hand->n_cards; i++) {
//     fprint_card(f, hand->cards[i][0]);
//     fprintf(f, " ");
//   }
// }

int deck_contains(deck_t * d, card_t c) {
   for(int i=0; i<d->n_cards; i++) {
    if(card_comp(*d->cards[i], c) == 0) {
      return 1;
    }
  }
  return 0;
}

void shuffle(deck_t * d){
    for(int i=0; i<d->n_cards; i++) {
        int x = rand() % d->n_cards;
        card_t * temp = d->cards[x];
        d->cards[x] = d->cards[i];
        d->cards[i] = temp;
    }
}

void assert_full_deck(deck_t * d) {
    assert(d->n_cards == FULL_DECK_SIZE);
    for(unsigned i=0; i<FULL_DECK_SIZE; i++) {
        bool is_card_in_deck = deck_contains(d, card_from_num(i));
        assert(is_card_in_deck);
    }
}

