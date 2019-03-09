#include "kirby.h"
#include "gametool.h"
#include "load&free.h"
#ifndef Map_
#define Map_
enum Floortype{Sky=0,Stair=1,Sharp=2,Air=3,Door=4};
struct Floor
{
    Floortype type;
};
struct Map
{
    Floor **floor=0;
    int num_rols=0;
    int num_cols=0;

};
int Createmap(Map *m);
int LoadMap(FILE *fp,Map *m);
void Printmap(SDL_Surface *screen,SDL_Surface* images[],Map *m);
void freemap(Map *m);
bool Gravity_pulls_you_down(Kirby *k,SDL_Surface *screen,SDL_Surface *images[],Map m);
void do_you_want_to_save(FILE *fp,Kirby k,int stage,SDL_Surface *screen,SDL_Surface *images[]);
#endif // Map_
