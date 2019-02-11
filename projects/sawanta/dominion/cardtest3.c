#include <stdio.h>
#include <stdbool.h>
#include "dominion.h"
#include "rngs.h"

#define asserttrue(bool) if(bool) printf("%s: TEST SUCCESSFULLY COMPLETED.\n", __FILE__); else printf("%s: TEST FAILED: '" #bool  "' on line %d.\n", __FILE__, __LINE__);

// This will test if the Village card functions proeprly

int main() {
	struct gameState G;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};

    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    bool result = true;
    
    initializeGame(2, k, 2, &G);
    G.whoseTurn = 0;

    int handCountBefore = G.handCount[0];
    int actionsBefore = G.numActions;

    // Village should draw one card into the hand. Village is discarded. This should result in a net gain of 0 cards in hand.
    // Also, it results in +2 actions
    cardEffect(village, choice1, choice2, choice3, &G, handpos, &bonus);
    int handCountAfter = G.handCount[0];
    int actionsAfter = G.numActions;

    asserttrue(handCountAfter - handCountBefore == 0);
    asserttrue(actionsAfter - actionsBefore == 2);

	return 0;
}