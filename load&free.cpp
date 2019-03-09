#include <string>
#include <stdlib.h>
#include <time.h>
#include "gametool.h"
#include "load&free.h"
void setTitle(float t)
{
    char a[100] ;
    snprintf(a,sizeof(a),"%f",t);
    SDL_WM_SetCaption( a, NULL );
}
void loadFiles(SDL_Surface* images[],TTF_Font *fonts[],Mix_Music **music,Mix_Chunk *effects[])
{
    images[image_sky]=load_image("images/sky.png",255,255,255);
    images[image_floor]=load_image("images/floor.png",255,255,255);
    images[image_sharp]=load_image("images/sharp.png",255,255,255);
    images[image_air]=load_image("images/air.png",255,255,255);
    images[image_door]=load_image("images/door.png",255,255,255);

    images[image_fly]=load_image("images/fly.png",255,255,255);
    images[image_flyleft]=load_image("images/flyleft.png",255,255,255);

    images[image_eat]=load_image("images/eat.png",255,255,255);
    images[image_eatleft]=load_image("images/eatleft.png",255,255,255);
    //start
    images[image_start]=load_image("images/start.jpg",0,0,0);
    images[image_gameover]=load_image("images/gameover.png",255,255,255);
    images[image_newgame]=load_image("images/newgame.jpg",0,0,0);
    images[image_loadgame]=load_image("images/loadgame.jpg",0,0,0);
    images[image_win]=load_image("images/win.jpg",255,255,255);
    images[image_save_yes]=load_image("images/save_yes.png",255,255,255);
    images[image_save_no]=load_image("images/save_no.png",255,255,255);
    images[image_no_savings]=load_image("images/no_savings.jpg",0,0,0);
    images[image_rules]=load_image("images/rules.png",0,0,0);
    //fire
    images[image_firemonster]=load_image("images/firemonster.png",255,255,255);
    images[image_fire]=load_image("images/fire.png",255,255,255);
    images[image_fireleft]=load_image("images/fireleft.png",255,255,255);
    images[image_fireEffect]=load_image("images/fireEffect.bmp",255,255,255);
    images[image_fireEffectleft]=load_image("images/fireEffectleft.bmp",255,255,255);
    //sword
    images[image_swordmonster]=load_image("images/swordmonster.png",255,255,255);
    images[image_sword]=load_image("images/sword.png",255,255,255);
    images[image_swordleft]=load_image("images/swordleft.png",255,255,255);
    images[image_SwordEffect]=load_image("images/SwordEffect.png",255,255,255);
    images[image_SwordEffectleft]=load_image("images/SwordEffectleft.png",255,255,255);
    //stage
    images[image_stage1]=load_image("images/stage1.png",255,255,255);
    images[image_stage2]=load_image("images/stage2.png",255,255,255);
    images[image_stage3]=load_image("images/stage3.png",255,255,255);









    fonts[0] = TTF_OpenFont("font/wt064.ttf",36);
    fonts[1] = TTF_OpenFont("font/wt064.ttf",24);
    fonts[2] = TTF_OpenFont("font/wt064.ttf",72);



    music[0] = Mix_LoadMUS( "music/start.mp3" );
    music[1] = Mix_LoadMUS( "music/stage.mp3" );

}
void freeAll(SDL_Surface* images[],TTF_Font *fonts[],Mix_Music *music,Mix_Chunk *effects[])
{
    for(int i= 0;i<sizeof(images)/sizeof(images[0]);i++){
        SDL_FreeSurface(images[i]);
    }

    for(int i= 0;i<sizeof(fonts)/sizeof(fonts[0]);i++){
        TTF_CloseFont(fonts[i]);
    }

    Mix_FreeMusic( music );
    for(int i= 0;i<sizeof(effects)/sizeof(effects[0]);i++){
        Mix_FreeChunk(effects[i]);
    }

    //Quit SDL_mixer
    Mix_CloseAudio();

    //Quit SDL_ttf
    TTF_Quit();

    //Quit SDL
    SDL_Quit();
}
