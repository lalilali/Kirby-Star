#include "gametool.h"
#include "load&free.h"
#ifndef Kirby_
#define Kirby_

enum Statetype{origin,sword,fire};

struct Kirby
{
    float x=0;
    float y=240;
    char hp[2]={'5','\0'};
    float jumpheight=100;
    Statetype state=origin;
    bool isWalkingRight=false;
    bool isWalkingLeft=false;
    bool isJumpingUp=false;
    bool isJumpingDown=false;
    bool isAttacking=false;
    bool isRight=true;
    bool gravity=true;
    bool isGround=true;
    bool godown=false;
};
struct Monster
{
    float x=0;
    float y=0;
    int hp=0;
    Statetype state=origin;
};
#endif // Kirby_
void Walk(Kirby *k , float x);
void JumpUp(Kirby *k );
bool JumpDown(Kirby *k );
bool Attack(Kirby *k,Monster *m,SDL_Surface *screen,SDL_Surface *images[]);
void kirby_hurt(Kirby *k,Monster *m,int *count);
void monster_in_stage(FILE *fp,Monster *fire_m,Monster *fire_m2,Monster *sword_m,Monster *sword_m2,int stage);
void monster_hurt(Kirby *k,Monster *m);
void monster_moves_by_itself(Monster *m,float *monster_distance);
