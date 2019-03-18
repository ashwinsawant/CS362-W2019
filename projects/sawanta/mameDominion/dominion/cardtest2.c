#include <stdio.h>
#include <stdbool.h>
#include "dominion.h"
#include "rngs.h"

#define asserttrue(bool) if(bool) printf("%s: TEST SUCCESSFULLY COMPLETED.\n", __FILE__); else printf("%s: TEST FAILED: '" #bool  "' on line %d.\n", __FILE__, __LINE__);

// This will test if the Smithy card functions proeprly

int main() {
	struct gameState G;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};

    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    bool result = true;
    
    initializeGame(2, k, 2, &G);
    G.whoseTurn = 0;

    int handCountBefore = G.handCount[0];

    // smithy should draw three cards into the hand. Smithy is discarded. This should result in a net gain of 2 cards in hand.
    cardEffect(smithy, choice1, choice2, choice3, &G, handpos, &bonus);
    int handCountAfter = G.handCount[0];

    asserttrue(handCountAfter - handCountBefore == 2);

	return 0;
}