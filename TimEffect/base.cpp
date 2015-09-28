#include "SDL.h"
using namespace std;
#include "SDL_image.h"
#include "baseHeader.h"


void base :: apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip)
{
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit
    SDL_BlitSurface( source, clip, destination, &offset );
}



bool base :: check_collision( SDL_Rect A, SDL_Rect B )
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = A.x;
    rightA = A.x + A.w;
    topA = A.y;
    bottomA = A.y + A.h;

    //Calculate the sides of rect B
    leftB = B.x;
    rightB = B.x + B.w;
    topB = B.y;
    bottomB = B.y + B.h;

    //check if the bottom of the first rect is less than the top of the second, if it is then there is no collision
    if( bottomA <= topB )
    {
        return false;
    }
    
    //check if the top of the first rect is more than the bottom of the second, if it is then there is no collision
    if( topA >= bottomB )
    {
        return false;
    }

    //check if the right of the first rect is less than the left of the second, if it is then there is no collision
    if( rightA <= leftB )
    {
        return false;
    }
    //check if the left of the first rect is more than the right of the second, if it is then there is no collision
    if( leftA >= rightB )
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}


bool base :: check_collision2( SDL_Rect A, SDL_Rect B )
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = A.x;
    rightA = A.x + A.w;
    topA = A.y;
    bottomA = A.y + A.h;

    //Calculate the sides of rect B
    leftB = B.x;
    rightB = B.x + B.w;
    topB = B.y;
    bottomB = B.y + B.h;

    //similar to the original collision detction method but has a larger collision box.
    if( bottomA + 10 <= topB )
    {
        return false;
    }

    if( topA - 10 >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}





//checks if the bottom of the first rect is touching the top of the scond
bool base:: ground_collision( SDL_Rect A, SDL_Rect B )
{
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = A.x;
    rightA = A.x + A.w;
    topA = A.y;
    bottomA = A.y + A.h;

    //Calculate the sides of rect B
    leftB = B.x;
    rightB = B.x + B.w;
    topB = B.y;
    bottomB = B.y + B.h;
     
     //if there hasnt been any collsion then there cant be ground collision
    if( !check_collision2(A,B) )
    {
        return false;
    }
     //then rules out each of the alternative possible collsion
    if( check_collision2(A,B) && rightA <= leftB )
    {
        return false;
    }
    
    if( check_collision2(A,B) && leftA >= rightB )
    {
        return false;
    }
    
    if( check_collision2(A,B) && topA >= topB )
    {
        return false;
    }
    
    //what is left is ground collision
    return true;
}





//similar to ground collision but check if the top of the first rect touches the bottom of the second rect
bool base:: roof_collision( SDL_Rect A, SDL_Rect B )
{
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = A.x;
    rightA = A.x + A.w;
    topA = A.y;
    bottomA = A.y + A.h;

    //Calculate the sides of rect B
    leftB = B.x;
    rightB = B.x + B.w;
    topB = B.y;
    bottomB = B.y + B.h;
     
     //if there hasnt been any collsion then there cant be ground collision
    if( !check_collision2(A,B) )
    {
        return false;
    }
     //rules out the alternative types of collsion
    if( check_collision2(A,B) && rightA <= leftB )
    {
        return false;
    }
    
    if( check_collision2(A,B) && leftA >= rightB )
    {
        return false; 
    }
    
    if( check_collision2(A,B) && bottomA <= bottomB )
    {
        return false;
    }
    //what is left is roof collision
    return true;
}


