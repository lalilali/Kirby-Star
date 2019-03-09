#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<windows.h>
#include "kirby.h"
void Walk(Kirby *k , float x)
{
    k->x+=x;
}
void JumpUp(Kirby *k )
{
    k->y-=1;
}
bool JumpDown(Kirby *k )
{
    if(k->gravity || k->isGround)
    {
        return false;
    }
    k->y+=1;
    return true;
}
bool Attack(Kirby *k,Monster *m,SDL_Surface *screen,SDL_Surface *images[])
{
    int yes;
    float distance;
    if(k->x > m->x)
    {
        yes=1;
        distance = k->x - m->x;
    }
    else
    {
        distance = m->x - k->x;
        yes=0;
    }
    if( distance<=100 && k->y >= m->y-50 && k->y <= m->y+50)
    {
        while(distance>0)
        {
            if(yes==1)
            {
                m->x += 1;
            }
            else
            {
                m->x -= 1;
            }
            distance -= 1;
            if(m->state==fire)
            {
                apply_surface(m->x,m->y,images[image_firemonster],screen,NULL);
                SDL_Flip(screen);
            }
            else if(m->state==sword)
            {
                apply_surface(m->x,m->y,images[image_swordmonster],screen,NULL);
                SDL_Flip(screen);
            }
            m->hp = 0;
        }
        return true;
    }
    return false;
}
void kirby_hurt(Kirby *k,Monster *m,int *count)
{
    float distance;
    if(k->x > m->x)
    {
        distance = k->x - m->x;
    }
    else
    {
        distance = m->x - k->x;
    }
    if(*count<=1000)
    {
        *count+=1;
    }
    else
    {
        if( distance<=50 && k->y >= m->y-10 && k->y <= m->y+10)
        {
            if(m->hp>0)
            {
                k->hp[0]-=1;
                *count=0;
            }
        }
    }
}
void monster_in_stage(FILE *fp,Monster *fire_m,Monster *fire_m2,Monster *sword_m,Monster *sword_m2,int stage)
{
    switch(stage)
    {
    case 1:
        fp=fopen("stage1_monster.txt","r");

        fscanf(fp,"%f %f",&fire_m->x,&fire_m->y);
        fire_m->hp=2;
        fscanf(fp,"%f %f",&sword_m->x,&sword_m->y);
        sword_m->hp=2;

        fclose(fp);
        break;
    case 2:
        fp=fopen("stage2_monster.txt","r");

        fscanf(fp,"%f %f",&fire_m->x,&fire_m->y);
        fire_m->hp=2;
        fscanf(fp,"%f %f",&sword_m->x,&sword_m->y);
        sword_m->hp=2;
        fscanf(fp,"%f %f",&fire_m2->x,&fire_m2->y);
        fire_m2->hp=2;

        fclose(fp);
        break;
    case 3:
        fp=fopen("stage3_monster.txt","r");

        fscanf(fp,"%f %f",&fire_m->x,&fire_m->y);
        fire_m->hp=2;
        fscanf(fp,"%f %f",&sword_m->x,&sword_m->y);
        sword_m->hp=2;
        fscanf(fp,"%f %f",&fire_m2->x,&fire_m2->y);
        fire_m2->hp=2;
        fscanf(fp,"%f %f",&sword_m2->x,&sword_m2->y);
        sword_m2->hp=2;

        fclose(fp);
        break;
    }
}
void monster_hurt(Kirby *k,Monster *m)
{
    float distance;
    if(k->x > m->x)
    {
        distance = k->x - m->x;
    }
    else
    {
        distance = m->x - k->x;
    }
    if( distance<=120 && k->y >= m->y-50 && k->y <= m->y+50)
    {
        m->hp-=1;
    }
}
void monster_moves_by_itself(Monster *m,float *monster_distance)
{
    if(*monster_distance>0)
    {
        m->x+=0.3;
        *monster_distance-=0.3;
    }
    else
    {
        m->x-=0.3;
        *monster_distance-=0.3;
        if(*monster_distance<-30)
        {
            *monster_distance=30;
        }

    }
}
