#ifndef LOADFREE_H_INCLUDED
#define LOADFREE_H_INCLUDED
#include "gametool.h"
void setTitle(float t);
enum image_name{image_sky,image_floor,image_sharp,image_air,image_door,
                image_stage1,image_stage2,image_stage3,
                image_fly,image_flyleft,image_eat,image_eatleft,
                image_start,image_gameover,image_newgame,image_loadgame,image_win,image_rules,
                image_save_yes,image_save_no,image_no_savings,
                image_firemonster,image_fire,image_fireleft,image_fireEffect,image_fireEffectleft,
                image_swordmonster,image_sword,image_swordleft,image_SwordEffect,image_SwordEffectleft};
void loadFiles(SDL_Surface* images[],TTF_Font *fonts[],Mix_Music **music,Mix_Chunk *effects[]);
void freeAll(SDL_Surface* images[],TTF_Font *fonts[],Mix_Music *music,Mix_Chunk *effects[]);
#endif // LOAD&FRE
