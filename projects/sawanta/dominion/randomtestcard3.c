#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>
#include "rngs.h"

#define asserttrue(bool) if(bool) printf("%s: TEST SUCCESSFULLY COMPLETED.\n", __FILE__); else printf("%s: TEST FAILED: '" #bool  "' on line %d.\n", __FILE__, __LINE__);


// This is the oracle function for smithyEffect
void checkCardEffect(struct gameState *post, int handPos) {
    struct gameState pre;
    memcpy(&pre, post, sizeof(struct gameState));

    time_t t = time(0);
    PlantSeeds(t);

    // this is what we think the effect of the function should be
    for (int i = 0; i < 3; i++) {
        drawCard(pre.whoseTurn, &pre);
    }
        
    //discard card from hand
    discardCard(handPos, pre.whoseTurn, &pre, 0);

    PlantSeeds(t);
    // call the function under test (indirectly, via cardEffect)
    int b = 0;
    cardEffect(smithy, 0, 0, 0, post, handPos, &b);

    // do the comparison
    int result = memcmp(&pre, post, sizeof(struct gameState));
    if(result == 0) {
        printf(".");
    } else {
        printf("x");
    }
}

int main() {
    struct gameState G;
    int handPos = 0;

    for(int n = 0; n < 2000; n++) {
        // initialize the gameState struct to random values
        for(int i = 0; i < sizeof(struct gameState); i++) {
            ((char*)&G)[i] = floor(Random() * 256);
        }
        // sanitize the struct for adventurerEffect function
        G.numPlayers = floor(Random() * MAX_PLAYERS);
        if(G.numPlayers == 0) G.numPlayers = 2; // at least two players have to play the game
        G.whoseTurn = floor(Random() * G.numPlayers);

        for(int j = 0; j < G.numPlayers; j++) {
            G.deckCount[j] = floor(Random() * MAX_DECK);
            if(G.deckCount[j] < 3) G.deckCount[j] = 3;
            G.discardCount[j] = floor(Random() * MAX_DECK);
            for(int k = 0; k < MAX_DECK; k++) {
                G.deck[j][k] = floor(Random() * 26);
                G.discard[j][k] = floor(Random() * 26);
            }
            G.handCount[j] = floor(Random() * MAX_HAND);
            if(G.handCount[j] == 0) G.handCount[j] = 1;
            handPos = floor(Random() * G.handCount[j]);
            for(int k = 0; k < MAX_HAND; k++) {
                G.hand[j][k] = floor(Random() * 26);
            }
            G.playedCardCount = floor(Random() * MAX_DECK);
        }
        checkCardEffect(&G, handPos);    // call the oracle
    }

    printf("\n");

    return 0;
}