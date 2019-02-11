#include <stdio.h>
#include <stdbool.h>
#include "dominion.h"
#include "rngs.h"

#define asserttrue(bool) if(bool) printf("%s: TEST SUCCESSFULLY COMPLETED.\n", __FILE__); else printf("%s: TEST FAILED: '" #bool  "' on line %d.\n", __FILE__, __LINE__);

// This will test if the Sea Hag card functions proeprly

int main() {
	struct gameState G;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};

    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    bool result = true;
    
    initializeGame(2, k, 2, &G);
    G.whoseTurn = 0;

    int deckCountBefore = G.deckCount[0];
    int actionsBefore = G.numActions;

    // Sea Hag will discard the top card of the deck and replace it with a Curse. The deck size remains unchanged.
    cardEffect(sea_hag, choice1, choice2, choice3, &G, handpos, &bonus);
    int deckCountAfter = G.deckCount[0];
    int actionsAfter = G.numActions;

    asserttrue(G.deck[0][deckCountAfter-1] == curse);
    asserttrue(deckCountAfter - deckCountBefore == 0);

	return 0;
}