#include "eval.h"

int card_ptr_comp(const void * vp1, const void * vp2) {
    const card_t * const *cp1 = vp1;
    const card_t * const *cp2 = vp2;
    const card_t * c1 = *cp1;
    const card_t * c2 = *cp2;
    if (c1->value != c2->value) {
        return c2->value - c1->value;
    }
    return c2->suit - c1->suit;
}

suit_t flush_suit(deck_t * hand) {
    unsigned suit_counts[4] = {0};
    for(int i=0; i<hand->n_cards; i++) {
        suit_t suit = hand->cards[i]->suit;
        suit_counts[suit]++;
        if (suit_counts[suit] >= 5) {
        return suit;
        }
    }
    return NUM_SUITS;
}

unsigned get_largest_element(unsigned * arr, size_t n) {
    unsigned largest = 0;
    for(int i=0; i<n; i++) {
        if (arr[i] > largest) {
        largest = arr[i];
        }
    }
    return largest;
}

size_t get_match_index(unsigned * match_counts, size_t n,unsigned n_of_akind){
    int match_index;
    for(match_index=0; match_index<n; match_index++) {
        if (match_counts[match_index] == n_of_akind) {
        return match_index;
        }
    }
    match_index = -1;
    assert(match_index != -1);
    return -1;
}
ssize_t  find_secondary_pair(deck_t * hand,
                             unsigned * match_counts,
                             size_t match_idx) {
    ssize_t index;
    for(index=0; index<hand->n_cards; index++) {
        if (match_counts[index] > 1
        && hand->cards[index]->value != hand->cards[match_idx]->value) {
        return index;
        }
    }
    return -1;
}

int is_n_length_straight_at(deck_t * hand, size_t index, suit_t fs, int n){
  int count =1;
  if (fs ==NUM_SUITS ){
    for (size_t i=index ; i<hand ->n_cards-1; i++){
      if ((*hand->cards[i]).value==(*hand->cards[i+1]).value) continue;
      if ((*hand->cards[i]).value-1==(*hand->cards[i+1]).value){
	count ++;
	if (count == n) return 1;}
      else return 0;
    }}
  else {
    if((*hand->cards[index]).suit != fs ) return 0;
    card_t* org=hand->cards[index];
    for (size_t i=index+1 ; i<hand ->n_cards; i++){
      if ((*hand->cards[i]).suit != fs) continue;
      if (org->value-1==(*hand->cards[i]).value){
	count ++;
	if (count == n) return 1;
	org=hand->cards[i]; }
      else return 0;}}

  return 0;
}

int is_ace_low_straight_at(deck_t * hand, size_t index, suit_t fs){
  // If suit is specified and first card is not that suit return false
  if(fs < NUM_SUITS && hand->cards[index]->suit != fs){
    return 0;
  }
  // If the first card is not an ace and 2nd not a 5 return false
  if(hand->cards[index]->value != VALUE_ACE){
    return 0;
  }
  if(hand->cards[index + 1]->value == 5){
    return is_n_length_straight_at(hand, index + 1, fs, 4);
  }
  if(hand->cards[index + 2]->value == 5){
    return is_n_length_straight_at(hand, index + 2, fs, 4);
  }
  return 0;
}

int is_straight_at(deck_t * hand, size_t index, suit_t fs) {
  if(is_ace_low_straight_at(hand, index, fs)){
    return -1; 
  }
  return is_n_length_straight_at(hand, index, fs, 5);
}

hand_eval_t build_hand_from_match(deck_t * hand,
                                  unsigned n,
                                  hand_ranking_t what,
                                  size_t idx) {

    hand_eval_t ans;
    ans.ranking = what;
    // Copy "n" cards from the hand, starting at "idx"
    // into the first "n" elements of the "cards" array
    // of "ans"
    for(int i=0; i<n; i++) {
        ans.cards[i] = hand->cards[idx+i];    // see eval.h
    }
    // Fill the rema#include "hash.h"inder of the "cards" array with the
    // highest-value cards from the hand which were not
    // in the "n of a kind".
    int i=n;
    int j=0;
    for(; i<5 && j<idx; i++, j++) {
        ans.cards[i] = hand->cards[j];
    }
    if(i < 5) {
        j=idx+n;
        for(; i<5; i++, j++) {
        ans.cards[i] = hand->cards[j];
        }
    }
    return ans;

}

