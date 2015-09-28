#include "SDL.h"
#include "SDL_image.h"
#ifndef BASEHEADER
#define BASEHEADER

//a simple point struct
struct point{
  int x;
  int y;   
};


class base
{
            public:
            
            //used for applying surfaces on top of each other
            void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL );
            
            //checks if two sdl_rects collide withe ach other
            bool check_collision( SDL_Rect A, SDL_Rect B );
            
            //a second collision detection method which has a larger collsion box, used in correlation with ground collision
            bool check_collision2( SDL_Rect A, SDL_Rect B );                    //rename
            
            //has a larder collision box and is used for pulling mtiles
            bool check_collision3( SDL_Rect A, SDL_Rect B );                    //rename
            
            //checks if the bottom of one rect is touching the top of another
            bool ground_collision( SDL_Rect A, SDL_Rect B );
            
            //checks if the top of one rect is touching the bottom of another
            bool roof_collision( SDL_Rect A, SDL_Rect B );
            
            //checks if the right of one rect is touching the left of another 
            bool left_collision( SDL_Rect A, SDL_Rect B );
            
             //checks if the right of one rect is touching the left of another, used for pulling mtiles
            bool left_collision2( SDL_Rect A, SDL_Rect B );
            
             //checks if the left of one rect is touching the right of another
            bool right_collision( SDL_Rect A, SDL_Rect B );
            
             //checks if the left of one rect is touching the bottom of another, used for pulling mtiles
            bool right_collision2( SDL_Rect A, SDL_Rect B );
            
                                                                            //no idea
            bool turret_collision( SDL_Rect A, SDL_Rect B );
            
            //used to check if a point collides with a sdl_rect
            bool point_collision( point test, SDL_Rect B );

};

#endif
