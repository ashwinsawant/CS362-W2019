#include <stdio.h>
#include <stdbool.h>
#include "dominion.h"
#include "rngs.h"

#define asserttrue(bool) if(bool) printf("%s: TEST SUCCESSFULLY COMPLETED.\n", __FILE__); else printf("%s: TEST FAILED: '" #bool  "' on line %d.\n", __FILE__, __LINE__);

int main() {
	struct gameState G;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};

    // This will test if the updateCoins function updates the number of coins properly

    initializeGame(2, k, 2, &G);

    // Replace player 1's hand with a test set of 5 cards, which has a copper, a silver and a gold card
    // and should lead to 6 coins
    int testhand[5] = {copper, gardens, silver, gold, smithy};

    for(int i = 0; i < 5; i++) {
        G.hand[0][i] = testhand[i];
    }

    updateCoins(0, &G, 2);

    // We will pass in a bonus of 2, leading to a total of 8 coins
    asserttrue(G.coins == 8);

	return 0;
}