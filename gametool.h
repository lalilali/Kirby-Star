#include <string>
#include <stdlib.h>
#include <time.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"

SDL_Surface* init();
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip );
SDL_Surface *load_image( char* filename ,int R ,int G,int B);
void textShow(int x, int y,SDL_Surface *screen,SDL_Color textColor,TTF_Font *font,std::string text);







