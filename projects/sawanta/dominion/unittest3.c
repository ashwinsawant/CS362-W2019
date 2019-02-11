#include <stdio.h>
#include <stdbool.h>
#include "dominion.h"
#include "rngs.h"

#define asserttrue(bool) if(bool) printf("%s: TEST SUCCESSFULLY COMPLETED.\n", __FILE__); else printf("%s: TEST FAILED: '" #bool  "' on line %d.\n", __FILE__, __LINE__);

// This will test if the fullDeckCount function counts cards properly

int main() {
	struct gameState G;
	int testdeck[8] = {adventurer, gardens, embargo, village, adventurer, mine, cutpurse, sea_hag};
    int testhand[5] = {adventurer, silver, village, minion, estate};
    int testdiscard[4] = {tribute, smithy, adventurer, duchy};

    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};
    initializeGame(2, k, 2, &G);

    // Replace player 1's deck, hand, discard pile with the ones declared above
    G.deckCount[0] = 8;
    for(int i = 0; i < 8; i++) {
        G.deck[0][i] = testdeck[i];
    }

    G.handCount[0] = 5;
    for(int i = 0; i < 5; i++) {
        G.hand[0][i] = testhand[i];
    }

    G.discardCount[0] = 4;
    for(int i = 0; i < 4; i++) {
        G.discard[0][i] = testdiscard[i];
    }

    int result = fullDeckCount(0, adventurer, &G);  // this should be 4

    asserttrue(result == 4);

	return 0;
}