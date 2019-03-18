#include <stdio.h>
#include <stdbool.h>
#include "dominion.h"
#include "rngs.h"

#define asserttrue(bool) if(bool) printf("%s: TEST SUCCESSFULLY COMPLETED.\n", __FILE__); else printf("%s: TEST FAILED: '" #bool  "' on line %d.\n", __FILE__, __LINE__);

int main() {
	struct gameState G;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};

    // This will test if the initializeGame function properly initializes the player deck, with
    // 7 copper and 3 estates

    initializeGame(2, k, 2, &G);

    bool pass = true;

    for(int i = 0; i < 2; i++) {
    	int copper_count = 0, estate_count = 0;
    	
    	for(int j = 0; j < 10; j++) {
    		if(G.deck[i][j] == copper)
    			copper_count++;
    		if(G.deck[i][j] == estate)
    			estate_count++;
    	}

    	if(copper_count != 7 || estate_count != 3)
    		pass = false;

    }

    asserttrue(pass);

	return 0;
}