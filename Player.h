#include <stdint.h>

typedef struct {
    int32_t x;
    int32_t y;

    const uint16_t *sprite;
    uint16_t speed;

    int32_t lastX;
    int32_t lastY;
} player_t;

typedef struct {
    int32_t x;
    int32_t y;

} pixel_t;


void initPlayer(player_t *plyr);
void initPlayers(player_t *plyrs, uint8_t plyrNum);

void drawPlayer(player_t *plyr);
void drawPlayers(player_t *plyrs, uint8_t plyrNum);

void movePlayerTowardPlayer(player_t *plyr, player_t *plyrTrgt);
void movePlayersTowardPlayer(player_t *plyrs, uint8_t plyrNum, player_t *plyrTrgt);

void movePlayerTowardPixel(player_t *plyr, pixel_t *pxl);
uint8_t pixelInPlayerHitBox(player_t *plyr, pixel_t *pxl);
uint8_t pixelsInPlayerHitBox(player_t *plyr, pixel_t *pxls, uint8_t pxlNum);
uint8_t pixelsInPlayesrHitBoxes(player_t *plyrs, uint8_t plyrNum, pixel_t *pxls, uint8_t pxlNum);

void updatePlayerPixels(player_t *plyr, pixel_t *pxls);

