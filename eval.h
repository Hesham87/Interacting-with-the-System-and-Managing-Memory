#ifndef EVAL_H
#define EVAL_H
#include "deck.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "hash.h"
struct hand_eval_tag {
  hand_ranking_t ranking;
  card_t *cards[5];
};
typedef struct hand_eval_tag hand_eval_t;

hand_eval_t evaluate_hand(deck_t * hand) ;
int compare_hands(deck_t * hand1, deck_t * hand2) ;
unsigned * get_match_counts(deck_t * hand);
int card_ptr_comp(const void * vp1, const void * vp2);
suit_t flush_suit(deck_t * hand);
unsigned get_largest_element(unsigned * arr, size_t n);
size_t get_match_index(unsigned * match_counts, size_t n,unsigned n_of_akind);
ssize_t  find_secondary_pair(deck_t * hand, unsigned * match_counts, size_t match_idx);
int is_n_length_straight_at(deck_t * hand, size_t index, suit_t fs, int n);
int is_ace_low_straight_at(deck_t * hand, size_t index, suit_t fs);
int is_straight_at(deck_t * hand, size_t index, suit_t fs);
hand_eval_t build_hand_from_match(deck_t * hand, unsigned n, hand_ranking_t what, size_t idx);
unsigned * get_match_counts(deck_t * hand);
void copy_straight(card_t ** to, deck_t *from, size_t ind, suit_t fs, size_t count);
int find_straight(deck_t * hand, suit_t fs, hand_eval_t * ans);


#endif