void sort_cards(card_t ** array, size_t nelements) {
  qsort(array, nelements, sizeof(const card_t *), card_ptr_comp);
}

int compare_hands(deck_t * hand1, deck_t * hand2) {
    sort_cards(hand1->cards, hand1->n_cards); 
    sort_cards(hand2->cards, hand2->n_cards); 
    hand_eval_t e1 = evaluate_hand(hand1);
    hand_eval_t e2 = evaluate_hand(hand2);
    if (e1.ranking != e2.ranking) {
        return e2.ranking - e1.ranking;
    }
    for(int i=0; i<5; i++) {
        if(e1.cards[i]->value != e2.cards[i]->value) {
        return e1.cards[i]->value - e2.cards[i]->value;
        }
    }
    return 0;
}



//You will write this function in Course 4.
//For now, we leave a prototype (and provide our
//implementation in eval-c4.o) so that the
//other functions we have provided can make
//use of get_match_counts.
unsigned * get_match_counts(deck_t * hand){
  unsigned * result = malloc(hand->n_cards * sizeof(*result));
  for(int i = 0; i < hand->n_cards; i++){
    result[i] = 1;
    for(int j = 0; j < i;j++){
      if(hand->cards[j]->value == hand->cards[i]->value){
        result[j]++;
        result[i] = result[j];
      }
    }
  }
  return result;
}
// unsigned * get_match_counts(deck_t * hand){
//   unsigned * result = malloc(hand->n_cards * sizeof(*result));
//   struct hashMap* mp = (struct hashMap*)malloc(sizeof(struct hashMap));
// 	initializeHashMap(mp);
//   for(int i = 0; i < hand->n_cards; i++){
//     if(search(mp, hand->cards[i]->value) != -1){
//       int temp = search(mp, hand->cards[i]->value);
//       delete(mp, hand->cards[i]->value);
//       temp ++;
//       insert(mp, hand->cards[i]->value, temp);
//     }
//     else{
//       insert(mp, hand->cards[i]->value, 1);
//     }
//   }
//   for(int i = 0; i < hand->n_cards; i++){
//     result[i] = search(mp, hand->cards[i]->value);
//   }
//   free_map(mp);
//   return result;
// }

// We provide the below functions.  You do NOT need to modify them
// In fact, you should not modify them!


//This function copies a straight starting at index "ind" from deck "from".
//This copies "count" cards (typically 5).
//into the card array "to"
//if "fs" is NUM_SUITS, then suits are ignored.
//if "fs" is any other value, a straight flush (of that suit) is copied.
void copy_straight(card_t ** to, deck_t *from, size_t ind, suit_t fs, size_t count) {
  assert(fs == NUM_SUITS || from->cards[ind]->suit == fs);
  unsigned nextv = from->cards[ind]->value;
  size_t to_ind = 0;
  while (count > 0) {
    assert(ind < from->n_cards);
    assert(nextv >= 2);
    assert(to_ind <5);
    if (from->cards[ind]->value == nextv &&
        (fs == NUM_SUITS || from->cards[ind]->suit == fs)){
      to[to_ind] = from->cards[ind];
      to_ind++;
      count--;
      nextv--;
    }
    ind++;
  }
}