//similar to ground collision but check if the right of the first rect touches the left of the second rect
bool base:: left_collision( SDL_Rect A, SDL_Rect B )
{

    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;
    
    leftA = A.x;
    rightA = A.x + A.w;
    topA = A.y;
    bottomA = A.y + A.h;
    
    leftB = B.x;
    rightB = B.x + B.w;
    topB = B.y;
    bottomB = B.y + B.h;
     
    if( !check_collision(A,B) )
    {
        return false;
    }
     
     
    if( check_collision(A,B) && bottomA <= topB )
    {
        return false;
    }
    
    if( check_collision(A,B) && topA >= bottomB )
    {
        return false;
    }
    
    if( check_collision(A,B) && leftA >= leftB )
    {
        return false;
    }
    return true;
}
//similar to ground collision but check if the left of the first rect touches the right of the second rect
bool base:: right_collision( SDL_Rect A, SDL_Rect B )
{

    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;
    
    leftA = A.x;
    rightA = A.x + A.w;
    topA = A.y;
    bottomA = A.y + A.h;
    
    leftB = B.x;
    rightB = B.x + B.w;
    topB = B.y;
    bottomB = B.y + B.h;
     
    if( !check_collision(A,B) )
    {
        return false;
    }
     
     
    if( check_collision(A,B) && bottomA <= topB )
    {
        return false;
    }
    
    if( check_collision(A,B) && topA >= bottomB )
    {
        return false;
    }
    
    if( check_collision(A,B) && rightA <= rightB )
    {
        return false;
    }
    return true;
}

//same as the left collsion but has a bigger collision box
bool base:: left_collision2( SDL_Rect A, SDL_Rect B )
{

    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;
    
    leftA = A.x + 20;
    rightA = A.x + A.w;
    topA = A.y;
    bottomA = A.y + A.h;
    
    leftB = B.x - 10;
    rightB = B.x + B.w - 10;
    topB = B.y;
    bottomB = B.y + B.h;
     
    if( !check_collision3(A,B) )
    {
        return false;
    }
     
     
    if(  bottomA <= topB )
    {
        return false;
    }
    
    if( topA >= bottomB )
    {
        return false;
    }
    
    if(  leftA >= rightB )
    {
        return false;
    }
    return true;
}

//same as the right collsion but has a bigger collision box
bool base:: right_collision2( SDL_Rect A, SDL_Rect B )
{

    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;
    
    leftA = A.x;
    rightA = A.x + A.w;
    topA = A.y;
    bottomA = A.y + A.h;
    
    leftB = B.x;
    rightB = B.x + B.w + 10;
    topB = B.y;
    bottomB = B.y + B.h;
     
    if( !check_collision3(A,B) )
    {
        return false;
    }
     
     
    if( bottomA <= topB )
    {
        return false;
    }
    
    if( topA >= bottomB )
    {
        return false;
    }
    
    if( rightA <= leftB )
    {
        return false;
    }
    return true;
}


bool base :: turret_collision( SDL_Rect A, SDL_Rect B )
{

    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = A.x + 100;
    rightA = A.x + A.w + 50;
    topA = A.y;
    bottomA = A.y + A.h;

    //Calculate the sides of rect B
    leftB = B.x;
    rightB = B.x + B.w + 25;
    topB = B.y;
    bottomB = B.y + B.h;

    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}

//same as other collision detection methods with a bigger collision box
bool base :: check_collision3( SDL_Rect A, SDL_Rect B )
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = A.x ;
    rightA = A.x + A.w;
    topA = A.y;
    bottomA = A.y + A.h;

    //Calculate the sides of rect B
    leftB = B.x  - 20;
    rightB = B.x + B.w + 20;
    topB = B.y;
    bottomB = B.y + B.h;

    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}

//checks if a poit collides with a rect
bool base :: point_collision( point p, SDL_Rect A )
{
    //The sides of the rectangles
    int leftA;
    int rightA;
    int topA;
    int bottomA;

    //Calculate the sides of rect A
    leftA = A.x ;
    rightA = A.x + A.w;
    topA = A.y;
    bottomA = A.y + A.h;


    //checks if the co ordinate of the point is inside the rectangle
    if( bottomA < p.y)
    {
        return false;
    }

    if( topA > p.y)
    {
        return false;
    }

    if( rightA < p.x )
    {
        return false;
    }

    if( leftA > p.x )
    {
        return false;
    }

    //if so then return true
    return true;
}
