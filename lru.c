#include <stdio.h>
#include "pages.h"

int pages[MAX_PAGES] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};

static int findPage(int buffer[], int page, int n) {
    for (int i = 0; i < n; i++)
        if (buffer[i] == page)
            return i;
    return -1;
}

void simulateLRU() {
    int buffer[MAX_FRAMES];
    int time[MAX_FRAMES];
    int hits = 0, misses = 0, counter = 0;

    for (int i = 0; i < MAX_FRAMES; i++) {
        buffer[i] = -1;
        time[i] = 0;
    }

    printf("\n===== LRU Page Replacement =====\n\n");

    for (int i = 0; i < MAX_PAGES; i++) {
        int page = pages[i];
        int pos = findPage(buffer, page, MAX_FRAMES);

        if (pos != -1) {
            hits++;
            time[pos] = ++counter;
        } else {
            misses++;
            int empty = -1;
            for (int j = 0; j < MAX_FRAMES; j++)
                if (buffer[j] == -1)
                    empty = j;

            if (empty != -1) {
                buffer[empty] = page;
                time[empty] = ++counter;
            } else {
                int lru = 0;
                for (int j = 1; j < MAX_FRAMES; j++)
                    if (time[j] < time[lru])
                        lru = j;
                buffer[lru] = page;
                time[lru] = ++counter;
            }
        }

        printf("Step %2d (Page %d): ", i + 1, page);
        for (int j = 0; j < MAX_FRAMES; j++)
            buffer[j] == -1 ? printf("- ") : printf("%d ", buffer[j]);
        printf(pos != -1 ? "-> HIT\n" : "-> MISS\n");
    }

    printf("\nTotal Hits: %d\nTotal Misses: %d\nHit Ratio: %.2f\n",
           hits, misses, (float)hits / MAX_PAGES);
}
