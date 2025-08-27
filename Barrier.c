#include <stdint.h>
#include <Barrier.h>

void adjustPlayerPosByBarrier(player_t *plyr, barrier_t *bar) {
    uint32_t x = (plyr->x>>20);
    uint32_t y = (plyr->y>>20);
    uint32_t xLast = (plyr->lastX>>20);
    uint32_t yLast = (plyr->lastY>>20);

    uint32_t upperBX = bar->upperXBound;
    uint32_t upperBY = bar->upperYBound;
    uint32_t lowerBX = bar->lowerXBound;
    uint32_t lowerBY = bar->lowerYBound;

    if( (xLast < lowerBX) && (x >= lowerBX) && (y >= lowerBY) && (y <= upperBY) ) plyr->x = ((lowerBX -1)<<20);

    if( (xLast > upperBX) && (x <= upperBX) && (y >= lowerBY) && (y <= upperBY) ) plyr->x = ((upperBX +1)<<20);

    if( (yLast < lowerBY) && (y >= lowerBY) && (x >= lowerBX) && (x <= lowerBX) ) plyr->y = ((lowerBY -1)<<20);

    if( (yLast > upperBY) && (y <= upperBY) && (x >= lowerBX) && (x <= upperBX) ) plyr->y = ((upperBY +1)<<20);
}


void adjustPlayersPosByBarrier(player_t *plyrs, uint8_t plyrNum, barrier_t *bar) {
    for (uint8_t i = 0; i < plyrNum; i++) {
        adjustPlayerPosByBarrier(&plyrs[i], bar);
    }
}

void adjustPlayersPosByBarriers(player_t *plyrs, uint8_t plyrNum, barrier_t *bar, uint8_t barNum) {
    for (uint8_t i = 0; i < barNum; i++) {
        adjustPlayersPosByBarrier(plyrs, plyrNum, &bar[i]);
    }
}

