#include "SDL.h"
#ifndef SETUPHEADER
#define SETUPHEADER


class Setup
{
     public: 
        //initialises the game
     bool init();
        //loads an image
     SDL_Surface *load_image( std::string filename );
        //loads all the needed files for the game
     bool load_files();
};

#endif
