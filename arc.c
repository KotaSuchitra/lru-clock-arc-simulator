#include <stdio.h>
#include "pages.h"

void simulateARC() {
    int T1[MAX_FRAMES] = {-1}, T2[MAX_FRAMES] = {-1};
    int hits = 0, misses = 0;
    int p = 1;  // balance factor between T1 (recency) and T2 (frequency)

    printf("\n===== ARC (Simplified) Page Replacement =====\n\n");

    for (int i = 0; i < MAX_PAGES; i++) {
        int page = pages[i];
        int foundT1 = -1, foundT2 = -1;

        for (int j = 0; j < MAX_FRAMES; j++) {
            if (T1[j] == page) foundT1 = j;
            if (T2[j] == page) foundT2 = j;
        }

        if (foundT1 != -1 || foundT2 != -1) {
            hits++;
            if (foundT1 != -1) {
                // move from T1 to T2
                T1[foundT1] = -1;
                for (int k = 0; k < MAX_FRAMES; k++)
                    if (T2[k] == -1) { T2[k] = page; break; }
            }
        } else {
            misses++;
            int inserted = 0;

            // Insert into T1 if space
            for (int j = 0; j < MAX_FRAMES; j++) {
                if (T1[j] == -1) {
                    T1[j] = page;
                    inserted = 1;
                    break;
                }
            }

            // If T1 full, evict LRU to T2 or replace in T2
            if (!inserted) {
                for (int j = 0; j < MAX_FRAMES; j++) {
                    if (T2[j] == -1) {
                        T2[j] = page;
                        inserted = 1;
                        break;
                    }
                }
            }

            if (!inserted) {
                T1[0] = page;  // simple overwrite for demo
            }
        }

        printf("Step %2d (Page %d): T1[", i + 1, page);
        for (int j = 0; j < MAX_FRAMES; j++) T1[j] == -1 ? printf("- ") : printf("%d ", T1[j]);
        printf("]  T2[");
        for (int j = 0; j < MAX_FRAMES; j++) T2[j] == -1 ? printf("- ") : printf("%d ", T2[j]);
        printf("] -> %s\n", (foundT1 != -1 || foundT2 != -1) ? "HIT" : "MISS");
    }

    printf("\nTotal Hits: %d\nTotal Misses: %d\nHit Ratio: %.2f\n",
           hits, misses, (float)hits / MAX_PAGES);
}
