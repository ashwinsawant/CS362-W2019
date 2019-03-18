#include <stdio.h>
#include <stdbool.h>
#include "dominion.h"
#include "rngs.h"

#define asserttrue(bool) if(bool) printf("%s: TEST SUCCESSFULLY COMPLETED.\n", __FILE__); else printf("%s: TEST FAILED: '" #bool  "' on line %d.\n", __FILE__, __LINE__);

// This will test the compare(a, b) function in dominion.c
// This function is supposed to return 1 if a>b, -1 if a<b, and 0 if they are equal

int main() {
    int a = 1, b = 2, c = 2;

    asserttrue(compare(&b, &a) == 1);
    asserttrue(compare(&a, &b) == -1);
    asserttrue(compare(&b, &b) == 0);

	return 0;
}