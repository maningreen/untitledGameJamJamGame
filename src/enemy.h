#ifndef enemy_h
#define enemy_h

#include <raylib.h>
#include <raymath.h>
#include "circle.h"
#include "player.h"
#include "missile.h"

#define enemyMaxHp 15
#define enemydefdmng 3
#define enemyPrefDist 300
#define enemySpeed 100
#define enemyDefShotSpeed 1.0f
#define enemyDefCircle (circle){(Vector2){0, 0}, 10, RED};
#define enemyViewDistance 600
#define enemyPrefDistanceSmoothing .1
#define enemyMinimumDistance 400
#define enemyPreferedAvoidDistance 550
#define enemyAvoidZonePrefDistance 100

#define enemyFric .8

struct enemy {
  Vector2 velocity;
  circle body;
  circle avoidZone;
  float health;
  float maxHealth;
  float damage;
  float speed;
  Player* player;
  float prefDistMaxOffset;
  float elapsedShotTime;
  float shotSpeed;
  float viewDistance;
  float targetDistance;
  bool seen;
};
typedef struct enemy enemy;

enemy initEnemy(Vector2 position, Player* player, circle planet);

bool tooCloseToPlayer(enemy en);

bool enemyCanSeePlayer(enemy en);

void navigate(enemy* en, float delta);

bool enemyTargetIsInPlanet(enemy* en);

bool shouldSpawnMissile(enemy* en);

void manageEnemy(enemy* en, Missile* out, float delta);

#endif
