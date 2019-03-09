#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<windows.h>
#include "map.h"
#include "kirby.h"
#include "gametool.h"
#include "load&free.h"


int main(int argc, char* args[])
{
    //initialize
    SDL_Surface *screen = init();
    Kirby k;
    Monster fire_m;
    Monster fire_m2;

    fire_m.state=fire;
    fire_m2.state=fire;

    Monster sword_m;
    Monster sword_m2;

    sword_m.state=sword;
    sword_m2.state=sword;


    //Load image & font & music
    TTF_Font *fonts[4];
    SDL_Surface* images[50];
    Mix_Music* music[10];
    Mix_Chunk* effects[4];
    loadFiles(images,fonts,music,effects);

    //Load map
    Map map;
    Createmap(&map);




    SDL_Event event;
    bool quit = false;
    bool next = false;
    int stage = 0;
    bool load_game = false;
    bool go_new_game = false;
    bool go_load_game = false;
    int count=0;
    float monster_distance[4]= {30,30,30,30};
    //play music
    Mix_PlayMusic(music[0], -1) ;
    //進版畫面
    while(quit == false && next == false)
    {
        if(SDL_PollEvent(&event))
        {
            apply_surface(0,0,images[image_start],screen,NULL);
            SDL_Flip(screen);

            if(event.type == SDL_QUIT)
            {
                quit = true;
            }
            else if( event.type == SDL_KEYDOWN )
            {
                switch(event.key.keysym.sym)
                {
                case SDLK_SPACE:
                    next=true;
                    break;
                default:
                    break;
                }
            }
        }
    }
    next=false;
    while(quit == false && next == false)
    {
        if(SDL_PollEvent(&event))
        {
            apply_surface(0,0,images[image_rules],screen,NULL);
            SDL_Flip(screen);

            if(event.type == SDL_QUIT)
            {
                quit = true;
            }
            else if( event.type == SDL_KEYDOWN )
            {
                switch(event.key.keysym.sym)
                {
                case SDLK_SPACE:
                    next=true;
                    break;
                default:
                    break;
                }
            }
        }
    }
    if(next==true)
    {
        apply_surface(0,0,images[image_newgame],screen,NULL);
        SDL_Flip(screen);
        while(quit == false && go_new_game == false && go_load_game == false)
        {
            if(SDL_PollEvent(&event))
            {

                if(event.type == SDL_QUIT)
                {
                    quit = true;
                }
                else if( event.type == SDL_KEYDOWN )
                {
                    switch(event.key.keysym.sym)
                    {
                    case SDLK_UP:
                        apply_surface(0,0,images[image_newgame],screen,NULL);
                        SDL_Flip(screen);
                        load_game = false;
                        break;
                    case SDLK_DOWN:
                        apply_surface(0,0,images[image_loadgame],screen,NULL);
                        SDL_Flip(screen);
                        load_game = true;
                        break;
                    case SDLK_SPACE:
                        if(load_game == true)
                        {
                            go_load_game=true;
                        }
                        else
                        {
                            go_new_game=true;
                        }
                        break;
                    default:
                        break;
                    }
                }
            }
        }
    }

    FILE *monster_fp;
    FILE *fp;
    FILE *save_fp;
    if(go_load_game)
    {
        fp=fopen("load.txt","r");
        if(fp==0)
        {
            apply_surface(0,0,images[image_no_savings],screen,NULL);
            SDL_Flip(screen);
            SDL_Delay(3000);
            quit=true;
        }
        else
        {
        fscanf(fp,"%d %c %d",&stage,&k.hp[0],&k.state);
        fclose(fp);
        }
    }
    Mix_PlayMusic(music[1], -1) ;
    //第1關
    if(go_new_game)
    {
        fp = fopen("stage1.txt","r");
        LoadMap(fp,&map);
        //第1關
        stage=1;
        apply_surface(0,0,images[image_stage1],screen,NULL);
        SDL_Flip(screen);
        SDL_Delay(2000);
        //寫入怪物資訊
        monster_in_stage(monster_fp,&fire_m,&fire_m2,&sword_m,&sword_m2,stage);
        while(quit == false && stage == 1 )
        {
            //卡比死亡
            if(k.y>=480 || k.hp[0]=='0')
            {
                break;
            }
            //印地圖
            Printmap(screen,images,&map);
            textShow(0,320,screen, {255,165,0},fonts[0],"------------------------------------------------------------------------------------------------");
            textShow(50,400,screen, {255,165,0},fonts[1],"Stage :");
            textShow(150,400,screen, {255,0,0},fonts[1],"1");
            textShow(250,400,screen, {255,165,0},fonts[1],"Hp :");
            textShow(320,400,screen, {255,0,0},fonts[1],k.hp);
            textShow(450,400,screen, {255,165,0},fonts[1],"Kirby State :");
            switch(k.state)
            {
            case origin:
                textShow(620,400,screen, {255,0,0},fonts[1],"origin");
                break;
            case fire:
                textShow(620,400,screen, {255,0,0},fonts[1],"fire");
                break;
            case sword:
                textShow(620,400,screen, {255,0,0},fonts[1],"sword");
                break;
            }
            //印怪物
            if(fire_m.hp>0)
            {
                apply_surface(fire_m.x,fire_m.y,images[image_firemonster],screen,NULL);
            }
            else
            {
                fire_m.x=0;
                fire_m.y=0;
            }
            if(fire_m2.hp>0)
            {
                apply_surface(fire_m2.x,fire_m2.y,images[image_firemonster],screen,NULL);
            }
            else
            {
                fire_m2.x=0;
                fire_m2.y=0;
            }
            if(sword_m.hp>0)
            {
                apply_surface(sword_m.x,sword_m.y,images[image_swordmonster],screen,NULL);
            }
            else
            {
                sword_m.x=0;
                sword_m.y=0;
            }
            if(sword_m2.hp>0)
            {
                apply_surface(sword_m2.x,sword_m2.y,images[image_swordmonster],screen,NULL);
            }
            else
            {
                sword_m2.x=0;
                sword_m2.y=0;
            }
            //怪物自己移動
            monster_moves_by_itself(&fire_m,&monster_distance[0]);
            monster_moves_by_itself(&fire_m2,&monster_distance[1]);
            monster_moves_by_itself(&sword_m,&monster_distance[2]);
            monster_moves_by_itself(&sword_m2,&monster_distance[3]);
            //遊戲事件
            if(SDL_PollEvent(&event))
            {
                if(event.type == SDL_QUIT)
                {
                    quit = true;
                }
                else if( event.type == SDL_KEYDOWN )
                {
                    switch(event.key.keysym.sym)
                    {
                    case SDLK_RIGHT:
                        if(k.isAttacking)
                        {
                            break;
                        }
                        k.isWalkingRight=true;
                        k.isRight=true;

                        break;
                    case SDLK_LEFT:
                        if(k.isAttacking)
                        {
                            break;
                        }
                        k.isWalkingLeft=true;
                        k.isRight=false;
                        break;
                    case SDLK_LALT:
                        if(k.isJumpingUp  ||  k.isJumpingDown || k.gravity)
                        {
                            break;
                        }
                        k.isJumpingUp=true;
                        break;
                    case SDLK_LCTRL:
                        if(k.isAttacking)
                        {
                            break;
                        }
                        k.isAttacking=true;
                        break;
                    case SDLK_UP:
                        if(k.x>=880 && k.x<=920  &&  k.y>=240 && k.y<=300)
                        {
                            stage=2;
                            //是否存檔
                            do_you_want_to_save(save_fp,k,stage,screen,images);
                        }
                        break;
                    case SDLK_LSHIFT:
                        k.state=origin;
                        break;
                    default:
                        break;
                    }
                }
                else if( event.type == SDL_KEYUP )
                {
                    switch(event.key.keysym.sym)
                    {
                    case SDLK_RIGHT:

                        k.isWalkingRight=false;
                        break;
                    case SDLK_LEFT:
                        k.isWalkingLeft=false;
                        break;
                    case SDLK_LCTRL:
                        k.isAttacking=false;
                        break;
                    default:
                        break;
                    }

                }

            }

            //判定卡比動作
            if(k.isJumpingUp)
            {
                JumpUp(&k);
                k.jumpheight-=1;
                if(k.jumpheight<=0)
                {
                    k.isJumpingUp = false;
                    k.jumpheight=100;
                    k.isJumpingDown = true;
                }
            }
            if(k.isJumpingDown)
            {
                if(JumpDown(&k))
                {
                    k.jumpheight-=1;
                }
                else if(k.jumpheight<=0)
                {
                    k.jumpheight=100;
                    k.isJumpingDown = false;
                }
                else
                {
                    k.isJumpingDown = false;
                    k.jumpheight=100;
                }

            }
            if(k.isWalkingRight)
            {
                Walk(&k,1);
                if(!k.isGround && !k.isJumpingUp && !k.isJumpingDown && !k.gravity)
                {
                    k.godown=true;
                }
                //撞到怪物
                kirby_hurt(&k,&fire_m,&count);
                kirby_hurt(&k,&fire_m2,&count);
                kirby_hurt(&k,&sword_m,&count);
                kirby_hurt(&k,&sword_m2,&count);
            }
            if(k.isWalkingLeft)
            {
                Walk(&k,-1);
                if(!k.isGround && !k.isJumpingUp && !k.isJumpingDown && !k.gravity)
                {
                    k.godown=true;
                }
                //撞到怪物
                kirby_hurt(&k,&fire_m,&count);
                kirby_hurt(&k,&fire_m2,&count);
                kirby_hurt(&k,&sword_m,&count);
                kirby_hurt(&k,&sword_m2,&count);
            }
            if(k.isAttacking)
            {
                switch(k.state)
                {
                case origin:
                    if(k.isRight==false)
                    {
                        apply_surface(k.x,k.y,images[image_eatleft],screen,NULL);
                    }
                    else
                    {
                        apply_surface(k.x,k.y,images[image_eat],screen,NULL);
                    }
                    SDL_Flip(screen);

                    if(Attack(&k,&fire_m,screen,images) || Attack(&k,&fire_m2,screen,images))
                    {
                        k.state=fire;
                        SDL_Delay(500);
                    }
                    else if(Attack(&k,&sword_m,screen,images) || Attack(&k,&sword_m2,screen,images))
                    {
                        k.state=sword;
                        SDL_Delay(500);
                    }

                    break;
                case fire:
                    if(k.isRight==false)
                    {
                        apply_surface(k.x-60,k.y,images[image_fireEffectleft],screen,NULL);
                    }
                    else
                    {
                        apply_surface(k.x+60,k.y,images[image_fireEffect],screen,NULL);
                    }
                    monster_hurt(&k,&fire_m);
                    monster_hurt(&k,&fire_m2);
                    monster_hurt(&k,&sword_m);
                    monster_hurt(&k,&sword_m2);
                    SDL_Flip(screen);

                    break;
                case sword:
                    if(k.isRight==false)
                    {
                        apply_surface(k.x-60,k.y,images[image_SwordEffectleft],screen,NULL);
                    }
                    else
                    {
                        apply_surface(k.x+60,k.y,images[image_SwordEffect],screen,NULL);
                    }
                    monster_hurt(&k,&fire_m);
                    monster_hurt(&k,&fire_m2);
                    monster_hurt(&k,&sword_m);
                    monster_hurt(&k,&sword_m2);
                    SDL_Flip(screen);

                    break;
                }
            }
            //判定左右邊
            if(k.isRight==false)
            {
                switch(k.state)
                {
                case origin:
                    if(k.isAttacking)
                    {
                        break;
                    }
                    apply_surface(k.x,k.y,images[image_flyleft],screen,NULL);
                    break;
                case fire:
                    apply_surface(k.x,k.y,images[image_fireleft],screen,NULL);
                    break;
                case sword:
                    apply_surface(k.x,k.y,images[image_swordleft],screen,NULL);
                    break;
                }
            }

            else
            {
                switch(k.state)
                {
                case origin:
                    if(k.isAttacking)
                    {
                        break;
                    }
                    apply_surface(k.x,k.y,images[image_fly],screen,NULL);
                    break;
                case fire:
                    apply_surface(k.x,k.y,images[image_fire],screen,NULL);
                    break;
                case sword:
                    apply_surface(k.x,k.y,images[image_sword],screen,NULL);
                    break;
                }
            }
            //判定地板
            if(Gravity_pulls_you_down(&k,screen,images,map))
            {
                if(k.isGround)
                {
                    k.gravity=false;
                    k.godown=false;
                }
            }

            if(k.godown || k.gravity)
            {
                if(!k.isGround)
                {
                    k.y+=1;
                }
            }

            //翻面
            SDL_Flip(screen);
        }
    }
    //第2關
    if(stage==2)
    {
        //寫入地圖
        fp = fopen("stage2.txt","r");
        LoadMap(fp,&map);
        apply_surface(0,0,images[image_stage2],screen,NULL);
        SDL_Flip(screen);
        SDL_Delay(2000);
        //寫入怪物資訊
        monster_in_stage(monster_fp,&fire_m,&fire_m2,&sword_m,&sword_m2,stage);
        //卡比重新回到左邊
        k.x=0;
        k.y=240;
        while(quit == false && stage == 2 )
        {
            //卡比死亡
            if(k.y>=480 || k.hp[0]=='0')
            {
                break;
            }
            //印地圖
            Printmap(screen,images,&map);
            textShow(0,320,screen, {255,165,0},fonts[0],"------------------------------------------------------------------------------------------------");
            textShow(50,400,screen, {255,165,0},fonts[1],"Stage :");
            textShow(150,400,screen, {255,0,0},fonts[1],"2");
            textShow(250,400,screen, {255,165,0},fonts[1],"Hp :");
            textShow(320,400,screen, {255,0,0},fonts[1],k.hp);
            textShow(450,400,screen, {255,165,0},fonts[1],"Kirby State :");
            switch(k.state)
            {
            case origin:
                textShow(620,400,screen, {255,0,0},fonts[1],"origin");
                break;
            case fire:
                textShow(620,400,screen, {255,0,0},fonts[1],"fire");
                break;
            case sword:
                textShow(620,400,screen, {255,0,0},fonts[1],"sword");
                break;
            }
            //印怪物
            if(fire_m.hp>0)
            {
                apply_surface(fire_m.x,fire_m.y,images[image_firemonster],screen,NULL);
            }
            else
            {
                fire_m.x=0;
                fire_m.y=0;
            }
            if(fire_m2.hp>0)
            {
                apply_surface(fire_m2.x,fire_m2.y,images[image_firemonster],screen,NULL);
            }
            else
            {
                fire_m2.x=0;
                fire_m2.y=0;
            }
            if(sword_m.hp>0)
            {
                apply_surface(sword_m.x,sword_m.y,images[image_swordmonster],screen,NULL);
            }
            else
            {
                sword_m.x=0;
                sword_m.y=0;
            }
            if(sword_m2.hp>0)
            {
                apply_surface(sword_m2.x,sword_m2.y,images[image_swordmonster],screen,NULL);
            }
            else
            {
                sword_m2.x=0;
                sword_m2.y=0;
            }
            //怪物自己移動
            monster_moves_by_itself(&fire_m,&monster_distance[0]);
            monster_moves_by_itself(&fire_m2,&monster_distance[1]);
            monster_moves_by_itself(&sword_m,&monster_distance[2]);
            monster_moves_by_itself(&sword_m2,&monster_distance[3]);
            //遊戲事件
            if(SDL_PollEvent(&event))
            {
                if(event.type == SDL_QUIT)
                {
                    quit = true;
                }
                else if( event.type == SDL_KEYDOWN )
                {
                    switch(event.key.keysym.sym)
                    {
                    case SDLK_RIGHT:
                        if(k.isAttacking)
                        {
                            break;
                        }
                        k.isWalkingRight=true;
                        k.isRight=true;

                        break;
                    case SDLK_LEFT:
                        if(k.isAttacking)
                        {
                            break;
                        }
                        k.isWalkingLeft=true;
                        k.isRight=false;
                        break;
                    case SDLK_LALT:
                        if(k.isJumpingUp  ||  k.isJumpingDown || k.gravity)
                        {
                            break;
                        }
                        k.isJumpingUp=true;
                        break;
                    case SDLK_LCTRL:
                        if(k.isAttacking)
                        {
                            break;
                        }
                        k.isAttacking=true;
                        break;
                    case SDLK_UP:
                        if(k.x>=880 && k.x<=920  &&  k.y>=240 && k.y<=300)
                        {
                            stage=3;
                            //是否存檔
                            do_you_want_to_save(save_fp,k,stage,screen,images);
                        }
                        break;
                    case SDLK_LSHIFT:
                        k.state=origin;
                        break;
                    default:
                        break;
                    }
                }
                else if( event.type == SDL_KEYUP )
                {
                    switch(event.key.keysym.sym)
                    {
                    case SDLK_RIGHT:

                        k.isWalkingRight=false;
                        break;
                    case SDLK_LEFT:
                        k.isWalkingLeft=false;
                        break;
                    case SDLK_LCTRL:
                        k.isAttacking=false;
                        break;
                    default:
                        break;
                    }

                }

            }

            //判定卡比動作
            if(k.isJumpingUp)
            {
                JumpUp(&k);
                k.jumpheight-=1;
                if(k.jumpheight<=0)
                {
                    k.isJumpingUp = false;
                    k.jumpheight=100;
                    k.isJumpingDown = true;
                }
            }
            if(k.isJumpingDown)
            {
                if(JumpDown(&k))
                {
                    k.jumpheight-=1;
                }
                else if(k.jumpheight<=0)
                {
                    k.jumpheight=100;
                    k.isJumpingDown = false;
                }
                else
                {
                    k.isJumpingDown = false;
                    k.jumpheight=100;
                }

            }
            if(k.isWalkingRight)
            {
                Walk(&k,1);
                if(!k.isGround && !k.isJumpingUp && !k.isJumpingDown && !k.gravity)
                {
                    k.godown=true;
                }
                //撞到怪物
                kirby_hurt(&k,&fire_m,&count);
                kirby_hurt(&k,&fire_m2,&count);
                kirby_hurt(&k,&sword_m,&count);
                kirby_hurt(&k,&sword_m2,&count);
            }
            if(k.isWalkingLeft)
            {
                Walk(&k,-1);
                if(!k.isGround && !k.isJumpingUp && !k.isJumpingDown && !k.gravity)
                {
                    k.godown=true;
                }
                //撞到怪物
                kirby_hurt(&k,&fire_m,&count);
                kirby_hurt(&k,&fire_m2,&count);
                kirby_hurt(&k,&sword_m,&count);
                kirby_hurt(&k,&sword_m2,&count);
            }
            if(k.isAttacking)
            {
                switch(k.state)
                {
                case origin:
                    if(k.isRight==false)
                    {
                        apply_surface(k.x,k.y,images[image_eatleft],screen,NULL);
                    }
                    else
                    {
                        apply_surface(k.x,k.y,images[image_eat],screen,NULL);
                    }
                    SDL_Flip(screen);

                    if(Attack(&k,&fire_m,screen,images) || Attack(&k,&fire_m2,screen,images))
                    {
                        k.state=fire;
                        SDL_Delay(500);
                    }
                    else if(Attack(&k,&sword_m,screen,images) || Attack(&k,&sword_m2,screen,images))
                    {
                        k.state=sword;
                        SDL_Delay(500);
                    }


                    break;
                case fire:
                    if(k.isRight==false)
                    {
                        apply_surface(k.x-60,k.y,images[image_fireEffectleft],screen,NULL);
                    }
                    else
                    {
                        apply_surface(k.x+60,k.y,images[image_fireEffect],screen,NULL);
                    }
                    monster_hurt(&k,&fire_m);
                    monster_hurt(&k,&fire_m2);
                    monster_hurt(&k,&sword_m);
                    monster_hurt(&k,&sword_m2);
                    SDL_Flip(screen);

                    break;
                case sword:
                    if(k.isRight==false)
                    {
                        apply_surface(k.x-60,k.y,images[image_SwordEffectleft],screen,NULL);
                    }
                    else
                    {
                        apply_surface(k.x+60,k.y,images[image_SwordEffect],screen,NULL);
                    }
                    monster_hurt(&k,&fire_m);
                    monster_hurt(&k,&fire_m2);
                    monster_hurt(&k,&sword_m);
                    monster_hurt(&k,&sword_m2);
                    SDL_Flip(screen);

                    break;
                }
            }
            //判定左右邊
            if(k.isRight==false)
            {
                switch(k.state)
                {
                case origin:
                    if(k.isAttacking)
                    {
                        break;
                    }
                    apply_surface(k.x,k.y,images[image_flyleft],screen,NULL);
                    break;
                case fire:
                    apply_surface(k.x,k.y,images[image_fireleft],screen,NULL);
                    break;
                case sword:
                    apply_surface(k.x,k.y,images[image_swordleft],screen,NULL);
                    break;
                }
            }

            else
            {
                switch(k.state)
                {
                case origin:
                    if(k.isAttacking)
                    {
                        break;
                    }
                    apply_surface(k.x,k.y,images[image_fly],screen,NULL);
                    break;
                case fire:
                    apply_surface(k.x,k.y,images[image_fire],screen,NULL);
                    break;
                case sword:
                    apply_surface(k.x,k.y,images[image_sword],screen,NULL);
                    break;
                }
            }
            //判定地板
            if(Gravity_pulls_you_down(&k,screen,images,map))
            {
                if(k.isGround)
                {
                    k.gravity=false;
                    k.godown=false;
                }
            }

            if(k.godown || k.gravity)
            {
                if(!k.isGround)
                {
                    k.y+=1;
                }
            }

            //翻面
            SDL_Flip(screen);
        }
    }
    //第3關
    if(stage==3)
    {
        //載入地圖
        fp = fopen("stage3.txt","r");
        LoadMap(fp,&map);
        apply_surface(0,0,images[image_stage3],screen,NULL);
        SDL_Flip(screen);
        SDL_Delay(2000);
        //寫入怪物資訊
        monster_in_stage(monster_fp,&fire_m,&fire_m2,&sword_m,&sword_m2,stage);
        //卡比重新回到左邊
        k.x=0;
        k.y=240;
        while(quit == false && stage == 3 )
        {
            //卡比死亡
            if(k.y>=480 || k.hp[0]=='0')
            {
                break;
            }
            //印地圖
            Printmap(screen,images,&map);
            textShow(0,320,screen, {255,165,0},fonts[0],"------------------------------------------------------------------------------------------------");
            textShow(50,400,screen, {255,165,0},fonts[1],"Stage :");
            textShow(150,400,screen, {255,0,0},fonts[1],"3");
            textShow(250,400,screen, {255,165,0},fonts[1],"Hp :");
            textShow(320,400,screen, {255,0,0},fonts[1],k.hp);
            textShow(450,400,screen, {255,165,0},fonts[1],"Kirby State :");
            switch(k.state)
            {
            case origin:
                textShow(620,400,screen, {255,0,0},fonts[1],"origin");
                break;
            case fire:
                textShow(620,400,screen, {255,0,0},fonts[1],"fire");
                break;
            case sword:
                textShow(620,400,screen, {255,0,0},fonts[1],"sword");
                break;
            }
            //印怪物
            if(fire_m.hp>0)
            {
                apply_surface(fire_m.x,fire_m.y,images[image_firemonster],screen,NULL);
            }
            else
            {
                fire_m.x=0;
                fire_m.y=0;
            }
            if(fire_m2.hp>0)
            {
                apply_surface(fire_m2.x,fire_m2.y,images[image_firemonster],screen,NULL);
            }
            else
            {
                fire_m2.x=0;
                fire_m2.y=0;
            }
            if(sword_m.hp>0)
            {
                apply_surface(sword_m.x,sword_m.y,images[image_swordmonster],screen,NULL);
            }
            else
            {
                sword_m.x=0;
                sword_m.y=0;
            }
            if(sword_m2.hp>0)
            {
                apply_surface(sword_m2.x,sword_m2.y,images[image_swordmonster],screen,NULL);
            }
            else
            {
                sword_m2.x=0;
                sword_m2.y=0;
            }
            //怪物自己移動
            monster_moves_by_itself(&fire_m,&monster_distance[0]);
            monster_moves_by_itself(&fire_m2,&monster_distance[1]);
            monster_moves_by_itself(&sword_m,&monster_distance[2]);
            monster_moves_by_itself(&sword_m2,&monster_distance[3]);
            //遊戲事件
            if(SDL_PollEvent(&event))
            {
                if(event.type == SDL_QUIT)
                {
                    quit = true;
                }
                else if( event.type == SDL_KEYDOWN )
                {
                    switch(event.key.keysym.sym)
                    {
                    case SDLK_RIGHT:
                        if(k.isAttacking)
                        {
                            break;
                        }
                        k.isWalkingRight=true;
                        k.isRight=true;

                        break;
                    case SDLK_LEFT:
                        if(k.isAttacking)
                        {
                            break;
                        }
                        k.isWalkingLeft=true;
                        k.isRight=false;
                        break;
                    case SDLK_LALT:
                        if(k.isJumpingUp  ||  k.isJumpingDown || k.gravity)
                        {
                            break;
                        }
                        k.isJumpingUp=true;
                        break;
                    case SDLK_LCTRL:
                        if(k.isAttacking)
                        {
                            break;
                        }
                        k.isAttacking=true;
                        break;
                    case SDLK_UP:
                        if(k.x>=880 && k.x<=920  &&  k.y>=240 && k.y<=300)
                        {
                            stage=4;
                        }
                        break;
                    case SDLK_LSHIFT:
                        k.state=origin;
                        break;
                    default:
                        break;
                    }
                }
                else if( event.type == SDL_KEYUP )
                {
                    switch(event.key.keysym.sym)
                    {
                    case SDLK_RIGHT:

                        k.isWalkingRight=false;
                        break;
                    case SDLK_LEFT:
                        k.isWalkingLeft=false;
                        break;
                    case SDLK_LCTRL:
                        k.isAttacking=false;
                        break;
                    default:
                        break;
                    }

                }

            }

            //判定卡比動作
            if(k.isJumpingUp)
            {
                JumpUp(&k);
                k.jumpheight-=1;
                if(k.jumpheight<=0)
                {
                    k.isJumpingUp = false;
                    k.jumpheight=100;
                    k.isJumpingDown = true;
                }
            }
            if(k.isJumpingDown)
            {
                if(JumpDown(&k))
                {
                    k.jumpheight-=1;
                }
                else if(k.jumpheight<=0)
                {
                    k.jumpheight=100;
                    k.isJumpingDown = false;
                }
                else
                {
                    k.isJumpingDown = false;
                    k.jumpheight=100;
                }

            }
            if(k.isWalkingRight)
            {
                Walk(&k,1);
                if(!k.isGround && !k.isJumpingUp && !k.isJumpingDown && !k.gravity)
                {
                    k.godown=true;
                }
                //撞到怪物
                kirby_hurt(&k,&fire_m,&count);
                kirby_hurt(&k,&fire_m2,&count);
                kirby_hurt(&k,&sword_m,&count);
                kirby_hurt(&k,&sword_m2,&count);
            }
            if(k.isWalkingLeft)
            {
                Walk(&k,-1);
                if(!k.isGround && !k.isJumpingUp && !k.isJumpingDown && !k.gravity)
                {
                    k.godown=true;
                }
                //撞到怪物
                kirby_hurt(&k,&fire_m,&count);
                kirby_hurt(&k,&fire_m2,&count);
                kirby_hurt(&k,&sword_m,&count);
                kirby_hurt(&k,&sword_m2,&count);
            }
            if(k.isAttacking)
            {
                switch(k.state)
                {
                case origin:
                    if(k.isRight==false)
                    {
                        apply_surface(k.x,k.y,images[image_eatleft],screen,NULL);
                    }
                    else
                    {
                        apply_surface(k.x,k.y,images[image_eat],screen,NULL);
                    }
                    SDL_Flip(screen);

                    if(Attack(&k,&fire_m,screen,images) || Attack(&k,&fire_m2,screen,images))
                    {
                        k.state=fire;
                        SDL_Delay(500);
                    }
                    else if(Attack(&k,&sword_m,screen,images) || Attack(&k,&sword_m2,screen,images))
                    {
                        k.state=sword;
                        SDL_Delay(500);
                    }


                    break;
                case fire:
                    if(k.isRight==false)
                    {
                        apply_surface(k.x-60,k.y,images[image_fireEffectleft],screen,NULL);
                    }
                    else
                    {
                        apply_surface(k.x+60,k.y,images[image_fireEffect],screen,NULL);
                    }
                    monster_hurt(&k,&fire_m);
                    monster_hurt(&k,&fire_m2);
                    monster_hurt(&k,&sword_m);
                    monster_hurt(&k,&sword_m2);
                    SDL_Flip(screen);

                    break;
                case sword:
                    if(k.isRight==false)
                    {
                        apply_surface(k.x-60,k.y,images[image_SwordEffectleft],screen,NULL);
                    }
                    else
                    {
                        apply_surface(k.x+60,k.y,images[image_SwordEffect],screen,NULL);
                    }
                    monster_hurt(&k,&fire_m);
                    monster_hurt(&k,&fire_m2);
                    monster_hurt(&k,&sword_m);
                    monster_hurt(&k,&sword_m2);
                    SDL_Flip(screen);

                    break;
                }
            }
            //判定左右邊
            if(k.isRight==false)
            {
                switch(k.state)
                {
                case origin:
                    if(k.isAttacking)
                    {
                        break;
                    }
                    apply_surface(k.x,k.y,images[image_flyleft],screen,NULL);
                    break;
                case fire:
                    apply_surface(k.x,k.y,images[image_fireleft],screen,NULL);
                    break;
                case sword:
                    apply_surface(k.x,k.y,images[image_swordleft],screen,NULL);
                    break;
                }
            }

            else
            {
                switch(k.state)
                {
                case origin:
                    if(k.isAttacking)
                    {
                        break;
                    }
                    apply_surface(k.x,k.y,images[image_fly],screen,NULL);
                    break;
                case fire:
                    apply_surface(k.x,k.y,images[image_fire],screen,NULL);
                    break;
                case sword:
                    apply_surface(k.x,k.y,images[image_sword],screen,NULL);
                    break;
                }
            }
            //判定地板
            if(Gravity_pulls_you_down(&k,screen,images,map))
            {
                if(k.isGround)
                {
                    k.gravity=false;
                    k.godown=false;
                }
            }

            if(k.godown || k.gravity)
            {
                if(!k.isGround)
                {
                    k.y+=1;
                }
            }

            //翻面
            SDL_Flip(screen);
        }
    }
    //結束畫面
    if(quit==true)
    {

    }
    else if(stage==4)
    {
        apply_surface(0,0,images[image_win],screen,NULL);
        SDL_Flip(screen);
        SDL_Delay(3000);

    }
    else
    {
        apply_surface(0,0,images[image_gameover],screen,NULL);
        textShow(300,200,screen, {255,0,0},fonts[2],"Game over!");
        SDL_Flip(screen);
        SDL_Delay(1000);
    }





    //Free the loaded image and quit sdl
    freeAll(images,fonts,music[10],effects);
    freemap(&map);

    return 0;
}
