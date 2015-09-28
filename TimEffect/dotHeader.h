#ifndef DOTHEADER
#define DOTHEADER

class Tile;
class mTile;
class turret;
//class timer;

class Dot : base
{
    private:
    //The velocity of the dot
    int xVel, yVel;
    
    //determines if the player is jumping
    bool jump;
    
    //tells you if the player is on the ground
    bool onGround;
    
    //if the player dies, this is where they will respawn
    int respawnX, respawnY;

    public:
    //Initializes the variables
    Dot();
        SDL_Rect box;

    //Takes key presses and adjusts the dot's velocity
    void handle_input();

    //Moves the dot
    void move( Tile *tiles[], mTile *mtiles[], turret *turrets[] );

    //Shows the dot on the screen
    void show();
    
    //makes the player jump
    void makeJump();
    
    //checks if the player has collidided with walls, mtiles or turrets
    bool touches_wall( SDL_Rect box, Tile *tiles[], mTile *mtiles[], turret *turrets[]);
    
    //checks if the player is touching the ground
    bool touches_ground(SDL_Rect box, Tile *tiles[], mTile *mtiles[], turret *turrets[]);
    
    //check if the player is touching a roof
    bool touches_roof(SDL_Rect box, Tile *tiles[], mTile *mtiles[]);
    
    //checks if a player is touching a tile that kills you
    bool touches_death( SDL_Rect box, Tile *tiles[] );
    
    //checks if you are touching the end of level tile
    bool touches_win(Tile *tiles[] );
    
    //determines if a player has beaten a level
    bool wins( Tile *tiles[] );
    
    //determines if a player has died
    bool dies( Tile *tiles[] );
    
    //checks if the player has aquired the time travel device
    bool getTime(SDL_Rect box, Tile *tiles[], bool timeGadget);

    //Sets the camera over the dot
    void set_camera();
    
    //sets the resapwn for the character based on the level
    void set_respawn();
    
    //stops the player when pausing
    void togglePause();
    
    void set_clips();
};

#endif 
