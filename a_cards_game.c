#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define SUITSIZE 13
#define DECKSIZE 52
#define NUMSUITS 4

struct card {
    char *face;
    char *suit;
};
typedef struct card CARD;

void fillDeck (CARD *, char *[], char *[]);
void shuffle (CARD *);
void deal (CARD *);

int main() {
    char *suit[NUMSUITS] = {"Hearts", "Diamonds", "Clubs", "Spades"};
    char *face[SUITSIZE] = {"Ace", "Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King"};
    CARD deck [DECKSIZE];
    srand(time(NULL));
    fillDeck(deck, face, suit);
    shuffle(deck);
    deal(deck);
}

void fillDeck(CARD wDeck[], char *wFace[], char *wSuit[]) {
    for (int i = 0; i <= DECKSIZE; i++) {
        wDeck[i].face = wFace[i % SUITSIZE];
        wDeck[i].suit = wSuit[i / SUITSIZE];
    }
}

void shuffle(CARD * wDeck) {
    int i, j;
    CARD temp;
    for (i = 0; i < DECKSIZE; i++) {
        j = rand() % DECKSIZE;
        temp = wDeck[i];
        wDeck[i] = wDeck[j];
        wDeck[j] = temp;
    }
}

void deal (CARD *wDeck) {
    printf("\n*************************************************************\n");
    printf("        Player1       Player2       Player3       Player4        ");
    printf("\n*************************************************************\n");
    printf("%5s, %-4s     %5s, %-4s     %5s, %-4s     %5s, %-4s",
        "Face", "Suit", "Face", "Suit", "Face", "Suit", "Face", "Suit");
    printf("\n-------------------------------------------------------------\n");
    for (int i = 0; i < DECKSIZE; i++) {
        printf("%5s, %-8s%c", wDeck[i].face, wDeck[i].suit,
            (i + 1) % 4 == 0 ? '\n' : '\t');
    }
}
