#include <stdint.h>
#include <stdlib.h>
#include <Player.h>
#include "../inc/ST7735.h"

#define X_HBX_OFFSET 1
#define Y_HBX_OFFSET 1
#define X_HBX_BOUND 3
#define Y_HBX_BOUND 3

#define SMLST_MOV 262144

#define D_DIV  10
#define D_MULT 7

#define MAX_SCREEN_X (128<<20)
#define MAX_SCREEN_Y (160<<20)

void initPlayer(player_t *plyr) {
    plyr->x = (plyr->x<<20);
    plyr->y = (plyr->y<<20);

    plyr->lastX = plyr->x;
    plyr->lastY = plyr->y;
}

void initPlayers(player_t *plyrs, uint8_t plyrNum) {
    for(uint8_t i =0; i < plyrNum; i++) {
        initPlayer(&plyrs[i]);
    }
}

void drawPlayer(player_t *plyr) {
    ST7735_FillRect((plyr->lastX>>20), (plyr->lastY>>20)-18, 9, 19, 0xF0F0);
    ST7735_DrawBitmap((plyr->x>>20), (plyr->y>>20), plyr->sprite, 9,19);
}

void drawPlayers(player_t *plyrs, uint8_t plyrNum) {
    for (uint8_t i = 0; i < plyrNum; i++) {
        drawPlayer(&plyrs[i]);
    }
}

void movePlayerTowardPlayer(player_t *plyr, player_t *plyrTrgt) {
    int32_t xDifference = plyrTrgt->x - plyr->x;
    int32_t yDifference = plyrTrgt->y - plyr->y;
    int32_t xDistanceToMove;
    int32_t yDistanceToMove;
    int32_t dDiv = 1;
    int32_t dMult = 1;

    plyr->lastX = plyr->x;
    plyr->lastY = plyr->y;

    if((xDifference != 0) && (yDifference != 0)) {
        dDiv = D_DIV;
        dMult = D_MULT;
    }

    xDistanceToMove = yDistanceToMove = ((SMLST_MOV*(plyr->speed))*dMult)/dDiv;

    if (xDifference < 0) xDistanceToMove *= -1;
    if (yDifference < 0) yDistanceToMove *= -1;


    if (abs(xDistanceToMove) > abs(xDifference)) xDistanceToMove = xDifference;
    if (abs(yDistanceToMove) > abs(yDifference)) yDistanceToMove = yDifference;

    plyr->x += xDistanceToMove;
    plyr->y += yDistanceToMove;


    if(plyr->x > MAX_SCREEN_X)    plyr->x = MAX_SCREEN_X;
    if(plyr->x < 0)               plyr->x = 0;
    if(plyr->y > MAX_SCREEN_Y)    plyr->y = MAX_SCREEN_Y;
    if(plyr->y < 0)               plyr->y = 0;
}

void movePlayersTowardPlayer(player_t *plyrs, uint8_t plyrNum, player_t *plyrTrgt){
    for (uint8_t i = 0; i < plyrNum; i++) {
        movePlayerTowardPlayer(&plyrs[i], plyrTrgt);
    }
}

void movePlayerTowardPixel(player_t *plyr, pixel_t *pxl) {
    int32_t xDifference = (pxl->x<<20) - plyr->x;
    int32_t yDifference = (pxl->y<<20) - plyr->y;
    int32_t xDistanceToMove;
    int32_t yDistanceToMove;

    int32_t dDiv = 1;
    int32_t dMult = 1;

    plyr->lastX = plyr->x;
    plyr->lastY = plyr->y;

    if((xDifference != 0) && (yDifference != 0)) {
        dDiv = D_DIV;
        dMult = D_MULT;
    }

    xDistanceToMove = yDistanceToMove = ((SMLST_MOV*(plyr->speed))*dMult)/dDiv;

    if (xDifference < 0) xDistanceToMove *= -1;
    if (yDifference < 0) yDistanceToMove *= -1;


    if (abs(xDistanceToMove) > abs(xDifference)) xDistanceToMove = xDifference;
    if (abs(yDistanceToMove) > abs(yDifference)) yDistanceToMove = yDifference;

    plyr->x += xDistanceToMove;
    plyr->y += yDistanceToMove;


    if(plyr->x > MAX_SCREEN_X)    plyr->x = MAX_SCREEN_X;
    if(plyr->x < 0)        plyr->x = 0;
    if(plyr->y > MAX_SCREEN_Y)    plyr->y = MAX_SCREEN_Y;
    if(plyr->y < 0)        plyr->y = 0;
}

uint8_t pixelInPlayerHitBox(player_t *plyr, pixel_t *pxl) {
    uint8_t hitBoxX = (plyr->x>>20) + X_HBX_OFFSET;
    uint8_t hitBoxY = (plyr->y>>20) + Y_HBX_OFFSET;

    if ((pxl->x >= hitBoxX) && (pxl->x <= hitBoxX + X_HBX_BOUND) && (pxl->y >= hitBoxY) && (pxl->y <= hitBoxY + Y_HBX_BOUND)) {
        return 1;
    }
    return 0;
}

uint8_t pixelsInPlayerHitBox(player_t *plyr, pixel_t *pxls, uint8_t pxlNum) {
    for (uint8_t i = 0; i < pxlNum; i++) {

        if (pixelInPlayerHitBox(plyr, &pxls[i])) {
            return 1;
        }

    }

    return 0;
}

uint8_t pixelsInPlayesrHitBoxes(player_t *plyrs, uint8_t plyrNum, pixel_t *pxls, uint8_t pxlNum) {
    for (uint8_t i = 0; i < plyrNum; i++) {
        if(pixelsInPlayerHitBox(&plyrs[i], pxls, pxlNum)) {
            return 1;
        }
    }
    return 0;
}

void updatePlayerPixels(player_t *plyr, pixel_t *pxls) {
    uint8_t x = (plyr->x>>20);
    uint8_t y = (plyr->y>>20);

    pixel_t playerPixels[] = {
                                                       {x+2, y  }, {x+3, y  },
                                           {x+1, y+1}, {x+2, y+1}, {x+3, y+1}, {x+4, y+1},
                               {x  , y+2}, {x+1, y+2}, {x+2, y+2}, {x+3, y+2}, {x+4, y+2}, {x+5, y+2},
                               {x  , y+3}, {x+1, y+3}, {x+2, y+3}, {x+3, y+3}, {x+4, y+3}, {x+5, y+3},
                                           {x+1, y+4}, {x+2, y+4}, {x+3, y+4}, {x+4, y+4},
                                                       {x+2, y+5}, {x+3, y+5}
                              };

    for (uint8_t i = 0; i < 24; i++) {
        pxls[i] = playerPixels[i];
    }

}






