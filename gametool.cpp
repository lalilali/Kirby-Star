#include "gametool.h"

SDL_Surface* init()
{
    SDL_Surface* screen;

    //Initialize all SDL subsystems
    SDL_Init( SDL_INIT_EVERYTHING );

    //Set up the screen
    screen = SDL_SetVideoMode( 960, 480, 32, SDL_SWSURFACE );

    //Set the window caption
    SDL_WM_SetCaption( "Kirby Star", NULL );

    //TTF lib init
    TTF_Init();

    //Initialize SDL_mixer
    Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 );

    //random
    srand(time(NULL));

    //If everything initialized fine
    return screen;
}
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit
    SDL_BlitSurface( source, clip, destination, &offset );
}

SDL_Surface *load_image( char* filename ,int R = -1,int G = -1,int B = -1)
{
    //The image that's loaded
    SDL_Surface* loadedImage = NULL;

    //The optimized image that will be used
    SDL_Surface* optimizedImage = NULL;

    //Load the image
    loadedImage = IMG_Load( filename );

    //If the image loaded
    if( loadedImage != NULL )
    {
        //Create an optimized image
        optimizedImage = SDL_DisplayFormat( loadedImage );

        //Free the old image
        SDL_FreeSurface( loadedImage );

        //If the image was optimized just fine
        if( optimizedImage != NULL && R!=-1 && G!=-1 && B!=-1)
        {
            //Map the color key
            Uint32 colorkey = SDL_MapRGB( optimizedImage->format, R,G,B );

            //Set all pixels of color R 0, G 0xFF, B 0xFF to be transparent
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, colorkey );
        }
    }

    //Return the optimized image
    return optimizedImage;
}
void textShow(int x, int y,SDL_Surface *screen,SDL_Color textColor,TTF_Font *font,std::string text)
{
    SDL_Surface *show = TTF_RenderText_Solid( font, text.c_str(), textColor );
    apply_surface( x, y, show, screen );
    SDL_FreeSurface(show);
}

//debug tool
