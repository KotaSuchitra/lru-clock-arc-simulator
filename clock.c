#include <stdio.h>
#include "pages.h"

void simulateClock() {
    int buffer[MAX_FRAMES];
    int refBit[MAX_FRAMES];
    int pointer = 0, hits = 0, misses = 0;

    for (int i = 0; i < MAX_FRAMES; i++) {
        buffer[i] = -1;
        refBit[i] = 0;
    }

    printf("\n===== CLOCK Page Replacement =====\n\n");

    for (int i = 0; i < MAX_PAGES; i++) {
        int page = pages[i];
        int found = -1;

        for (int j = 0; j < MAX_FRAMES; j++) {
            if (buffer[j] == page) {
                found = j;
                break;
            }
        }

        if (found != -1) {
            hits++;
            refBit[found] = 1;
        } else {
            misses++;
            while (refBit[pointer] == 1) {
                refBit[pointer] = 0;
                pointer = (pointer + 1) % MAX_FRAMES;
            }
            buffer[pointer] = page;
            refBit[pointer] = 1;
            pointer = (pointer + 1) % MAX_FRAMES;
        }

        printf("Step %2d (Page %d): ", i + 1, page);
        for (int j = 0; j < MAX_FRAMES; j++)
            buffer[j] == -1 ? printf("- ") : printf("%d ", buffer[j]);
        printf(found != -1 ? "-> HIT\n" : "-> MISS\n");
    }

    printf("\nTotal Hits: %d\nTotal Misses: %d\nHit Ratio: %.2f\n",
           hits, misses, (float)hits / MAX_PAGES);
}
