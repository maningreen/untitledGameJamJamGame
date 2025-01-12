#include <raylib.h>
#include <raymath.h>
#include <stdlib.h>
#include <time.h>
#include "stdio.h"
#include "circle.h"
#include "missile.h"
#include "player.h"
#include "enemy.h"
#include "stars.h"

#define screenDimensions (Vector2){1000 * 16/9, 1000 / (16 / 9)}

#define backroundColour BLACK

#define playerColour WHITE
#define planetColour PURPLE

#define friction .95f

#define cameraLatency .1

#define closeKey KEY_Q

#define misSize sizeof(Missile)

int main() {
  srand(time(NULL));
  InitWindow(screenDimensions.x, screenDimensions.y, "cool game :)");
  SetTargetFPS(60);
  Camera2D camera = {Vector2Scale(screenDimensions, .5), Vector2Scale(screenDimensions, .5),0, 1};

  Player player = {(circle){playerStartingPosition, playerR, playerColour}, Vector2Zero()};

  circle planet = {{5150, 5150}, 7000, planetColour};

  enemy en = initEnemy((Vector2){-300, -300}, &player, planet);

  Missile tmp = initMissile(Vector2Zero(), Vector2Zero(), 0, 0);
  Missile* missileArr = (Missile*)malloc(0);
  int missileCount = 0;

  circle* starArr = initStars(starCount);

  while(!WindowShouldClose()) {
    float delta = GetFrameTime();

    handleMovment(&player, planet, delta);
    playerApplyVelocity(&player);
    player.velocity = Vector2Scale(player.velocity, friction);

    //camera stuff
    Vector2 plrGlobalPos = {player.body.position.y + GetScreenWidth()/2.0f, -player.body.position.x + GetScreenHeight()/2.0f};
    camera.target = Vector2Lerp(camera.target, plrGlobalPos, cameraLatency);
    camera.offset = (Vector2){GetScreenWidth() * .5, GetScreenHeight() * .5};

    refreshStars(starArr, camera);

    manageEnemy(&en, &tmp, delta);
    if(tmp.valid) {
      missileCount++;
      missileArr = (Missile*)realloc(missileArr, misSize * missileCount);
      missileArr[missileCount - 1] = tmp;
    }

    //draw
    BeginDrawing();
    BeginMode2D(camera);

    ClearBackground(backroundColour);

    int i = 0;
    while(missileCount != 0 && i < missileCount) {
      if(!missileArr[i].valid) {
        //this is where we pop from stack
        missileArr = (Missile*)realloc(missileArr, misSize * (missileCount--));
        continue;
      }
        manageMissileMovement(&missileArr[i], delta);
        drawCircle(&missileArr[i].body);
      i++;
    }
    for(int i = 0; i < starCount; i++)
      drawCircle(&starArr[i]);
    drawCircle(&player.body);
    drawCircle(&planet);
    drawCircle(&en.body);

    DrawFPS(Vector2Subtract(camera.target,  camera.offset).x, Vector2Subtract(camera.target, camera.offset).y);

    EndDrawing();

    if(IsKeyDown(closeKey))
      break;
  }
  CloseWindow();

  destructStars(starArr);

  return 0;
}
