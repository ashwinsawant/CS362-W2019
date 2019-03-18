#include <stdio.h>
#include <stdbool.h>
#include "dominion.h"
#include "rngs.h"

#define asserttrue(bool) if(bool) printf("%s: TEST SUCCESSFULLY COMPLETED.\n", __FILE__); else printf("%s: TEST FAILED: '" #bool  "' on line %d.\n", __FILE__, __LINE__);

// This will test if the Adventurer card functions proeprly

int main() {
	struct gameState G;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};

    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    bool result = true;
    
    initializeGame(2, k, 2, &G);
    G.whoseTurn = 0;

    // adventurer should draw two treasure cards to the top of the hand
    cardEffect(adventurer, choice1, choice2, choice3, &G, handpos, &bonus);

    int handCount = G.handCount[0];
    for(int i = 1; i <= 2; i++) {
        int card = G.hand[0][handCount-i];
        if(card != copper && card != silver && card != gold)
            result = false;
    }

    asserttrue(result == true);

	return 0;
}