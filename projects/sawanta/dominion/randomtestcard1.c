#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "rngs.h"

#define asserttrue(bool) if(bool) printf("%s: TEST SUCCESSFULLY COMPLETED.\n", __FILE__); else printf("%s: TEST FAILED: '" #bool  "' on line %d.\n", __FILE__, __LINE__);

// This is the oracle function for sea_hagEffect
void checkCardEffect(struct gameState *post) {
    struct gameState pre;
    memcpy(&pre, post, sizeof(struct gameState));

    // this is what we think the effect of the function should be
    for (int i = 0; i < pre.numPlayers; i++) {
        if (i != pre.whoseTurn) {
            pre.discard[i][pre.discardCount[i]] = pre.deck[i][pre.deckCount[i]--];
            pre.deckCount[i]--;
            pre.discardCount[i]++;
            pre.deck[i][pre.deckCount[i]--] = curse;
        }
    }

    // call the function under test (indirectly, via cardEffect)
    int b = 0;
    cardEffect(sea_hag, 0, 0, 0, post, 0, &b);

    // do the comparison
    int result = memcmp(&pre, post, sizeof(struct gameState));
    if(result == 0)
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
        // sanitize the struct for sea_hagEffect function
        G.numPlayers = floor(Random() * MAX_PLAYERS);
        G.whoseTurn = floor(Random() * G.numPlayers);
        for(int j = 0; j < G.numPlayers; j++) {
            G.deckCount[j] = floor(Random() * MAX_DECK);
            G.discardCount[j] = floor(Random() * MAX_DECK);
        }
        checkCardEffect(&G);    // call the oracle
    }

    printf("\n");

    return 0;
}