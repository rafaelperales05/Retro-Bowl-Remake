#include <stdint.h>
#include <Player.h>

typedef struct {
    uint32_t upperXBound;
    uint32_t lowerXBound;
    uint32_t upperYBound;
    uint32_t lowerYBound;

} barrier_t;

void adjustPlayerPosByBarrier(player_t *plyr, barrier_t *bar);

void adjustPlayersPosByBarrier(player_t *plyrs, uint8_t plyrNum, barrier_t *bar);

void adjustPlayersPosByBarriers(player_t *plyrs, uint8_t plyrNum, barrier_t *bar, uint8_t barNum);
