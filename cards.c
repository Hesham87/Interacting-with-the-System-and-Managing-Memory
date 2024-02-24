#include "cards.h"

const char value_letters[13] = "234567890JQKA";
const char suit_letters[NUM_SUITS] = "shdc";

bool is_empty_card(card_t * c) {
  if (c == NULL) {
    return false;
  }
  return (c->value == 0) && (c->suit == 0);
}

void assert_card_valid(card_t c) {
    if(!is_empty_card(&c)){
        assert(c.value >= 2 && c.value <= VALUE_ACE);
        assert(c.suit >= SPADES && c.suit <= CLUBS );
    } 
}

int card_comp(card_t c1, card_t c2) {
  if (c1.value != c2.value) {
    return c2.value - c1.value;
  }
  return c2.suit - c1.suit;
}

const char * ranking_to_string(hand_ranking_t r) {
    switch(r) {
        case STRAIGHT_FLUSH:
            return "STRAIGHT_FLUSH";
        case FOUR_OF_A_KIND:
            return "FOUR_OF_A_KIND";
        case FULL_HOUSE:
            return "FULL_HOUSE";
        case FLUSH:
            return "FLUSH";
        case STRAIGHT:
            return "STRAIGHT";
        case THREE_OF_A_KIND:
            return "THREE_OF_A_KIND";
        case TWO_PAIR:
            return "TWO_PAIR";
        case PAIR:
            return "PAIR";
        case NOTHING:
            return "NOTHING";
        default:
            fprintf(stderr, "ranking_to_string: invalid hand ranking (%d)\n", r);  
            exit(EXIT_FAILURE);
    }
    return "";
}

char value_letter(card_t c) {
    assert(c.value >=2 && c.value <= VALUE_ACE);
    //printf("hello8\n");
    if (c.value >=2 && c.value <= 9) {
        //printf("hello9\n");
        return '0' + c.value;
    }
    switch(c.value) {
        case 10:
            //printf("hello9\n");
            return '0';
        case VALUE_JACK:
            //printf("hello9\n");
            return 'J';
        case VALUE_QUEEN:
            return 'Q';
        case VALUE_KING:
            return 'K';
        case VALUE_ACE:
            //printf("hello9\n");
            return 'A';
        default:
            fprintf(stderr, "value_letter: invalid value (%d)\n", c.value);
            exit(EXIT_FAILURE);
    }
}

unsigned value_from_letter(char value_let) {
    if(!strchr(value_letters, value_let)){
        printf("%c\n", value_let);
        assert(strchr(value_letters, value_let));
    }
    if (value_let > '0' && value_let <= '9') {
        return value_let - '0';
    } else {
        switch(value_let) {
        case '0':
        return 10;
        case 'A':
        return VALUE_ACE;
        case 'K':
        return VALUE_KING;
        case 'Q':
        return VALUE_QUEEN;
        case 'J':
        return VALUE_JACK;
        default:
            fprintf(stderr, "value_from_letter: invalid card value (%c)", value_let);
            exit(EXIT_FAILURE);
        }
  }
}

suit_t suit_from_letter(char suit_let) {
    assert(strchr(suit_letters, suit_let));
    switch(suit_let) {
        case 's':
            return SPADES;
        case 'h':
            return HEARTS;
        case 'd':
            return DIAMONDS;
        case 'c':
            return CLUBS;
        default:
            fprintf(stderr, "suit_from_letter: invalid card suit (%c)", suit_let);
            exit(EXIT_FAILURE);
    }
}


char suit_letter(card_t c) {
    assert_card_valid(c);
    //printf("hello6\n");
    if (c.suit < 0 || c.suit >= NUM_SUITS) {
        fprintf(stderr, "suit_letter: invalid suit (%d)\n", c.suit);
        exit(EXIT_FAILURE);
    }
    //printf("hello7\n");
    return suit_letters[c.suit];   
}

void print_card(card_t c) {
    if(!is_empty_card(&c)){
        assert_card_valid(c);
        //printf("hello4\n");
        printf("%c%c", value_letter(c), suit_letter(c));
        //printf("hello5\n");
    }
    else{
        printf("?%d", c.suit);
    }
}

void fprint_card(FILE * f, card_t c) {
    assert_card_valid(c);
    fprintf(f, "%c%c", value_letter(c), suit_letter(c));
}

card_t card_from_letters(char value_let, char suit_let) {
    card_t temp;
    temp.value = value_from_letter(value_let);
    temp.suit = suit_from_letter(suit_let);
    assert_card_valid(temp);
    return temp;
}

card_t card_from_num(unsigned c) {
    // printf("%d\n", c);
    // printf("\n");
    assert(c >= 0 && c < 52);
    card_t temp;
    temp.value = c % 13 + 2;
    temp.suit = c / 13;
    return temp;
}
