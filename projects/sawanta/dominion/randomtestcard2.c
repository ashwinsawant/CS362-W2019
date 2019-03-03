#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include "rngs.h"

#define asserttrue(bool) if(bool) printf("%s: TEST SUCCESSFULLY COMPLETED.\n", __FILE__); else printf("%s: TEST FAILED: '" #bool  "' on line %d.\n", __FILE__, __LINE__);

// This is the oracle function for adventurerEffect
void checkCardEffect(struct gameState *post) {
    // call the function under test (indirectly, via cardEffect)
    int b = 0;
    cardEffect(adventurer, 0, 0, 0, post, 0, &b);

    bool result = true;
    int currentPlayer = post->whoseTurn;
    int handCount = post->handCount[currentPlayer];
    for(int i = 1; i <= 2; i++) {
        int card = post->hand[currentPlayer][handCount-i];
        if(card != copper && card != silver && card != gold)
            result = false;
    }

    if(result == true)
        printf(".");
    else
        printf("x");
}

int main() {
    struct gameState G;

    for(int n = 0; n < 2000; n++) {
        // initialize the gameState struct to random values
        for(int i = 0; i < sizeof(struct gameState); i++) {
            ((char*)&G)[i] = floor(Random() * 256);
        }
        // sanitize the struct for adventurerEffect function
        G.numPlayers = floor(Random() * MAX_PLAYERS);
        if(G.numPlayers == 0) G.numPlayers = 1;
        G.whoseTurn = floor(Random() * G.numPlayers);
        for(int j = 0; j < G.numPlayers; j++) {
            G.deckCount[j] = floor(Random() * MAX_DECK);
            G.discardCount[j] = floor(Random() * MAX_DECK);
            for(int k = 0; k < MAX_DECK; k++) {
                G.deck[j][k] = floor(Random() * 26);
                G.discard[j][k] = floor(Random() * 26);
            }
            G.handCount[j] = floor(Random() * MAX_HAND);
            for(int k = 0; k < MAX_HAND; k++) {
                G.hand[j][k] = floor(Random() * 26);
            }
        }
        while(G.supplyCount[gold] + G.supplyCount[silver] + G.supplyCount[copper] < 2) {
            G.supplyCount[gold] = floor(Random() * 30);
            G.supplyCount[silver] = floor(Random() * 40);
            G.supplyCount[copper] = floor(Random() * 60);
        }
        checkCardEffect(&G);    // call the oracle
    }

    printf("\n");

    return 0;
}