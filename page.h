// pages.h
#ifndef PAGES_H
#define PAGES_H

#define MAX_PAGES 12
#define MAX_FRAMES 3

extern int pages[MAX_PAGES];

void simulateLRU();
void simulateClock();
void simulateARC();

#endif
