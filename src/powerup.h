#ifndef powerup_h
#define powerup_h

#include "circle.h"
#include "include.h"
#include "missile.h"
#include "enemy.h"

#define powerUpChance /*(0 - 1]*/ .5
#define powerUpSelectionGive 100
#define powerUpTimeTimeFreeze 10

bool shouldDropPowerup(unsigned int enCount);

void applyPowerup(Missile* misArr, unsigned int misCount, circle* target);

int getClosestItemToPosition(circle* arr, int arrSize, Vector2 position);

//returns index of target if so, else -1
int shouldApplyPowerup(Camera2D camera, enemy* enArr, unsigned int enCount);

#endif
