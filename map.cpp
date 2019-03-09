#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include "gametool.h"
#include "load&free.h"
#include "map.h"
int Createmap(Map *m)
{
    m->floor=0;
    m->num_rols=6;
    m->num_cols=12;
    m->floor = (Floor**)malloc(sizeof(Floor*)*m->num_rols);
    if(m->floor==0)
    {
        return 0;
    }
    for(int i=0 ; i<m->num_rols ; i++)
    {
        m->floor[i] = (Floor*)malloc(sizeof(Floor)*m->num_cols);
        if(m->floor[i]==0)
        {
            for(int j=0; j<i ; j++)
            {
                free(m->floor[j]);
            }
            free(m->floor);
            m->floor=0;
            return 0;
        }
    }
    return 1;
}
int LoadMap(FILE *fp,Map *m)
{
    if(fp==0)
    {
        return 0;
    }
    for(int i=0; i<m->num_rols; i++)
    {
        for(int j=0; j<m->num_cols; j++)
        {
            fscanf(fp,"%d",&m->floor[i][j].type);
        }
    }
    fclose(fp);
    return 1;
}
void Printmap(SDL_Surface *screen,SDL_Surface* images[],Map *m)
{
    for(int i=0; i<m->num_rols; i++)
    {
        for(int j=0; j<m->num_cols; j++)
        {
            switch(m->floor[i][j].type)
            {
            case 0:
                apply_surface(j*80,i*80,images[image_sky],screen,NULL);
                break;
            case 1:
                apply_surface(j*80,i*80,images[image_floor],screen,NULL);
                break;
            case 2:
                apply_surface(j*80,i*80,images[image_sharp],screen,NULL);
                break;
            case 3:
                apply_surface(j*80,i*80,images[image_air],screen,NULL);
                break;
            case 4:
                apply_surface(j*80,i*80,images[image_door],screen,NULL);
                break;
            }
        }
    }
}
void freemap(Map *m)
{
    for(int i=0 ; i<m->num_rols ; i++)
    {
        for(int j=0; j<m->num_cols ; j++)
        {
            free(m->floor);
        }
    }
}
bool Gravity_pulls_you_down(Kirby *k,SDL_Surface *screen,SDL_Surface *images[],Map map)
{
    for(int i=0; i<map.num_rols; i++)
    {
        for(int j=0; j<map.num_cols; j++)
        {
            if(k->x >= j*80 && k->x < j*80+40 && k->y >= i*80 && k->y < i*80+60)
            {

                switch(map.floor[i][j].type)
                {
                case 0:
                    k->gravity=false;
                    k->isGround=false;
                    break;
                case 1:
                    k->isGround=true;
                    k->gravity=false;
                    break;
                case 2:

                    break;
                case 3:
                    k->gravity=true;
                    k->isGround=false;
                    k->y+=1;
                    apply_surface(k->x,k->y,images[image_fly],screen,NULL);
                    SDL_Flip(screen);
                    break;
                case 4:
                    k->isGround=true;
                    k->gravity=false;
                    break;
                }
                return true;
            }
        }
    }
    return false;
}
void do_you_want_to_save(FILE *fp,Kirby k,int stage,SDL_Surface *screen,SDL_Surface *images[])
{
    SDL_Event event;
    int yes=1;
    bool save=false;
    bool quit = false;
    apply_surface(0,0,images[image_save_yes],screen,NULL);
    SDL_Flip(screen);
    while(save==false && quit==false)
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
                    apply_surface(0,0,images[image_save_yes],screen,NULL);
                    SDL_Flip(screen);
                    yes=1;
                    break;
                case SDLK_DOWN:
                    apply_surface(0,0,images[image_save_no],screen,NULL);
                    SDL_Flip(screen);
                    yes=0;
                    break;
                case SDLK_SPACE:
                    if(yes==1)
                    {
                        fp=fopen("load.txt","w");
                        if(fp==0)
                        {
                            break;
                        }
                        fprintf(fp,"%d %c %d",stage,k.hp[0],k.state);
                        fclose(fp);
                        save=true;
                    }
                    else if(yes==0)
                    {
                        save=true;
                    }
                    break;
                default:
                    break;
                }
            }
        }
    }
}