//This looks for a straight (or straight flush if "fs" is not NUM_SUITS)
// in "hand".  It calls the student's is_straight_at for each possible
// index to do the work of detecting the straight.
// If one is found, copy_straight is used to copy the cards into
// "ans".
int find_straight(deck_t * hand, suit_t fs, hand_eval_t * ans) {
  if (hand->n_cards < 5){
    return 0;
  }
  for(size_t i = 0; i <= hand->n_cards -5; i++) {
    int x = is_straight_at(hand, i, fs);
    if (x != 0){
      if (x < 0) { //ace low straight
        assert(hand->cards[i]->value == VALUE_ACE);
        if(!(fs == NUM_SUITS || hand->cards[i]->suit == fs)){
          print_hand(hand);
          printf("\n_________________________\n");
          print_card(*hand->cards[i]);
          printf("\n_________________________\n");
          printf("%d", (int)fs);
          printf("\n_________________________\n");
          assert(fs == NUM_SUITS || hand->cards[i]->suit == fs);
        }
        ans->cards[4] = hand->cards[i];
        size_t cpind = i+1;
        while(hand->cards[cpind]->value != 5 ||
              !(fs==NUM_SUITS || hand->cards[cpind]->suit ==fs)){
          cpind++;
          assert(cpind < hand->n_cards);
        }
        copy_straight(ans->cards, hand, cpind, fs,4) ;
      }
      else {
        copy_straight(ans->cards, hand, i, fs,5);
      }
      return 1;
    }
  }
  return 0;
}


//This function puts all the hand evaluation logic together.
//This function is longer than we generally like to make functions,
//and is thus not so great for readability :(
hand_eval_t evaluate_hand(deck_t * hand) {
  suit_t fs = flush_suit(hand);
  hand_eval_t ans;
  if (fs != NUM_SUITS) {
    if(find_straight(hand, fs, &ans)) {
      ans.ranking = STRAIGHT_FLUSH;
      return ans;
    }
  }
  unsigned * match_counts = get_match_counts(hand);
  unsigned n_of_a_kind = get_largest_element(match_counts, hand->n_cards);
  assert(n_of_a_kind <= 4);
  size_t match_idx = get_match_index(match_counts, hand->n_cards, n_of_a_kind);
  ssize_t other_pair_idx = find_secondary_pair(hand, match_counts, match_idx);
  free(match_counts);
  if (n_of_a_kind == 4) { //4 of a kind
    return build_hand_from_match(hand, 4, FOUR_OF_A_KIND, match_idx);
  }
  else if (n_of_a_kind == 3 && other_pair_idx >= 0) {     //full house
    ans = build_hand_from_match(hand, 3, FULL_HOUSE, match_idx);
    ans.cards[3] = hand->cards[other_pair_idx];
    ans.cards[4] = hand->cards[other_pair_idx+1];
    return ans;
  }
  else if(fs != NUM_SUITS) { //flush
    ans.ranking = FLUSH;
    size_t copy_idx = 0;
    for(size_t i = 0; i < hand->n_cards;i++) {
      if (hand->cards[i]->suit == fs){
        ans.cards[copy_idx] = hand->cards[i];
        copy_idx++;
        if (copy_idx >=5){
          break;
        }
      }
    }
    return ans;
  }
  else if(find_straight(hand,NUM_SUITS, &ans)) {     //straight
    ans.ranking = STRAIGHT;
    return ans;
  }
  else if (n_of_a_kind == 3) { //3 of a kind
    return build_hand_from_match(hand, 3, THREE_OF_A_KIND, match_idx);
  }
  else if (other_pair_idx >=0) {     //two pair
    assert(n_of_a_kind ==2);
    ans = build_hand_from_match(hand, 2, TWO_PAIR, match_idx);
    ans.cards[2] = hand->cards[other_pair_idx];
    ans.cards[3] = hand->cards[other_pair_idx + 1];
    if (match_idx > 0) {
      ans.cards[4] = hand->cards[0];
    }
    else if (other_pair_idx > 2) {  //if match_idx is 0, first pair is in 01
      //if other_pair_idx > 2, then, e.g. A A K Q Q
      ans.cards[4] = hand->cards[2];
    }
    else {       //e.g., A A K K Q
      ans.cards[4] = hand->cards[4];
    }
    return ans;
  }
  else if (n_of_a_kind == 2) {
    return build_hand_from_match(hand, 2, PAIR, match_idx);
  }
  return build_hand_from_match(hand, 0, NOTHING, 0);
}

